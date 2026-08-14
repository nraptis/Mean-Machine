#!/opt/anaconda3/bin/python3

"""Build the six-heart core asset and copy its matching gold records."""

from pathlib import Path
import csv
import shutil
import struct


PROJECT_ROOT = Path(__file__).resolve().parent
ASSETS = PROJECT_ROOT / "Assets"
SOURCE_CORE_PATH = ASSETS / "loop_core_patterns_11.bin"
SOURCE_STATS_FOLDER = ASSETS / "loop_stats"
OUTPUT_FOLDER = ASSETS / "top_hearts"
OUTPUT_CORE_PATH = OUTPUT_FOLDER / "loop_core_patterns_11.bin"
OUTPUT_MANIFEST_PATH = OUTPUT_FOLDER / "selected_hearts.csv"

SELECTED_HEARTS = [2, 1, 0, 15, 22, 154]

MAGIC = b"MMLC11B1"
HEADER_SIZE = 232
PATTERN_SIZE = 81
ROUND_BYTES = 33
SCORE_BYTES = 48
PATTERN_COUNT_OFFSET = 32
CHOSEN_WORST_OFFSET = 136
CHOSEN_BEST_OFFSET = 184


def pattern_record(source: bytes, index: int) -> bytes:
    start = HEADER_SIZE + index * PATTERN_SIZE
    end = start + PATTERN_SIZE
    if end > len(source):
        raise RuntimeError(f"Heart index {index} was outside the source asset")
    return source[start:end]


def validate_pattern(record: bytes, index: int) -> None:
    if len(record) != PATTERN_SIZE:
        raise RuntimeError(f"Heart {index:03d} had the wrong record size")
    rounds = record[:ROUND_BYTES]
    for column in range(3):
        roles = rounds[column:ROUND_BYTES:3]
        if sorted(roles) != list(range(11)):
            raise RuntimeError(
                f"Heart {index:03d} column {column} was not a permutation"
            )


def load_quality_scores() -> dict[int, tuple[int, float]]:
    scores = {}
    quality_path = SOURCE_STATS_FOLDER / "heart_quality.csv"
    with quality_path.open(newline="") as handle:
        for row in csv.DictReader(handle):
            scores[int(row["heart_index"])] = (
                int(row["rank"]),
                float(row["gold_floor_score_0_to_100"]),
            )
    return scores


def main() -> None:
    source = SOURCE_CORE_PATH.read_bytes()
    if len(source) < HEADER_SIZE or source[:8] != MAGIC:
        raise RuntimeError(f"Invalid source core asset: {SOURCE_CORE_PATH}")

    source_pattern_count = struct.unpack_from("<Q", source, PATTERN_COUNT_OFFSET)[0]
    expected_size = HEADER_SIZE + source_pattern_count * PATTERN_SIZE
    if len(source) != expected_size:
        raise RuntimeError(
            f"Source core asset size was {len(source)}, expected {expected_size}"
        )
    if max(SELECTED_HEARTS) >= source_pattern_count:
        raise RuntimeError("A selected heart index exceeded the source pattern count")

    records = [pattern_record(source, index) for index in SELECTED_HEARTS]
    for index, record in zip(SELECTED_HEARTS, records):
        validate_pattern(record, index)

    # The source asset is sorted strongest-to-weakest by its original core
    # comparator. Preserve the global provenance fields and replace only the
    # selected count plus the selected-set best/worst score records.
    header = bytearray(source[:HEADER_SIZE])
    struct.pack_into("<Q", header, PATTERN_COUNT_OFFSET, len(records))
    strongest_index = min(SELECTED_HEARTS)
    weakest_index = max(SELECTED_HEARTS)
    strongest_score = pattern_record(source, strongest_index)[ROUND_BYTES:]
    weakest_score = pattern_record(source, weakest_index)[ROUND_BYTES:]
    if len(strongest_score) != SCORE_BYTES or len(weakest_score) != SCORE_BYTES:
        raise RuntimeError("Selected heart score records had the wrong size")
    header[CHOSEN_WORST_OFFSET:CHOSEN_WORST_OFFSET + SCORE_BYTES] = weakest_score
    header[CHOSEN_BEST_OFFSET:CHOSEN_BEST_OFFSET + SCORE_BYTES] = strongest_score

    OUTPUT_FOLDER.mkdir(parents=True, exist_ok=True)
    OUTPUT_CORE_PATH.write_bytes(bytes(header) + b"".join(records))

    scores = load_quality_scores()
    manifest_rows = []
    for position, heart_index in enumerate(SELECTED_HEARTS):
        stats_name = f"heart_{heart_index:03d}_gold_stats.bin"
        source_stats = SOURCE_STATS_FOLDER / stats_name
        output_stats = OUTPUT_FOLDER / stats_name
        shutil.copy2(source_stats, output_stats)
        if source_stats.read_bytes() != output_stats.read_bytes():
            raise RuntimeError(f"Copied stats did not match for heart {heart_index:03d}")
        rank, score = scores[heart_index]
        manifest_rows.append(
            {
                "top_heart_position": position,
                "source_heart_index": heart_index,
                "gold_floor_rank": rank,
                "gold_floor_score_0_to_100": f"{score:.6f}",
                "gold_stats_file": stats_name,
            }
        )

    with OUTPUT_MANIFEST_PATH.open("w", newline="") as handle:
        writer = csv.DictWriter(handle, fieldnames=manifest_rows[0].keys())
        writer.writeheader()
        writer.writerows(manifest_rows)

    packaged = OUTPUT_CORE_PATH.read_bytes()
    packaged_count = struct.unpack_from("<Q", packaged, PATTERN_COUNT_OFFSET)[0]
    if packaged_count != len(SELECTED_HEARTS):
        raise RuntimeError("Packaged core asset recorded the wrong heart count")
    for position, expected_record in enumerate(records):
        if pattern_record(packaged, position) != expected_record:
            raise RuntimeError(
                f"Packaged heart at position {position} did not match its source"
            )

    print(f"Saved {len(records)} hearts to {OUTPUT_CORE_PATH}")
    for position, heart_index in enumerate(SELECTED_HEARTS):
        rank, score = scores[heart_index]
        print(
            f"  position {position}: heart {heart_index:03d}, "
            f"rank {rank}, floor {score:.6f}"
        )


if __name__ == "__main__":
    main()
