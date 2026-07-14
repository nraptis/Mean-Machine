#!/usr/bin/env python3

from dataclasses import dataclass
from itertools import product


@dataclass(frozen=True)
class Slice:
    ingress: tuple[str, ...]
    cross: tuple[str, ...]
    dest: str
    inverted: bool
    ingress_last_locked: bool = False
    cross_last_locked: bool = False


@dataclass
class Config:
    name: str
    batch: str
    primary_sources: tuple[str, ...]
    expected_destinations: tuple[str, ...]
    slices: tuple[Slice, ...]
    residual_sources: tuple[str, ...] = ()
    max_context_sources: int = 4
    bind_duplicate_source_slots: bool = False
    special_twelve_pass: bool = False
    validate_primary_combos: bool = True
    warmup_destination_count: int = 0
    validate_chained_destinations: bool = True


def forced_forward(item: str, stage_slice: Slice) -> bool:
    forced = stage_slice.ingress if stage_slice.ingress_last_locked else stage_slice.ingress[:-1]
    return item in forced


def forced_backward(item: str, stage_slice: Slice) -> bool:
    forced = stage_slice.cross if stage_slice.cross_last_locked else stage_slice.cross[:-1]
    return item in forced


def append_unique(items: list[str], item: str) -> None:
    if item not in items:
        items.append(item)


def external_sources(config: Config) -> set[str]:
    result: list[str] = []
    written_destinations: list[str] = []
    for stage_slice in config.slices:
        for item in stage_slice.ingress + stage_slice.cross:
            if item not in written_destinations:
                append_unique(result, item)
        if stage_slice.dest in config.expected_destinations:
            append_unique(written_destinations, stage_slice.dest)
    return set(result)


