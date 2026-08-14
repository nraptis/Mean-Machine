# The 180 Eleven-Role Loop Cores

This file documents how the 180 cores stored in
`loop_core_patterns_11.bin` were chosen. The binary is the authoritative,
fixed asset. Core generation was intentionally removed after this batch was
selected; normal builds only load and validate the saved patterns.

## What a core represents

A core contains 11 ordered rounds. Each round is a triplet:

```text
{ lead, source, feedback }
```

The triplet fixes the variable roles in the ARX heart. In simplified form, it
describes this statement group:

```cpp
lead = lead + source;
feedback = feedback ^ lead;
feedback = RotL64(feedback * constant, rotation);
```

The core does not select the concrete constants, rotations, salts, nonce
words, or context inputs. It only specifies the structural flow between the
11 abstract roles A through K. Head and tail patterns supply other parts of a
complete loop recipe later.

## Candidate construction rules

The generator searched a reduced, canonical space of eleven-round patterns.
A candidate had to satisfy all of the following construction rules:

1. Every role A-K appears exactly once in the `lead` column.
2. Every role A-K appears exactly once in the `source` column.
3. Every role A-K appears exactly once in the `feedback` column.
4. Within each triplet, the three roles are spread around the cyclic
   eleven-role ring. The accepted circular-gap families are permutations of
   `{2, 4, 5}` and `{3, 3, 5}`. Thus every triplet contains a five-position
   hop and does not cluster all three roles together.
5. Patterns equivalent under a global renaming of A-K count as the same
   pattern. Canonicalization scans the pattern in row-major order and assigns
   A, B, C, and so on when a symbol is first encountered. For example,
   globally swapping the names A and D does not produce another core.

These rules generated `2,667,804` canonical candidates for the saved run.

## Immediate eligibility filters

Each candidate was interpreted as a directed information-flow graph. A
candidate entered the scored pool only when it passed the graph-level safety
filters used by the farmer:

- all 22 directed interactions supplied by the eleven triplets are distinct;
- the directed graph is strongly connected;
- the undirected projection has no articulation point;
- the undirected projection has no bridge;
- reciprocal edge pairs are absent;
- the three columns remain valid permutations of A-K.

`257,350` of the `2,667,804` evaluated candidates were eligible.

These are structural filters. They do not claim a cryptographic proof and do
not measure output bit balance or avalanche behavior.

## Structural ranking

Candidates were ranked by the following comparator. Earlier items have
priority when two records are compared:

1. **Eligibility** — an eligible record always outranks an ineligible record.
2. **Directed edges** — maximize distinct directed interactions; 22 is the
   maximum supplied by eleven two-edge triplets.
3. **Reciprocal edges** — minimize immediate two-way pair reuse.
4. **Strong connectivity** — prefer every role reaching every other role.
5. **Articulation points** — minimize single-role graph bottlenecks.
6. **Bridges** — minimize single-edge graph bottlenecks.
7. **Floor balance** — maximize
   `min(destination floor, source floor)`.
8. **Floor total** — maximize
   `destination floor + source floor`.
9. **Journey balance** — maximize
   `min(destination journey, source journey)`.
10. **Journey total** — maximize
    `destination journey + source journey`.
11. **Influence curve area** — maximize dependency growth accumulated across
    all rounds, rewarding earlier flow rather than only a strong final state.
12. **Final influence total** — maximize total dependency reach at the end of
    the core.
13. **Directed diameter** — minimize the longest shortest directed path.

If all score fields tie, the row-major core bytes provide a deterministic
lexicographic tie-break. Balancing destination and source behavior therefore
takes precedence over making one side exceptionally strong while leaving the
other side weaker.

The dependency simulation is deliberately structural: an update unions the
influence sets of the roles participating in that update and observes how
those sets propagate through the ordered rounds.

The top 180 records under this ordering were clipped into the final asset.
They are all different canonical structures, not merely relabelings of the
same structure.

## Recorded selection range

The binary header preserves the following comparator endpoints from the
selection run:

| Set | Edges | Reciprocal | Strong | Articulation | Bridges | Destination floor | Source floor | Destination journey | Source journey | Final total | Curve area | Diameter |
| --- | ---: | ---: | ---: | ---: | ---: | ---: | ---: | ---: | ---: | ---: | ---: | ---: |
| All evaluated, worst | 11 | 0 | 1 | 0 | 0 | 3 | 3 | 24 | 0 | 48 | 331 | 10 |
| All evaluated, best | 22 | 0 | 1 | 0 | 0 | 8 | 8 | 41 | 28 | 112 | 603 | 4 |
| Chosen worst | 22 | 0 | 1 | 0 | 0 | 6 | 6 | 33 | 33 | 95 | 540 | 4 |
| Chosen best | 22 | 0 | 1 | 0 | 0 | 8 | 8 | 41 | 28 | 112 | 603 | 4 |

The `worst` and `best` rows are complete records at the two ends of the
comparator, not independent per-column minima and maxima. For example, they do
not imply that every chosen core has diameter 4.

