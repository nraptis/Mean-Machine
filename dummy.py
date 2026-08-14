#!/opt/anaconda3/bin/python3

"""Initial pandas analysis for the generated loop-metric table."""

from pathlib import Path

import pandas as pd


#
# Analysis knobs
#

PROJECT_ROOT = Path(__file__).resolve().parent
TABLE_PATH = PROJECT_ROOT / "random_metric_table_explore.csv"
SCHEMA_PATH = PROJECT_ROOT / "random_metric_table_schema.csv"

EXPECTED_HEART_COUNT = 180
EXPECTED_ROWS_PER_HEART = 5_000
EXPECTED_METRIC_COUNT = 45

UBIQUITOUS_OUTPUT_PATH = PROJECT_ROOT / "dummy_ubiquitous_columns.csv"
SAME_MAXIMUM_OUTPUT_PATH = PROJECT_ROOT / "dummy_same_heart_maxima.csv"
HEART_MAXIMA_OUTPUT_PATH = PROJECT_ROOT / "dummy_heart_maxima.csv"


def load_metric_columns() -> tuple[pd.DataFrame, list[str]]:
    schema = pd.read_csv(SCHEMA_PATH)
    metric_rows = schema[schema["direction"].isin(["higher", "lower"])].copy()
    metric_columns = metric_rows["column_name"].tolist()

    if len(metric_columns) != EXPECTED_METRIC_COUNT:
        raise RuntimeError(
            f"Expected {EXPECTED_METRIC_COUNT} metric columns in "
            f"{SCHEMA_PATH}, found "
            f"{len(metric_columns)}"
        )

    return metric_rows, metric_columns


def main() -> None:
    metric_schema, metric_columns = load_metric_columns()
    use_columns = ["heart_index", *metric_columns]
    column_types = {column: "int32" for column in use_columns}

    print(f"Loading {TABLE_PATH}")
    table = pd.read_csv(
        TABLE_PATH,
        usecols=use_columns,
        dtype=column_types,
    )

    if table.isna().any().any():
        raise RuntimeError("The metric table contained missing values")

    rows_per_heart = table.groupby("heart_index", sort=True).size()
    observed_heart_count = len(rows_per_heart)
    observed_row_count = len(table)

    print()
    print("TABLE SHAPE")
    print("-----------")
    print(f"Rows:              {observed_row_count:,}")
    print(f"Hearts:            {observed_heart_count:,}")
    print(f"Rows/heart range:  {rows_per_heart.min():,}..{rows_per_heart.max():,}")

    complete_shape = (
        observed_heart_count == EXPECTED_HEART_COUNT
        and rows_per_heart.index.min() == 0
        and rows_per_heart.index.max() == EXPECTED_HEART_COUNT - 1
        and (rows_per_heart == EXPECTED_ROWS_PER_HEART).all()
    )
    if complete_shape:
        print("Completeness:       complete")
    else:
        print(
            "Completeness:       PARTIAL — same-heart-maximum results are "
            "only provisional"
        )

    metric_minimums = table[metric_columns].min(axis=0)
    metric_maximums = table[metric_columns].max(axis=0)
    ubiquitous_mask = metric_minimums.eq(metric_maximums)
    ubiquitous_columns = metric_minimums[ubiquitous_mask]

    schema_by_name = metric_schema.set_index("column_name")
    ubiquitous_output = pd.DataFrame(
        {
            "column_name": ubiquitous_columns.index,
            "direction": [
                schema_by_name.at[column, "direction"]
                for column in ubiquitous_columns.index
            ],
            "value": ubiquitous_columns.values,
        }
    )
    ubiquitous_output.to_csv(UBIQUITOUS_OUTPUT_PATH, index=False)

    print()
    print("UBIQUITOUS METRIC COLUMNS")
    print("-------------------------")
    print(
        "These metrics had exactly one value across every observed row. "
        "They cannot rank candidates in this dataset."
    )
    for row in ubiquitous_output.itertuples(index=False):
        print(f"{row.column_name} = {row.value}")
    print(f"Count: {len(ubiquitous_output)}/{len(metric_columns)}")

    heart_maxima = table.groupby("heart_index", sort=True)[metric_columns].max()
    heart_maxima.to_csv(HEART_MAXIMA_OUTPUT_PATH, index=True)

    maximum_of_heart_maxima = heart_maxima.max(axis=0)
    minimum_of_heart_maxima = heart_maxima.min(axis=0)
    same_maximum_mask = maximum_of_heart_maxima.eq(minimum_of_heart_maxima)
    same_maximums = maximum_of_heart_maxima[same_maximum_mask]

    same_maximum_output = pd.DataFrame(
        {
            "column_name": same_maximums.index,
            "direction": [
                schema_by_name.at[column, "direction"]
                for column in same_maximums.index
            ],
            "maximum": same_maximums.values,
            "observed_heart_count": observed_heart_count,
            "complete_180_heart_run": complete_shape,
        }
    )
    same_maximum_output.to_csv(SAME_MAXIMUM_OUTPUT_PATH, index=False)

    print()
    print("SAME RAW MAXIMUM FOR EVERY OBSERVED HEART")
    print("-----------------------------------------")
    if observed_heart_count == 1:
        print("Only one heart is present, so this section is not yet informative.")
    for row in same_maximum_output.itertuples(index=False):
        print(f"{row.column_name} = {row.maximum}")
    print(f"Count: {len(same_maximum_output)}/{len(metric_columns)}")

    print()
    print("SAVED")
    print("-----")
    print(UBIQUITOUS_OUTPUT_PATH)
    print(SAME_MAXIMUM_OUTPUT_PATH)
    print(HEART_MAXIMA_OUTPUT_PATH)


if __name__ == "__main__":
    main()
