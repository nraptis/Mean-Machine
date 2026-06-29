from __future__ import annotations

import argparse
import json
from dataclasses import dataclass
from pathlib import Path

from PIL import Image

from lane_family_image import BACKGROUND_GRAY
from slice_image import (
    DEFAULT_OUTPUT_ROOT as DEFAULT_SLICE_IMAGE_ROOT,
    make_slice_image,
    output_path_for_slice,
)


DEFAULT_EXPORT_ROOT = Path(__file__).resolve().parent / "EXPORTS"
DEFAULT_OUTPUT_ROOT = Path(__file__).resolve().parent / "BYTE_FLOW_IMAGES"
DEFAULT_TIMELINE = "KDFA"


@dataclass(frozen=True)
class TimelineSlice:
    index: int
    name: str
    folder: Path


def timeline_slices(
    export_root: Path | str = DEFAULT_EXPORT_ROOT,
    timeline_name: str = DEFAULT_TIMELINE,
) -> list[TimelineSlice]:
    root = Path(export_root).expanduser().resolve()
    manifest_path = root / "manifest.json"
    manifest = json.loads(manifest_path.read_text(encoding="utf-8"))

    for timeline in manifest.get("timelines", []):
        if timeline.get("name") != timeline_name:
            continue
        slices = [
            TimelineSlice(
                index=int(slice_info["index"]),
                name=slice_info["name"],
                folder=root / slice_info["folder"],
            )
            for slice_info in timeline.get("slices", [])
        ]
        return sorted(slices, key=lambda item: item.index)

    raise ValueError(f"timeline not found: {timeline_name}")


def make_byte_flow_image(
    slices: list[TimelineSlice],
    include_domain_bundle: bool = True,
    save_slice_images: bool = True,
    slice_output_root: Path | str = DEFAULT_SLICE_IMAGE_ROOT,
) -> Image.Image:
    slice_images: list[Image.Image] = []
    slice_root = Path(slice_output_root).expanduser().resolve()
    if save_slice_images:
        slice_root.mkdir(parents=True, exist_ok=True)

    previous_slice: TimelineSlice | None = None
    for timeline_slice in slices:
        previous_folder = previous_slice.folder if previous_slice is not None else None
        image = make_slice_image(
            timeline_slice.folder,
            previous_slice_folder=previous_folder,
            include_domain_bundle=include_domain_bundle,
        )
        if save_slice_images:
            image.save(output_path_for_slice(timeline_slice.folder, slice_root))
        slice_images.append(image)
        previous_slice = timeline_slice

    width = sum(image.width for image in slice_images)
    height = max((image.height for image in slice_images), default=0)
    flow_image = Image.new("RGB", (width, height), BACKGROUND_GRAY)

    x = 0
    for image in slice_images:
        flow_image.paste(image, (x, 0))
        x += image.width

    return flow_image


def output_path_for_timeline(timeline_name: str, output_root: Path | str) -> Path:
    root = Path(output_root).expanduser().resolve()
    return root / f"{timeline_name}.png"


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("--timeline", default=DEFAULT_TIMELINE)
    parser.add_argument(
        "--no-domain-bundle",
        action="store_true",
        help="omit PhaseA domain-bundle previews from each slice",
    )
    args = parser.parse_args()

    output_root = DEFAULT_OUTPUT_ROOT
    output_root.mkdir(parents=True, exist_ok=True)
    slices = timeline_slices(DEFAULT_EXPORT_ROOT, args.timeline)
    image = make_byte_flow_image(
        slices,
        include_domain_bundle=not args.no_domain_bundle,
        save_slice_images=True,
    )
    output_path = output_path_for_timeline(args.timeline, output_root)
    image.save(output_path)
    print(f"Saved: {output_path}")


if __name__ == "__main__":
    main()
