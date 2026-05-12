#!/bin/bash

set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "${ROOT_DIR}"

# Backward-compatible argument shape:
# old: run_practrand_passwords_and_list.sh <input_dir> <password_file> <size_spec> <output_dir>
# new: run_practrand_passwords_and_list.sh <password_file> <size_spec> <output_dir>
if [[ $# -ge 2 && -d "${1}" && -f "${2}" ]]; then
  shift
fi

PASSWORD_FILE="${1:-}"
SIZE_SPEC="${2:-32blk}"
OUTPUT_DIR="${3:-${ROOT_DIR}/passwords_and_list_32blk_passers}"

MAX_FAIL="${MAX_FAIL:-0}"
MAX_VERY_SUSPICIOUS="${MAX_VERY_SUSPICIOUS:-1000}"
MAX_SUSPICIOUS="${MAX_SUSPICIOUS:-0}"
MAX_MILDLY_SUSPICIOUS="${MAX_MILDLY_SUSPICIOUS:-999999}"
MAX_UNUSUAL="${MAX_UNUSUAL:-999999}"
MAX_ATTEMPTS="${MAX_ATTEMPTS:-3}"
RETRY_NO_REPORT_DELAY_SEC="${RETRY_NO_REPORT_DELAY_SEC:-1.5}"
KEEP_FAILING_OUTPUT="${KEEP_FAILING_OUTPUT:-0}"

if [[ -z "${PASSWORD_FILE}" ]]; then
  echo "missing password file argument" >&2
  exit 1
fi
if [[ ! -f "${PASSWORD_FILE}" ]]; then
  echo "missing password file: ${PASSWORD_FILE}" >&2
  exit 1
fi

cmd=(
  "${ROOT_DIR}/tools/run_practrand_passwords_and_list.py"
  "${PASSWORD_FILE}"
  "${SIZE_SPEC}"
  "${OUTPUT_DIR}"
)

if [[ "${KEEP_FAILING_OUTPUT}" == "1" ]]; then
  cmd+=("--keep-failing-output")
fi

env \
  MAX_FAIL="${MAX_FAIL}" \
  MAX_VERY_SUSPICIOUS="${MAX_VERY_SUSPICIOUS}" \
  MAX_SUSPICIOUS="${MAX_SUSPICIOUS}" \
  MAX_MILDLY_SUSPICIOUS="${MAX_MILDLY_SUSPICIOUS}" \
  MAX_UNUSUAL="${MAX_UNUSUAL}" \
  MAX_ATTEMPTS="${MAX_ATTEMPTS}" \
  RETRY_NO_REPORT_DELAY_SEC="${RETRY_NO_REPORT_DELAY_SEC}" \
  "${cmd[@]}"
