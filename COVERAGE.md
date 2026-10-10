# Coverage and limitations

Snapshot: **10 October 2026**. This is a source-backed handbook with known collection gaps, not a complete export of the account.

## What was inspected

- 525 solved-problem entries were inventoried initially. 2 additional solved problems were observed during recovery, bringing the documented inventory to **527 problems**.
- Actual C++ code was captured for **249 distinct problems**.
- Those problems supplied **369 accepted C++ submission records**, or **359 exact distinct code texts**. These are different measurements; distinct code texts are not a solved-problem count.
- The problem-level index maps every captured problem to an observed pattern.
- Existing GitHub solutions were not used as a substitute for inaccessible LeetCode code.

## Collection status

Collection resumed after the earlier access interruption. Newly recovered source pages are now represented by exact code files and provenance; any remaining entries below still lack captured code.

| Evidence status | Problems |
| --- | ---: |
| Actual accepted C++ source captured | 249 |
| Recent inventory entry, source not collected | 0 |
| Accepted C++ source link observed, source not collected | 0 |
| Older accepted C++ listing observed, no code collected | 0 |
| No accepted C++ found in the inspected older listing | 278 |

The last row is an observation about the inspected listings, not proof that the account never used C++ for those tasks. The previously incomplete histories for **3. Longest Substring Without Repeating Characters** and **300. Longest Increasing Subsequence** were completed during recovery: 27 and 13 attempts were inspected, respectively. The first had one accepted C++ source, now captured; the second had none in the inspected history. These observations do not establish an exhaustive export of the account.

## Profile count reconciliation

At **19:26:25 UTC on 10 October 2026**, the [LeetCode profile](https://leetcode.com/u/VanyushaDoronin/) displayed **250 C++ problems solved** and **527 total problems solved**. This handbook has actual accepted C++ source for **249 problems**, leaving a **one-problem difference** from that language aggregate. The bounded reconciliation recovered the three newly observed C++ solutions, verified the expanded 527-problem inventory, and checked the new Word Search attempts; its other new attempt was Time Limit Exceeded, not another accepted source. The remaining historical language-count discrepancy is unresolved: no additional accepted C++ source was identified. This is **not a complete account or C++ export**, and the 278 no-C++-observed rows above must not be treated as proof that no historical C++ solution exists for them.

## Remaining recent source pages

Every entry in this previously identified group now has captured source code.

## Older C++ listings awaiting source inspection

Every entry in this previously identified group now has captured source code.

## Source fidelity and validation

- All 369 captured source records are preserved as individual original files; they contain 359 exact distinct code texts.
- Source bytes, including whitespace and original comments, are copied from the captured code strings without edits. The manifest records the captured SHA-256 for each file.
- No derived framework or rewritten algorithm templates are included. Original wrappers and LeetCode-specific assumptions remain intact.
- The fidelity checker checks source preservation and index coverage. It does not replace LeetCode's harness, compile all originals, or re-run their algorithmic tests.
- Topic explanations separate meaningful algorithmic variants from equivalent resubmissions. All variants still have their own source links.
- No inaccessible source is represented as inspected, and no third-party implementation fills a gap.
- No login credentials, session cookies, or verification codes are included.

## Requested graph algorithms

Dijkstra is now backed by the original [743 min-heap implementation](topics/dsu-and-graphs/originals/743__2158089044.cpp) and the [778 minimax variant](topics/dsu-and-graphs/originals/778__2159581294.cpp). Their unchanged [additive](topics/dsu-and-graphs/snippets/dijkstra-network-delay.cpp) and [minimax](topics/dsu-and-graphs/snippets/dijkstra-minimax-grid.cpp) excerpts are available directly. The recovered [2045 implementation](topics/dsu-and-graphs/originals/2045__2158128996.cpp) tracks two distinct arrival times with a deque; it is not Yen’s simple-path algorithm. No original Prim or Yen implementation has been verified in the captured code. The three captured 1584 variants and the sorted-edge 778 variant use Kruskal/DSU. Uncaptured implementations are not replaced by newly written code.

## Snapshot boundary

These counts describe the captured snapshot dated 10 October 2026. The original files and their manifest are the evidence boundary for this handbook; newly written explanations do not expand that boundary. Captured sources are not an exhaustive history of every accepted attempt.
