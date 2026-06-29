from __future__ import annotations

import struct
from dataclasses import dataclass
from typing import Sequence

from PIL import Image, ImageDraw, ImageFont

from lane_family_image import DARK_GRAY, PANEL_GRAY
from lane_image import BLACK, BORDER_SIZE, LIGHT_GRAY, SQUARE_SIZE


S_SALT = 32
SAMPLE_COUNT = 24
UINT64_SIZE = 8
SALT_ARRAY_COUNT = 6
MATERIAL_COUNT = 3
MATERIAL_WORD_COUNT = SALT_ARRAY_COUNT * S_SALT
PHASE_A_SALT_WORD_COUNT = MATERIAL_COUNT * MATERIAL_WORD_COUNT
PHASE_A_SALT_SIZE = PHASE_A_SALT_WORD_COUNT * UINT64_SIZE
LABEL_WIDTH = 170
PADDING = 14
TITLE_HEIGHT = 30
IMAGE_GAP = 12


@dataclass(frozen=True)
class NamedDomainBundle:
    name: str
    data: bytes | bytearray | Sequence[int]


def _font(size: int) -> ImageFont.ImageFont:
    try:
        return ImageFont.truetype("Arial.ttf", size=size)
    except OSError:
        return ImageFont.load_default()


def _title_case_name(name: str) -> str:
    return "_".join(part.capitalize() for part in name.split("_"))


def _channel_from_word(word: int) -> int:
    return word & 0xFF


def _sample_index(index: int) -> int:
    return index * S_SALT // SAMPLE_COUNT


def _salt_word(words: Sequence[int], material_index: int, salt_index: int, word_index: int) -> int:
    offset = material_index * MATERIAL_WORD_COUNT
    offset += salt_index * S_SALT
    offset += word_index
    return words[offset]


def phase_a_bundle_colors(bundle: bytes | bytearray | Sequence[int]) -> list[tuple[int, int, int]]:
    bundle_bytes = bytes(bundle)
    if len(bundle_bytes) < PHASE_A_SALT_SIZE:
        raise ValueError(
            f"domain bundle expected at least {PHASE_A_SALT_SIZE} bytes, got {len(bundle_bytes)}"
        )
    phase_a = bundle_bytes[:PHASE_A_SALT_SIZE]
    if all(byte == 0 for byte in phase_a):
        return [BLACK] * SAMPLE_COUNT

    words = struct.unpack(f"<{PHASE_A_SALT_WORD_COUNT}Q", phase_a)
    colors: list[tuple[int, int, int]] = []
    for sample in range(SAMPLE_COUNT):
        word_index = _sample_index(sample)
        red_word = sum(_salt_word(words, material, 0, word_index) for material in range(3))
        green_word = sum(_salt_word(words, material, 1, word_index) for material in range(3))
        blue_word = sum(_salt_word(words, material, 2, word_index) for material in range(3))
        colors.append((
            _channel_from_word(red_word),
            _channel_from_word(green_word),
            _channel_from_word(blue_word),
        ))

    return colors


def make_domain_bundle_image(
    bundle: bytes | bytearray | Sequence[int],
    padding_blocks: int = 0,
) -> Image.Image:
    colors = phase_a_bundle_colors(bundle)
    width = BORDER_SIZE * 2 + (SAMPLE_COUNT + padding_blocks) * SQUARE_SIZE
    height = BORDER_SIZE * 2 + SQUARE_SIZE
    image = Image.new("RGB", (width, height), LIGHT_GRAY)
    draw = ImageDraw.Draw(image)
    left_padding_blocks = padding_blocks // 2
    for index, color in enumerate(colors):
        left = BORDER_SIZE + (left_padding_blocks + index) * SQUARE_SIZE
        top = BORDER_SIZE
        draw.rectangle(
            (left, top, left + SQUARE_SIZE - 1, top + SQUARE_SIZE - 1),
            fill=color,
        )
    return image


def make_domain_bundle_family_image(
    bundles: Sequence[NamedDomainBundle],
    padding_blocks: int = 8,
) -> Image.Image:
    bundle_images = [
        make_domain_bundle_image(bundle.data, padding_blocks=padding_blocks)
        for bundle in bundles
    ]
    bundle_width = max((image.width for image in bundle_images), default=0)
    bundle_height = max((image.height for image in bundle_images), default=20)
    row_gap = 8
    width = PADDING * 2 + LABEL_WIDTH + IMAGE_GAP + bundle_width
    height = PADDING * 2 + TITLE_HEIGHT
    if bundles:
        height += len(bundles) * bundle_height + (len(bundles) - 1) * row_gap

    image = Image.new("RGB", (width, height), PANEL_GRAY)
    draw = ImageDraw.Draw(image)
    draw.text((PADDING, PADDING), "domain bundles", fill=DARK_GRAY, font=_font(18))

    y = PADDING + TITLE_HEIGHT
    for bundle, bundle_image in zip(bundles, bundle_images):
        draw.text((PADDING, y + 3), _title_case_name(bundle.name), fill=DARK_GRAY, font=_font(12))
        image.paste(bundle_image, (PADDING + LABEL_WIDTH + IMAGE_GAP, y))
        y += bundle_height + row_gap

    return image
