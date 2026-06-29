from __future__ import annotations

import ast
import json
import struct
from dataclasses import dataclass
from pathlib import Path
from typing import Dict, Iterator, List, Optional, Tuple

try:
    import numpy as np
except ImportError:  # Keep this usable from Apple's plain system Python.
    np = None


DEFAULT_EXPORT_ROOT = Path(__file__).resolve().parent / "EXPORTS"


@dataclass(frozen=True)
class NpyArray:
    path: Path
    shape: Tuple[int, ...]
    data: bytes

    def first_bytes(self, count: int = 32) -> bytes:
        return self.data[:count]


@dataclass
class SnapshotArray:
    timeline_name: str
    slice_index: int
    slice_name: str
    array_name: str
    path: Path
    shape: Tuple[int, ...]
    dtype: str
    data: object

    @property
    def full_name(self) -> str:
        return f"{self.timeline_name}/{self.slice_index:03d}_{self.slice_name}/{self.array_name}"


@dataclass
class SnapshotSlice:
    timeline_name: str
    index: int
    name: str
    folder: str
    arrays: Dict[str, SnapshotArray]

    def iter_arrays(self) -> Iterator[SnapshotArray]:
        yield from self.arrays.values()


@dataclass
class SnapshotTimeline:
    name: str
    slices: List[SnapshotSlice]

    def iter_arrays(self) -> Iterator[SnapshotArray]:
        for snapshot_slice in self.slices:
            yield from snapshot_slice.iter_arrays()


@dataclass
class SnapshotExport:
    root: Path
    manifest: dict
    timelines: Dict[str, SnapshotTimeline]

    def iter_arrays(self) -> Iterator[SnapshotArray]:
        for timeline in self.timelines.values():
            yield from timeline.iter_arrays()


def _load_npy_uint8_without_numpy(path: Path) -> NpyArray:
    with path.open("rb") as file:
        magic = file.read(6)
        if magic != b"\x93NUMPY":
            raise ValueError(f"{path} is not a .npy file")

        major = file.read(1)[0]
        minor = file.read(1)[0]
        if (major, minor) == (1, 0):
            header_length = struct.unpack("<H", file.read(2))[0]
        elif (major, minor) in ((2, 0), (3, 0)):
            header_length = struct.unpack("<I", file.read(4))[0]
        else:
            raise ValueError(f"unsupported .npy version {(major, minor)} in {path}")

        header = ast.literal_eval(file.read(header_length).decode("latin1").strip())
        if header.get("descr") not in ("|u1", "uint8", "<u1"):
            raise ValueError(f"{path} is not uint8: {header.get('descr')}")
        if header.get("fortran_order"):
            raise ValueError(f"{path} uses fortran_order=True, unsupported here")

        shape = tuple(int(value) for value in header["shape"])
        data = file.read()

    expected = 1
    for dimension in shape:
        expected *= dimension
    if len(data) != expected:
        raise ValueError(f"{path} expected {expected} bytes, got {len(data)}")

    return NpyArray(path=path, shape=shape, data=data)


def load_array(path: Path, mmap_mode: Optional[str] = None) -> object:
    if np is not None:
        return np.load(path, mmap_mode=mmap_mode)
    return _load_npy_uint8_without_numpy(path)


def first_bytes(array: object, count: int = 32) -> bytes:
    if isinstance(array, NpyArray):
        return array.first_bytes(count)

    if np is not None:
        return np.asarray(array, dtype=np.uint8).reshape(-1)[:count].tobytes()

    raise TypeError(f"unsupported array object: {type(array)!r}")


def load_exports(root: Path | str = DEFAULT_EXPORT_ROOT,
                 mmap_mode: Optional[str] = None) -> SnapshotExport:
    export_root = Path(root).expanduser().resolve()
    manifest_path = export_root / "manifest.json"
    with manifest_path.open("r", encoding="utf-8") as file:
        manifest = json.load(file)

    timelines: Dict[str, SnapshotTimeline] = {}
    for timeline_info in manifest.get("timelines", []):
        timeline_name = timeline_info["name"]
        slices: List[SnapshotSlice] = []

        for slice_info in timeline_info.get("slices", []):
            slice_index = int(slice_info["index"])
            slice_name = slice_info["name"]
            arrays: Dict[str, SnapshotArray] = {}

            for array_name, array_info in slice_info.get("arrays", {}).items():
                array_path = export_root / array_info["path"]
                shape = tuple(int(value) for value in array_info.get("shape", ()))
                data = load_array(array_path, mmap_mode=mmap_mode)
                arrays[array_name] = SnapshotArray(
                    timeline_name=timeline_name,
                    slice_index=slice_index,
                    slice_name=slice_name,
                    array_name=array_name,
                    path=array_path,
                    shape=shape,
                    dtype=array_info.get("dtype", "uint8"),
                    data=data,
                )

            slices.append(SnapshotSlice(
                timeline_name=timeline_name,
                index=slice_index,
                name=slice_name,
                folder=slice_info.get("folder", ""),
                arrays=arrays,
            ))

        timelines[timeline_name] = SnapshotTimeline(name=timeline_name, slices=slices)

    return SnapshotExport(root=export_root, manifest=manifest, timelines=timelines)
