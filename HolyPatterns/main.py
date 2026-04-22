#!/usr/bin/env python3

from __future__ import annotations

import argparse
import json
import math
from dataclasses import dataclass
from typing import Iterable

import numpy as np
import pandas as pd


S_BLOCK = 7680
PRODUCT_SIZES = [
    ("S_BLOCK", S_BLOCK),
    ("S_BLOCK*34", S_BLOCK * 34),
    ("S_BLOCK*34*4", S_BLOCK * 34 * 4),
]

DEFAULT_PATTERNS = ["zeros", "ramp", "odd_ramp", "password", "random"]
DEFAULT_MULS = [3, 33]
DEFAULT_ADDS = [1, 13, 17]
BORING_SEED_WEIGHT = 0.25

PASSWORD_BYTES = np.frombuffer(b"Password123!", dtype=np.uint8)
POPCOUNT = np.array([bin(aValue).count("1") for aValue in range(256)], dtype=np.uint8)


@dataclass(frozen=True)
class UnaryMulXorAddSpec:
    mul: int
    add: int

    @property
    def name(self) -> str:
        return f"((a * {self.mul}) ^ (a + {self.add}))"

    def apply_scalar(self, a_value: int) -> int:
        return (((a_value * self.mul) & 0xFF) ^ ((a_value + self.add) & 0xFF)) & 0xFF

    def apply_array(self, a_values: np.ndarray) -> np.ndarray:
        a_wide = a_values.astype(np.uint16)
        a_mul = (a_wide * self.mul) & 0xFF
        a_add = (a_wide + self.add) & 0xFF
        return np.bitwise_xor(a_mul, a_add).astype(np.uint8)


def parse_int_list(p_text: str) -> list[int]:
    a_values: list[int] = []
    for a_part in p_text.split(","):
        a_part = a_part.strip()
        if not a_part:
            continue
        a_values.append(int(a_part, 0))
    return a_values


def parse_text_list(p_text: str) -> list[str]:
    return [a_part.strip() for a_part in p_text.split(",") if a_part.strip()]


def build_pattern(p_name: str, p_size: int, p_rng: np.random.Generator) -> np.ndarray:
    if p_name == "zeros":
        return np.zeros(p_size, dtype=np.uint8)

    if p_name == "ramp":
        return (np.arange(p_size, dtype=np.uint32) & 0xFF).astype(np.uint8)

    if p_name == "odd_ramp":
        return ((np.arange(p_size, dtype=np.uint32) * 2 + 1) & 0xFF).astype(np.uint8)

    if p_name == "password":
        a_repeat = int(math.ceil(float(p_size) / float(PASSWORD_BYTES.size)))
        return np.tile(PASSWORD_BYTES, a_repeat)[:p_size].copy()

    if p_name == "random":
        return p_rng.integers(0, 256, size=p_size, dtype=np.uint8)

    raise ValueError(f"Unknown pattern: {p_name}")


def entropy_bits(p_values: np.ndarray) -> float:
    a_counts = np.bincount(p_values, minlength=256)
    a_probs = a_counts[a_counts > 0].astype(np.float64) / float(p_values.size)
    return float(-(a_probs * np.log2(a_probs)).sum())


def adjacent_equal_fraction(p_values: np.ndarray) -> float:
    if p_values.size < 2:
        return 1.0
    return float(np.mean(p_values[:-1] == p_values[1:]))


def bit_flip_fraction(p_prev: np.ndarray, p_next: np.ndarray) -> float:
    a_xor = np.bitwise_xor(p_prev, p_next)
    return float(POPCOUNT[a_xor].mean() / 8.0)


