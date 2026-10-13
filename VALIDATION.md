# Source-fidelity validation

Snapshot: **13 October 2026**. History verification is incremental; see [Coverage](COVERAGE.md).

## Verified properties

- All **405 original files**, **91 snippets**, and previous source/snippet records are unchanged from published baseline `b68b71b3bbdd55961abfe9068d58fb0f10b8e093`.
- Added **8 Accepted C++ sources** and **8 literal excerpts**. All **413 originals**, **291 problems**, **403 distinct source texts**, **11 topics**, and **386,945 source bytes** are accounted for.
- Every original SHA-256 matches; all new files match independent capture strings. Submission IDs and provenance URLs agree.
- All **99 snippets** are literal contiguous source slices with matching byte offsets, line ranges and hashes.
- Every original is linked from its topic appendix and source index. Local Markdown links and fragment line ranges resolve. No unlisted C++ files are present.
- English topic tables explain actual costs and combinations. Existing generic graph and DP explanations are reused; source-specific geometry, packed keys, mutation and bounds are documented separately.

## Reproduce

Run `python3 tools/check_originals.py` and `python3 tools/verify_snippets.py`. Supply a retained capture through `--capture-json` for an independent full source comparison when available.

These are fidelity/provenance checks, not compilation or algorithm-correctness tests. LeetCode judge types/includes are not supplied; no original implementation was silently changed.
