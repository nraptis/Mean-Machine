#!/bin/bash

set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "${ROOT_DIR}"

OUTPUT_DIR="${1:-${ROOT_DIR}/alphabet_gauntlet_32blk_passers}"
PASSWORD_FILE="${PASSWORD_FILE:-}"

MAX_FAIL="${MAX_FAIL:-0}"
MAX_VERY_SUSPICIOUS="${MAX_VERY_SUSPICIOUS:-1000}"
MAX_SUSPICIOUS="${MAX_SUSPICIOUS:-0}"
MAX_MILDLY_SUSPICIOUS="${MAX_MILDLY_SUSPICIOUS:-999999}"
MAX_UNUSUAL="${MAX_UNUSUAL:-999999}"
MAX_ATTEMPTS="${MAX_ATTEMPTS:-3}"
RETRY_NO_REPORT_DELAY_SEC="${RETRY_NO_REPORT_DELAY_SEC:-1.5}"
KEEP_FAILING_OUTPUT="${KEEP_FAILING_OUTPUT:-0}"

temp_password_file=""
cleanup() {
  if [[ -n "${temp_password_file}" && -f "${temp_password_file}" ]]; then
    rm -f "${temp_password_file}"
  fi
}
trap cleanup EXIT

if [[ -z "${PASSWORD_FILE}" ]]; then
  temp_password_file="$(mktemp "${TMPDIR:-/tmp}/alphabet_gauntlet_XXXXXX.txt")"
  python3 - <<'PY' > "${temp_password_file}"
for value in range(ord("a"), ord("z") + 1):
    print(chr(value))
PY
  PASSWORD_FILE="${temp_password_file}"
fi

env \
  MAX_FAIL="${MAX_FAIL}" \
  MAX_VERY_SUSPICIOUS="${MAX_VERY_SUSPICIOUS}" \
  MAX_SUSPICIOUS="${MAX_SUSPICIOUS}" \
  MAX_MILDLY_SUSPICIOUS="${MAX_MILDLY_SUSPICIOUS}" \
  MAX_UNUSUAL="${MAX_UNUSUAL}" \
  MAX_ATTEMPTS="${MAX_ATTEMPTS}" \
  RETRY_NO_REPORT_DELAY_SEC="${RETRY_NO_REPORT_DELAY_SEC}" \
  KEEP_FAILING_OUTPUT="${KEEP_FAILING_OUTPUT}" \
  "${ROOT_DIR}/run_practrand_passwords_and_list.sh" \
  "${PASSWORD_FILE}" \
  "32blk" \
  "${OUTPUT_DIR}"