def analyze_scalar_mapping(p_spec: UnaryMulXorAddSpec) -> dict[str, object]:
    a_inputs = np.arange(256, dtype=np.uint8)
    a_outputs = p_spec.apply_array(a_inputs)
    a_counts = np.bincount(a_outputs, minlength=256)

    a_seen = [False] * 256
    a_cycle_lengths: list[int] = []
    a_fixed_points = 0
    for a_start in range(256):
        if a_seen[a_start]:
            continue

        a_order: dict[int, int] = {}
        a_path: list[int] = []
        a_value = a_start
        while (a_value not in a_order) and (not a_seen[a_value]):
            a_order[a_value] = len(a_path)
            a_path.append(a_value)
            a_value = p_spec.apply_scalar(a_value)

        if a_value in a_order:
            a_cycle = a_path[a_order[a_value]:]
            a_cycle_lengths.append(len(a_cycle))
            if len(a_cycle) == 1:
                a_fixed_points += 1

        for a_path_value in a_path:
            a_seen[a_path_value] = True

    a_avalanche_weights: list[int] = []
    for a_input in range(256):
        a_output = p_spec.apply_scalar(a_input)
        for a_bit in range(8):
            a_flipped_input = a_input ^ (1 << a_bit)
            a_flipped_output = p_spec.apply_scalar(a_flipped_input)
            a_avalanche_weights.append(bin(a_output ^ a_flipped_output).count("1"))

    return {
        "transform": p_spec.name,
        "distinct_outputs": int(np.count_nonzero(a_counts)),
        "max_output_multiplicity": int(a_counts.max()),
        "is_permutation": bool(np.all(a_counts == 1)),
        "cycle_count": int(len(a_cycle_lengths)),
        "longest_cycle": int(max(a_cycle_lengths) if a_cycle_lengths else 0),
        "fixed_points": int(a_fixed_points),
        "avg_avalanche": float(np.mean(a_avalanche_weights)),
        "min_avalanche": int(min(a_avalanche_weights)),
        "max_avalanche": int(max(a_avalanche_weights)),
    }


def search_outputs(p_s1: int, p_s2: int) -> np.ndarray:
    a_inputs = np.arange(256, dtype=np.uint16)
    a_mul = (a_inputs * p_s1) & 0xFF
    a_add = (a_inputs + p_s2) & 0xFF
    return np.bitwise_xor(a_mul, a_add).astype(np.uint8)


def analyze_stage1_pair(p_s1: int, p_s2: int) -> dict[str, object]:
    a_outputs = search_outputs(p_s1, p_s2)
    a_distinct_outputs = int(np.unique(a_outputs).size)
    a_is_permutation = (a_distinct_outputs == 256)

    a_seed_weights = np.ones(256, dtype=np.float64)
    a_seed_weights[0] = BORING_SEED_WEIGHT
    a_seed_weights[1] = BORING_SEED_WEIGHT

    a_seen = [False] * 256
    a_cycle_length_of = np.zeros(256, dtype=np.int32)
    a_orbit_span_of = np.zeros(256, dtype=np.int32)
    a_longest_cycle = 0
    a_cycle_count = 0
    a_fixed_points = 0

    for a_start in range(256):
        if a_seen[a_start]:
            continue

        a_order: dict[int, int] = {}
        a_path: list[int] = []
        a_value = a_start
        while (a_value not in a_order) and (not a_seen[a_value]):
            a_order[a_value] = len(a_path)
            a_path.append(a_value)
            a_value = int(a_outputs[a_value])

        a_cycle_start = len(a_path)
        a_cycle_length = 0
        a_repeat_span = 0

        if a_value in a_order:
            a_cycle_start = a_order[a_value]
            a_cycle_length = len(a_path) - a_cycle_start
            a_repeat_span = len(a_path)
            a_cycle_count += 1
            a_longest_cycle = max(a_longest_cycle, a_cycle_length)
            if a_cycle_length == 1:
                a_fixed_points += 1

            for a_index in range(a_cycle_start, len(a_path)):
                a_node = a_path[a_index]
                a_cycle_length_of[a_node] = a_cycle_length
                a_orbit_span_of[a_node] = a_repeat_span

        else:
            a_cycle_length = int(a_cycle_length_of[a_value])
            a_repeat_span = int(a_orbit_span_of[a_value]) + len(a_path)

        for a_index in range(a_cycle_start - 1, -1, -1):
            a_node = a_path[a_index]
            a_cycle_length_of[a_node] = a_cycle_length
            a_orbit_span_of[a_node] = a_repeat_span - a_index

        for a_node in a_path:
            a_seen[a_node] = True

    a_weight_total = float(a_seed_weights.sum())
    a_weighted_mean_span = float(np.dot(a_orbit_span_of, a_seed_weights) / a_weight_total)
    a_weighted_mean_cycle = float(np.dot(a_cycle_length_of, a_seed_weights) / a_weight_total)
    a_fixed_point_fraction = float(a_fixed_points / 256.0)
    a_score = (
        0.60 * (a_weighted_mean_span / 256.0) +
        0.25 * (a_distinct_outputs / 256.0) +
        0.15 * (a_longest_cycle / 256.0) -
        0.10 * a_fixed_point_fraction
    )

    return {
        "s1": int(p_s1),
        "s2": int(p_s2),
        "score": float(a_score),
        "distinct_outputs": a_distinct_outputs,
        "is_permutation": bool(a_is_permutation),
        "weighted_mean_span": a_weighted_mean_span,
        "weighted_mean_cycle": a_weighted_mean_cycle,
        "longest_cycle": int(a_longest_cycle),
        "cycle_count": int(a_cycle_count),
        "fixed_points": int(a_fixed_points),
    }


