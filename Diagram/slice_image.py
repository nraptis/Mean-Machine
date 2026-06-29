from __future__ import annotations

import argparse
from collections import defaultdict
from pathlib import Path

from PIL import Image, ImageDraw, ImageFont

from domain_bundle_image import (
    NamedDomainBundle,
    make_domain_bundle_family_image,
)
from key_box_image import (
    KeyBoxRows,
    changed_key_box_rows,
    make_key_box_family_image,
    split_key_box_rows,
)
from lane_family_image import BACKGROUND_GRAY, DARK_GRAY, NamedLane, make_lane_family_image
from loader import load_array

try:
    import numpy as np
except ImportError:
    np = None


DEFAULT_SLICE_FOLDER = (
    Path(__file__).resolve().parent / "EXPORTS" / "KDFA" / "slice_2_KDF_A_B"
)
DEFAULT_OUTPUT_ROOT = Path(__file__).resolve().parent / "SLICE_IMAGES"
FAMILY_ORDER = ("operation", "expansion", "work", "snow", "fire", "invest")
DOMAIN_BUNDLE_ORDER = ("domain_bundle", "domain_bundle_inbuilt", "domain_bundle_ephemeral")
PADDING = 18
PANEL_GAP = 14
TITLE_HEIGHT = 34


def _font(size: int) -> ImageFont.ImageFont:
    try:
        return ImageFont.truetype("Arial.ttf", size=size)
    except OSError:
        return ImageFont.load_default()


def _array_bytes(array: object) -> bytes:
    data = getattr(array, "data", None)
    if isinstance(data, bytes):
        return data
    if np is not None:
        return np.asarray(array, dtype=np.uint8).reshape(-1).tobytes()
    raise TypeError(f"unsupported array object: {type(array)!r}")


def _lane_sort_key(path: Path) -> tuple[str, str]:
    stem = path.stem
    family, suffix = stem.split("_lane_", 1)
    return family, suffix


def _display_slice_name(slice_folder: Path) -> str:
    return slice_folder.parent.name + " / " + slice_folder.name


def _load_lane_families(
    slice_folder: Path,
    previous_slice_folder: Path | None = None,
) -> dict[str, list[NamedLane]]:
    families: dict[str, list[NamedLane]] = defaultdict(list)
    for path in sorted(slice_folder.glob("*_lane_*.npy"), key=_lane_sort_key):
        family, _suffix = path.stem.split("_lane_", 1)
        array = load_array(path, mmap_mode="r")
        data = _array_bytes(array)
        changed = False
        if previous_slice_folder is not None:
            previous_path = previous_slice_folder / path.name
            if previous_path.exists():
                previous_array = load_array(previous_path, mmap_mode="r")
                changed = data != _array_bytes(previous_array)
            else:
                changed = True
        families[family].append(NamedLane(name=path.stem, data=data, changed=changed))
    return families


def _load_domain_bundles(slice_folder: Path) -> list[NamedDomainBundle]:
    bundles: list[NamedDomainBundle] = []
    for name in DOMAIN_BUNDLE_ORDER:
        path = slice_folder / f"{name}.npy"
        if path.exists():
            array = load_array(path, mmap_mode="r")
            bundles.append(NamedDomainBundle(name=name, data=_array_bytes(array)))
    return bundles


def _load_key_box(
    slice_folder: Path,
    name: str,
    previous_slice_folder: Path | None,
) -> KeyBoxRows | None:
    path = slice_folder / f"{name}.npy"
    if not path.exists():
        return None

    array = load_array(path, mmap_mode="r")
    data = _array_bytes(array)
    previous_data = None
    if previous_slice_folder is not None:
        previous_path = previous_slice_folder / path.name
        if previous_path.exists():
            previous_array = load_array(previous_path, mmap_mode="r")
            previous_data = _array_bytes(previous_array)

    return KeyBoxRows(
        name=name,
        rows=split_key_box_rows(data),
        changed_rows=changed_key_box_rows(data, previous_data),
    )


def _load_key_box_image(
    slice_folder: Path,
    previous_slice_folder: Path | None,
) -> Image.Image | None:
    key_box_a = _load_key_box(slice_folder, "key_box_a", previous_slice_folder)
    key_box_b = _load_key_box(slice_folder, "key_box_b", previous_slice_folder)
    if key_box_a is None or key_box_b is None:
        return None
    return make_key_box_family_image(key_box_a, key_box_b)


def make_slice_image(
    slice_folder: Path | str = DEFAULT_SLICE_FOLDER,
    previous_slice_folder: Path | str | None = None,
    include_domain_bundle: bool = True,
) -> Image.Image:
    folder = Path(slice_folder).expanduser().resolve()
    previous_folder = None
    if previous_slice_folder is not None:
        previous_folder = Path(previous_slice_folder).expanduser().resolve()
    families = _load_lane_families(folder, previous_folder)
    ordered_names = [name for name in FAMILY_ORDER if name in families]
    ordered_names.extend(name for name in sorted(families) if name not in FAMILY_ORDER)

    panel_images = [
        make_lane_family_image(name, families[name])
        for name in ordered_names
    ]

    key_box_image = _load_key_box_image(folder, previous_folder)
    if key_box_image is not None:
        panel_images.append(key_box_image)

    if include_domain_bundle:
        domain_bundles = _load_domain_bundles(folder)
        if domain_bundles:
            panel_images.append(make_domain_bundle_family_image(domain_bundles))

    width = PADDING * 2 + max((image.width for image in panel_images), default=0)
    height = PADDING * 2 + TITLE_HEIGHT
    if panel_images:
        height += sum(image.height for image in panel_images)
        height += PANEL_GAP * (len(panel_images) - 1)

    image = Image.new("RGB", (width, height), BACKGROUND_GRAY)
    draw = ImageDraw.Draw(image)
    draw.text(
        (PADDING, PADDING),
        _display_slice_name(folder),
        fill=DARK_GRAY,
        font=_font(20),
    )

    y = PADDING + TITLE_HEIGHT
    for panel_image in panel_images:
        image.paste(panel_image, (PADDING, y))
        y += panel_image.height + PANEL_GAP

    return image


def output_path_for_slice(slice_folder: Path | str, output_root: Path | str) -> Path:
    folder = Path(slice_folder).expanduser().resolve()
    root = Path(output_root).expanduser().resolve()
    return root / f"{folder.parent.name}__{folder.name}.png"


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "--no-domain-bundle",
        action="store_true",
        help="omit the PhaseA domain-bundle preview panel",
    )
    args = parser.parse_args()

    output_root = DEFAULT_OUTPUT_ROOT
    output_root.mkdir(parents=True, exist_ok=True)
    output_path = output_path_for_slice(DEFAULT_SLICE_FOLDER, output_root)
    make_slice_image(
        DEFAULT_SLICE_FOLDER,
        include_domain_bundle=not args.no_domain_bundle,
    ).save(output_path)
    print(f"Saved: {output_path}")


if __name__ == "__main__":
    main()
