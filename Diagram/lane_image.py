from __future__ import annotations

import hashlib
from typing import Sequence

from PIL import Image, ImageDraw


PIECE_COUNT = 32
SQUARE_SIZE = 12
BORDER_SIZE = 4
BLOOD_RED = (136, 8, 8)
LIGHT_GRAY = (211, 211, 211)
BLACK = (0, 0, 0)


def _even_slice(data: bytes, index: int, count: int) -> bytes:
    start = len(data) * index // count
    end = len(data) * (index + 1) // count
    return data[start:end]


def _hash64(data: bytes, domain: bytes) -> int:
    digest = hashlib.blake2b(data, digest_size=8, person=domain).digest()
    return int.from_bytes(digest, "big")


def _channel_from_word(word: int) -> int:
    return word & 0xFF


def _piece_color(piece: bytes) -> tuple[int, int, int]:
    red_data = _even_slice(piece, 0, 3)
    green_data = _even_slice(piece, 1, 3)
    blue_data = _even_slice(piece, 2, 3)

    red = _channel_from_word(_hash64(red_data, b"lane-red"))
    green = _channel_from_word(_hash64(green_data, b"lane-green"))
    blue = _channel_from_word(_hash64(blue_data, b"lane-blue"))
    return red, green, blue


def data_colors(
    data: bytes | bytearray | Sequence[int],
    piece_count: int,
) -> list[tuple[int, int, int]]:
    data_bytes = bytes(data)
    if not data_bytes or all(byte == 0 for byte in data_bytes):
        return [BLACK] * piece_count

    return [
        _piece_color(_even_slice(data_bytes, index, piece_count))
        for index in range(piece_count)
    ]


def lane_colors(lane: bytes | bytearray | Sequence[int]) -> list[tuple[int, int, int]]:
    return data_colors(lane, PIECE_COUNT)


def make_lane_image(lane: bytes | bytearray | Sequence[int], changed: bool) -> Image.Image:
    colors = lane_colors(lane)
    border_color = BLOOD_RED if changed else LIGHT_GRAY
    width = BORDER_SIZE * 2 + PIECE_COUNT * SQUARE_SIZE
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
