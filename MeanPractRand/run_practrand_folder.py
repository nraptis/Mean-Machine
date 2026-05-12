#!/usr/bin/env python3

from __future__ import annotations

import re
import shutil
import subprocess
from pathlib import Path

# ============================================================
# Editable config (no shell/python args required)
# ============================================================
ROOT_DIR = Path('/Users/magneto/Desktop/Codex Playground/MeanPractRand')
BITSTREAM_FOLDER = ROOT_DIR / 'streams'
REPORT_PATH = ROOT_DIR / 'generated' / 'practrand_folder_report.txt'
RUN_OUTPUT_DIR = ROOT_DIR / 'generated' / 'practrand_folder_runs'

RECURSIVE_SCAN = False
RNG_MODE = 'stdin8'
PRACTRAND_BIN = ''
# Extra static args to append after the per-file -tlmin/-tlmax args.
PRACTRAND_EXTRA_ARGS: list[str] = []
# ============================================================


FAIL_RE = re.compile(r'\bFAIL\b', re.IGNORECASE)
VERY_SUSPICIOUS_RE = re.compile(r'\bVERY\s+SUSPICIOUS\b', re.IGNORECASE)
SUSPICIOUS_RE = re.compile(r'\bSUSPICIOUS\b', re.IGNORECASE)
MILDLY_SUSPICIOUS_RE = re.compile(r'\bMILDLY\s+SUSPICIOUS\b', re.IGNORECASE)
UNUSUAL_RE = re.compile(r'\bUNUSUAL\b', re.IGNORECASE)


def resolve_practrand_bin() -> Path:
    if PRACTRAND_BIN:
        result = Path(PRACTRAND_BIN).expanduser()
        return result

    which_bin = shutil.which('RNG_test')
    if which_bin:
        return Path(which_bin)

    local_build = ROOT_DIR / 'build' / 'practrand' / 'RNG_test'
    if local_build.exists():
        return local_build

    fallback = Path('/Users/magneto/Desktop/Codex Playground/Twist/build/practrand/RNG_test')
    if fallback.exists():
        return fallback

    raise RuntimeError(
        'RNG_test not found. Set PRACTRAND_BIN near the top of run_practrand_folder.py.'
    )


def collect_bin_files(folder: Path, recursive: bool) -> list[Path]:
    if recursive:
        files = [p for p in folder.rglob('*.bin') if p.is_file()]
    else:
        files = [p for p in folder.glob('*.bin') if p.is_file()]
    return sorted(files)


def first_fail_line(text: str) -> str:
    for line in text.splitlines():
        if FAIL_RE.search(line):
            return line.strip()
    return ''


def count_matches(text: str, pattern: re.Pattern[str]) -> int:
    count = 0
    for line in text.splitlines():
        if pattern.search(line):
            count += 1
    return count


