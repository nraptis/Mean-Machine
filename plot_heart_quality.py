#!/opt/anaconda3/bin/python3

"""Plot the weighted per-metric floor across each heart's top three rolls."""

from argparse import ArgumentParser
import os
from pathlib import Path
import re
import struct

MATPLOTLIB_CACHE = Path("/tmp/mean-machine-matplotlib")
MATPLOTLIB_CACHE.mkdir(parents=True, exist_ok=True)
os.environ.setdefault("MPLCONFIGDIR", str(MATPLOTLIB_CACHE))
os.environ.setdefault("XDG_CACHE_HOME", str(MATPLOTLIB_CACHE))

import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt
import pandas as pd


PROJECT_ROOT = Path(__file__).resolve().parent
DEFAULT_INPUT = PROJECT_ROOT / "Assets" / "loop_stats" / "heart_quality.csv"
DEFAULT_STATS_FOLDER = PROJECT_ROOT / "Assets" / "loop_stats"
WEIGHTS_PATH = PROJECT_ROOT / "MeanMachine" / "LoopWeights.hpp"
DEFAULT_OUTPUT = (
    PROJECT_ROOT / "Assets" / "loop_stats" / "heart_gold_floor_scores.png"
)

SCORE_COLUMN = "gold_floor_score_0_to_100"
SELECTED_HEART_COUNT = 16
GOLD_MAGIC = b"MMGOLD11"


def parse_arguments():
    parser = ArgumentParser(
        description="Plot heart-quality scores emitted by LoopGoldRateSearch."
    )
    parser.add_argument("--input", type=Path, default=DEFAULT_INPUT)
    parser.add_argument("--output", type=Path, default=DEFAULT_OUTPUT)
    return parser.parse_args()


def load_weights() -> list[int]:
    source = WEIGHTS_PATH.read_text()
    matches = re.findall(
        r'\{"[^"]+",\s*(?:true|false),\s*(\d+)U\}',
        source,
    )
    weights = [int(value) for value in matches]
    if len(weights) != 50:
        raise RuntimeError(
            f"Expected 50 metric weights in {WEIGHTS_PATH}, found {len(weights)}"
        )
    return weights


