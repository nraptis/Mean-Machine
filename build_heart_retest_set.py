#!/opt/anaconda3/bin/python3

"""Build the 22-heart comparison set used by the next gold-rate run."""

from collections import deque
from pathlib import Path
import csv
import re
import struct


PROJECT_ROOT = Path(__file__).resolve().parent
ASSETS = PROJECT_ROOT / "Assets"
SOURCE_CORE_PATH = ASSETS / "loop_core_patterns_11.bin"
SOURCE_QUALITY_PATH = ASSETS / "loop_stats" / "heart_quality.csv"
LEGACY_CORE_PATH = PROJECT_ROOT / "MeanMachine" / "LoopScaffoldCores.hpp"
OUTPUT_FOLDER = ASSETS / "heart_retest"
OUTPUT_HEART_FOLDER = OUTPUT_FOLDER / "hearts"
OUTPUT_CORE_PATH = OUTPUT_FOLDER / "loop_core_patterns_11.bin"
OUTPUT_MANIFEST_PATH = OUTPUT_FOLDER / "heart_manifest.csv"
OUTPUT_README_PATH = OUTPUT_FOLDER / "README.md"

GOLD_HEARTS = [2, 1, 0, 15, 22, 154]
SILVER_HEARTS = [53, 132, 165, 104, 138, 79, 175, 21, 139, 156]

MAGIC = b"MMLC11B1"
VERSION = 2
ROLE_COUNT = 11
HEADER_SIZE = 232
ROUND_BYTES = 33
SCORE_FIELD_COUNT = 12
SCORE_BYTES = SCORE_FIELD_COUNT * 4
PATTERN_SIZE = ROUND_BYTES + SCORE_BYTES


def read_source_asset():
    data = SOURCE_CORE_PATH.read_bytes()
    if len(data) < HEADER_SIZE or data[:8] != MAGIC:
        raise RuntimeError(f"Invalid source asset: {SOURCE_CORE_PATH}")
    version, role_count = struct.unpack_from("<II", data, 8)
    pattern_count = struct.unpack_from("<Q", data, 32)[0]
    expected_size = HEADER_SIZE + pattern_count * PATTERN_SIZE
    if version != VERSION or role_count != ROLE_COUNT or len(data) != expected_size:
        raise RuntimeError("Source core asset had an incompatible layout")
    return data, pattern_count


def record_at(data, index):
    start = HEADER_SIZE + index * PATTERN_SIZE
    end = start + PATTERN_SIZE
    if start < HEADER_SIZE or end > len(data):
        raise RuntimeError(f"Heart index {index:03d} was outside the source asset")
    return data[start:end]


def rounds_from_record(record):
    return [tuple(record[offset:offset + 3])
            for offset in range(0, ROUND_BYTES, 3)]


def validate_rounds(rounds, label):
    if len(rounds) != ROLE_COUNT:
        raise RuntimeError(f"{label} did not contain {ROLE_COUNT} rounds")
    for column in range(3):
        values = sorted(row[column] for row in rounds)
        if values != list(range(ROLE_COUNT)):
            raise RuntimeError(f"{label} column {column} was not a permutation")


def connected_count(graph, skipped_vertex=None):
    seen = set()
    count = 0
    for start in range(ROLE_COUNT):
        if start == skipped_vertex or start in seen:
            continue
        count += 1
        stack = [start]
        seen.add(start)
        while stack:
            node = stack.pop()
            for destination in graph[node]:
                if destination != skipped_vertex and destination not in seen:
                    seen.add(destination)
                    stack.append(destination)
    return count


def reachable(graph, start):
    seen = {start}
    stack = [start]
    while stack:
        node = stack.pop()
        for destination in graph[node]:
            if destination not in seen:
                seen.add(destination)
                stack.append(destination)
    return seen