def validate(config: Config) -> list[str]:
    errors: list[str] = []

    if len(config.slices) != len(config.expected_destinations):
        errors.append("destination count did not match slice count")

    for index, stage_slice in enumerate(config.slices):
        prefix = f"{config.name} {config.batch} slice {index + 1} (slice index = {index})"
        if not (2 <= len(stage_slice.ingress) <= config.max_context_sources):
            errors.append(f"{prefix} ingress source count outside allowed range")
        if not (2 <= len(stage_slice.cross) <= config.max_context_sources):
            errors.append(f"{prefix} cross source count outside allowed range")
        if index < len(config.expected_destinations) and stage_slice.dest != config.expected_destinations[index]:
            errors.append(f"{prefix} destination did not match expected destination order")
        if stage_slice.inverted != ((index % 2) == 1):
            errors.append(f"{prefix} inverted flag did not alternate false/true")

    five_wide_ingress_count = sum(1 for stage_slice in config.slices if len(stage_slice.ingress) > 4)
    five_wide_cross_count = sum(1 for stage_slice in config.slices if len(stage_slice.cross) > 4)
    if config.special_twelve_pass:
        if len(config.slices) != 12:
            errors.append(f"{config.name} special twelve-pass loop did not have 12 slices")
        if five_wide_ingress_count > 1:
            errors.append(f"{config.name} special twelve-pass loop used more than one five-wide ingress")
        if five_wide_cross_count > 1:
            errors.append(f"{config.name} special twelve-pass loop used more than one five-wide cross")
    elif five_wide_ingress_count > 0 or five_wide_cross_count > 0:
        errors.append(f"{config.name} used five-wide sources without special twelve-pass validation")

    expected_external_sources = set(config.primary_sources + config.residual_sources)
    actual_external_sources = external_sources(config)
    if actual_external_sources != expected_external_sources:
        errors.append(f"{config.name} external source set mismatch: actual {sorted(actual_external_sources)}, expected {sorted(expected_external_sources)}")

    available: list[str] = []
    for item in config.primary_sources + config.residual_sources:
        append_unique(available, item)
    for index, stage_slice in enumerate(config.slices):
        prefix = f"{config.name} {config.batch} slice {index + 1} (slice index = {index})"
        for item in stage_slice.ingress + stage_slice.cross:
            if item not in available:
                errors.append(f"{prefix} read {item} before it was available")

        if len(available) < 2:
            errors.append(f"{prefix} source graph requires at least 2 available sources")
        elif len(available) == 2:
            if not (len(stage_slice.ingress) == 2 and
                    len(stage_slice.cross) == 2 and
                    stage_slice.cross[0] == stage_slice.ingress[1] and
                    stage_slice.cross[1] == stage_slice.ingress[0]):
                errors.append(f"{prefix} source graph with 2 available sources must use ingress [a, b], cross [b, a]")
        elif len(available) == 3:
            if not (len(stage_slice.ingress) == 2 and
                    len(stage_slice.cross) == 2 and
                    stage_slice.cross[0] == stage_slice.ingress[0] and
                    stage_slice.cross[1] not in stage_slice.ingress):
                errors.append(f"{prefix} source graph with 3 available sources must use ingress [a, b], cross [a, c]")
        else:
            seen = set()
            for item in stage_slice.ingress + stage_slice.cross:
                if item in seen:
                    errors.append(f"{prefix} source graph used a duplicate source with 4 or more available sources")
                    break
                seen.add(item)

        if stage_slice.dest not in available:
            available.append(stage_slice.dest)

    if config.validate_chained_destinations:
        for index in range(1, len(config.slices)):
            prefix = f"{config.name} {config.batch} slice {index + 1} (slice index = {index})"
            previous_dest = config.slices[index - 1].dest
            if config.slices[index].ingress[0] != previous_dest:
                errors.append(f"{prefix} did not use previous dest as first source")
            if not forced_forward(previous_dest, config.slices[index]):
                errors.append(f"{prefix} did not force previous dest forward")

    residual_index = 0
    for index, stage_slice in enumerate(config.slices):
        prefix = f"{config.name} {config.batch} slice {index + 1} (slice index = {index})"
        remaining_residuals = len(config.residual_sources) - residual_index
        remaining_slices = len(config.slices) - index
        should_use_cross_residual = remaining_residuals > remaining_slices
        should_use_ingress_residual = remaining_residuals > 0

        if should_use_ingress_residual:
            expected = config.residual_sources[residual_index]
            if stage_slice.ingress[-1] != expected:
                errors.append(f"{prefix} residual graph expected ingress random source {expected}")
            residual_index += 1
        elif stage_slice.ingress[-1] in config.residual_sources:
            errors.append(f"{prefix} residual graph used ingress residual after residuals were consumed")

        if should_use_cross_residual:
            expected = config.residual_sources[residual_index]
            if stage_slice.cross[-1] != expected:
                errors.append(f"{prefix} residual graph expected cross random source {expected}")
            residual_index += 1
        elif stage_slice.cross[-1] in config.residual_sources:
            errors.append(f"{prefix} residual graph used unexpected cross residual")

    if config.validate_chained_destinations:
        for index, stage_slice in enumerate(config.slices):
            prefix = f"{config.name} {config.batch} slice {index + 1} (slice index = {index})"
            if index < config.warmup_destination_count:
                continue

            use_count = 0
            has_forward = False
            has_backward = False
            for later_slice in config.slices[index + 1:]:
                if stage_slice.dest in later_slice.ingress:
                    use_count += 1
                    has_forward = has_forward or forced_forward(stage_slice.dest, later_slice)
                if stage_slice.dest in later_slice.cross:
                    use_count += 1
                    has_backward = has_backward or forced_backward(stage_slice.dest, later_slice)
            required_use_count = min(len(config.slices) - index - 1, 3)
            if index == len(config.slices) - 1:
                if use_count != 0:
                    errors.append(f"{prefix} final destination had a future use")
            elif use_count < required_use_count:
                errors.append(f"{prefix} destination had {use_count} future uses, expected {required_use_count}")
            elif required_use_count == 1 and not has_forward:
                errors.append(f"{prefix} destination was used once but not forced forward")
            elif required_use_count >= 2 and not (has_forward and has_backward):
                errors.append(f"{prefix} destination lacked forward/backward coverage")

    if not config.bind_duplicate_source_slots:
        for index, stage_slice in enumerate(config.slices):
            prefix = f"{config.name} {config.batch} slice {index + 1} (slice index = {index})"
            if len(set(stage_slice.ingress)) != len(stage_slice.ingress):
                errors.append(f"{prefix} duplicated an ingress source")
            if len(set(stage_slice.cross)) != len(stage_slice.cross):
                errors.append(f"{prefix} duplicated a cross source")

    if config.validate_primary_combos:
        if config.name in ("GSeedRunSeed_A", "GTwistRunTwist_A"):
            expected_combos = (
                (True, True, False),
                (True, False, True),
                (False, True, False),
                (False, False, True),
            )
        else:
            expected_combos = list(product((True, False), repeat=len(config.primary_sources)))
        for combo in expected_combos:
            found = False
            for stage_slice in config.slices:
                ok = True
                for item, is_forward in zip(config.primary_sources, combo):
                    ok = ok and (forced_forward(item, stage_slice) if is_forward else forced_backward(item, stage_slice))
                found = found or ok
            if not found:
                bits = "".join("F" if value else "B" for value in combo)
                errors.append(f"{config.name} missing primary direction combo {bits}")

    if not config.validate_primary_combos:
        for primary_source in config.primary_sources:
            use_count = 0
            has_forced_forward = False
            has_forced_backward = False
            for stage_slice in config.slices:
                use_count += stage_slice.ingress.count(primary_source)
                use_count += stage_slice.cross.count(primary_source)
                has_forced_forward = has_forced_forward or forced_forward(primary_source, stage_slice)
                has_forced_backward = has_forced_backward or forced_backward(primary_source, stage_slice)
            if not has_forced_forward:
                errors.append(f"{config.name} primary source {primary_source} was never forced-forward")
            if not has_forced_backward:
                errors.append(f"{config.name} primary source {primary_source} was never forced-backward")
            if use_count > 4:
                errors.append(f"{config.name} primary source {primary_source} was used more than 4 times: {use_count}")

    return errors


