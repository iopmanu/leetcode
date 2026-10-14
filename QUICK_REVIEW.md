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
| Positive products admit every suffix of a valid window | Shrink product + count endings | After restoration, every start in the window qualifies; count right-left+1 | [Product window](topics/windows-and-prefixes/snippets/positive-product-window.cpp) |
| Fixed-length candidates need distinct values and a best sum | Frequency map + running sum | Erasing zero counts makes map size equal the number of live values | [Distinct-window sum](topics/windows-and-prefixes/snippets/fixed-window-distinct-sum.cpp) |
| One sorted pair makes many index pairs feasible | Fix largest side + bulk count | Every left index up to right-1 has at least the tested left value | [Triangle count](topics/search-and-sort/snippets/triangle-two-pointer-count.cpp) |
| One item can occupy each nonnegative value | Dense counts + upward surplus carry | Every excess item must pay once to leave a full slot | [Duplicate carry](topics/greedy-and-intervals/snippets/dense-bucket-duplicate-carry.cpp) |
| Return every partition using a reused validity predicate | Palindrome table + push/recurse/pop | The current pieces concatenate to exactly the processed prefix | [Partition paths](topics/dp-and-backtracking/snippets/palindrome-table-partition-enumeration.cpp) |
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

- [Palindrome partitioning](topics/dp-and-backtracking/snippets/palindrome-table-partition-enumeration.cpp) keeps the literal inclusive `l <= s.size()` loop; its terminator comparison depends on non-NUL input.
- [Duplicate buckets](topics/greedy-and-intervals/snippets/dense-bucket-duplicate-carry.cpp) allocate by maximum value plus input length, not just the number of distinct values.
- [Closest triple](topics/search-and-sort/snippets/three-sum-closest-frontier.cpp) retains an `int` sentinel and `int` differences; its bounded source contract matters.

For all retained variants and their context, use the final appendix in each [topic chapter](README.md#topics). No original has been silently repaired or replaced with a new template.

- The [H-Index II original](topics/search-and-sort/originals/275__2170348113.cpp) rescans all citations per binary-search predicate: O(n log(n+1)), not O(log n).
- The [unique-sum window](topics/windows-and-prefixes/originals/1695__2170086755.cpp) initializes one million counters; its literal cost includes that fixed domain.
