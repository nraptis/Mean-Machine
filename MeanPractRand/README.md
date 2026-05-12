# MeanPractRand

Standalone PractRand rig for the exported `TwistExpander_PractRandCandidate` from MeanMachine.

## Defaults
- Block size for `blk` size specs: `8192` bytes (`S_BLOCK`)
- Default run size: `32blk`
- Default retry delay for no-report/emitter failures: `1.5` seconds
- Default retry attempts: `3`

## Scripts
- `run_build_practrand_candidate_stream.sh`
  - Builds `build/mean_practrand_stream`
- `run_practrand_candidate_once.sh [password] [size_spec] [output_root]`
  - Single PractRand run with gate scoring
- `run_practrand_32blk_in_place.sh [password] [output_root]`
  - Convenience wrapper for one-password `32blk` runs
- `run_practrand_passwords_and_list.sh <password_file> [size_spec] [output_dir]`
  - AND-gauntlet over a password file
- `run_practrand_32blk_alphabet_gauntlet.sh [output_dir]`
  - a-z gauntlet at `32blk`

## Notes
- `PRACTRAND_BIN` can be set to override `RNG_test` path.
- Scripts fall back to `/Users/magneto/Desktop/Codex Playground/Twist/build/practrand/RNG_test` if needed.