def run_stage1_search(p_s1_min: int, p_s1_max: int, p_s2_min: int, p_s2_max: int) -> pd.DataFrame:
    a_rows: list[dict[str, object]] = []
    for a_s1 in range(p_s1_min, p_s1_max + 1):
        for a_s2 in range(p_s2_min, p_s2_max + 1):
            a_rows.append(analyze_stage1_pair(a_s1, a_s2))
    return pd.DataFrame(a_rows)


def summarize_stage1_by_s1(p_results: pd.DataFrame) -> pd.DataFrame:
    a_rows: list[dict[str, object]] = []
    for a_s1, a_group in p_results.groupby("s1", sort=True):
        a_group = a_group.sort_values(["score", "longest_cycle", "weighted_mean_cycle", "s2"], ascending=[False, False, False, True])
        a_best = a_group.iloc[0]
        a_rows.append(
            {
                "s1": int(a_s1),
                "best_s2": int(a_best["s2"]),
                "best_score": float(a_best["score"]),
                "avg_score": float(a_group["score"].mean()),
                "perm_count": int(a_group["is_permutation"].sum()),
                "full_cycle_count": int((a_group["longest_cycle"] == 256).sum()),
                "best_longest_cycle": int(a_best["longest_cycle"]),
                "best_weighted_span": float(a_best["weighted_mean_span"]),
                "best_weighted_cycle": float(a_best["weighted_mean_cycle"]),
            }
        )
    return pd.DataFrame(a_rows)


def summarize_stage1_mod_class(p_results: pd.DataFrame) -> pd.DataFrame:
    a_frame = p_results.copy()
    a_frame["s1_mod_2"] = a_frame["s1"] % 2
    a_frame["s1_mod_4"] = a_frame["s1"] % 4

    a_rows: list[dict[str, object]] = []
    for a_mod4, a_group in a_frame.groupby("s1_mod_4", sort=True):
        a_rows.append(
            {
                "s1_mod_4": int(a_mod4),
                "pair_count": int(len(a_group)),
                "perm_fraction": float(a_group["is_permutation"].mean()),
                "full_cycle_fraction": float((a_group["longest_cycle"] == 256).mean()),
                "avg_score": float(a_group["score"].mean()),
                "best_score": float(a_group["score"].max()),
            }
        )
    return pd.DataFrame(a_rows)


def print_stage1_report(p_results: pd.DataFrame, p_top_n: int) -> None:
    a_top_pairs = p_results.sort_values(
        ["score", "longest_cycle", "weighted_mean_cycle", "s1", "s2"],
        ascending=[False, False, False, True, True],
    ).head(p_top_n)

    a_by_s1 = summarize_stage1_by_s1(p_results)
    a_top_s1 = a_by_s1.sort_values(
        ["best_score", "full_cycle_count", "avg_score", "s1"],
        ascending=[False, False, False, True],
    ).head(p_top_n)

    a_mod_summary = summarize_stage1_mod_class(p_results)

    print_frame(
        "Stage 1 top parameter pairs",
        a_top_pairs,
        ["score", "weighted_mean_span", "weighted_mean_cycle"],
    )
    print_frame(
        "Stage 1 top s1 summary",
        a_top_s1,
        ["best_score", "avg_score", "best_weighted_span", "best_weighted_cycle"],
    )
    print_frame(
        "Stage 1 s1 mod-class summary",
        a_mod_summary,
        ["perm_fraction", "full_cycle_fraction", "avg_score", "best_score"],
    )


