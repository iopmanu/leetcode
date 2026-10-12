# Source-fidelity validation

Source-fidelity snapshot: **12 October 2026**. History work was incremental; the last full audit of the then-inventoried histories was **10 October 2026**. See [Coverage](COVERAGE.md) for exact scope and source-extraction limits.

## Verified properties

- **382 prior originals and 80 prior snippets** remain byte-for-byte identical to the published baseline at 8a64a6df49ed8689ac5b6af21667d1b469ffa859. All prior source/snippet records and tab-separated index rows are preserved.
- **23 original files and 11 literal snippets** were added; already covered approaches retain provenance without duplicate theory sections.
- **405 originals**, **283 problems**, **395 distinct code texts**, **11 topics**, and **378,874 original source bytes** are recorded. Equivalent resubmissions remain separate source IDs.
- Every original SHA-256 agrees with its file; all 23 new files match separately retained captured strings. Source URLs agree with submission IDs.
- All **91 snippets** are exact contiguous original slices with verified byte offsets, line ranges, SHA-256, and source links.
- Every original is linked from its topic appendix and source index. Local Markdown links resolve, and no unlisted C++ files are present.
- Topic cost tables describe these implementations, including the full-scan H-Index II predicate, million-counter initialization, and per-element gcd. Original input assumptions and limitations are documented separately.

## Reproduce repository checks

Run `python3 tools/check_originals.py` and `python3 tools/verify_snippets.py` from the repository root. The first validates source manifests and index coverage; the second validates literal excerpts. A separately retained combined capture can additionally be supplied through `--capture-json` when available.

These checks do not compile the original LeetCode classes, supply their judge harness, or test algorithm correctness outside their original constraints. New capture fidelity was checked against complete displayed source blocks; it is not an independently downloaded raw-submission export.
