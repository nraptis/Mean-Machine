#!/usr/bin/env python3
"""Plan balanced residual lanes for GTwistRunTwist and GSeedRunSeed.

The planner has four kinds of hard constraints:

* Fuse lanes are never residuals.
* A pipeline may add more forbidden families (Twist forbids Expansion).
* Every eligible previous-stage input and warmup is carried forward.
* Source, Key A, Key B, and the live Snow lanes can be required per stage.

After satisfying hard constraints, the planner fills every available residual
slot up to the stage maximum (never more than 12). Optional lanes with fewer
than two uses are always selected before lanes that already have two uses.
Future hard requirements and lane recency break ties deterministically.

Examples:

    python3 lane_calc.py --pipeline twist
    python3 lane_calc.py --pipeline seed --format cpp
    python3 lane_calc.py --pipeline seed --format json
    python3 lane_calc.py --pipeline twist --max GTwistRunTwist_C=8
    python3 lane_calc.py --pipeline seed \
        --require GSeedRunSeed_C=source,key_a,snow \
        --optional GSeedRunSeed_C=key_b
    python3 lane_calc.py --self-test

"""

from __future__ import annotations

import argparse
import json
import sys
from collections import Counter
from dataclasses import asdict, dataclass, replace
from typing import Iterable, Sequence


MAX_RESIDUALS = 12
SPECIAL_REQUIREMENTS = ("source", "key_a", "key_b", "snow")
UNIVERSALLY_FORBIDDEN_FAMILIES = frozenset(("fuse",))
SUPPORTED_SIX_PASS_COUNTS = frozenset(range(0, MAX_RESIDUALS + 1))
G_PASS_FACTORY_ARRAY_COUNTS = frozenset(range(1, MAX_RESIDUALS + 1))


def lane_group(name: str, letters: str = "abcd") -> tuple[str, ...]:
    return tuple(f"{name}_{letter}" for letter in letters)


SOURCE = ("source",)
KEYS = ("key_a", "key_b")
SCRAP = lane_group("scrap")
EXPANSION = lane_group("expansion")
WIND = lane_group("wind")
SNOW = lane_group("snow")
OPERATION = lane_group("operation")
WATER = lane_group("water")
FUSE = lane_group("fuse")
FIRE = lane_group("fire")
EARTH = lane_group("earth")
WORK = lane_group("work")
INVEST_AB = lane_group("invest", "ab")
INVEST_CD = lane_group("invest", "cd")
INVEST_EF = lane_group("invest", "ef")
INVEST_GH = lane_group("invest", "gh")
INVEST_AD = lane_group("invest")
INVEST_EH = lane_group("invest", "efgh")


def unique(items: Iterable[str]) -> tuple[str, ...]:
    result: list[str] = []
    for item in items:
        if item not in result:
            result.append(item)
    return tuple(result)


def lane_family(lane: str) -> str:
    if lane in ("source", "key_a", "key_b"):
        return lane
    return lane.rsplit("_", 1)[0]


@dataclass(frozen=True)
class Requirements:
    source: bool = False
    key_a: bool = False
    key_b: bool = False
    snow: bool = False

    def enabled_names(self) -> tuple[str, ...]:
        return tuple(name for name in SPECIAL_REQUIREMENTS if getattr(self, name))

    def with_values(self, names: Iterable[str], value: bool) -> "Requirements":
        updates = {name: value for name in names}
        return replace(self, **updates)


@dataclass(frozen=True)
class Stage:
    name: str
    inputs: tuple[str, ...]
    warmups: tuple[str, ...] = ()
    outputs: tuple[str, ...] = ()
    after_outputs: tuple[str, ...] = ()
    max_residuals: int = MAX_RESIDUALS
    requirements: Requirements = Requirements()

    @property
    def writes(self) -> tuple[str, ...]:
        return unique(self.warmups + self.outputs)


@dataclass(frozen=True)
class Pipeline:
    name: str
    initial_lanes: tuple[str, ...]
    stages: tuple[Stage, ...]
    forbidden_families: frozenset[str] = UNIVERSALLY_FORBIDDEN_FAMILIES


@dataclass(frozen=True)
class StageContext:
    stage: Stage
    candidates: tuple[str, ...]
    required: tuple[str, ...]
    carry_required: tuple[str, ...]
    target_count: int
    last_write: dict[str, int]