def run_buffer_rounds(
    p_spec: UnaryMulXorAddSpec,
    p_pattern_name: str,
    p_size_label: str,
    p_size: int,
    p_rounds: int,
    p_rng: np.random.Generator,
) -> list[dict[str, object]]:
    a_prev = build_pattern(p_pattern_name, p_size, p_rng)
    a_rows: list[dict[str, object]] = []

    for a_round in range(1, p_rounds + 1):
        a_next = p_spec.apply_array(a_prev)
        a_counts = np.bincount(a_next, minlength=256)
        a_rows.append(
            {
                "transform": p_spec.name,
                "size_label": p_size_label,
                "size": p_size,
                "pattern": p_pattern_name,
                "round": a_round,
                "unique_values": int(np.count_nonzero(a_counts)),
                "entropy_bits": entropy_bits(a_next),
                "changed_fraction": float(np.mean(a_prev != a_next)),
                "bit_flip_fraction": bit_flip_fraction(a_prev, a_next),
                "max_bucket_fraction": float(a_counts.max() / float(p_size)),
                "zero_fraction": float(np.mean(a_next == 0)),
                "adjacent_equal_fraction": adjacent_equal_fraction(a_next),
            }
        )
        a_prev = a_next

    return a_rows


def build_specs(p_muls: Iterable[int], p_adds: Iterable[int]) -> list[UnaryMulXorAddSpec]:
    a_specs = [UnaryMulXorAddSpec(a_mul, a_add) for a_mul in p_muls for a_add in p_adds]
    a_specs.sort(key=lambda p_spec: (p_spec.mul, p_spec.add))
    return a_specs


def summarize_buffer_rows(p_rows: list[dict[str, object]]) -> pd.DataFrame:
    a_frame = pd.DataFrame(p_rows)
    a_summaries: list[dict[str, object]] = []

    a_group_columns = ["transform", "size_label", "size", "pattern"]
    for _, a_group in a_frame.groupby(a_group_columns, sort=False):
        a_group = a_group.sort_values("round")
        a_final = a_group.iloc[-1]
        a_summaries.append(
            {
                "transform": a_final["transform"],
                "size_label": a_final["size_label"],
                "pattern": a_final["pattern"],
                "final_unique": int(a_final["unique_values"]),
                "min_unique": int(a_group["unique_values"].min()),
                "final_entropy": float(a_final["entropy_bits"]),
                "min_entropy": float(a_group["entropy_bits"].min()),
                "min_changed": float(a_group["changed_fraction"].min()),
                "min_bit_flip": float(a_group["bit_flip_fraction"].min()),
                "max_bucket": float(a_group["max_bucket_fraction"].max()),
                "max_adjacent_equal": float(a_group["adjacent_equal_fraction"].max()),
                "max_zero_fraction": float(a_group["zero_fraction"].max()),
            }
        )

    return pd.DataFrame(a_summaries)


def print_frame(p_title: str, p_frame: pd.DataFrame, p_float_cols: list[str]) -> None:
    a_frame = p_frame.copy()
    for a_col in p_float_cols:
        if a_col in a_frame.columns:
            a_frame[a_col] = a_frame[a_col].map(lambda a_value: f"{a_value:.4f}")
    print("")
    print(p_title)
    print(a_frame.to_string(index=False))


