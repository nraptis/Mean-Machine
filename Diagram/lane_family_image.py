from __future__ import annotations

from dataclasses import dataclass
from typing import Sequence

from PIL import Image, ImageDraw, ImageFont

from lane_image import make_lane_image


BACKGROUND_GRAY = (150, 150, 150)
DARK_GRAY = (48, 48, 48)
PANEL_GRAY = (166, 166, 166)
LANE_LABEL_WIDTH = 170
PADDING = 14
TITLE_HEIGHT = 30
ROW_GAP = 8
IMAGE_GAP = 12


@dataclass(frozen=True)
class NamedLane:
    name: str
    data: bytes | bytearray | Sequence[int]
    changed: bool = False


def _font(size: int) -> ImageFont.ImageFont:
    try:
        return ImageFont.truetype("Arial.ttf", size=size)
    except OSError:
        return ImageFont.load_default()


def _title_case_lane_name(name: str) -> str:
    return "_".join(part.capitalize() for part in name.split("_"))


def make_lane_family_image(family_name: str, lanes: Sequence[NamedLane]) -> Image.Image:
    lane_images = [make_lane_image(lane.data, changed=lane.changed) for lane in lanes]
    lane_width = max((image.width for image in lane_images), default=0)
    lane_height = max((image.height for image in lane_images), default=20)
    row_height = lane_height
    width = PADDING * 2 + LANE_LABEL_WIDTH + IMAGE_GAP + lane_width
    height = PADDING * 2 + TITLE_HEIGHT
    if lanes:
        height += len(lanes) * row_height + (len(lanes) - 1) * ROW_GAP

    image = Image.new("RGB", (width, height), PANEL_GRAY)
    draw = ImageDraw.Draw(image)
    title_font = _font(18)
    label_font = _font(12)

    draw.text((PADDING, PADDING), family_name, fill=DARK_GRAY, font=title_font)
    y = PADDING + TITLE_HEIGHT
    for lane, lane_image in zip(lanes, lane_images):
        label = _title_case_lane_name(lane.name)
        draw.text((PADDING, y + 3), label, fill=DARK_GRAY, font=label_font)
        image.paste(lane_image, (PADDING + LANE_LABEL_WIDTH + IMAGE_GAP, y))
        y += row_height + ROW_GAP

    return image