@dataclass(frozen=True)
class StagePlan:
    stage: Stage
    residuals: tuple[str, ...]
    required: tuple[str, ...]
    carry_required: tuple[str, ...]
    optional_selected: tuple[str, ...]
    omitted_candidates: tuple[str, ...]
    target_count: int
    usage_before: dict[str, int]
    usage_after_required: dict[str, int]
    usage_after: dict[str, int]


@dataclass(frozen=True)
class PipelinePlan:
    pipeline: Pipeline
    stages: tuple[StagePlan, ...]
    final_usage: dict[str, int]


def is_forbidden(lane: str, pipeline: Pipeline) -> bool:
    return lane_family(lane) in pipeline.forbidden_families


def special_required_lanes(
    requirements: Requirements,
    candidates: Sequence[str],
    stage_name: str,
) -> tuple[str, ...]:
    required: list[str] = []
    for name in requirements.enabled_names():
        if name == "snow":
            snow_lanes = [lane for lane in candidates if lane_family(lane) == "snow"]
            if not snow_lanes:
                raise ValueError(f"{stage_name}: Snow was required but no Snow residual is eligible")
            required.extend(snow_lanes)
            continue

        if name not in candidates:
            raise ValueError(f"{stage_name}: {name} was required but is not an eligible residual")
        required.append(name)
    return unique(required)


def build_contexts(pipeline: Pipeline) -> tuple[StageContext, ...]:
    live = list(unique(pipeline.initial_lanes))
    last_write = {lane: -1 for lane in live}
    previous_stage: Stage | None = None
    contexts: list[StageContext] = []

    for stage_index, stage in enumerate(pipeline.stages):
        if not 0 <= stage.max_residuals <= MAX_RESIDUALS:
            raise ValueError(
                f"{stage.name}: max_residuals must be between 0 and {MAX_RESIDUALS}"
            )

        missing_inputs = [lane for lane in stage.inputs if lane not in live]
        if missing_inputs:
            raise ValueError(
                f"{stage.name}: inputs are not live: {', '.join(missing_inputs)}"
            )

        excluded = set(stage.inputs + stage.writes)
        candidates = tuple(
            lane
            for lane in live
            if lane not in excluded and not is_forbidden(lane, pipeline)
        )

        carry_required: tuple[str, ...] = ()
        if previous_stage is not None:
            carry_required = tuple(
                lane
                for lane in unique(previous_stage.inputs + previous_stage.warmups)
                if lane in candidates
            )

        required = unique(
            carry_required
            + special_required_lanes(stage.requirements, candidates, stage.name)
        )
        if len(required) > stage.max_residuals:
            raise ValueError(
                f"{stage.name}: {len(required)} required residuals exceed the "
                f"stage maximum of {stage.max_residuals}"
            )

        contexts.append(
            StageContext(
                stage=stage,
                candidates=candidates,
                required=required,
                carry_required=carry_required,
                target_count=min(stage.max_residuals, len(candidates)),
                last_write=dict(last_write),
            )
        )

        for lane in stage.writes + stage.after_outputs:
            if lane not in live:
                live.append(lane)
            last_write[lane] = stage_index
        previous_stage = stage

    return tuple(contexts)


def future_required_counts(
    contexts: Sequence[StageContext], current_index: int
) -> Counter[str]:
    counts: Counter[str] = Counter()
    for context in contexts[current_index + 1 :]:
        counts.update(context.required)
    return counts


def plan_pipeline(pipeline: Pipeline) -> PipelinePlan:
    contexts = build_contexts(pipeline)
    usage: Counter[str] = Counter()
    plans: list[StagePlan] = []

    for stage_index, context in enumerate(contexts):
        usage_before = dict(usage)
        selected = list(context.required)
        usage.update(selected)
        usage_after_required = dict(usage)

        future_required = future_required_counts(contexts, stage_index)
        optional = [lane for lane in context.candidates if lane not in context.required]
        optional.sort(
            key=lambda lane: (
                usage[lane] >= 2,
                usage[lane] + future_required[lane],
                usage[lane],
                -context.last_write.get(lane, -1),
                lane,
            )
        )

        optional_count = context.target_count - len(selected)
        optional_selected = optional[:optional_count]
        selected.extend(optional_selected)
        usage.update(optional_selected)

        plans.append(
            StagePlan(
                stage=context.stage,
                residuals=tuple(selected),
                required=context.required,
                carry_required=context.carry_required,
                optional_selected=tuple(optional_selected),
                omitted_candidates=tuple(optional[optional_count:]),
                target_count=context.target_count,
                usage_before=usage_before,
                usage_after_required=usage_after_required,
                usage_after=dict(usage),
            )
        )

    return PipelinePlan(
        pipeline=pipeline,
        stages=tuple(plans),
        final_usage=dict(sorted(usage.items())),
    )