def main() -> None:
    a_parser = argparse.ArgumentParser(
        description=(
            "HolyPatterns runs byte-fragment experiments over the exact product buffer sizes. "
            "It currently focuses on unary transforms of the form ((a * mul) ^ (a + add))."
        )
    )
    a_parser.add_argument("--mul-list", default="3,33", help="Comma-separated multiply constants.")
    a_parser.add_argument("--add-list", default="1,13,17", help="Comma-separated add constants.")
    a_parser.add_argument(
        "--patterns",
        default="zeros,ramp,odd_ramp,password,random",
        help="Comma-separated pattern names: zeros,ramp,odd_ramp,password,random",
    )
    a_parser.add_argument("--rounds", type=int, default=5, help="How many times to apply T(a) to each array.")
    a_parser.add_argument("--seed", type=int, default=1337, help="Seed used for random-pattern generation.")
    a_parser.add_argument("--csv", default="", help="Optional CSV path for the per-round buffer rows.")
    a_parser.add_argument("--json", default="", help="Optional JSON path for search summaries.")
    a_parser.add_argument("--scalar-only", action="store_true", help="Skip the buffer-size experiments.")
    a_parser.add_argument("--buffer-only", action="store_true", help="Skip the 256-value scalar mapping report.")
    a_parser.add_argument("--stage1-search", action="store_true", help="Exhaustively score (a * s1) ^ (a + s2) over the requested ranges.")
    a_parser.add_argument("--s1-min", type=int, default=2, help="Minimum s1 for stage1 search.")
    a_parser.add_argument("--s1-max", type=int, default=255, help="Maximum s1 for stage1 search.")
    a_parser.add_argument("--s2-min", type=int, default=1, help="Minimum s2 for stage1 search.")
    a_parser.add_argument("--s2-max", type=int, default=255, help="Maximum s2 for stage1 search.")
    a_parser.add_argument("--top-n", type=int, default=20, help="How many rows to print in the top reports.")
    a_args = a_parser.parse_args()

    a_muls = parse_int_list(a_args.mul_list)
    a_adds = parse_int_list(a_args.add_list)
    a_patterns = parse_text_list(a_args.patterns)

    if not a_muls:
        raise SystemExit("No multiply constants were provided.")
    if not a_adds:
        raise SystemExit("No add constants were provided.")
    if not a_patterns:
        raise SystemExit("No patterns were provided.")
    if a_args.rounds <= 0:
        raise SystemExit("Rounds must be positive.")
    if a_args.top_n <= 0:
        raise SystemExit("top-n must be positive.")

    if a_args.stage1_search:
        if a_args.s1_min > a_args.s1_max:
            raise SystemExit("s1-min must be <= s1-max.")
        if a_args.s2_min > a_args.s2_max:
            raise SystemExit("s2-min must be <= s2-max.")

        a_stage1 = run_stage1_search(a_args.s1_min, a_args.s1_max, a_args.s2_min, a_args.s2_max)
        print_stage1_report(a_stage1, a_args.top_n)

        if a_args.json:
            a_payload = {
                "top_pairs": a_stage1.sort_values(
                    ["score", "longest_cycle", "weighted_mean_cycle", "s1", "s2"],
                    ascending=[False, False, False, True, True],
                ).head(a_args.top_n).to_dict(orient="records"),
                "top_s1": summarize_stage1_by_s1(a_stage1).sort_values(
                    ["best_score", "full_cycle_count", "avg_score", "s1"],
                    ascending=[False, False, False, True],
                ).head(a_args.top_n).to_dict(orient="records"),
                "mod_summary": summarize_stage1_mod_class(a_stage1).to_dict(orient="records"),
            }
            with open(a_args.json, "w", encoding="utf-8") as a_file:
                json.dump(a_payload, a_file, indent=2)
            print("")
            print(f"Wrote stage1 search summary to: {a_args.json}")
        return

    a_specs = build_specs(a_muls, a_adds)
    a_rng = np.random.default_rng(a_args.seed)

    if not a_args.buffer_only:
        a_scalar_rows = [analyze_scalar_mapping(a_spec) for a_spec in a_specs]
        a_scalar_frame = pd.DataFrame(a_scalar_rows)
        print_frame(
            "Scalar 256-value report",
            a_scalar_frame,
            ["avg_avalanche"],
        )

    if not a_args.scalar_only:
        a_buffer_rows: list[dict[str, object]] = []
        for a_spec in a_specs:
            for a_size_label, a_size in PRODUCT_SIZES:
                for a_pattern in a_patterns:
                    a_buffer_rows.extend(
                        run_buffer_rounds(
                            a_spec,
                            a_pattern,
                            a_size_label,
                            a_size,
                            a_args.rounds,
                            a_rng,
                        )
                    )

        a_summary_frame = summarize_buffer_rows(a_buffer_rows)
        print_frame(
            "Buffer-size summary",
            a_summary_frame,
            [
                "final_entropy",
                "min_entropy",
                "min_changed",
                "min_bit_flip",
                "max_bucket",
                "max_adjacent_equal",
                "max_zero_fraction",
            ],
        )

        if a_args.csv:
            pd.DataFrame(a_buffer_rows).to_csv(a_args.csv, index=False)
            print("")
            print(f"Wrote detailed round rows to: {a_args.csv}")


if __name__ == "__main__":
    main()