FIRE = ("fire_a", "fire_b", "fire_c", "fire_d")
WORK = ("work_a", "work_b", "work_c", "work_d")
EXPAND = ("expand_a", "expand_b", "expand_c", "expand_d")
OPERATION = ("operation_a", "operation_b", "operation_c", "operation_d")
SNOW = ("snow_a", "snow_b", "snow_c", "snow_d")
INVEST = ("invest_a", "invest_b", "invest_c", "invest_d")
EARTH = ("earth_a", "earth_b", "earth_c", "earth_d")
WATER = ("water_a", "water_b", "water_c", "water_d")
FUSE = ("fuse_a", "fuse_b", "fuse_c", "fuse_d")
KEY_SOURCE = ("key_a", "key_b", "source")
SOURCE_SNOW = ("source", "snow")


def starter_key_source_fire_slices() -> tuple[Slice, ...]:
    return (
        Slice(("key_a", "key_b"),
              ("key_a", "source"), "fire_a", False),
        Slice(("fire_a", "key_a"),
              ("key_b", "source"), "fire_b", True),
        Slice(("fire_b", "key_b"),
              ("key_a", "source", "fire_a"), "fire_c", False),
        Slice(("fire_c", "key_b", "source", "fire_a"),
              ("key_a", "fire_b"), "fire_d", True),
        Slice(("fire_d", "key_a", "key_b", "source", "fire_b"),
              ("fire_a", "fire_c"), "work_a", False),
        Slice(("work_a", "fire_c"),
              ("key_a", "key_b", "source", "fire_b", "fire_a"), "work_b", True),
        Slice(("work_b", "key_a", "source", "fire_a"),
              ("key_b", "fire_d", "work_a"), "work_c", False),
        Slice(("work_c", "source", "work_a", "fire_a"),
              ("key_a", "key_b", "work_b", "fire_b"), "work_d", True),
        Slice(("work_d", "key_a", "key_b", "work_c"),
              ("source", "work_a", "fire_c", "fire_d"), "expand_a", False),
        Slice(("expand_a", "key_a", "work_d", "work_b"),
              ("key_b", "source", "work_c", "fire_d"), "expand_b", True),
        Slice(("expand_b", "work_d", "key_b", "work_c"),
              ("key_a", "source", "expand_a", "work_b"), "expand_c", False),
        Slice(("expand_c", "key_a"),
              ("work_d", "expand_a", "expand_b", "key_b"), "expand_d", True),
    )