def twist_pipeline() -> Pipeline:
    stages = (
        Stage(
            "GTwistRunTwist_A",
            inputs=SOURCE + KEYS,
            warmups=SCRAP[:2],
            outputs=WIND,
            max_residuals=0,
        ),
        Stage(
            "GTwistRunTwist_B",
            inputs=WIND,
            warmups=SCRAP[2:],
            outputs=SNOW,
            max_residuals=5,
            requirements=Requirements(source=True, key_a=True, key_b=True),
        ),
        Stage(
            "GTwistRunTwist_C",
            inputs=SNOW,
            warmups=INVEST_AB,
            outputs=OPERATION,
            max_residuals=9,
            requirements=Requirements(source=True),
        ),
        Stage(
            "GTwistRunTwist_D",
            inputs=OPERATION,
            warmups=INVEST_CD,
            outputs=WATER,
            requirements=Requirements(snow=True),
        ),
        Stage(
            "GTwistRunTwist_E",
            inputs=WATER,
            outputs=FUSE,
            after_outputs=FIRE,
            max_residuals=12,
            requirements=Requirements(key_a=True, key_b=True, snow=True),
        ),
        Stage(
            "GTwistRunTwist_F",
            inputs=FIRE,
            warmups=INVEST_EF,
            outputs=EARTH,
            requirements=Requirements(snow=True),
        ),
        Stage(
            "GTwistRunTwist_G",
            inputs=EARTH,
            warmups=INVEST_GH,
            outputs=WORK,
        ),
    )
    return Pipeline(
        name="twist",
        initial_lanes=SOURCE + KEYS,
        stages=stages,
        forbidden_families=UNIVERSALLY_FORBIDDEN_FAMILIES | frozenset(("expansion",)),
    )


def seed_pipeline() -> Pipeline:
    stages = (
        Stage(
            "GSeedRunSeed_A",
            inputs=SOURCE + KEYS,
            warmups=SCRAP[:2],
            outputs=EXPANSION,
            max_residuals=0,
        ),
        Stage(
            "GSeedRunSeed_B",
            inputs=EXPANSION,
            outputs=EARTH[:2] + WORK,
            requirements=Requirements(source=True, key_a=True, key_b=True),
        ),
        Stage(
            "GSeedRunSeed_C",
            inputs=WORK[2:] + EARTH[:2],
            warmups=EARTH[2:],
            outputs=OPERATION,
            requirements=Requirements(source=True, key_a=True),
        ),
        Stage(
            "GSeedRunSeed_D",
            inputs=OPERATION,
            warmups=SNOW[:2],
            outputs=FUSE,
            after_outputs=FIRE,
            requirements=Requirements(source=True, key_b=True),
        ),
        Stage(
            "GSeedRunSeed_E",
            inputs=FIRE,
            warmups=WATER[2:],
            outputs=INVEST_AD,
            requirements=Requirements(key_a=True, key_b=True, snow=True),
        ),
        Stage(
            "GSeedRunSeed_F",
            inputs=INVEST_AD,
            warmups=SNOW[2:],
            outputs=WIND,
            requirements=Requirements(source=True, key_a=True, snow=True),
        ),
        Stage(
            "GSeedRunSeed_G",
            inputs=WIND,
            warmups=WATER[:2],
            outputs=OPERATION,
            requirements=Requirements(source=True, key_b=True, snow=True),
        ),
        Stage(
            "GSeedRunSeed_H",
            inputs=OPERATION,
            warmups=FIRE[:2],
            outputs=FUSE,
            after_outputs=INVEST_EH,
            requirements=Requirements(source=True, key_a=True, snow=True),
        ),
        Stage(
            "GSeedRunSeed_I",
            inputs=INVEST_EH,
            warmups=FIRE[2:],
            outputs=WORK,
            requirements=Requirements(key_a=True, key_b=True, snow=True),
        ),
    )
    return Pipeline(
        name="seed",
        initial_lanes=SOURCE + KEYS,
        stages=stages,
        forbidden_families=UNIVERSALLY_FORBIDDEN_FAMILIES,
    )


