#!/bin/bash

set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "${ROOT_DIR}"

PASSWORD_TEXT="${PASSWORD_TEXT:-${1:-a}}"
SIZE_SPEC="${SIZE_SPEC:-${2:-32blk}}"
OUTPUT_ROOT="${OUTPUT_ROOT:-${3:-${ROOT_DIR}/generated/practrand_single_runs}}"

PRACTRAND_BIN="${PRACTRAND_BIN:-}"
SEED="${SEED:-11400714819323198485}"
MAX_FAIL="${MAX_FAIL:-0}"
MAX_VERY_SUSPICIOUS="${MAX_VERY_SUSPICIOUS:-1000}"
MAX_SUSPICIOUS="${MAX_SUSPICIOUS:-0}"
MAX_MILDLY_SUSPICIOUS="${MAX_MILDLY_SUSPICIOUS:-999999}"
MAX_UNUSUAL="${MAX_UNUSUAL:-999999}"
MAX_ATTEMPTS="${MAX_ATTEMPTS:-3}"
RETRY_NO_REPORT_DELAY_SEC="${RETRY_NO_REPORT_DELAY_SEC:-1.5}"
KEEP_STREAM="${KEEP_STREAM:-0}"

if [[ -z "${PRACTRAND_BIN}" ]]; then
  if command -v RNG_test >/dev/null 2>&1; then
    PRACTRAND_BIN="$(command -v RNG_test)"
  elif [[ -x "${ROOT_DIR}/build/practrand/RNG_test" ]]; then
    PRACTRAND_BIN="${ROOT_DIR}/build/practrand/RNG_test"
  elif [[ -x "/Users/magneto/Desktop/Codex Playground/Twist/build/practrand/RNG_test" ]]; then
    PRACTRAND_BIN="/Users/magneto/Desktop/Codex Playground/Twist/build/practrand/RNG_test"
  else
    echo "Set PRACTRAND_BIN to the path of RNG_test" >&2
    exit 1
  fi
fi

if [[ ! -x "${PRACTRAND_BIN}" ]]; then
  echo "PractRand binary is not executable: ${PRACTRAND_BIN}" >&2
  exit 1
fi

if ! [[ "${MAX_ATTEMPTS}" =~ ^[0-9]+$ ]] || (( MAX_ATTEMPTS < 1 )); then
  echo "MAX_ATTEMPTS must be >= 1" >&2
  exit 1
fi

parse_output="$({
python3 - "${SIZE_SPEC}" <<'PY'
import sys

def parse_size_spec(spec: str):
    text = spec.strip().lower()
    if not text:
        raise ValueError("empty size_spec")

    block_bytes = 8192
    named_sizes = {
        "l1": 261120,
        "block_size_l1": 261120,
        "l2": 522240,
        "block_size_l2": 522240,
        "l3": 1044480,
        "block_size_l3": 1044480,
    }
    if text in named_sizes:
        total = named_sizes[text]
        return total, text.upper().replace("BLOCK_SIZE_", "")

    unit_multipliers = {
        "b": 1,
        "byte": 1,
        "bytes": 1,
        "blk": block_bytes,
        "block": block_bytes,
        "blocks": block_bytes,
        "kb": 1024,
        "k": 1024,
        "kib": 1024,
        "mb": 1024 * 1024,
        "m": 1024 * 1024,
        "mib": 1024 * 1024,
    }

    digits = []
    suffix = []
    for ch in text:
        if ch.isdigit() and not suffix:
            digits.append(ch)
        elif ch in " _":
            continue
        else:
            suffix.append(ch)

    if not digits:
        raise ValueError(f"invalid size_spec: {spec}")

    value = int("".join(digits))
    unit = "".join(suffix) or "mb"
    if unit not in unit_multipliers:
        raise ValueError(f"unsupported size unit in size_spec: {spec}")

    total = value * unit_multipliers[unit]
    if total % block_bytes == 0 and unit in {"blk", "block", "blocks"}:
        tag = f"{total // block_bytes:03d}BLK"
    elif total % (1024 * 1024) == 0:
        tag = f"{total // (1024 * 1024):03d}MB"
    elif total % 1024 == 0:
        tag = f"{total // 1024:03d}KB"
    else:
        tag = f"{total:05d}B"
    return total, tag

bytes_total, stage_tag = parse_size_spec(sys.argv[1])
print(bytes_total)
print(stage_tag)
PY
} 2>/dev/null)" || {
  echo "invalid size spec: ${SIZE_SPEC}" >&2
  exit 1
}