def seed_a_starter_slices() -> tuple[Slice, ...]:
    return (
        Slice(("source", "key_a"),
              ("source", "key_b"), "water_a", False, True, True),
        Slice(("water_a", "key_b"),
              ("source", "key_a"), "water_b", True, True, True),
        Slice(("water_b", "source", "key_b"),
              ("key_a", "water_a"), "expand_a", False, True, False),
        Slice(("expand_a", "water_a"),
              ("water_b", "key_b"), "expand_b", True),
        Slice(("expand_b", "water_b"),
              ("expand_a", "key_a"), "expand_c", False),
        Slice(("expand_c", "expand_a"),
              ("expand_b", "water_b"), "expand_d", True),
    )


def starter_source_snow_fire_slices() -> tuple[Slice, ...]:
    return (
        Slice(("source", "snow"),
              ("snow", "source"), "fire_a", False),
        Slice(("fire_a", "snow"),
              ("fire_a", "source"), "fire_b", True),
        Slice(("fire_b", "snow"),
              ("source", "fire_a"), "fire_c", False),
        Slice(("fire_c", "fire_b"),
              ("source", "snow", "fire_a"), "fire_d", True),
        Slice(("fire_d", "source", "snow", "fire_a"),
              ("fire_c", "fire_b"), "work_a", False),
        Slice(("work_a", "snow", "fire_c"),
              ("fire_d", "source", "fire_b", "fire_a"), "work_b", True),
        Slice(("work_b", "source", "fire_d"),
              ("snow", "work_a", "fire_c", "fire_b"), "work_c", False),
        Slice(("work_c", "snow", "work_a"),
              ("source", "work_b", "fire_d", "fire_c"), "work_d", True),
        Slice(("work_d", "source", "snow", "work_c"),
              ("work_a", "fire_d", "fire_b", "fire_a"), "expand_a", False),
        Slice(("expand_a", "snow", "work_d", "work_b"),
              ("source", "work_c", "fire_d", "fire_a"), "expand_b", True),
        Slice(("expand_b", "work_d", "source", "work_c"),
              ("snow", "expand_a", "work_b", "fire_b"), "expand_c", False),
        Slice(("expand_c", "snow"),
              ("work_d", "expand_a", "expand_b", "source"), "expand_d", True),
    )


def kdf_a_a_warmup_slices() -> tuple[Slice, ...]:
    return (
        Slice(("source", "snow"),
              ("snow", "source"), "fire_a", False),
        Slice(("fire_a", "snow"),
              ("fire_a", "source"), "fire_b", True),
        Slice(("fire_b", "source"),
              ("fire_a", "snow"), "expand_a", False),
        Slice(("expand_a", "snow", "fire_a"),
              ("source", "fire_b"), "expand_b", True),
        Slice(("expand_b", "source", "snow", "fire_a"),
              ("expand_a", "fire_b"), "expand_c", False),
        Slice(("expand_c", "expand_a", "fire_a"),
              ("expand_b", "source", "snow", "fire_b"), "expand_d", True),
    )


