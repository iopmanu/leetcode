#!/usr/bin/env python3
"""Verify unchanged captured C++ sources; no compiler or external packages needed."""

import argparse
import hashlib
import json
import re
from pathlib import Path


def check(root, capture_json=None):
    errors = []
    try:
        records = json.loads((root / "sources.json").read_text(encoding="utf-8"))
    except (OSError, ValueError) as exc:
        return [f"cannot read sources.json: {exc}"], None
    if not isinstance(records, list):
        return ["sources.json must contain a list"], None

    expected_topics = {
        "range-queries", "dsu-and-graphs", "search-and-sort",
        "monotonic-and-heaps", "design-structures", "strings-and-tries",
        "trees-and-lists", "dp-and-backtracking", "windows-and-prefixes",
        "greedy-and-intervals", "math-and-bits",
    }
    if len(records) != 369:
        errors.append(f"expected 369 submission records; found {len(records)}")
    ids, problems, topics, hashes, paths = set(), set(), set(), set(), set()
    by_id = {}
    source_index = (root / "SOURCES.md").read_text(encoding="utf-8") if (root / "SOURCES.md").is_file() else ""
    total_bytes = 0
    for index, record in enumerate(records):
        required = ("source_id", "problem", "url", "sha256", "path", "topic", "problem_id", "problem_url")
        if not isinstance(record, dict) or any(not isinstance(record.get(k), str) or not record[k] for k in required):
            errors.append(f"invalid manifest record at index {index}")
            continue
        sid, path, topic = record["source_id"], record["path"], record["topic"]
        if sid in ids:
            errors.append(f"duplicate source ID: {sid}")
        if path in paths:
            errors.append(f"duplicate source path: {path}")
        ids.add(sid)
        paths.add(path)
        by_id[sid] = record
        problems.add(record["problem"])
        topics.add(topic)
        hashes.add(record["sha256"])
        expected_path = f"topics/{topic}/originals/{record['problem_id']}__{sid}.cpp"
        if path != expected_path or topic not in expected_topics or not sid.isdigit() or not record["problem_id"].isdigit():
            errors.append(f"unexpected source path or ID: {path}")
            continue
        if record["problem"].split(".", 1)[0] != record["problem_id"]:
            errors.append(f"problem ID/title mismatch: {sid}")
        if not re.fullmatch(r"[0-9a-f]{64}", record["sha256"]):
            errors.append(f"invalid SHA-256: {sid}")
        allowed_source_urls = {
            record["problem_url"] + f"submissions/{sid}",
            f"https://leetcode.com/submissions/detail/{sid}",
        }
        if record["url"].rstrip("/") not in allowed_source_urls:
            errors.append(f"source URL/ID mismatch: {sid}")
        original = root / path
        if not original.is_file():
            errors.append(f"missing original: {path}")
            continue
        data = original.read_bytes()
        total_bytes += len(data)
        if hashlib.sha256(data).hexdigest() != record["sha256"]:
            errors.append(f"hash mismatch: {path}")
        topic_readme = root / "topics" / topic / "README.md"
        text = topic_readme.read_text(encoding="utf-8") if topic_readme.is_file() else ""
        if f"(originals/{original.name})" not in text:
            errors.append(f"original not linked from topic index: {path}")
        if f"({path})" not in source_index:
            errors.append(f"original not linked from source index: {path}")

    actual_paths = {p.relative_to(root).as_posix() for p in (root / "topics").glob("*/originals/*") if p.is_file()}
    for path in sorted(actual_paths - paths):
        errors.append(f"unlisted original: {path}")
    for count, expected, name in [(len(problems), 249, "problems"), (len(hashes), 359, "distinct source hashes")]:
        if count != expected:
            errors.append(f"expected {expected} {name}; found {count}")
    if topics != expected_topics:
        errors.append("topic set differs from the captured 11-topic mapping")

    if capture_json is not None:
        try:
            capture = json.loads(capture_json.read_text(encoding="utf-8"))
            captured = {r["submission_id"]: r for r in capture}
            if len(capture) != 369 or len(captured) != 369 or set(captured) != ids:
                errors.append("capture and manifest source IDs/counts differ")
            for sid in ids & set(captured):
                record, original = by_id[sid], captured[sid]
                data = original["code"].encode("utf-8")
                digest = hashlib.sha256(data).hexdigest()
                if digest != original["code_hash"] or digest != record["sha256"]:
                    errors.append(f"capture hash mismatch: {sid}")
                if original["problem"] != record["problem"] or original["submission_url"] != record["url"]:
                    errors.append(f"capture provenance mismatch: {sid}")
                file = root / record["path"]
                if file.is_file() and file.read_bytes() != data:
                    errors.append(f"capture byte mismatch: {sid}")
        except (OSError, ValueError, KeyError, TypeError) as exc:
            errors.append(f"cannot verify capture JSON: {exc}")
    return errors, total_bytes


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--root", type=Path, default=Path(__file__).resolve().parents[1], help="handbook root (default: parent of tools)")
    parser.add_argument("--capture-json", type=Path, help="optional normalized capture for direct byte comparison")
    args = parser.parse_args()
    errors, total_bytes = check(args.root.resolve(), args.capture_json)
    if errors:
        for error in errors:
            print(f"FAIL: {error}")
        return 1
    print(f"PASS: 369 originals, 249 problems, 359 distinct code texts, 11 topics, {total_bytes:,} unchanged source bytes")
    print("PASS: every original is linked from its topic and the complete source index")
    if args.capture_json:
        print("PASS: all original files also match the supplied captured code strings byte for byte")
    print("Scope: source fidelity and index coverage only; no C++ compilation or algorithm tests")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