STREAM_BYTES="$(printf '%s\n' "${parse_output}" | sed -n '1p')"
STAGE_TAG="$(printf '%s\n' "${parse_output}" | sed -n '2p')"
if ! [[ "${STREAM_BYTES}" =~ ^[0-9]+$ ]] || (( STREAM_BYTES <= 0 )); then
  echo "invalid stream bytes parsed from size spec: ${SIZE_SPEC}" >&2
  exit 1
fi

PASSWORD_LABEL="$(python3 - "${PASSWORD_TEXT}" <<'PY'
import re
import sys
label = re.sub(r"[^A-Za-z0-9]+", "_", sys.argv[1]).strip("_").lower()
print(label or "blank")
PY
)"

RUN_ID="$(date +%Y%m%d_%H%M%S)_$$_$RANDOM"
RUN_LABEL="candidate_${PASSWORD_LABEL}_${STAGE_TAG}_${RUN_ID}"
RUN_DIR="${OUTPUT_ROOT}/${RUN_LABEL}"
STREAM_FILE="${RUN_DIR}/byte_stream.bin"
REPORT_FILE="${RUN_DIR}/practrand_output.txt"
SCORE_FILE="${RUN_DIR}/score.txt"

mkdir -p "${RUN_DIR}"

fail_count=0
very_suspicious_count=0
suspicious_count=0
mildly_suspicious_count=0
unusual_count=0
normalish_count=0
normal_count=0
total_results=0
status="NO_REPORT"
gate_status="NO_REPORT"
attempts_used=0
report_bytes=0
pass_gate=0

for ((attempt=1; attempt<=MAX_ATTEMPTS; ++attempt)); do
  attempts_used="${attempt}"

  if ! OUTPUT_BIN="${OUTPUT_BIN:-${ROOT_DIR}/build/mean_practrand_stream}" \
       BYTES="${STREAM_BYTES}" \
       PASSWORD_TEXT="${PASSWORD_TEXT}" \
       SEED="${SEED}" \
       OUTPUT_PATH="${STREAM_FILE}" \
       bash "${ROOT_DIR}/run_emit_practrand_candidate_stream.sh" >/dev/null 2>&1; then
    status="EMIT_FAIL"
    gate_status="EMIT_FAIL"
    if (( attempt < MAX_ATTEMPTS )); then
      echo "RETRY_EMIT_FAIL attempt=${attempt} delay_sec=${RETRY_NO_REPORT_DELAY_SEC}" >&2
      sleep "${RETRY_NO_REPORT_DELAY_SEC}"
      continue
    fi
    break
  fi

  SIZE_KIB="$((STREAM_BYTES / 1024))"
  SIZE_ARG="${SIZE_KIB}KB"
  "${PRACTRAND_BIN}" stdin8 -tlmin "${SIZE_ARG}" -tlmax "${SIZE_ARG}" < "${STREAM_FILE}" > "${REPORT_FILE}" 2>&1 || true

  parse_counts="$({
python3 - "${REPORT_FILE}" <<'PY'
import pathlib
import re
import sys

report_path = pathlib.Path(sys.argv[1])
counts = {
    "fail": 0,
    "very_suspicious": 0,
    "suspicious": 0,
    "mildly_suspicious": 0,
    "unusual": 0,
    "normalish": 0,
    "normal": 0,
    "total_results": 0,
}

if report_path.exists():
    for raw_line in report_path.read_text(encoding="utf-8", errors="ignore").splitlines():
        line = raw_line.rstrip()
        if "Test Name" in line or "length=" in line or not line.strip():
            continue
        lower_line = line.lower()
        match = re.search(r"(?:no anomalies in|and)\s+(\d+)\s+test result\(s\)(?:\s+without anomalies)?", lower_line)
        if match:
            val = int(match.group(1))
            counts["normal"] += val
            counts["total_results"] += val
            continue
        if "fail" in lower_line:
            counts["fail"] += 1
            counts["total_results"] += 1
        elif "very suspicious" in lower_line:
            counts["very_suspicious"] += 1
            counts["total_results"] += 1
        elif "mildly suspicious" in lower_line:
            counts["mildly_suspicious"] += 1
            counts["total_results"] += 1
        elif "suspicious" in lower_line:
            counts["suspicious"] += 1
            counts["total_results"] += 1
        elif "unusual" in lower_line:
            counts["unusual"] += 1
            counts["total_results"] += 1
        elif "normalish" in lower_line:
            counts["normalish"] += 1
            counts["total_results"] += 1
        elif "normal" in lower_line:
            counts["normal"] += 1
            counts["total_results"] += 1

for key, value in counts.items():
    print(f"{key}={value}")