def kdf_a_b_warmup_slices() -> tuple[Slice, ...]:
    return (
        Slice(("expand_a", "expand_b"),
              ("expand_c", "expand_d"), "fire_c", False),
        Slice(("fire_c", "expand_b", "expand_c"),
              ("expand_a", "expand_d"), "fire_d", True),
        Slice(("fire_d", "expand_d", "expand_c"),
              ("expand_b", "fire_c"), "operation_a", False),
        Slice(("operation_a", "expand_c", "fire_c"),
              ("expand_d", "fire_d"), "operation_b", True),
        Slice(("operation_b", "fire_d"),
              ("operation_a", "expand_a"), "operation_c", False),
        Slice(("operation_c", "operation_a"),
              ("operation_b", "expand_b"), "operation_d", True),
    )


def kdf_b_a_operation_residual_slices() -> tuple[Slice, ...]:
    return (
        Slice(("work_a", "work_b", "operation_a"),
              ("work_c", "work_d"), "fire_a", False),
        Slice(("fire_a", "work_c", "operation_b"),
              ("work_a", "work_d", "work_b"), "fire_b", True),
        Slice(("fire_b", "work_d", "operation_c"),
              ("work_b", "fire_a"), "expand_a", False),
        Slice(("expand_a", "work_c", "operation_d"),
              ("fire_b", "work_d"), "expand_b", True),
        Slice(("expand_b", "fire_b"),
              ("expand_a", "work_a"), "expand_c", False),
        Slice(("expand_c", "expand_a"),
              ("expand_b", "work_b"), "expand_d", True),
    )


def four_pass_slices(primary: tuple[str, ...],
                     residuals: tuple[str, ...],
                     destinations: tuple[str, ...]) -> tuple[Slice, ...]:
    p = primary
    r = residuals
    d = destinations
    return (
        Slice((p[0], p[1], r[0]),
              (p[2], p[3], r[1]), d[0], False),
        Slice((d[0], p[2], p[3], r[2]),
              (p[0], p[1], r[3]), d[1], True),
        Slice((d[1], p[0], p[1], r[4]),
              (d[0], p[2], r[5]), d[2], False),
        Slice((d[2], d[0], p[3], r[6]),
              (d[1], p[1], r[7]), d[3], True),
    )


def six_pass_slices(primary: tuple[str, ...],
                    residuals: tuple[str, ...],
                    destinations: tuple[str, ...]) -> tuple[Slice, ...]:
    p = primary
    r = residuals
    d = destinations
    return (
        Slice((p[0], p[1], r[0]),
              (p[2], p[3], r[1]), d[0], False),
        Slice((d[0], p[2], p[3], r[2]),
              (p[0], p[1], r[3]), d[1], True),
        Slice((d[1], p[0], r[4]),
              (d[0], p[2]), d[2], False),
        Slice((d[2], d[0], r[5]),
              (d[1], p[3]), d[3], True),
        Slice((d[3], d[1], r[6]),
              (d[2], d[0]), d[4], False),
        Slice((d[4], d[2], r[7]),
              (d[3], p[1]), d[5], True),
    )


def six_pass_no_residual_slices(primary: tuple[str, ...],
                                destinations: tuple[str, ...]) -> tuple[Slice, ...]:
    p = primary
    d = destinations
    return (
        Slice((p[0], p[1]),
              (p[2], p[3]), d[0], False, True, True),
        Slice((d[0], p[2], p[3]),
              (p[0], p[1]), d[1], True, True, True),
        Slice((d[1], p[0]),
              (d[0], p[2]), d[2], False),
        Slice((d[2], d[0]),
              (d[1], p[3]), d[3], True),
        Slice((d[3], d[1]),
              (d[2], p[0]), d[4], False),
        Slice((d[4], d[2]),
              (d[3], p[1]), d[5], True),
    )


