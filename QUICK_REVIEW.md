# Quick review: recognize, compose, recall

Use [the topic algorithm tables](README.md#topics) to choose a building block and check its actual cost. Use [exact snippets](SNIPPETS.md) for implementation recall. The problem catalogs are supporting appendices.

## One-minute composition prompts

Cover the invariant column, explain why the composition works, then open the original code. All examples below are observed implementations.

| If you recognize… | Try composing… | State this invariant | Open the implementation |
| --- | --- | --- | --- |
| Repeated interval-sum queries/counts | Prefix algebra + hash frequencies | Only earlier prefixes are eligible; query before insert | [Prefix counts](topics/windows-and-prefixes/snippets/prefix-sum-frequency.cpp) |
| Negative values break ordinary shrinking | Prefix sums + monotonic candidates | A later lower prefix is at least as useful for every future end | [Shortest interval deque](topics/monotonic-and-heaps/snippets/shortest-subarray-monotonic-deque.cpp) |
| Broad coordinate updates, narrow queries | Lazy tree + the operation’s composition rule | Assignment overwrites; chmin composes by minimum; their identities differ | [Assignment/max](topics/range-queries/snippets/lazy-segment-tree-699.cpp), [chmin/min](topics/range-queries/snippets/segment-tree-range-chmin.cpp) |
| Need a position by remaining rank | Subtree counts + descent | Go right only after subtracting all available slots in the left child | [Order-statistic tree](topics/range-queries/snippets/order-statistic-segment-tree-406.cpp) |
| Connectivity under removals | Reverse time + DSU | The reversed process only adds vertices/edges | [Reverse DSU](topics/dsu-and-graphs/snippets/reverse-dsu-last-day-to-cross.cpp) |
| One weighted path objective changes | Heap traversal + new path aggregation | `sum` and `max` are different extension rules; the finalized frontier is still ordered by path cost | [Dijkstra](topics/dsu-and-graphs/snippets/dijkstra-network-delay.cpp), [minimax](topics/dsu-and-graphs/snippets/dijkstra-minimax-grid.cpp) |
| Need to know whether an edge is indispensable | Baseline MST + omit/force edge + DSU rebuild | Compare feasibility and total weight against the same baseline optimum | [Critical/pseudo-critical edges](topics/dsu-and-graphs/snippets/kruskal-critical-and-pseudo-critical-edges.cpp) |
| Need exact removal among equal ordered values | Ordered multisets + indexes + iterator lookup | Identity is the index; order is the value; balancing preserves the median | [Median structure](topics/monotonic-and-heaps/snippets/sliding-median-finder-struct.cpp) |
| Negative multiplication can improve a bad state | Two DP extrema | Both updates read the previous maximum and minimum | [Maximum product](topics/dp-and-backtracking/snippets/maximum-product-two-states.cpp) |
| Tree paths can branch, returned paths cannot | Child summary + global best | Return one branch; test both branches only at their common root | [Tree path summary](topics/trees-and-lists/snippets/dfs-maximum-path-sum.cpp) |
| Repeated string-prefix work | Prefix-function fallback | A mismatch keeps the longest proper border already known to match | [KMP](topics/strings-and-tries/snippets/kmp-search.cpp) |
| Two string constraints must be indexed together | Encode suffix + separator + prefix in a trie | A single trie path represents both constraints and the latest matching index | [Prefix/suffix trie](topics/strings-and-tries/snippets/prefix-suffix-trie.cpp) |
| Lookup and order require different operations | Hash lookup + stable list nodes | Every live key maps to the iterator for its current node | [LRU](topics/design-structures/snippets/lru-cache.cpp) |
| Counting choices dominates generating answers | Aggregate pair summaries / value multiplicities | Preserve the number of index choices after collapsing equal values | [Pair-sum counts](topics/math-and-bits/snippets/four-sum-pair-frequency.cpp), [multiplicity cases](topics/math-and-bits/snippets/three-sum-multiplicity-cases.cpp) |

## Before adapting an original

1. **Define the state.** What does one stored count, node, iterator, mask, or DP cell mean?
2. **Explain the transition.** Why can a candidate be popped, skipped, finalized, merged, or forgotten permanently?
3. **Account for the composition.** Include sorting, coordinate construction, heap duplicates, string copies, recursion, retained maps, and output. Hashing is expected-time unless stronger assumptions are justified.
4. **Check the contract.** Inclusive bounds? Empty input? Duplicate identity? Sentinel value? Integer width? Input mutation? Member state reset? LeetCode-provided types?
5. **Compare the actual variant.** The full original is authoritative. A short excerpt may omit its caller and domain restrictions.

## Source-specific traps to remember

- [Lazy assignment](topics/range-queries/snippets/lazy-segment-tree-699.cpp) uses zero to mean “no pending assignment”; it is specialized to positive heights.
- [Raw-coordinate interval tree](topics/range-queries/originals/1851__2168532079.cpp) allocates by the largest endpoint, not the number of intervals.
- [Quickselect](topics/search-and-sort/snippets/quickselect-helper.cpp) is recursive with a deterministic pivot, not a guaranteed linear-time selection implementation.
- [Fixed-bucket hash map](topics/design-structures/snippets/custom-hash-map.cpp) does not resize; [LRU](topics/design-structures/snippets/lru-cache.cpp) assumes positive capacity.
- [Word search](topics/dp-and-backtracking/snippets/word-search-mark-restore.cpp) uses bitwise OR, so every branch is evaluated even after a match.
- [KMP palindrome encoding](topics/strings-and-tries/snippets/shortest-palindrome-kmp.cpp) requires its delimiter to be outside the input alphabet.

For all retained variants and their context, use the final appendix in each [topic chapter](README.md#topics). No original has been silently repaired or replaced with a new template.