PY
} 2>/dev/null)"

  fail_count="$(printf '%s\n' "${parse_counts}" | awk -F= '/^fail=/{print $2}')"
  very_suspicious_count="$(printf '%s\n' "${parse_counts}" | awk -F= '/^very_suspicious=/{print $2}')"
  suspicious_count="$(printf '%s\n' "${parse_counts}" | awk -F= '/^suspicious=/{print $2}')"
  mildly_suspicious_count="$(printf '%s\n' "${parse_counts}" | awk -F= '/^mildly_suspicious=/{print $2}')"
  unusual_count="$(printf '%s\n' "${parse_counts}" | awk -F= '/^unusual=/{print $2}')"
  normalish_count="$(printf '%s\n' "${parse_counts}" | awk -F= '/^normalish=/{print $2}')"
  normal_count="$(printf '%s\n' "${parse_counts}" | awk -F= '/^normal=/{print $2}')"
  total_results="$(printf '%s\n' "${parse_counts}" | awk -F= '/^total_results=/{print $2}')"

  if [[ -f "${REPORT_FILE}" ]]; then
    report_bytes="$(wc -c < "${REPORT_FILE}" | tr -d '[:space:]')"
  else
    report_bytes=0
  fi

  if [[ "${report_bytes}" != "0" ]]; then
    status="REPORT"
  else
    status="NO_REPORT"
  fi

  if [[ -z "${total_results}" ]]; then
    total_results=0
  fi

  if (( total_results <= 0 )); then
    gate_status="NO_REPORT"
    if (( attempt < MAX_ATTEMPTS )); then
      echo "RETRY_NO_REPORT attempt=${attempt} delay_sec=${RETRY_NO_REPORT_DELAY_SEC}" >&2
      sleep "${RETRY_NO_REPORT_DELAY_SEC}"
      continue
    fi
    break
  fi

  if (( fail_count <= MAX_FAIL )) &&
     (( very_suspicious_count <= MAX_VERY_SUSPICIOUS )) &&
     (( suspicious_count <= MAX_SUSPICIOUS )) &&
     (( mildly_suspicious_count <= MAX_MILDLY_SUSPICIOUS )) &&
     (( unusual_count <= MAX_UNUSUAL )); then
    gate_status="PASS"
    pass_gate=1
  elif (( fail_count > MAX_FAIL )); then
    gate_status="TOO_MANY_FAIL"
  elif (( very_suspicious_count > MAX_VERY_SUSPICIOUS )); then
    gate_status="TOO_MANY_VERY_SUSPICIOUS"
  elif (( suspicious_count > MAX_SUSPICIOUS )); then
    gate_status="TOO_MANY_SUSPICIOUS"
  elif (( mildly_suspicious_count > MAX_MILDLY_SUSPICIOUS )); then
    gate_status="TOO_MANY_MILDLY_SUSPICIOUS"
  else
    gate_status="TOO_MANY_UNUSUAL"
  fi

  break

done

cat > "${SCORE_FILE}" <<SCORE
password_text=${PASSWORD_TEXT}
size_spec=${SIZE_SPEC}
stage_tag=${STAGE_TAG}
stream_bytes=${STREAM_BYTES}
practrand_bin=${PRACTRAND_BIN}
run_dir=${RUN_DIR}
stream_file=${STREAM_FILE}
report_file=${REPORT_FILE}
status=${status}
gate_status=${gate_status}
attempts_used=${attempts_used}
report_bytes=${report_bytes}
fail=${fail_count}
very_suspicious=${very_suspicious_count}
suspicious=${suspicious_count}
mildly_suspicious=${mildly_suspicious_count}
unusual=${unusual_count}
normalish=${normalish_count}
normal=${normal_count}
total_results=${total_results}
SCORE

if [[ "${KEEP_STREAM}" != "1" ]]; then
  rm -f "${STREAM_FILE}"
fi

echo "password_text=${PASSWORD_TEXT}"
echo "size_spec=${SIZE_SPEC}"
echo "stage_tag=${STAGE_TAG}"
echo "stream_bytes=${STREAM_BYTES}"
echo "status=${status}"
echo "gate_status=${gate_status}"
echo "attempts_used=${attempts_used}"
echo "report_bytes=${report_bytes}"
echo "fail=${fail_count}"
echo "very_suspicious=${very_suspicious_count}"
echo "suspicious=${suspicious_count}"
echo "mildly_suspicious=${mildly_suspicious_count}"
echo "unusual=${unusual_count}"
echo "normalish=${normalish_count}"
echo "normal=${normal_count}"
echo "total_results=${total_results}"
echo "run_dir=${RUN_DIR}"
echo "score_file=${SCORE_FILE}"
echo "report_file=${REPORT_FILE}"

if (( pass_gate == 1 )); then
  exit 0
fi
exit 2