def derive_quality_table(stats_folder: Path) -> pd.DataFrame:
    weights = load_weights()
    weight_total = sum(weights)
    if weight_total <= 0:
        raise RuntimeError("The enabled metric weights summed to zero")

    rows = []
    for path in sorted(stats_folder.glob("heart_*_gold_stats.bin")):
        data = path.read_bytes()
        if len(data) < 64 or data[:8] != GOLD_MAGIC:
            raise RuntimeError(f"Invalid gold-stat header in {path}")
        (
            version,
            heart_index,
            role_count,
            metric_count,
            candidate_count,
            percent_scale,
            _trials,
            _raw_attempts,
            _heart_signature,
            _weight_signature,
        ) = struct.unpack_from("<6I4Q", data, 8)
        if version != 1 or metric_count != len(weights) or candidate_count != 3:
            raise RuntimeError(f"Unsupported gold-stat format in {path}")

        gold_offset = 64 + (2 * metric_count * 4)
        gold_percents = struct.unpack_from(f"<{metric_count}I", data, gold_offset)
        weighted_sum = sum(
            weight * percent for weight, percent in zip(weights, gold_percents)
        )
        floor_fixed = (weighted_sum + (weight_total // 2)) // weight_total

        candidate_size = (3 * 4) + (3 * role_count) + (metric_count * 4)
        candidate_offset = 64 + (3 * metric_count * 4)
        candidate_scores = [
            struct.unpack_from("<I", data, candidate_offset + i * candidate_size)[0]
            for i in range(candidate_count)
        ]
        fixed_to_percent = 100.0 / percent_scale
        rows.append(
            {
                "heart_index": heart_index,
                SCORE_COLUMN: floor_fixed * fixed_to_percent,
                "relative_heart_score_0_to_300": (
                    sum(candidate_scores) * fixed_to_percent
                ),
                "relative_top_1_0_to_100": candidate_scores[0] * fixed_to_percent,
                "relative_top_2_0_to_100": candidate_scores[1] * fixed_to_percent,
                "relative_top_3_0_to_100": candidate_scores[2] * fixed_to_percent,
                "normalization_scope": "per_heart_sample_range",
            }
        )

    if not rows:
        raise RuntimeError(f"No gold-stat files were found in {stats_folder}")

    table = pd.DataFrame(rows).sort_values(
        [SCORE_COLUMN, "relative_heart_score_0_to_300", "heart_index"],
        ascending=[False, False, True],
    ).reset_index(drop=True)
    table.insert(0, "rank", table.index + 1)
    table.insert(
        1,
        "selected_top_24",
        ["yes" if i < SELECTED_HEART_COUNT else "no" for i in table.index],
    )
    return table


def save_sorted_outputs(table: pd.DataFrame, csv_path: Path) -> None:
    table.to_csv(csv_path, index=False, float_format="%.6f")
    ranking_path = csv_path.parent / "heart_quality_sorted.txt"
    lines = [
        "GOLD HEART FLOOR RANKING",
        "rank | heart | floor score | top 24",
        "-----+-------+-------------+-------",
    ]
    for row in table.itertuples(index=False):
        lines.append(
            f"{int(row.rank):4d} | {int(row.heart_index):03d}   | "
            f"{getattr(row, SCORE_COLUMN):11.6f} | "
            f"{'yes' if row.selected_top_24 == 'yes' else ''}"
        )
    ranking_path.write_text("\n".join(lines) + "\n")


def load_quality_table(path: Path) -> pd.DataFrame:
    if not path.exists():
        table = derive_quality_table(DEFAULT_STATS_FOLDER)
        save_sorted_outputs(table, path)
    else:
        table = pd.read_csv(path)
        if SCORE_COLUMN not in table.columns:
            table = derive_quality_table(DEFAULT_STATS_FOLDER)
            save_sorted_outputs(table, path)

    required = {"heart_index", SCORE_COLUMN}
    missing = sorted(required.difference(table.columns))
    if missing:
        raise RuntimeError(f"Missing columns in {path}: {', '.join(missing)}")
    if table.empty:
        raise RuntimeError(f"No completed hearts were present in {path}")
    if table["heart_index"].duplicated().any():
        raise RuntimeError(f"Duplicate heart indices were present in {path}")
    return table


def plot_quality(table: pd.DataFrame, output_path: Path) -> None:
    if "rank" in table.columns:
        ranked = table.sort_values("rank").reset_index(drop=True)
    else:
        ranked = table.sort_values(
            [SCORE_COLUMN, "heart_index"], ascending=[False, True]
        ).reset_index(drop=True)
    selected_count = min(SELECTED_HEART_COUNT, len(ranked))
    selected = ranked.iloc[:selected_count].copy()

    figure, axes = plt.subplots(2, 1, figsize=(12, 9), constrained_layout=True)
    scopes = table.get("normalization_scope")
    title = "Gold-search heart floor scores"
    if scopes is not None and scopes.nunique() == 1:
        title += f" — {scopes.iloc[0].replace('_', ' ')} normalization"
    figure.suptitle(title, fontsize=16)

    rank_numbers = ranked.index + 1
    axes[0].plot(rank_numbers, ranked[SCORE_COLUMN], color="#777777", linewidth=1.5)
    axes[0].scatter(
        rank_numbers[selected_count:],
        ranked.loc[selected_count:, SCORE_COLUMN],
        color="#777777",
        s=14,
        label="not selected",
    )
    axes[0].scatter(
        rank_numbers[:selected_count],
        selected[SCORE_COLUMN],
        color="#315a9d",
        s=28,
        label=f"selected top {selected_count}",
        zorder=3,
    )
    axes[0].axvline(
        selected_count + 0.5,
        color="#315a9d",
        linestyle=":",
        linewidth=1.2,
    )
    axes[0].axhline(
        ranked[SCORE_COLUMN].median(),
        color="#777777",
        linestyle="--",
        linewidth=1.0,
        label=f"median {ranked[SCORE_COLUMN].median():.3f}",
    )
    axes[0].annotate(
        f"heart {int(ranked.iloc[0]['heart_index']):03d}\n"
        f"{ranked.iloc[0][SCORE_COLUMN]:.3f}",
        (1, ranked.iloc[0][SCORE_COLUMN]),
        xytext=(12, -28),
        textcoords="offset points",
    )
    axes[0].annotate(
        f"heart {int(ranked.iloc[-1]['heart_index']):03d}\n"
        f"{ranked.iloc[-1][SCORE_COLUMN]:.3f}",
        (len(ranked), ranked.iloc[-1][SCORE_COLUMN]),
        xytext=(-12, 12),
        textcoords="offset points",
        ha="right",
    )
    axes[0].annotate(
        f"cutoff {selected.iloc[-1][SCORE_COLUMN]:.3f}",
        (selected_count, selected.iloc[-1][SCORE_COLUMN]),
        xytext=(10, 12),
        textcoords="offset points",
    )
    axes[0].set_title(
        "Weighted score of the weakest top-three result for every metric"
    )
    axes[0].set_xlabel("Rank")
    axes[0].set_ylabel("Gold floor score (0–100)")
    axes[0].grid(axis="y", alpha=0.25)
    axes[0].legend(frameon=False)

    selected_for_bars = selected.iloc[::-1]
    axes[1].barh(
        [f"heart {int(value):03d}" for value in selected_for_bars["heart_index"]],
        selected_for_bars[SCORE_COLUMN],
        color="#315a9d",
    )
    axes[1].set_title(f"Selected top {selected_count} hearts")
    axes[1].set_xlabel("Gold floor score (0–100)")
    axes[1].set_ylabel("")
    axes[1].grid(axis="x", alpha=0.25)
    axes[1].bar_label(
        axes[1].containers[0],
        fmt="%.3f",
        padding=3,
        fontsize=8,
    )

    output_path.parent.mkdir(parents=True, exist_ok=True)
    figure.savefig(output_path, dpi=180)
    plt.close(figure)


def main() -> None:
    arguments = parse_arguments()
    table = load_quality_table(arguments.input)
    plot_quality(table, arguments.output)

    if "rank" in table.columns:
        ranked = table.sort_values("rank")
    else:
        ranked = table.sort_values(
            [SCORE_COLUMN, "heart_index"], ascending=[False, True]
        )
    best = ranked.iloc[0]
    worst = ranked.iloc[-1]
    print(f"Plotted {len(table)} completed hearts to {arguments.output}")
    print(
        f"Best:  heart {int(best['heart_index']):03d} = "
        f"{best[SCORE_COLUMN]:.6f}"
    )
    print(
        f"Worst: heart {int(worst['heart_index']):03d} = "
        f"{worst[SCORE_COLUMN]:.6f}"
    )
    print(
        f"Range: {best[SCORE_COLUMN] - worst[SCORE_COLUMN]:.6f}; "
        f"median: {table[SCORE_COLUMN].median():.6f}"
    )
    print()
    print(f"TOP {min(SELECTED_HEART_COUNT, len(ranked))} HEARTS")
    print("rank  heart  gold floor score")
    for rank, row in enumerate(ranked.head(SELECTED_HEART_COUNT).itertuples(), 1):
        print(
            f"{rank:4d}  {int(row.heart_index):03d}    "
            f"{getattr(row, SCORE_COLUMN):.6f}"
        )


if __name__ == "__main__":
    main()