def six_pass_recent_residual_slices(primary: tuple[str, ...],
                                    residuals: tuple[str, ...],
                                    destinations: tuple[str, ...]) -> tuple[Slice, ...]:
    p = primary
    r = residuals
    d = destinations
    return (
        Slice((p[0], p[1], r[0]),
              (p[2], p[3]), d[0], False),
        Slice((d[0], p[2], r[1]),
              (p[0], p[3]), d[1], True),
        Slice((d[1], p[3], r[2]),
              (d[0], p[1], p[0]), d[2], False),
        Slice((d[2], d[0], r[3]),
              (d[1], p[3], p[2]), d[3], True),
        Slice((d[3], d[2], p[1]),
              (p[2], d[0], d[1]), d[4], False),
        Slice((d[4], p[0], p[1]),
              (d[3], d[2], d[1]), d[5], True),
    )


def six_pass_terminal_slices(primary: tuple[str, ...],
                             residuals: tuple[str, ...],
                             destinations: tuple[str, ...]) -> tuple[Slice, ...]:
    p = primary
    r = residuals
    d = destinations
    return (
        Slice((p[0], r[0]),
              (p[1], r[1]), d[0], False),
        Slice((p[2], r[2]),
              (p[3], r[3]), d[1], True),
        Slice((p[1], r[4]),
              (p[0], p[2]), d[2], False),
        Slice((p[3], r[5]),
              (p[1], p[0]), d[3], True),
        Slice((p[0], r[6]),
              (p[2], p[3]), d[4], False),
        Slice((p[2], r[7]),
              (p[3], p[1]), d[5], True),
    )


def eight_pass_slices(primary: tuple[str, ...],
                      residuals: tuple[str, ...],
                      destinations: tuple[str, ...]) -> tuple[Slice, ...]:
    p = primary
    r = residuals
    d = destinations
    return (
        Slice((p[3], p[2], r[0]),
              (p[1], p[0]), d[0], False),
        Slice((d[0], p[3], r[1]),
              (p[2], p[1], p[0]), d[1], True),
        Slice((d[1], p[3], r[2]),
              (d[0], p[2], p[1], p[0]), d[2], False),
        Slice((d[2], p[3], d[0], r[3]),
              (d[1], p[2], p[1], p[0]), d[3], True),
        Slice((d[3], d[0], r[4]),
              (d[2], d[1], p[2], p[1]), d[4], False),
        Slice((d[4], d[2], r[5]),
              (d[3], d[1], p[2], p[0]), d[5], True),
        Slice((d[5], d[3], r[6]),
              (d[4], d[2], p[3], p[1]), d[6], False),
        Slice((d[6], d[4], r[7]),
              (d[5], d[3], p[2], p[0]), d[7], True),
    )


def midstage_config(name: str,
                    batch: str,
                    primary: tuple[str, ...],
                    residuals: tuple[str, ...],
                    destinations: tuple[str, ...],
                    slices: tuple[Slice, ...],
                    warmup_destination_count: int = 0,
                    validate_chained_destinations: bool = True) -> Config:
    return Config(
        name=name,
        batch=batch,
        primary_sources=primary,
        residual_sources=residuals,
        expected_destinations=destinations,
        validate_primary_combos=False,
        warmup_destination_count=warmup_destination_count,
        validate_chained_destinations=validate_chained_destinations,
        slices=slices,
    )


def twist_a_config() -> Config:
    return Config(
        name="GTwistRunTwist_A",
        batch="twist_loop_a",
        primary_sources=("source", "key_a", "key_b"),
        expected_destinations=("water_a", "water_b") + EXPAND,
        warmup_destination_count=2,
        slices=seed_a_starter_slices(),
    )