def cpp_slot(lane: str) -> str:
    direct = {
        "source": "Slot::kSource",
        "key_a": "Slot::kKeyRowReadA",
        "key_b": "Slot::kKeyRowReadB",
    }
    if lane in direct:
        return direct[lane]

    family, letter = lane.rsplit("_", 1)
    letter = letter.upper()
    family_names = {
        "scrap": "ScrapLane",
        "expansion": "ExpansionLane",
        "wind": "WindLane",
        "snow": "SnowLane",
        "operation": "OperationLane",
        "water": "WaterLane",
        "fuse": "FuseLane",
        "fire": "FireLane",
        "earth": "EarthLane",
        "work": "WorkLane",
        "invest": "Invest",
    }
    return f"Slot::k{family_names[family]}{letter}"


NUMBER_WORDS = {
    0: "No",
    1: "One",
    2: "Two",
    3: "Three",
    4: "Four",
    5: "Five",
    6: "Six",
    7: "Seven",
    8: "Eight",
    9: "Nine",
    10: "Ten",
    11: "Eleven",
    12: "Twelve",
}


def factory_name(count: int) -> str | None:
    if count not in SUPPORTED_SIX_PASS_COUNTS:
        return None
    return f"SixPass{NUMBER_WORDS[count]}ResidualSlices"


def requirements_text(requirements: Requirements) -> str:
    return ", ".join(
        f"{name}={'required' if getattr(requirements, name) else 'optional'}"
        for name in SPECIAL_REQUIREMENTS
    )


def render_human(plan: PipelinePlan) -> str:
    lines = [f"{plan.pipeline.name} residual plan"]
    for stage_plan in plan.stages:
        stage = stage_plan.stage
        lines.append("")
        lines.append(
            f"{stage.name}: {len(stage_plan.residuals)}/{stage.max_residuals} residuals"
        )
        lines.append(f"  requirements: {requirements_text(stage.requirements)}")
        lines.append(
            "  carry: " + (", ".join(stage_plan.carry_required) or "none")
        )
        lines.append(
            "  residuals: " + (", ".join(stage_plan.residuals) or "none")
        )
        factory = factory_name(len(stage_plan.residuals))
        lines.append(f"  factory: {factory or 'no matching GPassFactory helper'}")

    usage_groups: dict[int, list[str]] = {}
    for lane, count in plan.final_usage.items():
        usage_groups.setdefault(count, []).append(lane)
    lines.append("")
    lines.append("final use counts:")
    for count in sorted(usage_groups):
        lines.append(f"  {count}x: {', '.join(usage_groups[count])}")
    return "\n".join(lines)


def render_cpp(plan: PipelinePlan) -> str:
    lines: list[str] = []
    for stage_plan in plan.stages:
        stage = stage_plan.stage
        count = len(stage_plan.residuals)
        lines.append(f"// {stage.name}")
        lines.append(f"// {requirements_text(stage.requirements)}")
        if count in G_PASS_FACTORY_ARRAY_COUNTS:
            array_type = f"GPassFactory::SlotArray{count}"
        else:
            array_type = f"std::array<Slot, {count}U>"
        lines.append(
            f"const {array_type} aResidualSources = {{"
            if count
            else "// No residual array required."
        )
        if count:
            for lane in stage_plan.residuals:
                lines.append(f"    {cpp_slot(lane)},")
            lines.append("};")
        factory = factory_name(count)
        if factory:
            lines.append(f"// GPassFactory::{factory}(aInputs, aResidualSources, aDestinations)")
        else:
            lines.append(f"// No SixPass helper currently exists for {count} residuals.")
        lines.append("")
    return "\n".join(lines).rstrip()


def render_json(plan: PipelinePlan) -> str:
    payload = {
        "pipeline": plan.pipeline.name,
        "forbidden_families": sorted(plan.pipeline.forbidden_families),
        "stages": [
            {
                "name": stage_plan.stage.name,
                "max_residuals": stage_plan.stage.max_residuals,
                "requirements": asdict(stage_plan.stage.requirements),
                "carry_required": list(stage_plan.carry_required),
                "required": list(stage_plan.required),
                "residuals": list(stage_plan.residuals),
                "factory": factory_name(len(stage_plan.residuals)),
            }
            for stage_plan in plan.stages
        ],
        "final_usage": plan.final_usage,
    }
    return json.dumps(payload, indent=2, sort_keys=True)