def build_length_args(file_size_bytes: int) -> list[str]:
    size_kib = max(1, file_size_bytes // 1024)
    size_arg = f'{size_kib}KB'
    return ['-tlmin', size_arg, '-tlmax', size_arg]


def sanitize_name(name: str) -> str:
    safe = re.sub(r'[^A-Za-z0-9._-]+', '_', name).strip('_')
    return safe or 'stream'


def run_one_file(practrand_bin: Path, stream_file: Path) -> dict:
    stream_size = stream_file.stat().st_size
    command = [str(practrand_bin), RNG_MODE]
    command.extend(build_length_args(stream_size))
    command.extend(PRACTRAND_EXTRA_ARGS)

    with stream_file.open('rb') as in_handle:
        completed = subprocess.run(
            command,
            stdin=in_handle,
            stdout=subprocess.PIPE,
            stderr=subprocess.STDOUT,
            text=True,
            errors='replace',
        )

    output_text = completed.stdout or ''
    fail_line = first_fail_line(output_text)

    fail_count = count_matches(output_text, FAIL_RE)
    very_suspicious_count = count_matches(output_text, VERY_SUSPICIOUS_RE)
    mildly_suspicious_count = count_matches(output_text, MILDLY_SUSPICIOUS_RE)
    unusual_count = count_matches(output_text, UNUSUAL_RE)

    # Subtract the "very" and "mildly" hits from generic "suspicious" tally.
    suspicious_total = count_matches(output_text, SUSPICIOUS_RE)
    suspicious_count = suspicious_total - very_suspicious_count - mildly_suspicious_count
    if suspicious_count < 0:
        suspicious_count = 0

    if completed.returncode != 0:
        status = 'FAIL'
        reason = f'RNG_test exit={completed.returncode}'
    elif fail_line:
        status = 'FAIL'
        reason = fail_line
    elif not output_text.strip():
        status = 'FAIL'
        reason = 'empty PractRand output'
    else:
        status = 'PASS'
        reason = 'no FAIL token'

    output_file = RUN_OUTPUT_DIR / f"{sanitize_name(stream_file.stem)}_practrand_output.txt"
    output_file.write_text(output_text, encoding='utf-8')

    return {
        'stream_file': stream_file,
        'stream_size': stream_size,
        'status': status,
        'reason': reason,
        'output_file': output_file,
        'command': command,
        'fail': fail_count,
        'very_suspicious': very_suspicious_count,
        'suspicious': suspicious_count,
        'mildly_suspicious': mildly_suspicious_count,
        'unusual': unusual_count,
    }


def write_summary(practrand_bin: Path, results: list[dict]) -> None:
    passed = [r for r in results if r['status'] == 'PASS']
    failed = [r for r in results if r['status'] == 'FAIL']

    lines: list[str] = []
    lines.append('PractRand Folder Report')
    lines.append(f'bitstream_folder={BITSTREAM_FOLDER}')
    lines.append(f'practrand_bin={practrand_bin}')
    lines.append(f'rng_mode={RNG_MODE}')
    lines.append(f'recursive_scan={1 if RECURSIVE_SCAN else 0}')
    lines.append('')

    lines.append(f'files_total={len(results)}')
    lines.append(f'files_passed={len(passed)}')
    lines.append(f'files_failed={len(failed)}')
    lines.append('')

    lines.append('failed_files:')
    if failed:
        for idx, row in enumerate(failed, start=1):
            lines.append(
                f"{idx}. {row['stream_file']} :: {row['reason']} :: output={row['output_file']}"
            )
    else:
        lines.append('none')

    lines.append('')
    lines.append('all_results:')
    for row in results:
        lines.append(
            f"{row['status']} :: {row['stream_file']} :: "
            f"fail={row['fail']} very_suspicious={row['very_suspicious']} "
            f"suspicious={row['suspicious']} mildly_suspicious={row['mildly_suspicious']} "
            f"unusual={row['unusual']} :: output={row['output_file']}"
        )

    REPORT_PATH.parent.mkdir(parents=True, exist_ok=True)
    REPORT_PATH.write_text('\n'.join(lines) + '\n', encoding='utf-8')



def main() -> int:
    if not BITSTREAM_FOLDER.exists() or not BITSTREAM_FOLDER.is_dir():
        raise RuntimeError(f'bitstream folder missing: {BITSTREAM_FOLDER}')

    RUN_OUTPUT_DIR.mkdir(parents=True, exist_ok=True)

    practrand_bin = resolve_practrand_bin()
    if not practrand_bin.exists() or not practrand_bin.is_file():
        raise RuntimeError(f'PractRand binary not found: {practrand_bin}')

    streams = collect_bin_files(BITSTREAM_FOLDER, RECURSIVE_SCAN)
    if not streams:
        raise RuntimeError(f'no .bin files found in {BITSTREAM_FOLDER}')

    print(f'bitstream_folder={BITSTREAM_FOLDER}')
    print(f'practrand_bin={practrand_bin}')
    print(f'files_to_test={len(streams)}')

    results: list[dict] = []
    for idx, stream_file in enumerate(streams, start=1):
        print(f'[{idx}/{len(streams)}] testing {stream_file.name}')
        result = run_one_file(practrand_bin, stream_file)
        print(f"  status={result['status']} reason={result['reason']}")
        results.append(result)

    write_summary(practrand_bin, results)

    failed_count = sum(1 for r in results if r['status'] == 'FAIL')
    passed_count = len(results) - failed_count

    print(f'files_passed={passed_count}')
    print(f'files_failed={failed_count}')
    print(f'report_path={REPORT_PATH}')

    return 0 if failed_count == 0 else 2


if __name__ == '__main__':
    raise SystemExit(main())