def score_rounds(rounds):
    edges = set()
    for lead, source, feedback in rounds:
        edges.add((source, lead))
        edges.add((lead, feedback))

    directed = [set() for _ in range(ROLE_COUNT)]
    undirected = [set() for _ in range(ROLE_COUNT)]
    for source, destination in edges:
        directed[source].add(destination)
        undirected[source].add(destination)
        undirected[destination].add(source)

    reciprocal_count = sum(
        (destination, source) in edges for source, destination in edges
    ) // 2
    strongly_connected = int(all(
        len(reachable(directed, start)) == ROLE_COUNT
        for start in range(ROLE_COUNT)
    ))

    base_component_count = connected_count(undirected)
    articulation_count = sum(
        connected_count(undirected, vertex) > base_component_count
        for vertex in range(ROLE_COUNT)
    )
    bridge_count = 0
    for source in range(ROLE_COUNT):
        for destination in undirected[source]:
            if source >= destination:
                continue
            graph_without_edge = [set(neighbors) for neighbors in undirected]
            graph_without_edge[source].remove(destination)
            graph_without_edge[destination].remove(source)
            bridge_count += (
                connected_count(graph_without_edge) > base_component_count
            )

    directed_diameter = 0
    for start in range(ROLE_COUNT):
        distances = [-1] * ROLE_COUNT
        distances[start] = 0
        queue = deque([start])
        while queue:
            node = queue.popleft()
            for destination in directed[node]:
                if distances[destination] < 0:
                    distances[destination] = distances[node] + 1
                    queue.append(destination)
        path_maximum = (max(distances) if min(distances) >= 0 else ROLE_COUNT)
        directed_diameter = max(directed_diameter, path_maximum)

    influence = [1 << role for role in range(ROLE_COUNT)]
    destination_area = [0] * ROLE_COUNT
    source_area = [0] * ROLE_COUNT
    influence_curve_area = 0
    for lead, source, feedback in rounds:
        influence[lead] |= influence[source]
        influence[feedback] |= influence[lead]

        destination_counts = [bin(mask).count("1") for mask in influence]
        influence_curve_area += sum(destination_counts)
        for destination, count in enumerate(destination_counts):
            destination_area[destination] += count
        for source_role in range(ROLE_COUNT):
            source_area[source_role] += sum(
                (mask >> source_role) & 1 for mask in influence
            )

    final_destination_counts = [bin(mask).count("1") for mask in influence]
    final_source_counts = [
        sum((mask >> source) & 1 for mask in influence)
        for source in range(ROLE_COUNT)
    ]
    return (
        len(edges),
        reciprocal_count,
        strongly_connected,
        articulation_count,
        bridge_count,
        min(final_destination_counts),
        min(final_source_counts),
        min(destination_area),
        min(source_area),
        sum(final_destination_counts),
        influence_curve_area,
        directed_diameter,
    )


def score_from_record(record):
    return struct.unpack("<12I", record[ROUND_BYTES:])


def make_record(rounds):
    validate_rounds(rounds, "legacy heart")
    round_bytes = bytes(value for row in rounds for value in row)
    return round_bytes + struct.pack("<12I", *score_rounds(rounds))


def load_legacy_rounds():
    text = LEGACY_CORE_PATH.read_text()
    triplets = [
        tuple(int(value) for value in match)
        for match in re.findall(
            r"\{(\d+)U,\s*(\d+)U,\s*(\d+)U\}", text
        )
    ]
    expected_count = 6 * ROLE_COUNT
    if len(triplets) != expected_count:
        raise RuntimeError(
            f"Expected {expected_count} legacy triplets, found {len(triplets)}"
        )
    return [
        triplets[index:index + ROLE_COUNT]
        for index in range(0, expected_count, ROLE_COUNT)
    ]


def quality_rows():
    rows = {}
    with SOURCE_QUALITY_PATH.open(newline="") as handle:
        for row in csv.DictReader(handle):
            rows[int(row["heart_index"])] = row
    return rows


def comparator_key(record):
    score = score_from_record(record)
    (edges, reciprocal, strong, articulation, bridges,
     destination_floor, source_floor,
     destination_journey, source_journey,
     final_total, curve_area, diameter) = score
    eligible = int(
        edges == 22 and reciprocal == 0 and strong == 1 and
        articulation == 0 and bridges == 0
    )
    return (
        eligible,
        edges,
        -reciprocal,
        strong,
        -articulation,
        -bridges,
        min(destination_floor, source_floor),
        destination_floor + source_floor,
        min(destination_journey, source_journey),
        destination_journey + source_journey,
        curve_area,
        final_total,
        -diameter,
        record[:ROUND_BYTES],
    )


def build_asset(records):
    worst_record = min(records, key=comparator_key)
    best_record = max(records, key=comparator_key)
    worst_score = worst_record[ROUND_BYTES:]
    best_score = best_record[ROUND_BYTES:]
    eligible_count = sum(comparator_key(record)[0] for record in records)

    header = bytearray()
    header.extend(MAGIC)
    header.extend(struct.pack("<IIQQQ", VERSION, ROLE_COUNT,
                              len(records), eligible_count, len(records)))
    header.extend(worst_score)
    header.extend(best_score)
    header.extend(worst_score)
    header.extend(best_score)
    if len(header) != HEADER_SIZE:
        raise RuntimeError("Generated header had the wrong size")
    return bytes(header) + b"".join(records)


def write_manifest(entries):
    fieldnames = [
        "position",
        "name",
        "group",
        "source_heart_index",
        "previous_rank",
        "previous_gold_floor_score_0_to_100",
        "legacy_plan_index",
        "heart_file",
    ]
    with OUTPUT_MANIFEST_PATH.open("w", newline="") as handle:
        writer = csv.DictWriter(handle, fieldnames=fieldnames)
        writer.writeheader()
        writer.writerows(entries)