## Exhaustive rerun: score boundaries

The historical generator was rerun over all `2,667,804` candidates. It again
produced exactly `257,350` eligible candidates. A second analysis-only pass
retained rejected candidates as well so the very bottom of the complete
population could be inspected. Its temporary binaries were written outside
the project; `loop_core_patterns_11.bin` was not overwritten. The first 180
serialized records from the rerun matched the saved asset byte-for-byte.

The tables below are in the farmer's actual comparator order. `Rank` is
one-based. `DF`/`SF` are destination/source floor, `DJ`/`SJ` are
destination/source journey, and `Diam` is directed diameter.

### Top three of all 2,667,804 candidates

| Rank | Eligible | Edges | Recip | Strong | Artic | Bridges | DF | SF | DJ | SJ | Total | Curve | Diam |
| ---: | :---: | ---: | ---: | ---: | ---: | ---: | ---: | ---: | ---: | ---: | ---: | ---: | ---: |
| 1 | yes | 22 | 0 | 1 | 0 | 0 | 8 | 8 | 41 | 28 | 112 | 603 | 4 |
| 2 | yes | 22 | 0 | 1 | 0 | 0 | 8 | 8 | 31 | 28 | 112 | 604 | 4 |
| 3 | yes | 22 | 0 | 1 | 0 | 0 | 7 | 8 | 33 | 36 | 101 | 531 | 5 |

### Bottom three of the selected 180

| Selected rank | Eligible rank | Edges | Recip | Strong | Artic | Bridges | DF | SF | DJ | SJ | Total | Curve | Diam |
| ---: | ---: | ---: | ---: | ---: | ---: | ---: | ---: | ---: | ---: | ---: | ---: | ---: | ---: |
| 178 | 178 | 22 | 0 | 1 | 0 | 0 | 6 | 6 | 35 | 33 | 94 | 502 | 4 |
| 179 | 179 | 22 | 0 | 1 | 0 | 0 | 6 | 6 | 35 | 33 | 93 | 500 | 4 |
| 180 | 180 | 22 | 0 | 1 | 0 | 0 | 6 | 6 | 33 | 33 | 95 | 540 | 4 |

### Best three eligible candidates not selected

There are `257,170` unselected eligible candidates: eligible ranks
181 through 257,350.

| Eligible rank | Edges | Recip | Strong | Artic | Bridges | DF | SF | DJ | SJ | Total | Curve | Diam |
| ---: | ---: | ---: | ---: | ---: | ---: | ---: | ---: | ---: | ---: | ---: | ---: | ---: |
| 181 | 22 | 0 | 1 | 0 | 0 | 6 | 6 | 45 | 32 | 95 | 556 | 4 |
| 182 | 22 | 0 | 1 | 0 | 0 | 6 | 6 | 41 | 32 | 99 | 553 | 4 |
| 183 | 22 | 0 | 1 | 0 | 0 | 6 | 6 | 39 | 32 | 95 | 532 | 5 |

### Worst three eligible candidates not selected

| Eligible rank | Edges | Recip | Strong | Artic | Bridges | DF | SF | DJ | SJ | Total | Curve | Diam |
| ---: | ---: | ---: | ---: | ---: | ---: | ---: | ---: | ---: | ---: | ---: | ---: | ---: |
| 257,348 | 22 | 0 | 1 | 0 | 0 | 4 | 4 | 24 | 16 | 69 | 401 | 5 |
| 257,349 | 22 | 0 | 1 | 0 | 0 | 4 | 4 | 23 | 16 | 68 | 427 | 4 |
| 257,350 | 22 | 0 | 1 | 0 | 0 | 4 | 4 | 23 | 16 | 69 | 414 | 4 |

### Bottom three of all 2,667,804 candidates

| Overall rank | Eligible | Edges | Recip | Strong | Artic | Bridges | DF | SF | DJ | SJ | Total | Curve | Diam |
| ---: | :---: | ---: | ---: | ---: | ---: | ---: | ---: | ---: | ---: | ---: | ---: | ---: | ---: |
| 2,667,802 | no | 14 | 0 | 1 | 0 | 0 | 3 | 3 | 23 | 0 | 59 | 363 | 7 |
| 2,667,803 | no | 11 | 0 | 1 | 0 | 0 | 3 | 3 | 26 | 0 | 52 | 347 | 10 |
| 2,667,804 | no | 11 | 0 | 1 | 0 | 0 | 3 | 3 | 24 | 0 | 48 | 331 | 10 |

## Why the final count is 180

The count is also the first dimension of the later recipe system:

```text
180 cores x 110 head/tail choices = 19,800 recipes
19,800 recipes / 33 expanders = 600 recipes per expander
```

The current exporter consumes 584 of those 600 recipes for each expander and
retains 16 as spares.

## Runtime validation

`LoopCorePatternFarmer::Load` verifies the binary header, version, exact file
size, role count, and the permutation rule for all three columns. The saved
scores and the first five patterns are printed when the asset is loaded.
