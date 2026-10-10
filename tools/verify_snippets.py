#!/usr/bin/env python3
"""Check that every snippet is an exact recorded byte slice of its original."""
import hashlib
import json
from pathlib import Path


def main():
    root = Path(__file__).resolve().parents[1]
    sources = {item["source_id"]: item for item in json.loads((root / "sources.json").read_text())}
    snippets = json.loads((root / "snippets.json").read_text())
    errors = []
    for item in snippets:
        path = root / item["path"]
        source = sources[item["source_id"]]
        original = (root / source["path"]).read_bytes()
        actual = path.read_bytes()
        if hashlib.sha256(original).hexdigest() != source["sha256"]:
            errors.append(f"Original changed: {source['path']}")
        if actual != original[item["start_byte"]:item["end_byte"]]:
            errors.append(f"Snippet is not the original slice: {item['path']}")
        if hashlib.sha256(actual).hexdigest() != item["sha256"]:
            errors.append(f"Snippet hash differs: {item['path']}")
    recorded = {item["path"] for item in snippets}
    actual_files = {p.relative_to(root).as_posix() for p in root.glob("topics/*/snippets/*.cpp")}
    if recorded != actual_files:
        errors.append("Snippet manifest/file set differs")
    if errors:
        raise SystemExit("\n".join(errors))
    print(f"PASS: {len(snippets)} snippets exactly match their original source slices")
    print("Fidelity only: this does not compile or test the original algorithms.")


if __name__ == "__main__":
    main()