def write_readme(entries):
    lines = [
        "# Heart Retest Set",
        "",
        "This folder contains the 22 loop hearts selected for the next",
        "head/tail gold-rate comparison:",
        "",
        "- 6 gold hearts: ranks 1-6 from the previous 180-heart run;",
        "- 10 silver hearts: ranks 7-16 from that run;",
        "- 6 legacy hearts: the original P0-P5 plans converted from",
        "  `LoopScaffoldCores.hpp` into scored `LoopCorePattern11` records.",
        "",
        "`loop_core_patterns_11.bin` is the combined, loader-compatible",
        "22-heart asset. `hearts/` contains the same records as individually",
        "loadable one-heart assets. `heart_manifest.csv` preserves their",
        "names, groups, previous ranks, and source indices.",
        "",
        "| Position | Name | Group | Source | Previous rank | Previous floor |",
        "| ---: | --- | --- | ---: | ---: | ---: |",
    ]
    for entry in entries:
        source = entry["source_heart_index"] or "legacy"
        rank = entry["previous_rank"] or "-"
        score = entry["previous_gold_floor_score_0_to_100"] or "-"
        lines.append(
            f"| {entry['position']} | {entry['name']} | {entry['group']} | "
            f"{source} | {rank} | {score} |"
        )
    lines.append("")
    OUTPUT_README_PATH.write_text("\n".join(lines))


def main():
    source_data, source_count = read_source_asset()
    quality = quality_rows()

    # Prove that this implementation is exactly the scoring implementation
    # used to serialize the authoritative 180-heart source asset.
    for index in range(source_count):
        record = record_at(source_data, index)
        rounds = rounds_from_record(record)
        validate_rounds(rounds, f"source heart {index:03d}")
        if score_rounds(rounds) != score_from_record(record):
            raise RuntimeError(f"Score reproduction failed at heart {index:03d}")

    records = []
    entries = []
    selected_source_indices = GOLD_HEARTS + SILVER_HEARTS
    selected_names = (
        [f"gold_heart_{chr(ord('a') + index)}" for index in range(6)] +
        [f"silver_heart_{chr(ord('a') + index)}" for index in range(10)]
    )
    for position, (name, source_index) in enumerate(
            zip(selected_names, selected_source_indices)):
        record = record_at(source_data, source_index)
        records.append(record)
        quality_row = quality[source_index]
        entries.append({
            "position": position,
            "name": name,
            "group": "gold" if position < 6 else "silver",
            "source_heart_index": f"{source_index:03d}",
            "previous_rank": quality_row["rank"],
            "previous_gold_floor_score_0_to_100":
                f"{float(quality_row['gold_floor_score_0_to_100']):.6f}",
            "legacy_plan_index": "",
            "heart_file": f"hearts/{name}.bin",
        })

    for legacy_index, rounds in enumerate(load_legacy_rounds()):
        position = len(records)
        name = f"old_heart_{chr(ord('a') + legacy_index)}"
        record = make_record(rounds)
        records.append(record)
        entries.append({
            "position": position,
            "name": name,
            "group": "old",
            "source_heart_index": "",
            "previous_rank": "",
            "previous_gold_floor_score_0_to_100": "",
            "legacy_plan_index": legacy_index,
            "heart_file": f"hearts/{name}.bin",
        })

    round_keys = [record[:ROUND_BYTES] for record in records]
    if len(set(round_keys)) != len(round_keys):
        raise RuntimeError("The retest set contained an exact duplicate heart")

    OUTPUT_HEART_FOLDER.mkdir(parents=True, exist_ok=True)
    combined = build_asset(records)
    OUTPUT_CORE_PATH.write_bytes(combined)
    for entry, record in zip(entries, records):
        path = OUTPUT_FOLDER / entry["heart_file"]
        path.write_bytes(build_asset([record]))
    write_manifest(entries)
    write_readme(entries)

    # Verify the serialized records and count, not just the in-memory inputs.
    packaged_data, packaged_count = read_asset_at(OUTPUT_CORE_PATH)
    if packaged_count != len(records):
        raise RuntimeError("Combined retest asset recorded the wrong count")
    for position, record in enumerate(records):
        if record_at(packaged_data, position) != record:
            raise RuntimeError(f"Retest record {position} changed during output")

    print(f"Saved {len(records)} hearts to {OUTPUT_FOLDER}")
    print("  gold:  6")
    print("  silver: 10")
    print("  old:    6 (converted and scored)")
    for entry, record in zip(entries, records):
        score = score_from_record(record)
        print(
            f"  {entry['position']:2d} {entry['name']:<15} "
            f"floor={min(score[5], score[6])} "
            f"journey={min(score[7], score[8])} "
            f"total={score[9]} curve={score[10]} diameter={score[11]}"
        )


def read_asset_at(path):
    data = path.read_bytes()
    if len(data) < HEADER_SIZE or data[:8] != MAGIC:
        raise RuntimeError(f"Invalid generated asset: {path}")
    pattern_count = struct.unpack_from("<Q", data, 32)[0]
    expected_size = HEADER_SIZE + pattern_count * PATTERN_SIZE
    if len(data) != expected_size:
        raise RuntimeError(f"Generated asset had an incorrect size: {path}")
    return data, pattern_count


if __name__ == "__main__":
    main()
