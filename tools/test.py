#!/usr/bin/env python3
"""Compile and run every standalone topic test, then check header interoperability."""

import argparse
import os
from pathlib import Path
import subprocess
import tempfile


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--sanitizers", action="store_true")
    args = parser.parse_args()
    root = Path(__file__).resolve().parents[1]
    tests = sorted((root / "topics").glob("*/test.cpp"))
    if not tests:
        raise SystemExit("No topic tests found")
    compiler = os.environ.get("CXX", "g++")
    flags = ["-std=c++20", "-Wall", "-Wextra", "-Werror", "-pedantic"]
    flags += (["-O1", "-g", "-fsanitize=address,undefined", "-fno-omit-frame-pointer"]
              if args.sanitizers else ["-O2"])
    with tempfile.TemporaryDirectory(prefix="leetcode-pattern-tests-") as directory:
        build = Path(directory)
        for test in tests:
            executable = build / test.parent.name
            print(f"TEST {test.parent.name}", flush=True)
            subprocess.run([compiler, *flags, str(test), "-o", str(executable)], check=True)
            subprocess.run([str(executable)], check=True)
        headers = sorted((root / "topics").glob("*/templates.hpp"))
        source = build / "all_headers.cpp"
        source.write_text("\n".join(f'#include "{p.relative_to(root)}"' for p in headers)
                          + "\nint main() {}\n")
        executable = build / "all_headers"
        subprocess.run([compiler, *flags, "-I", str(root), str(source), "-o", str(executable)], check=True)
        subprocess.run([str(executable)], check=True)
    print(f"PASS: {len(tests)} topic suites and {len(headers)} headers together")


if __name__ == "__main__":
    main()
