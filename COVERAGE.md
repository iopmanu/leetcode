# Coverage and limitations

## Current handbook: incremental update on 11 October 2026

The handbook now preserves **382 Accepted C++ submissions from 261 problems**, with **372 exact distinct code texts**, **80 literal snippets**, and **11 topics**. This update adds **13 submission IDs**, including 12 displaying 11 October and one newly observed 10 October boundary source. All 369 prior originals and 69 prior snippets remain byte-for-byte unchanged.

The current solved-problem inventory was read completely: **11 pages, 532 unique problem URLs**, five additions, no removed old URLs, and no duplicates. History work was **incremental**, not a new full-history audit of all 532 problems:

- All **13 changed problem histories** were expanded and checked across all languages and statuses: **38 attempt rows**. Each history showed one complete page, with visible rows matching its count.
- Three additional prior-boundary histories were rechecked, adding **10 rows**. The current check therefore inspected **16 complete exposed histories and 48 rows**.
- The updated inventory counts for all 527 old problems were compared with the prior audit. Only expected changed problems and the previously known one-attempt discrepancy differed; no new unexplained count mismatch was found.
- Every newly observed Accepted C++ ID was captured, and all **382 originals** match the combined retained captured strings and manifest hashes. The current source payload is **363,548 bytes**. All **80 snippets** match literal original slices.

The last complete exposed-history audit remains **10 October 2026**, covering the then-inventoried 527 solved problems. Its measurements and methodology are retained below as a dated baseline, not presented as a fresh audit of the 532-problem inventory.

### Current unresolved aggregate differences

At **20:47:10 UTC on 11 October 2026**, the [LeetCode profile](https://leetcode.com/u/VanyushaDoronin/) displayed **262 C++ problems solved** and **532 total problems solved**. The preserved C++ sources cover **261 problems**, so the **one-problem difference remains unresolved**. No missing Accepted C++ source was found in the histories checked during this incremental update.

The refreshed inventory totals **1,415 attempts**, while the known complete-history baseline plus the newly observed attempts totals **1,416**. This carries forward the previously documented one-row difference; it is not a claim that all current histories were reopened. The difference does not correspond to an uncaptured Accepted C++ source identified in the checked histories.

Submission display dates are preserved as observed; no timezone for those display dates is asserted. Source and snippet checks establish fidelity and navigation only. No new compilation or algorithm-runtime validation was performed, and inaccessible, deleted, future, other-language, or non-Accepted source is outside this capture.

## Full exposed-history audit baseline: 10 October 2026

Snapshot: **10 October 2026**. The submission histories exposed by all **527 inventoried solved problems** have been checked completely. Every Accepted C++ submission found in those histories has a preserved original in this handbook. The profile's C++ aggregate still differs by one problem, so this is not a claim that every account-level metric or inaccessible historical record has been reconciled.

### Verified coverage at the baseline

| Measurement | Count |
| --- | ---: |
| Inventoried solved problems | 527 |
| Complete exposed submission histories checked | 527 |
| Attempt rows checked, across all languages and statuses | 1,397 |
| Problems with an Accepted C++ submission in those histories | 249 |
| Accepted C++ submission IDs found and preserved | 369 |
| Exact distinct C++ code texts | 359 |
| Histories with no Accepted C++ submission observed | 278 |
| Observed Accepted C++ submissions without captured source | 0 |

The initial inventory had 525 problems. Two newly observed solved problems brought it to 527. Newly observed Accepted C++ submissions were included in the captured corpus before this final verification.

The final history audit found no additional Accepted C++ IDs beyond the 369 already captured. Submission count, distinct code-text count, and distinct problem count are separate measurements.

### How baseline completeness was checked

History verification was completed on **10 October 2026**.

1. Open each inventoried problem's submission history with all statuses and languages available. Other-language rows were inspected as history metadata so that older C++ attempts could not be hidden behind a newer submission in another language. No Python or other-language source code was collected for this handbook.
2. Read every exposed history chunk, including lazy-loaded rows. Independently parse the saved rows and require every attempt ordinal from **1 through the largest observed ordinal** exactly once, without gaps or duplicates. Verify all 527 distinct problem URLs against the solved-problem inventory.
3. Derive Accepted C++ IDs from the actual row status and language. Match the complete ID set and each problem URL against the captured corpus and [source manifest](sources.json).
4. Recompute SHA-256 from every captured source string and compare it with the manifest and the bytes of all 369 original files. No mismatches or missing originals were found.

These are aggregate findings from the complete exposed-history verification. Source provenance remains in the original-file manifest. Completeness is scoped to the UI histories available during the snapshot; it does not certify unseen, deleted, or otherwise inaccessible records.

### Aggregate differences at the baseline

#### Profile language count at the baseline

At **19:26:25 UTC on 10 October 2026**, the [LeetCode profile](https://leetcode.com/u/VanyushaDoronin/) displayed **250 C++ problems solved** and **527 total problems solved**. The exhaustive check of the 527 exposed problem histories identifies Accepted C++ submissions for **249 problems**.

That **one-problem difference remains unresolved**. No missing Accepted C++ ID was found in these histories, and no explanation for the profile's different count has been established. The 278 histories without an observed Accepted C++ submission should not be used to assert that no unavailable historical C++ record could exist.

#### Inventory attempt count at the baseline

The progress inventory totals **1,396 attempts**, while the complete history rows total **1,397**. One inventory row reports one fewer attempt than its fully inspected history. Every exposed history ordinal was checked, including the extra row. No counting-rule explanation has been established. This difference does not add an Accepted C++ source or leave a history ordinal unchecked.

### Source fidelity and validation at the baseline

- All 369 captured source records remain separate original files, including equivalent resubmissions; they contain 359 exact distinct code texts.
- Source bytes, whitespace, and original comments are preserved without edits. All 69 snippets remain exact excerpts of those originals.
- No derived framework or rewritten algorithm templates are included. Original wrappers and LeetCode-specific assumptions remain intact.
- The fidelity checker validates source preservation, snippet provenance, and index coverage. It does not compile all originals, replace LeetCode's harness, or re-run their algorithmic tests.
- Topic explanations organize source-backed ideas and meaningful variants. Explanatory prose does not expand the source evidence.
- No inaccessible implementation is represented as inspected, and no existing GitHub or third-party implementation fills a gap.
- No login credentials, session cookies, or verification codes are included.

## Requested graph algorithms

Dijkstra is now backed by the original [743 min-heap implementation](topics/dsu-and-graphs/originals/743__2158089044.cpp) and the [778 minimax variant](topics/dsu-and-graphs/originals/778__2159581294.cpp). Their unchanged [additive](topics/dsu-and-graphs/snippets/dijkstra-network-delay.cpp) and [minimax](topics/dsu-and-graphs/snippets/dijkstra-minimax-grid.cpp) excerpts are available directly. The recovered [2045 implementation](topics/dsu-and-graphs/originals/2045__2158128996.cpp) tracks two distinct arrival times with a deque; it is not Yen’s simple-path algorithm. No original Prim or Yen implementation has been verified in the captured code. The three captured 1584 variants and the sorted-edge 778 variant use Kruskal/DSU. Uncaptured implementations are not replaced by newly written code.


## Full-audit snapshot boundary

Coverage is complete for the **Accepted C++ rows exposed in the 527 audited solved-problem histories during the 10 October 2026 snapshot**. The source files and manifest preserve every such observed submission. The audit is not an export of other-language code, failed C++ source, future submissions, or records the UI does not expose. The unresolved profile aggregate is stated separately above.
