#!/opt/anaconda3/bin/python3

"""Package the twelve selected final-farm hearts in ranking order."""

from pathlib import Path
import csv
import shutil
import struct


PROJECT_ROOT = Path(__file__).resolve().parent
SOURCE_FOLDER = PROJECT_ROOT / "Assets" / "heart_retest" / "hearts"
SOURCE_STATS_FOLDER = PROJECT_ROOT / "Assets" / "heart_retest" / "loop_stats"
OUTPUT_FOLDER = PROJECT_ROOT / "Assets" / "alien_farm"
OUTPUT_STATS_FOLDER = OUTPUT_FOLDER / "gold_stats"
MANIFEST_PATH = OUTPUT_FOLDER / "heart_manifest.csv"
INADEQUATE_FOLDER = PROJECT_ROOT / "Assets" / "alien_hearts_inadequate"
INADEQUATE_STATS_FOLDER = INADEQUATE_FOLDER / "gold_stats"
INADEQUATE_MANIFEST_PATH = INADEQUATE_FOLDER / "heart_manifest.csv"

MAGIC = b"MMLC11B1"
HEADER_SIZE = 232
PATTERN_SIZE = 81
GOLD_STATS_MAGIC = b"MMGOLD11"
GOLD_STATS_SIZE = 1399

SELECTED_HEARTS = [
    ("gold_heart_a", 78.904200),
    ("silver_heart_e", 77.987000),
    ("silver_heart_h", 77.971300),
    ("gold_heart_b", 77.748200),
]

INADEQUATE_HEARTS = [
    ("silver_heart_g", 76.974900),
    ("gold_heart_d", 76.565400),
    ("gold_heart_c", 76.193800),
    ("silver_heart_f", 76.066300),
    ("silver_heart_c", 75.930400),
    ("silver_heart_a", 75.719200),
    ("gold_heart_f", 75.315700),
    ("silver_heart_d", 74.272700),
]


def validate_single_heart(path):
    data = path.read_bytes()
    if len(data) != HEADER_SIZE + PATTERN_SIZE or data[:8] != MAGIC:
        raise RuntimeError(f"Invalid single-heart asset: {path}")
    pattern_count = struct.unpack_from("<Q", data, 32)[0]
    if pattern_count != 1:
        raise RuntimeError(f"Expected one heart in {path}, found {pattern_count}")
    rounds = data[HEADER_SIZE:HEADER_SIZE + 33]
    for column in range(3):
        if sorted(rounds[column:33:3]) != list(range(11)):
            raise RuntimeError(f"Invalid role permutation in {path}")
    return data


def validate_gold_stats(path):
    data = path.read_bytes()
    if len(data) != GOLD_STATS_SIZE or data[:8] != GOLD_STATS_MAGIC:
        raise RuntimeError(f"Invalid gold-stat asset: {path}")
    return data


