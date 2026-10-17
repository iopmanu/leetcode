# An idea-first handbook of my original C++ solutions

Start with an algorithm or a reusable trick, learn how its state composes with another structure, then open the exact implementation. Problems are examples and source references, collected at the end of each chapter.

All implementation links lead to **VanyushaDoronin's unchanged captured LeetCode code**: **434 accepted submission records, 309 problems, 116 literal snippets, 11 topics**. Explanations organize the originals; no new algorithm implementations are supplied.

Latest incremental source update: **17 October 2026**. The last complete exposed-history audit remains **10 October 2026**; [coverage](COVERAGE.md) keeps those scopes separate.

## Start here

1. **Choose a building block** from the topic tables below. Each chapter opens with actual time/space costs and direct implementation links.
2. **Find a composition** in its “Combinations and tricks” section: recognition cue → components → invariant → tradeoffs → original code.
3. **Recall the code** with [the snippet navigator](SNIPPETS.md) and [quick-review prompts](QUICK_REVIEW.md).
4. Use the problem/source appendix only when you need the original constraints, full solution, or another captured variant.

## Topics

| Building blocks | Main algorithms and costs | Combinations worth recognizing |
| --- | --- | --- |
| Binary search, partitioning, sorting | [Search and sort](topics/search-and-sort/README.md#main-algorithms-and-structures) | [Monotone feasibility; sorted halves + cross-pair counting; rotation + index translation](topics/search-and-sort/README.md#combinations-and-tricks) |
| Prefix sums, count maps, windows, difference arrays | [Windows and prefixes](topics/windows-and-prefixes/README.md#main-algorithms-and-structures) | [Prefix algebra + frequency lookup; count deficits + shrink; interval endpoints + prefix reconstruction](topics/windows-and-prefixes/README.md#combinations-and-tricks) |
| Monotonic stacks/deques, heaps, ordered multisets | [Monotonic structures and heaps](topics/monotonic-and-heaps/README.md#main-algorithms-and-structures) | [Dominance + expiry; prefix sums + deque; indexed removal + balanced halves](topics/monotonic-and-heaps/README.md#combinations-and-tricks) |
| Fenwick, merge-sort trees, segment trees | [Range queries](topics/range-queries/README.md#main-algorithms-and-structures) | [Compression + range aggregation; subtree counts + kth selection; ordered aggregate + merge](topics/range-queries/README.md#combinations-and-tricks) |
| DSU, BFS/DFS, Dijkstra, topological order, lowlink | [DSU and graphs](topics/dsu-and-graphs/README.md#main-algorithms-and-structures) | [Reverse time + connectivity; heap + path relaxation; postorder + edge consumption](topics/dsu-and-graphs/README.md#combinations-and-tricks) |
| Tree summaries, pointer rewiring, traversal | [Trees and lists](topics/trees-and-lists/README.md#main-algorithms-and-structures) | [Return one branch + update a complete path; reverse groups + reconnect; list + heap](topics/trees-and-lists/README.md#combinations-and-tricks) |
| Memoization, state compression, backtracking | [DP and backtracking](topics/dp-and-backtracking/README.md#main-algorithms-and-structures) | [DAG + memoized DFS; paired extrema; mark/recurse/restore](topics/dp-and-backtracking/README.md#combinations-and-tricks) |
| KMP, tries, string parsing and matching | [Strings and tries](topics/strings-and-tries/README.md#main-algorithms-and-structures) | [Reversal + delimiter + LPS; suffix/prefix encoding + trie; nested state + stacks](topics/strings-and-tries/README.md#combinations-and-tricks) |
| Hash maps, lists, frequency groups, dense arrays | [Design structures](topics/design-structures/README.md#main-algorithms-and-structures) | [Lookup + stable iterators; frequency + recency; swap-tail + index repair](topics/design-structures/README.md#combinations-and-tricks) |
| Interval scans, two pointers, greedy frontiers | [Greedy and intervals](topics/greedy-and-intervals/README.md#main-algorithms-and-structures) | [Sorting + exchange argument; interval grouping + frontier; greedy choice + feasibility](topics/greedy-and-intervals/README.md#combinations-and-tricks) |
| Counting, bit summaries, geometry, digit generation | [Math and bits](topics/math-and-bits/README.md#main-algorithms-and-structures) | [Pair summaries + compatibility; multiplicities + combinations; geometry + hashing](topics/math-and-bits/README.md#combinations-and-tricks) |

## Combine structures around an invariant

These are compositions actually present in the captured sources, not a list of hypothetical templates.

| Recognition trigger | Compose | Invariant to recall | Direct implementation |
| --- | --- | --- | --- |
| Count intervals whose sum equals a target | Prefix sum + frequency map | Before inserting the current prefix, count earlier prefixes at `sum-k` | [Prefix frequencies](topics/windows-and-prefixes/snippets/prefix-sum-frequency.cpp) |
| Shortest interval reaches a target even with negative values | Prefix sum + monotonic deque | Later, no-larger prefixes dominate older candidates; feasible oldest candidates can be retired | [Monotonic prefix deque](topics/monotonic-and-heaps/snippets/shortest-subarray-monotonic-deque.cpp) |
| Count sums in a numeric band | Prefix sums + sorted coordinates + Fenwick counts | Remove the current prefix before counting compatible later ones | [Range-sum counting](topics/range-queries/originals/327__2152424852.cpp) |
| Place items by the number of empty slots before them | Sorting + count segment tree + rank descent | A subtree count is the number of still-available positions | [Kth empty position](topics/range-queries/originals/406__2152399602.cpp) |
| Blocks fall onto large-coordinate intervals | Coordinate compression + lazy assignment/max tree | Query the old maximum, then assign the new common top height | [Compressed falling squares](topics/range-queries/originals/699__2155079538.cpp) |
| Deletions make online connectivity awkward | Reverse processing + DSU + boundary sentinels | Reversing deletions produces only component merges | [Reverse-time connectivity](topics/dsu-and-graphs/snippets/reverse-dsu-last-day-to-cross.cpp) |
| Need shortest cost or smallest path bottleneck | Min-heap + finalized states + a path extension rule | Pop the smallest candidate; extend with addition or maximum | [Additive Dijkstra](topics/dsu-and-graphs/snippets/dijkstra-network-delay.cpp), [minimax variant](topics/dsu-and-graphs/snippets/dijkstra-minimax-grid.cpp) |
| Need lookup, eviction order, and cheap moves | Hash map + linked list + stored iterators | Each map entry points to exactly one live list node | [LRU](topics/design-structures/snippets/lru-cache.cpp), [frequency buckets for LFU](topics/design-structures/snippets/lfu-cache.cpp) |
| Need median while old duplicate values leave | Two ordered multisets + unique indexes + iterator map | Halves stay ordered and size-balanced; indexes identify exact occurrences | [Sliding median helper](topics/monotonic-and-heaps/snippets/sliding-median-finder-struct.cpp) |
| Need the best path through a branching node | Postorder + child summaries + global best | Return one extendable branch; combine two only for the completed answer | [Maximum path sum](topics/trees-and-lists/snippets/dfs-maximum-path-sum.cpp) |
| Need the longest palindromic prefix | Reverse string + safe delimiter + KMP LPS | The final border cannot cross the delimiter as an ordinary character match | [Shortest-palindrome KMP](topics/strings-and-tries/snippets/shortest-palindrome-kmp.cpp) |
| Count tuples with repeated pair outcomes | Pair enumeration + frequency map + compatibility test | Frequencies preserve index multiplicity after collapsing equal summaries | [Sum complements](topics/math-and-bits/snippets/four-sum-pair-frequency.cpp), [AND-mask compatibility](topics/math-and-bits/snippets/bitwise-and-pair-frequency.cpp) |
| Circular order must reuse candidates without duplicating state | Register original indexes once + replay value candidates | Every pending index is resolved at most once | [Circular next greater](topics/monotonic-and-heaps/snippets/circular-next-greater-two-passes.cpp) |
| Pair alignment changes once | Binary search + parity-matched neighbor | Even/odd pairs agree before the singleton | [Pair parity](topics/search-and-sort/snippets/binary-search-pair-parity.cpp) |
| Deletion constraints collapse to one modular length | Equal-remainder runs + gcd progression | Valid lengths are 1 modulo k/gcd(k,r) | [Gcd-rounded run length](topics/math-and-bits/snippets/equal-remainder-run-gcd-length.cpp) |
| AND/OR operations preserve bit inventories | Bit counts + convex concentration | Each constructed number consumes at most one occurrence of every available bit | [Conserved bit layers](topics/math-and-bits/snippets/conserved-bit-count-concentration.cpp) |
| Each sorted product row is implicit | One heap head per row + unique successor | No pair needs multiple discovery paths | [Cartesian row frontier](topics/monotonic-and-heaps/snippets/implicit-cartesian-row-frontier.cpp) |
| A few expensive steps can be made free | Bounded heap + exchange of the cheapest free step | Free resources cover the largest encountered costs | [Resource allocation](topics/monotonic-and-heaps/snippets/heap-exchange-scarce-free-steps.cpp) |
| Winners have semantic ties | Composite quickselect order + output-only sort | Selection and presentation agree on every tie | [Word-rank selection](topics/search-and-sort/snippets/composite-rank-quickselect-words.cpp) |
| Arrival order and execution priority differ | Sorted arrival pointer + ready-task heap + clock jumps | Admit all due tasks before each non-preemptive choice | [Event-driven scheduler](topics/monotonic-and-heaps/snippets/sorted-arrivals-ready-task-heap.cpp) |
| Need the immediate next multiset arrangement | Rightmost pivot + smallest increase + suffix reversal | Preserve the longest prefix, then minimize the tail | [Next permutation](topics/search-and-sort/snippets/lexicographic-pivot-suffix-reversal.cpp) |
| Leaves need the complete ancestor path | Depth-indexed buffer + leaf-only evaluation | Only the current prefix is read; leaf rescans determine cost | [Path-buffer method](topics/trees-and-lists/snippets/shared-path-buffer-leaf-evaluation.cpp) |
| A fixed sum must maximize bounded digit squares | Concentrate mass + quotient/remainder + descending construction | At most one digit is neither zero nor nine | [Digit concentration](topics/math-and-bits/snippets/bounded-digit-concentration.cpp) |
| Static rectangle totals need four boundary terms | Padded 2D prefixes + inclusion–exclusion | Subtract excluded strips and restore their shared corner | [Rectangle sums](topics/range-queries/snippets/padded-2d-prefix-rectangle.cpp) |
| One new value changes a whole interval of subarray starts | Last occurrence + additive lazy first/second moments | Update Σx² using the old Σx, then update Σx | [Distinct-count moments](topics/range-queries/snippets/last-occurrence-lazy-moments.cpp) |
| A unique sorted arrangement is reached by arbitrary swaps | Original indexes + permutation cycles | A cycle of length c contributes c−1 swaps | [Cycle count](topics/search-and-sort/snippets/composite-key-permutation-cycles.cpp) |
| Sorted tree values must be consumed incrementally | Deferred left spine + stack | The stack top is the next unvisited inorder node | [Lazy iterator](topics/trees-and-lists/snippets/deferred-inorder-stack-iterator.cpp) |

## Read the cost of this implementation

Topic tables distinguish preprocessing from operations, auxiliary state from returned output, expected hashing from worst-case guarantees, and recursion/copies from in-place work. Their bounds describe the linked variant, not every algorithm with the same name.

Examples: the custom hash map has 32 fixed buckets; quickselect has a deterministic pivot and quadratic worst case; a sliding median uses ordered multisets; one prerequisite traversal has no visited guard; some DSU variants lack valid size balancing. Those details remain visible beside the relevant ideas. A correct reduction can still have an inefficient or fragile captured implementation.

## Source and provenance appendix

- [Complete source index](SOURCES.md): all problems and every retained submission, including duplicates.
- [Coverage and limitations](COVERAGE.md): aggregate history-verification results, methodology, and unresolved count differences.
- [Validation](VALIDATION.md): byte-fidelity checks and their limits.
- [Source manifest](sources.json): submission IDs, URLs, SHA-256 values, local paths.
- [Snippet manifest](snippets.json): exact byte/line ranges and hashes.
- [Tab-separated source index](source-index.tsv): compact searchable records.

### Original code, original context


This repository adds navigation and explanation around the original code. It introduces no shared algorithm framework, rewritten templates, extra guards, new namespaces, or standardized interfaces. There is no combined build: many files deliberately define their own `Solution`, `Node`, or other problem-specific types.

The sources were captured from LeetCode and may rely on its standard-library setup, provided node types, problem APIs, compiler mode, and problem constraints. Some sources use C++20 features. They are not all standalone translation units. Original comments keep their original language; explanatory prose is English.

Acceptance on the original problem is not proof of correctness for unrestricted inputs, repeated object reuse, or a different harness. Imperfections remain unchanged. Submission links may require access to the original LeetCode account; the local copies do not.

### Verify source fidelity

Run from this folder:

```bash
python3 tools/check_originals.py
python3 tools/verify_snippets.py
```

For an additional byte-for-byte comparison with the separately retained normalized capture:

```bash
python3 tools/check_originals.py --capture-json /path/to/normalized-records.json
```

The original-source checker verifies recorded hashes, source IDs, local paths, source coverage, and that every original is linked from its topic index. The snippet checker verifies that all 116 excerpts are literal source slices. Neither checker compiles the solutions or asserts that every algorithm works outside its original LeetCode context.