def twist_b_config() -> Config:
    return midstage_config(
        name="GTwistRunTwist_B",
        batch="twist_loop_b",
        primary=EXPAND,
        residuals=FIRE + WORK,
        destinations=OPERATION,
        slices=four_pass_slices(EXPAND, FIRE + WORK, OPERATION),
    )


def twist_c_config() -> Config:
    return midstage_config(
        name="GTwistRunTwist_C",
        batch="twist_loop_c",
        primary=OPERATION,
        residuals=FIRE + EXPAND,
        destinations=WORK,
        slices=four_pass_slices(OPERATION, FIRE + EXPAND, WORK),
    )


def kdf_a_a_config() -> Config:
    return Config(
        name="GSeedRunKDF_A_A",
        batch="kdf_a_loop_a",
        primary_sources=SOURCE_SNOW,
        expected_destinations=("fire_a", "fire_b") + EXPAND,
        warmup_destination_count=2,
        slices=kdf_a_a_warmup_slices(),
    )


def seed_a_config() -> Config:
    return Config(
        name="GSeedRunSeed_A",
        batch="seed_loop_a",
        primary_sources=("source", "key_a", "key_b"),
        expected_destinations=("water_a", "water_b") + EXPAND,
        warmup_destination_count=2,
        slices=seed_a_starter_slices(),
    )


def seed_b_config() -> Config:
    return midstage_config(
        name="GSeedRunSeed_B",
        batch="seed_loop_a",
        primary=EXPAND,
        residuals=(),
        destinations=WORK + ("earth_a", "earth_b"),
        slices=six_pass_no_residual_slices(EXPAND, WORK + ("earth_a", "earth_b")),
    )


def seed_c_config() -> Config:
    return midstage_config(
        name="GSeedRunSeed_C",
        batch="seed_loop_b",
        primary=("work_c", "work_d", "earth_a", "earth_b"),
        residuals=("work_a", "work_b", "expand_c", "expand_d"),
        destinations=("earth_c", "earth_d") + OPERATION,
        slices=six_pass_recent_residual_slices(
            ("work_c", "work_d", "earth_a", "earth_b"),
            ("work_a", "work_b", "expand_c", "expand_d"),
            ("earth_c", "earth_d") + OPERATION,
        ),
    )


def seed_d_config() -> Config:
    return midstage_config(
        name="GSeedRunSeed_D",
        batch="seed_loop_b",
        primary=OPERATION,
        residuals=WORK + ("earth_a", "earth_b") + ("expand_a", "expand_b"),
        destinations=("snow_a", "snow_b") + FUSE,
        slices=six_pass_terminal_slices(
            OPERATION,
            WORK + ("earth_a", "earth_b") + ("expand_a", "expand_b"),
            ("snow_a", "snow_b") + FUSE,
        ),
        validate_chained_destinations=False,
    )


def seed_e_config() -> Config:
    return midstage_config(
        name="GSeedRunSeed_E",
        batch="seed_loop_c",
        primary=FIRE,
        residuals=("snow_a", "snow_b", "work_c", "work_d", "earth_a", "earth_b", "water_a", "water_b"),
        destinations=("invest_a", "invest_b") + EXPAND,
        slices=six_pass_slices(
            FIRE,
            ("snow_a", "snow_b", "work_c", "work_d", "earth_a", "earth_b", "water_a", "water_b"),
            ("invest_a", "invest_b") + EXPAND,
        ),
    )


def seed_f_config() -> Config:
    return midstage_config(
        name="GSeedRunSeed_F",
        batch="seed_loop_c",
        primary=EXPAND,
        residuals=("snow_a", "snow_b", "invest_a", "invest_b", "earth_c", "earth_d", "fire_a", "fire_b"),
        destinations=("work_a", "work_b", "snow_c", "snow_d", "work_c", "work_d"),
        slices=six_pass_slices(
            EXPAND,
            ("snow_a", "snow_b", "invest_a", "invest_b", "earth_c", "earth_d", "fire_a", "fire_b"),
            ("work_a", "work_b", "snow_c", "snow_d", "work_c", "work_d"),
        ),
    )