def parse_assignment(text: str, option_name: str) -> tuple[str, str]:
    if "=" not in text:
        raise ValueError(f"{option_name} expects STAGE=VALUE, received {text!r}")
    stage_name, value = text.split("=", 1)
    if not stage_name or not value:
        raise ValueError(f"{option_name} expects non-empty STAGE and VALUE")
    return stage_name, value


def resolve_stage(pipelines: Sequence[Pipeline], requested_name: str) -> tuple[int, int]:
    lowered = requested_name.lower()
    exact: list[tuple[int, int]] = []
    suffix: list[tuple[int, int]] = []
    for pipeline_index, pipeline in enumerate(pipelines):
        for stage_index, stage in enumerate(pipeline.stages):
            if stage.name.lower() == lowered:
                exact.append((pipeline_index, stage_index))
            if stage.name.lower().endswith(f"_{lowered}"):
                suffix.append((pipeline_index, stage_index))
    matches = exact or suffix
    if len(matches) != 1:
        names = ", ".join(
            stage.name for pipeline in pipelines for stage in pipeline.stages
        )
        raise ValueError(
            f"stage {requested_name!r} is unknown or ambiguous; use one of: {names}"
        )
    return matches[0]


def apply_overrides(
    pipelines: Sequence[Pipeline],
    require_overrides: Sequence[str],
    optional_overrides: Sequence[str],
    max_overrides: Sequence[str],
    max_all: int | None,
) -> tuple[Pipeline, ...]:
    mutable_stages = [list(pipeline.stages) for pipeline in pipelines]

    if max_all is not None:
        if not 0 <= max_all <= MAX_RESIDUALS:
            raise ValueError(f"--max-all must be between 0 and {MAX_RESIDUALS}")
        for pipeline_index, stages in enumerate(mutable_stages):
            for stage_index, stage in enumerate(stages):
                if stage.max_residuals:
                    stages[stage_index] = replace(stage, max_residuals=max_all)

    def update_requirements(assignments: Sequence[str], value: bool, option: str) -> None:
        for assignment in assignments:
            stage_name, raw_names = parse_assignment(assignment, option)
            names = tuple(name.strip() for name in raw_names.split(",") if name.strip())
            invalid = [name for name in names if name not in SPECIAL_REQUIREMENTS]
            if invalid:
                raise ValueError(
                    f"{option}: invalid requirement(s) {', '.join(invalid)}; "
                    f"choose from {', '.join(SPECIAL_REQUIREMENTS)}"
                )
            pipeline_index, stage_index = resolve_stage(pipelines, stage_name)
            stage = mutable_stages[pipeline_index][stage_index]
            mutable_stages[pipeline_index][stage_index] = replace(
                stage,
                requirements=stage.requirements.with_values(names, value),
            )

    update_requirements(require_overrides, True, "--require")
    update_requirements(optional_overrides, False, "--optional")

    for assignment in max_overrides:
        stage_name, raw_maximum = parse_assignment(assignment, "--max")
        try:
            maximum = int(raw_maximum)
        except ValueError as error:
            raise ValueError(f"--max requires an integer, received {raw_maximum!r}") from error
        if not 0 <= maximum <= MAX_RESIDUALS:
            raise ValueError(f"--max must be between 0 and {MAX_RESIDUALS}")
        pipeline_index, stage_index = resolve_stage(pipelines, stage_name)
        mutable_stages[pipeline_index][stage_index] = replace(
            mutable_stages[pipeline_index][stage_index],
            max_residuals=maximum,
        )

    return tuple(
        replace(pipeline, stages=tuple(mutable_stages[pipeline_index]))
        for pipeline_index, pipeline in enumerate(pipelines)
    )


