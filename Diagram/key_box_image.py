from __future__ import annotations

from dataclasses import dataclass
from typing import Sequence

from PIL import Image, ImageDraw, ImageFont

from lane_family_image import DARK_GRAY, PANEL_GRAY
from lane_image import (
    BLOOD_RED,
    BORDER_SIZE,
    LIGHT_GRAY,
    SQUARE_SIZE,
    data_colors,
)


KEY_BOX_ROWS = 8
KEY_BOX_BLOCKS = 20
LABEL_WIDTH = 26
PADDING = 14
TITLE_HEIGHT = 30
ROW_GAP = 8
PAIR_GAP = 20
IMAGE_GAP = 8


@dataclass(frozen=True)
class KeyBoxRows:
    name: str
    rows: list[bytes]
    changed_rows: list[bool]


def _font(size: int) -> ImageFont.ImageFont:
    try:
        return ImageFont.truetype("Arial.ttf", size=size)
    except OSError:
        return ImageFont.load_default()


def split_key_box_rows(data: bytes | bytearray | Sequence[int]) -> list[bytes]:
    key_bytes = bytes(data)
    return [
        key_bytes[len(key_bytes) * index // KEY_BOX_ROWS: len(key_bytes) * (index + 1) // KEY_BOX_ROWS]
        for index in range(KEY_BOX_ROWS)
    ]


def changed_key_box_rows(
    data: bytes | bytearray | Sequence[int],
    previous_data: bytes | bytearray | Sequence[int] | None,
) -> list[bool]:
    rows = split_key_box_rows(data)
    if previous_data is None:
        return [False] * len(rows)
    previous_rows = split_key_box_rows(previous_data)
    return [
        row != previous_rows[index] if index < len(previous_rows) else True
        for index, row in enumerate(rows)
    ]


def make_key_box_row_image(row: bytes | bytearray | Sequence[int], changed: bool) -> Image.Image:
    colors = data_colors(row, KEY_BOX_BLOCKS)
    border_color = BLOOD_RED if changed else LIGHT_GRAY
    width = BORDER_SIZE * 2 + KEY_BOX_BLOCKS * SQUARE_SIZE
    height = BORDER_SIZE * 2 + SQUARE_SIZE
    image = Image.new("RGB", (width, height), border_color)
    draw = ImageDraw.Draw(image)
    for index, color in enumerate(colors):
        left = BORDER_SIZE + index * SQUARE_SIZE
        top = BORDER_SIZE
        draw.rectangle(
            (left, top, left + SQUARE_SIZE - 1, top + SQUARE_SIZE - 1),
            fill=color,
        )
    return image


def make_key_box_family_image(key_box_a: KeyBoxRows, key_box_b: KeyBoxRows) -> Image.Image:
    rows_a = [
        make_key_box_row_image(row, changed)
        for row, changed in zip(key_box_a.rows, key_box_a.changed_rows)
    ]
    rows_b = [
        make_key_box_row_image(row, changed)
        for row, changed in zip(key_box_b.rows, key_box_b.changed_rows)
    ]
    row_width = max((image.width for image in rows_a + rows_b), default=0)
    row_height = max((image.height for image in rows_a + rows_b), default=20)
    width = PADDING * 2 + (LABEL_WIDTH + IMAGE_GAP + row_width) * 2 + PAIR_GAP
    height = PADDING * 2 + TITLE_HEIGHT
    height += KEY_BOX_ROWS * row_height + (KEY_BOX_ROWS - 1) * ROW_GAP

    image = Image.new("RGB", (width, height), PANEL_GRAY)
    draw = ImageDraw.Draw(image)
    title_font = _font(18)
    label_font = _font(12)
    draw.text((PADDING, PADDING), "key boxes", fill=DARK_GRAY, font=title_font)

    y = PADDING + TITLE_HEIGHT
    b_x = PADDING + LABEL_WIDTH + IMAGE_GAP + row_width + PAIR_GAP
    for index in range(KEY_BOX_ROWS):
        draw.text((PADDING, y + 3), f"A{index + 1}", fill=DARK_GRAY, font=label_font)
        image.paste(rows_a[index], (PADDING + LABEL_WIDTH + IMAGE_GAP, y))
        draw.text((b_x, y + 3), f"B{index + 1}", fill=DARK_GRAY, font=label_font)
        image.paste(rows_b[index], (b_x + LABEL_WIDTH + IMAGE_GAP, y))
        y += row_height + ROW_GAP

    return image
