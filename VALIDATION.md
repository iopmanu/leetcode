# Source-fidelity validation

Snapshot: **10 October 2026**.

## What was checked

- **369 original C++ files** preserve the exact UTF-8 bytes of their captured code strings.
- The originals cover **249 problems**, **11 topic folders**, and **359 distinct code texts**. Equivalent resubmissions and exact duplicates remain separate records.
- The total original source payload is **356,082 bytes**. No header, wrapper, comment, whitespace, or final newline was added to an original.
- Each manifest SHA-256 matches its original file and its separately retained captured code record.
- Each original file is linked from its topic README and the complete source index.
- **69 key snippets** match literal slices of the original files. Their locations and hashes are recorded in [snippets.json](snippets.json).
- The source-fidelity checker was exercised with temporary altered copies. It rejected changed bytes, a missing source file, an unlisted extra original, and an omitted manifest record.

## Repeat the checks

From the repository root:

```bash
python3 tools/check_originals.py
python3 tools/verify_snippets.py
```

If the separately retained normalized capture is available:

```bash
python3 tools/check_originals.py --capture-json /path/to/normalized-records.json
```

The additional argument compares every file directly with the captured code string, alongside the manifest hash and provenance checks. It is optional; the ordinary checks are self-contained.

## What was not checked

These are fidelity and navigation checks, not runtime validation. The originals were not compiled together, rewritten for a standalone harness, or re-tested as a common library. Many files depend on LeetCode-provided includes, types, APIs, compiler settings, and problem constraints.

Any prior compiler, unit-test, sanitizer, or AddressSanitizer results for generalized templates do **not** apply to these original files or their literal excerpts. Captured acceptance identifies the historical LeetCode submission; it is not a new correctness or safety claim for broader inputs.

Known collection gaps remain listed in [Coverage and limitations](COVERAGE.md).