def seed_g_config() -> Config:
    return midstage_config(
        name="GSeedRunSeed_G",
        batch="seed_loop_d",
        primary=WORK,
        residuals=("snow_a", "snow_c", "earth_b", "earth_d", "expand_a", "expand_c", "fire_b", "fire_d"),
        destinations=("operation_a", "operation_b", "invest_c", "invest_d", "operation_c", "operation_d"),
        slices=six_pass_slices(
            WORK,
            ("snow_a", "snow_c", "earth_b", "earth_d", "expand_a", "expand_c", "fire_b", "fire_d"),
            ("operation_a", "operation_b", "invest_c", "invest_d", "operation_c", "operation_d"),
        ),
    )


def kdf_a_c_config() -> Config:
    return midstage_config(
        name="GSeedRunKDF_A_C",
        batch="kdf_a_loop_c",
        primary=OPERATION,
        residuals=FIRE + EXPAND,
        destinations=WORK,
        slices=four_pass_slices(OPERATION, FIRE + EXPAND, WORK),
    )


def kdf_a_b_config() -> Config:
    return midstage_config(
        name="GSeedRunKDF_A_B",
        batch="kdf_a_loop_b",
        primary=EXPAND,
        residuals=(),
        destinations=("fire_c", "fire_d") + OPERATION,
        slices=kdf_a_b_warmup_slices(),
        warmup_destination_count=2,
    )


def kdf_a_d_config() -> Config:
    return midstage_config(
        name="GSeedRunKDF_A_D",
        batch="kdf_a_loop_d",
        primary=EXPAND,
        residuals=FIRE + OPERATION,
        destinations=WORK,
        slices=four_pass_slices(EXPAND, FIRE + OPERATION, WORK),
    )


def kdf_b_a_config() -> Config:
    return midstage_config(
        name="GSeedRunKDF_B_A",
        batch="kdf_b_loop_a",
        primary=WORK,
        residuals=OPERATION,
        destinations=("fire_a", "fire_b") + EXPAND,
        slices=kdf_b_a_operation_residual_slices(),
        warmup_destination_count=2,
    )


def kdf_b_b_config() -> Config:
    return midstage_config(
        name="GSeedRunKDF_B_B",
        batch="kdf_b_loop_b",
        primary=EXPAND,
        residuals=FIRE + WORK,
        destinations=OPERATION,
        slices=four_pass_slices(EXPAND, FIRE + WORK, OPERATION),
    )


def kdf_b_c_config() -> Config:
    return midstage_config(
        name="GSeedRunKDF_B_C",
        batch="kdf_b_loop_c",
        primary=OPERATION,
        residuals=FIRE + WORK,
        destinations=EXPAND,
        slices=four_pass_slices(OPERATION, FIRE + WORK, EXPAND),
    )


def kdf_b_d_config() -> Config:
    return midstage_config(
        name="GSeedRunKDF_B_D",
        batch="kdf_b_loop_d",
        primary=WORK,
        residuals=FIRE + OPERATION,
        destinations=EXPAND,
        slices=four_pass_slices(WORK, FIRE + OPERATION, EXPAND),
    )


def main() -> int:
    for config in (kdf_a_a_config(), seed_a_config(), seed_b_config(), seed_c_config(),
                   seed_d_config(), seed_e_config(), seed_f_config(), seed_g_config(),
                   kdf_a_b_config(), kdf_a_c_config(), kdf_a_d_config(),
                   kdf_b_a_config(), kdf_b_b_config(), kdf_b_c_config(), kdf_b_d_config(),
                   twist_a_config(), twist_b_config(), twist_c_config()):
        errors = validate(config)
        if errors:
            print(f"{config.name}: FAIL")
            for error in errors:
                print(f"  {error}")
            return 1
        print(f"{config.name}: OK")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
