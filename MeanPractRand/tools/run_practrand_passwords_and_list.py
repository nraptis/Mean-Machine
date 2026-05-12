#!/usr/bin/env python3

from __future__ import annotations

import argparse
import csv
import os
import re
import subprocess
import sys
from pathlib import Path


def read_passwords(password_file: Path) -> list[str]:
    passwords: list[str] = []
    for raw_line in password_file.read_text(encoding="utf-8").splitlines():
        password = raw_line.strip()
        if not password or password.startswith("#"):
            continue
        passwords.append(password)
    return passwords


def sanitize_password_label(password: str) -> str:
    label = re.sub(r"[^A-Za-z0-9]+", "_", password).strip("_").lower()
    return label or "blank"


def parse_key_value_output(text: str) -> dict[str, str]:
    data: dict[str, str] = {}
    for line in text.splitlines():
        if "=" not in line:
            continue
        key, value = line.split("=", 1)
        data[key.strip()] = value.strip()
    return data


def main() -> int:
    parser = argparse.ArgumentParser(
        description="Run a PractRand password list as an AND gauntlet for the MeanPractRand candidate."
    )
    parser.add_argument("password_file")
    parser.add_argument("size_spec")
    parser.add_argument("output_dir")
    parser.add_argument("--keep-failing-output", action="store_true")
    args = parser.parse_args()

    root = Path(__file__).resolve().parents[1]
    password_file = Path(args.password_file).expanduser().resolve()
    output_dir = Path(args.output_dir).expanduser().resolve()

    if not password_file.is_file():
        raise SystemExit(f"missing password file: {password_file}")

    passwords = read_passwords(password_file)
    if not passwords:
        raise SystemExit(f"no passwords found in {password_file}")

    output_dir.mkdir(parents=True, exist_ok=True)

    summary_csv = output_dir / f"summary_passwords_and_list_{args.size_spec}.csv"
    summary_csv.write_text(
        "password,label,status,gate_status,attempts_used,report_bytes,fail,very_suspicious,suspicious,mildly_suspicious,unusual,normalish,normal,total_results,run_dir,score_file,report_file\n",
        encoding="utf-8",
    )

    passed_txt = output_dir / f"passed_passwords_{args.size_spec}.txt"
    failed_txt = output_dir / f"failed_passwords_{args.size_spec}.txt"
    passed_txt.write_text("", encoding="utf-8")
    failed_txt.write_text("", encoding="utf-8")

    print(f"password_file={password_file}")
    print(f"password_count={len(passwords)}")
    print(f"size_spec={args.size_spec}")
    print(f"output_dir={output_dir}")

    passed_all = True
    failed_label = ""
    failed_gate_status = ""

    for password in passwords:
        label = sanitize_password_label(password)
        cmd = [
            "bash",
            str(root / "run_practrand_candidate_once.sh"),
            password,
            args.size_spec,
            str(output_dir / "runs"),
        ]

        completed = subprocess.run(
            cmd,
            cwd=root,
            capture_output=True,
            text=True,
            env=os.environ.copy(),
        )

        parsed = parse_key_value_output(completed.stdout)
        status = parsed.get("status", "UNKNOWN")
        gate_status = parsed.get("gate_status", "UNKNOWN")

        with summary_csv.open("a", encoding="utf-8", newline="") as handle:
            writer = csv.writer(handle)
            writer.writerow(
                [
                    password,
                    label,
                    status,
                    gate_status,
                    parsed.get("attempts_used", ""),
                    parsed.get("report_bytes", ""),
                    parsed.get("fail", ""),
                    parsed.get("very_suspicious", ""),
                    parsed.get("suspicious", ""),
                    parsed.get("mildly_suspicious", ""),
                    parsed.get("unusual", ""),
                    parsed.get("normalish", ""),
                    parsed.get("normal", ""),
                    parsed.get("total_results", ""),
                    parsed.get("run_dir", ""),
                    parsed.get("score_file", ""),
                    parsed.get("report_file", ""),
                ]
            )

        print(
            "GAUNTLET_RESULT "
            f"password={password} label={label} status={status} gate_status={gate_status} "
            f"attempts={parsed.get('attempts_used', '')} total_results={parsed.get('total_results', '')}"
        )

        if completed.returncode == 0 and gate_status == "PASS":
            with passed_txt.open("a", encoding="utf-8") as handle:
                handle.write(f"{password}\n")
            continue

        passed_all = False
        failed_label = label
        failed_gate_status = gate_status
        with failed_txt.open("a", encoding="utf-8") as handle:
            handle.write(f"{password},{label},{gate_status}\n")

        if not args.keep_failing_output:
            run_dir_text = parsed.get("run_dir", "")
            if run_dir_text:
                try:
                    run_dir = Path(run_dir_text)
                    if run_dir.exists() and run_dir.is_dir():
                        for child in run_dir.iterdir():
                            if child.is_file():
                                child.unlink(missing_ok=True)
                except Exception:
                    pass

        break

    print(f"summary_csv={summary_csv}")
    print(f"passed_passwords={passed_txt}")
    print(f"failed_passwords={failed_txt}")

    if passed_all:
        print("GAUNTLET_PASS")
        return 0

    print(f"GAUNTLET_FAIL label={failed_label} gate_status={failed_gate_status}")
    return 2


if __name__ == "__main__":
    raise SystemExit(main())
