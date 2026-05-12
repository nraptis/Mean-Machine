#!/bin/bash

set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "${ROOT_DIR}"

OUTPUT_BIN="${OUTPUT_BIN:-${ROOT_DIR}/build/mean_practrand_stream}"
BYTES="${BYTES:-$((32 * 8192))}"
SEED="${SEED:-11400714819323198485}"
PASSWORD_TEXT="${PASSWORD_TEXT:-a}"
BITS_MODE="${BITS_MODE:-0}"
OUTPUT_PATH="${OUTPUT_PATH:-}"

if [[ ! -x "${OUTPUT_BIN}" ]]; then
  OUTPUT_BIN="${OUTPUT_BIN}" bash "${ROOT_DIR}/run_build_practrand_candidate_stream.sh"
fi

ARGS=(--bytes "${BYTES}")
if [[ -n "${PASSWORD_TEXT}" ]]; then
  ARGS+=(--password-text "${PASSWORD_TEXT}")
else
  ARGS+=(--seed "${SEED}")
fi
if [[ "${BITS_MODE}" == "1" ]]; then
  ARGS+=(--bits)
fi
if [[ -n "${OUTPUT_PATH}" ]]; then
  ARGS+=(--output "${OUTPUT_PATH}")
fi

"${OUTPUT_BIN}" "${ARGS[@]}"
