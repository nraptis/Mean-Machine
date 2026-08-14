# Loop Ascendency Farm

The Ascendency farm treats every `(heart, head slot)` pair as a separate,
resumable task. There are 180 hearts and 110 tasks per heart. A task keeps one
best-known tail and never depends on another task finishing first.

## Layout

Records use one-based loop names and zero-based heart names:

```text
Assets/loop_farm/heart_00/tier_0/loop_001.bin
Assets/loop_farm/heart_00/tier_1/loop_002.bin
Assets/loop_farm/heart_00/tier_2/loop_003.bin
Assets/loop_farm/heart_00/working/loop_004.bin
```

Each binary record stores its heart and head indices, cumulative raw attempt
count, best tail, all 50 current score fields, tier, format version, and score
schema version. The `working` tier preserves partial progress before a task
has cleared the Tier 2 floor.

Writes use a temporary sibling followed by an atomic rename. Promotion writes
the new tier first and removes the old tier copy afterward.

## Ladder

The 110 current production recipes for each heart establish that heart's fixed
reference distributions. The gates do not change as new candidates arrive.
All four direct integer measurements must pass the indicated heart-local
cutoff: minimum dual-tail reach, maximum ordered source-orphan area, maximum
single-orbiter ordered-pair damage, and minimum surviving fanout after one
orbiter is removed. Spectral estimates and static shortest-path-load scores
are deliberately excluded.

- Tier 0: best 5% side of all four heart-local reference distributions.
- Tier 1: best 20% side of all four distributions.
- Tier 2: better half of all four distributions.
- Working: best known valid loop, but it has not reached Tier 2.

“Tier 0” is the current max-stat farming target. It is not a proof of a
mathematical maximum or of cryptographic security. Heart-local thresholds are
important: a global threshold can make a heart permanently ineligible because
some measurements are partly constrained by the heart itself. Changing the
score schema bumps the binary version so stale records fail loudly instead of
being silently misread.

## Measured yield

The integer-only scorecard was checked on five heart/head pairs with 50 random
valid tails per pair. Every active measurement varied in all five samples.
Single-orbiter damage made the first ranking decision in all five; each of the
other measurements still resolved ties in two samples.

Two fresh-heart farms then tested Tier-0 feasibility. An early-stop run found
107 Tier-0 tasks out of 110 after 129,283 valid candidates. A full-budget run
tested 5,000 valid candidates for every task and finished with all 110 tasks at
Tier 0 after 550,000 valid candidates. The detailed reasoning and exact gates
are recorded in `ascendency_metric_cut_analysis.txt`.

## Running

From the command-line executable:

```text
--inventory-loop-ascendency11 [all|heart|first-last|comma-list]
--farm-loop-ascendency11 [hearts] [valid_candidates_per_task] [checkpoint_attempts] [skip_tier_0:0|1]
```

Examples:

```text
--farm-loop-ascendency11 0 1000 1000 1
--farm-loop-ascendency11 4,9,12-15 100000 10000 1
--inventory-loop-ascendency11 all
```

The same controls are grouped at the top of `AppDelegate.mm`. A farm run first
loads any saved record, otherwise seeds that task from the current production
tail asset. A saved Tier 0 task is skipped when `skip_tier_0` is enabled.
