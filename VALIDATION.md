# Source-fidelity validation

Snapshot: **14 October 2026**. History verification is incremental; see [Coverage](COVERAGE.md).

## Verified properties

- All **413 prior originals**, **99 prior snippets**, and previous source/snippet records are unchanged from published baseline `0f3abc4ac3d39e12f5d3401c265e5986d824cd32`.
- Added **4 Accepted C++ sources** and **4 literal excerpts**. All **417 originals**, **294 problems**, **407 distinct source texts**, **11 topics**, and **390,831 source bytes** are accounted for.
- Every original SHA-256 matches; all source files match retained capture strings. Submission IDs and provenance URLs agree.
- All **103 snippets** are literal contiguous source slices with matching byte offsets, line ranges and hashes.
- Every original is linked from its topic appendix and source index. Local Markdown links resolve. No unlisted C++ files are present.
- English tables explain actual implementation costs. Existing BFS and convex-concentration explanations are extended rather than copied into duplicate chapters. Fixed buffer, numeric bounds, null placeholders, leaf rescans and scalar-prefix alternatives are described separately from unchanged code.

## Reproduce

Run `python3 tools/check_originals.py` and `python3 tools/verify_snippets.py`. Supply a retained capture through `--capture-json` for an independent source comparison when available.

These are fidelity/provenance checks, not compilation or algorithm-correctness tests. LeetCode judge types/includes are not supplied; no original implementation was silently changed.
