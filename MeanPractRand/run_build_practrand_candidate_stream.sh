#!/bin/bash

set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "${ROOT_DIR}"

MEANMACHINE_ROOT="${MEANMACHINE_ROOT:-/Users/magneto/Desktop/Codex Playground/MeanMachine}"
TWIST_LIB_DIR="${MEANMACHINE_ROOT}/MeanMachine/Library - Twist"
CANDIDATE_DIR="${MEANMACHINE_ROOT}/CornTesting/Gen"

INPUT_CPP="${INPUT_CPP:-${CANDIDATE_DIR}/TwistExpander_PractRandCandidate.cpp}"
OUTPUT_BIN="${OUTPUT_BIN:-${ROOT_DIR}/build/mean_practrand_stream}"
CXXFLAGS_EXTRA="${CXXFLAGS_EXTRA:--O3 -DNDEBUG}"

if [[ ! -f "${INPUT_CPP}" ]]; then
  echo "missing candidate source: ${INPUT_CPP}" >&2
  exit 1
fi

mkdir -p "$(dirname "${OUTPUT_BIN}")"

# shellcheck disable=SC2086
clang++ -std=c++20 ${CXXFLAGS_EXTRA} \
  -I"${TWIST_LIB_DIR}" \
  -I"${CANDIDATE_DIR}" \
  "${ROOT_DIR}/src/MeanPractRandStream.cpp" \
  "${TWIST_LIB_DIR}/TwistCryptoGenerator.cpp" \
  "${TWIST_LIB_DIR}/TwistCryptoScoring.cpp" \
  "${TWIST_LIB_DIR}/TwistExpander.cpp" \
  "${TWIST_LIB_DIR}/TwistFastMatrix.cpp" \
  "${TWIST_LIB_DIR}/TwistMasking.cpp" \
  "${TWIST_LIB_DIR}/TwistMix64.cpp" \
  "${TWIST_LIB_DIR}/TwistSelect.cpp" \
  "${TWIST_LIB_DIR}/TwistSnow.cpp" \
  "${TWIST_LIB_DIR}/TwistWorkSpace.cpp" \
  "${INPUT_CPP}" \
  -o "${OUTPUT_BIN}"

echo "built ${OUTPUT_BIN}"
