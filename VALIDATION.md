# Source-fidelity validation

Snapshot: **17 October 2026**. History verification is incremental; see [Coverage](COVERAGE.md).

## Verified properties

- All **417 prior originals**, **103 prior snippets**, and prior source/snippet records are unchanged from published baseline `d47a56d6726ee5c1d0c96e7ab8220b6ce5f7111a`.
- Added **17 Accepted C++ originals** and **13 literal excerpts**. All **434 sources**, **309 problems**, **424 distinct source texts**, **11 topics**, and **407,051 original bytes** are accounted for.
- Every original SHA-256 matches; all source files match the separately retained captured strings byte for byte. Submission IDs, problem URLs and provenance links agree.
- All **116 snippets** are exact contiguous original slices with matching hashes, byte offsets and inclusive occupied line ranges. A retained excerpt may omit the final line terminator without changing its inclusive line range.
- Every original is linked from its topic appendix and source index. Every snippet has a direct local link; local file targets and code-line fragments resolve, and submission links match the source manifest. No unlisted C++ files are present.
- English idea-first explanations retain the actual variants: fixed-size memo initialization and stack cost, last-occurrence interval updates with first/second moments, permutation-cycle identity, iterator amortization, BST pointer ownership, two general-tree LCA methods and output-copy costs. Already-covered validation, sorting, quadratic enumeration and alternative window bookkeeping receive provenance without duplicate snippets.

## Reproduce

Run `python3 tools/check_originals.py` and `python3 tools/verify_snippets.py`. Supply the separately retained full capture through `--capture-json` for an independent source comparison when available. These repository tools check source hashes, provenance/index coverage and literal excerpt bytes; this update also independently checked recorded line ranges and local/provenance link targets before publication.

These are fidelity/provenance checks, not compilation or algorithm-correctness tests. LeetCode judge types/includes are not supplied; no original implementation was silently changed.