def main():
    OUTPUT_FOLDER.mkdir(parents=True, exist_ok=True)
    OUTPUT_STATS_FOLDER.mkdir(parents=True, exist_ok=True)
    INADEQUATE_FOLDER.mkdir(parents=True, exist_ok=True)
    INADEQUATE_STATS_FOLDER.mkdir(parents=True, exist_ok=True)
    rows = []
    for rank, (source_name, score) in enumerate(SELECTED_HEARTS, start=1):
        source_path = SOURCE_FOLDER / f"{source_name}.bin"
        output_name = f"alien_heart_{rank:02d}.bin"
        output_path = OUTPUT_FOLDER / output_name
        source_stats_path = SOURCE_STATS_FOLDER / f"{source_name}_gold_stats.bin"
        output_stats_name = f"alien_heart_{rank:02d}_gold_stats.bin"
        output_stats_path = OUTPUT_STATS_FOLDER / output_stats_name
        source_data = validate_single_heart(source_path)
        source_stats_data = validate_gold_stats(source_stats_path)
        shutil.copy2(source_path, output_path)
        shutil.copy2(source_stats_path, output_stats_path)
        if validate_single_heart(output_path) != source_data:
            raise RuntimeError(f"Copied heart changed: {output_path}")
        if validate_gold_stats(output_stats_path) != source_stats_data:
            raise RuntimeError(f"Copied gold stats changed: {output_stats_path}")
        rows.append({
            "alien_rank": rank,
            "alien_name": output_path.stem,
            "source_name": source_name,
            "gold_floor_score_0_to_100": f"{score:.6f}",
            "heart_file": output_name,
            "reference_stats_file": output_stats_name,
        })

    inadequate_rows = []
    for original_rank, (source_name, score) in enumerate(
            INADEQUATE_HEARTS, start=len(SELECTED_HEARTS) + 1):
        source_path = SOURCE_FOLDER / f"{source_name}.bin"
        output_name = f"alien_heart_{original_rank:02d}.bin"
        output_path = INADEQUATE_FOLDER / output_name
        source_stats_path = SOURCE_STATS_FOLDER / f"{source_name}_gold_stats.bin"
        output_stats_name = (
            f"alien_heart_{original_rank:02d}_gold_stats.bin"
        )
        output_stats_path = INADEQUATE_STATS_FOLDER / output_stats_name
        source_data = validate_single_heart(source_path)
        source_stats_data = validate_gold_stats(source_stats_path)
        shutil.copy2(source_path, output_path)
        shutil.copy2(source_stats_path, output_stats_path)
        if validate_single_heart(output_path) != source_data:
            raise RuntimeError(f"Copied heart changed: {output_path}")
        if validate_gold_stats(output_stats_path) != source_stats_data:
            raise RuntimeError(f"Copied gold stats changed: {output_stats_path}")
        inadequate_rows.append({
            "original_alien_rank": original_rank,
            "alien_name": output_path.stem,
            "source_name": source_name,
            "gold_floor_score_0_to_100": f"{score:.6f}",
            "heart_file": output_name,
            "reference_stats_file": output_stats_name,
        })

    expected_files = {row["heart_file"] for row in rows}
    actual_files = {path.name for path in OUTPUT_FOLDER.glob("*.bin")}
    unexpected_files = sorted(actual_files - expected_files)
    if unexpected_files:
        raise RuntimeError(
            "Alien farm contained unexpected .bin files: " +
            ", ".join(unexpected_files)
        )

    expected_stats_files = {row["reference_stats_file"] for row in rows}
    actual_stats_files = {
        path.name for path in OUTPUT_STATS_FOLDER.glob("*.bin")
    }
    unexpected_stats_files = sorted(actual_stats_files - expected_stats_files)
    if unexpected_stats_files:
        raise RuntimeError(
            "Alien farm gold-stat folder contained unexpected .bin files: " +
            ", ".join(unexpected_stats_files)
        )

    expected_inadequate_files = {
        row["heart_file"] for row in inadequate_rows
    }
    actual_inadequate_files = {
        path.name for path in INADEQUATE_FOLDER.glob("*.bin")
    }
    unexpected_inadequate_files = sorted(
        actual_inadequate_files - expected_inadequate_files
    )
    if unexpected_inadequate_files:
        raise RuntimeError(
            "Inadequate alien-heart folder contained unexpected .bin files: " +
            ", ".join(unexpected_inadequate_files)
        )

    expected_inadequate_stats_files = {
        row["reference_stats_file"] for row in inadequate_rows
    }
    actual_inadequate_stats_files = {
        path.name for path in INADEQUATE_STATS_FOLDER.glob("*.bin")
    }
    unexpected_inadequate_stats_files = sorted(
        actual_inadequate_stats_files - expected_inadequate_stats_files
    )
    if unexpected_inadequate_stats_files:
        raise RuntimeError(
            "Inadequate alien-heart gold-stat folder contained unexpected "
            ".bin files: " + ", ".join(unexpected_inadequate_stats_files)
        )

    with MANIFEST_PATH.open("w", newline="") as handle:
        writer = csv.DictWriter(handle, fieldnames=rows[0].keys())
        writer.writeheader()
        writer.writerows(rows)

    with INADEQUATE_MANIFEST_PATH.open("w", newline="") as handle:
        writer = csv.DictWriter(handle, fieldnames=inadequate_rows[0].keys())
        writer.writeheader()
        writer.writerows(inadequate_rows)

    print(f"Saved {len(rows)} hearts to {OUTPUT_FOLDER}")
    for row in rows:
        print(
            f"  {row['alien_name']} <- {row['source_name']} "
            f"({row['gold_floor_score_0_to_100']})"
        )
    print(f"Saved {len(inadequate_rows)} inadequate hearts to {INADEQUATE_FOLDER}")


if __name__ == "__main__":
    main()