def verify_plan(plan: PipelinePlan) -> None:
    for stage_plan in plan.stages:
        if len(stage_plan.residuals) != stage_plan.target_count:
            raise AssertionError(f"{stage_plan.stage.name}: planner did not fill to its maximum")
        if len(stage_plan.residuals) > MAX_RESIDUALS:
            raise AssertionError(f"{stage_plan.stage.name}: exceeded {MAX_RESIDUALS} residuals")
        if not set(stage_plan.required).issubset(stage_plan.residuals):
            raise AssertionError(f"{stage_plan.stage.name}: dropped a required residual")
        for lane in stage_plan.residuals:
            if is_forbidden(lane, plan.pipeline):
                raise AssertionError(f"{stage_plan.stage.name}: selected forbidden lane {lane}")

        omitted_below_two = [
            lane
            for lane in stage_plan.omitted_candidates
            if stage_plan.usage_after_required.get(lane, 0) < 2
        ]
        selected_at_two = [
            lane
            for lane in stage_plan.optional_selected
            if stage_plan.usage_after_required.get(lane, 0) >= 2
        ]
        if omitted_below_two and selected_at_two:
            raise AssertionError(
                f"{stage_plan.stage.name}: selected {selected_at_two} at two uses while "
                f"leaving {omitted_below_two} below two"
            )


def self_test() -> None:
    for count in range(MAX_RESIDUALS + 1):
        expected = f"SixPass{NUMBER_WORDS[count]}ResidualSlices"
        if factory_name(count) != expected:
            raise AssertionError(f"missing SixPass factory mapping for {count} residuals")

    twist = plan_pipeline(twist_pipeline())
    seed = plan_pipeline(seed_pipeline())
    verify_plan(twist)
    verify_plan(seed)

    twist_by_name = {stage.stage.name: stage for stage in twist.stages}
    if len(twist_by_name["GTwistRunTwist_B"].residuals) != 5:
        raise AssertionError("Twist B should exercise SixPassFiveResidualSlices")
    if len(twist_by_name["GTwistRunTwist_C"].residuals) != 9:
        raise AssertionError("Twist C should exercise SixPassNineResidualSlices")
    if any(lane_family(lane) == "expansion" for lane in twist.final_usage):
        raise AssertionError("Twist must never use Expansion residuals")

    if not any(stage.stage.name == "GSeedRunSeed_I" for stage in seed.stages):
        raise AssertionError("Seed planning must cover GSeedRunSeed A through I")


def make_parser() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "--pipeline",
        choices=("twist", "seed", "all"),
        default="twist",
        help="pipeline profile to plan (default: twist)",
    )
    parser.add_argument(
        "--format",
        choices=("human", "json", "cpp"),
        default="human",
        help="output format (default: human)",
    )
    parser.add_argument(
        "--require",
        action="append",
        default=[],
        metavar="STAGE=LANES",
        help="require comma-separated source,key_a,key_b,snow for one stage",
    )
    parser.add_argument(
        "--optional",
        action="append",
        default=[],
        metavar="STAGE=LANES",
        help="make comma-separated special lanes optional for one stage",
    )
    parser.add_argument(
        "--max",
        action="append",
        default=[],
        metavar="STAGE=N",
        help="set one stage's maximum residual count (0 through 12)",
    )
    parser.add_argument(
        "--max-all",
        type=int,
        help="override every non-starter stage maximum (0 through 12)",
    )
    parser.add_argument(
        "--self-test",
        action="store_true",
        help="verify both built-in profiles and exit",
    )
    return parser


def main(argv: Sequence[str] | None = None) -> int:
    parser = make_parser()
    args = parser.parse_args(argv)

    try:
        if args.self_test:
            self_test()
            print("lane_calc.py: self-test passed")
            return 0

        profiles = {
            "twist": (twist_pipeline(),),
            "seed": (seed_pipeline(),),
            "all": (twist_pipeline(), seed_pipeline()),
        }
        pipelines = apply_overrides(
            profiles[args.pipeline],
            require_overrides=args.require,
            optional_overrides=args.optional,
            max_overrides=args.max,
            max_all=args.max_all,
        )
        plans = tuple(plan_pipeline(pipeline) for pipeline in pipelines)
        for plan in plans:
            verify_plan(plan)

        renderer = {
            "human": render_human,
            "cpp": render_cpp,
        }.get(args.format)
        if args.format == "json":
            payloads = [json.loads(render_json(plan)) for plan in plans]
            print(json.dumps(payloads[0] if len(payloads) == 1 else payloads,
                             indent=2,
                             sort_keys=True))
        else:
            assert renderer is not None
            print("\n\n".join(renderer(plan) for plan in plans))
        return 0
    except (AssertionError, KeyError, ValueError) as error:
        print(f"lane_calc.py: error: {error}", file=sys.stderr)
        return 1


if __name__ == "__main__":
    raise SystemExit(main())
