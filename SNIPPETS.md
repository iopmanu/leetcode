# Snippet navigator: building blocks and compositions

Choose the state you need to maintain, then open its implementation. [Topic tables](README.md#topics) give source-specific time/space costs; [quick review](QUICK_REVIEW.md) asks you to recover the invariant before reading the code.

## Find a building block

| Need to maintain or discover… | Open these exact fragments | Compose them in context |
| --- | --- | --- |
| An ordered boundary or a rank | [Binary search](topics/search-and-sort/snippets/binary-search.cpp), [lower bound](topics/search-and-sort/snippets/binary-search-insert-position.cpp), [quickselect](topics/search-and-sort/snippets/quickselect-helper.cpp) | [Search + sorting tricks](topics/search-and-sort/README.md#combinations-and-tricks) |
| Sorted runs and pair relationships | [Merge-sort pair counting](topics/search-and-sort/snippets/merge-sort-reverse-pairs.cpp), [3Sum pointers](topics/search-and-sort/snippets/three-sum-skip-duplicates.cpp) | [Sorting + counting](topics/search-and-sort/README.md#combinations-and-tricks) |
| Interval totals, coverage, or outstanding counts | [Prefix frequencies](topics/windows-and-prefixes/snippets/prefix-sum-frequency.cpp), [difference array](topics/windows-and-prefixes/snippets/difference-array-capacity.cpp), [covering window](topics/windows-and-prefixes/snippets/minimum-covering-window.cpp) | [Algebra + count state](topics/windows-and-prefixes/README.md#combinations-and-tricks) |
| A frontier of undominated candidates | [Histogram stack](topics/monotonic-and-heaps/snippets/histogram-monotonic-stack.cpp), [prefix-sum deque](topics/monotonic-and-heaps/snippets/shortest-subarray-monotonic-deque.cpp) | [Dominance + expiry](topics/monotonic-and-heaps/README.md#combinations-and-tricks) |
| Dynamic rank, range sum, or aggregated intervals | [Fenwick](topics/range-queries/snippets/fenwick-307.cpp), [merge-sort tree](topics/range-queries/snippets/merge-sort-tree-315.cpp), [kth empty slot](topics/range-queries/snippets/order-statistic-segment-tree-406.cpp) | [Compression + counting + descent](topics/range-queries/README.md#combinations-and-tricks) |
| Range updates with a composable pending operation | [Assignment/max](topics/range-queries/snippets/lazy-segment-tree-699.cpp), [chmin/min](topics/range-queries/snippets/segment-tree-range-chmin.cpp), [ordered product aggregate](topics/range-queries/snippets/ordered-product-segment-tree-3525.cpp) | [Lazy operation and merge invariants](topics/range-queries/README.md#combinations-and-tricks) |
| Components under additions | [Union-find](topics/dsu-and-graphs/snippets/union-find-struct.cpp), [reverse-time DSU](topics/dsu-and-graphs/snippets/reverse-dsu-last-day-to-cross.cpp), [Kruskal](topics/dsu-and-graphs/snippets/kruskal-min-cost-connect-points.cpp) | [Connectivity + time reversal or edge order](topics/dsu-and-graphs/README.md#combinations-and-tricks) |
| A reachable frontier, shortest cost, or bottleneck | [Multi-source BFS](topics/dsu-and-graphs/snippets/bfs-multi-source-rotting-oranges.cpp), [Dijkstra](topics/dsu-and-graphs/snippets/dijkstra-network-delay.cpp), [minimax Dijkstra](topics/dsu-and-graphs/snippets/dijkstra-minimax-grid.cpp) | [Traversal + path-state choice](topics/dsu-and-graphs/README.md#combinations-and-tricks) |
| Dependency or cut information | [Kahn order](topics/dsu-and-graphs/snippets/topological-sort-kahn.cpp), [cycle states](topics/dsu-and-graphs/snippets/directed-cycle-dfs.cpp), [lowlink bridges](topics/dsu-and-graphs/snippets/tarjan-bridges.cpp) | [Traversal order + summaries](topics/dsu-and-graphs/README.md#combinations-and-tricks) |
| An extendable tree summary or linked chain | [Diameter](topics/trees-and-lists/snippets/dfs-diameter.cpp), [maximum path](topics/trees-and-lists/snippets/dfs-maximum-path-sum.cpp), [group reversal](topics/trees-and-lists/snippets/reverse-k-group.cpp) | [Return a partial result, combine a full answer](topics/trees-and-lists/README.md#combinations-and-tricks) |
| Reusable subproblem results or reversible choices | [Memoized grid DFS](topics/dp-and-backtracking/snippets/memo-longest-increasing-path.cpp), [two extrema](topics/dp-and-backtracking/snippets/maximum-product-two-states.cpp), [mark/restore](topics/dp-and-backtracking/snippets/word-search-mark-restore.cpp) | [State compression + DAG or backtracking](topics/dp-and-backtracking/README.md#combinations-and-tricks) |
| Reusable prefixes or combined string constraints | [KMP](topics/strings-and-tries/snippets/kmp-search.cpp), [palindrome KMP](topics/strings-and-tries/snippets/shortest-palindrome-kmp.cpp), [trie](topics/strings-and-tries/snippets/trie-prefix-tree.cpp), [suffix/prefix trie](topics/strings-and-tries/snippets/prefix-suffix-trie.cpp) | [Encoding + prefix structure](topics/strings-and-tries/README.md#combinations-and-tricks) |
| Lookup plus mutable order, identity, or frequency | [LRU](topics/design-structures/snippets/lru-cache.cpp), [LFU](topics/design-structures/snippets/lfu-cache.cpp), [frequency stack](topics/design-structures/snippets/frequency-stack.cpp), [swap-tail set](topics/design-structures/snippets/randomized-set-swap-tail.cpp), [indexed median](topics/monotonic-and-heaps/snippets/sliding-median-finder-struct.cpp) | [Combine structures by complementary operations](topics/design-structures/README.md#combinations-and-tricks) |
| Feasible intervals or combinatorial multiplicities | [Earliest finish](topics/greedy-and-intervals/snippets/earliest-finish-intervals.cpp), [merge intervals](topics/greedy-and-intervals/snippets/merge-intervals.cpp), [pair sums](topics/math-and-bits/snippets/four-sum-pair-frequency.cpp), [pair AND masks](topics/math-and-bits/snippets/bitwise-and-pair-frequency.cpp) | [Greedy proofs](topics/greedy-and-intervals/README.md#combinations-and-tricks), [counting reductions](topics/math-and-bits/README.md#combinations-and-tricks) |

## What the excerpts preserve

All **69 `.cpp` fragments** are unchanged contiguous slices of captured submissions. Names, types, indentation, comments, helpers, and quirks remain as written. Some need the original class, includes, LeetCode node types, or caller: the context below each link identifies these dependencies. [Full originals](SOURCES.md) retain the complete submitted code; [snippet provenance](snippets.json) records the exact ranges.

The snippets are not a newly designed standalone library. `tools/verify_snippets.py` verifies exact equality, not correctness for arbitrary inputs.

**Graph coverage:** additive and minimax Dijkstra are captured. The [two-arrival-time implementation](topics/dsu-and-graphs/snippets/two-distinct-arrival-times.cpp) uses a deque and two distinct times, not Yen’s simple-path algorithm. No original Prim or Yen implementation is verified; the captured point-MST variants use Kruskal/DSU. Missing code has not been invented.

## Implementation context

The remaining entries are organized by reusable building block. Problem titles identify provenance, rather than define the navigation.

## Search, partition, and rearrange

[Algorithms, costs, and tricks](topics/search-and-sort/README.md)

### [Binary search: lower-bound insertion position](topics/search-and-sort/snippets/binary-search-insert-position.cpp)

Original: [35. Search Insert Position](topics/search-and-sort/originals/35__2146678224.cpp#L3-L15) · [submission 2146678224](https://leetcode.com/problems/search-insert-position/submissions/2146678224/)

Complete original searchInsert method. The remaining left position is the first index whose value is at least target, or nums.size() when no such value exists. Assumes nums is sorted in ascending order. Uses the original unqualified vector and LeetCode compilation context.

### [Binary search: rotation pivot and translated index](topics/search-and-sort/snippets/binary-search-rotated-array.cpp)

Original: [33. Search in Rotated Sorted Array](topics/search-and-sort/originals/33__2125939691.cpp#L3-L33) · [submission 2125939691](https://leetcode.com/problems/search-in-rotated-sorted-array/submissions/2125939691/)

Complete original search method from submission 2125939691. First finds the rotation pivot against nums.back(), then translates mid through (mid + rotation) % nums.size(). This is a particular earlier original submission, not a correction of a newer version. Assumes the distinct-value rotated-array problem conditions. Keeps the original unused n variable. Uses the original unqualified vector and LeetCode compilation context.

### [Binary search: closed interval](topics/search-and-sort/snippets/binary-search.cpp)

Original: [704. Binary Search](topics/search-and-sort/originals/704__2146675354.cpp#L3-L17) · [submission 2146675354](https://leetcode.com/problems/binary-search/submissions/2146675354/)

Complete original search method, preserving its closed interval [left, right], original names, and indentation. Returns an index or -1. Assumes nums is sorted in ascending order. Uses the original unqualified vector and LeetCode compilation context.

### [Merge sort with reverse-pair counting](topics/search-and-sort/snippets/merge-sort-reverse-pairs.cpp)

Original: [493. Reverse Pairs](topics/search-and-sort/originals/493__2150875619.cpp#L1-L65) · [submission 2150875619](https://leetcode.com/problems/reverse-pairs/submissions/2150875619/)

Complete original Solution is retained because merge and mergeSort use the class result accumulator. Counts cross-half pairs using 2LL * R[j], then performs the merge. The original wrapper and result declaration remain unchanged. Sorts nums in place. result is initialized once; calling reversePairs again on the same Solution object does not reset it. Requires the original LeetCode vector and standard-library context.

### [Quickselect: in-place partition helper](topics/search-and-sort/snippets/quickselect-helper.cpp)

Original: [215. Kth Largest Element in an Array](topics/search-and-sort/originals/215__2144679787.cpp#L7-L34) · [submission 2144679787](https://leetcode.com/problems/kth-largest-element-in-an-array/submissions/2144679787/)

Complete original quickselect member function with indentation unchanged. Its original findKthLargest wrapper passes left=0, right=nums.size()-1, and k=nums.size()-k; the helper k is a zero-based ascending rank. Recursion mutates nums, and the original ignores recursive return values before returning nums[k]. Mutates nums and assumes a valid nonempty range and rank. Deterministic middle-element pivot has quadratic worst-case running time. Uses the original unqualified vector and LeetCode compilation context.

### [3Sum: fixed index, opposing pointers, and duplicate skips](topics/search-and-sort/snippets/three-sum-skip-duplicates.cpp)

Original: [15. 3Sum](topics/search-and-sort/originals/15__2147771319.cpp#L3-L35) · [submission 2147771319](https://leetcode.com/problems/3sum/submissions/2147771319/)

Complete original threeSum method. Sorts nums in place, fixes one index, scans the remaining pair from both ends, and skips repeated values after emitting a triple. The n>=3 and bounded-int-sum assumptions of the source problem remain: nums.size()-2 is unsigned and sum remains int. The quadratic scan and original vector output construction are unchanged.

### [Array rotation: reverse suffix, prefix, then whole array](topics/search-and-sort/snippets/array-rotation-three-reversals.cpp)

Original: [189. Rotate Array](topics/search-and-sort/originals/189__2147800911.cpp#L3-L9) · [submission 2147800911](https://leetcode.com/problems/rotate-array/submissions/2147800911/)

Complete original rotate method. Reduces k modulo nums.size(), reverses the final k elements, the preceding prefix, and then the full vector. Mutates the array in O(n) time and O(1) auxiliary space. Requires the original nonempty-array and nonnegative-k contract; no empty-input guard was added.


## Maintain window and prefix state

[Algorithms, costs, and tricks](topics/windows-and-prefixes/README.md)

### [Sliding window: satisfy counts, then shrink](topics/windows-and-prefixes/snippets/minimum-covering-window.cpp)

Original: [76. Minimum Window Substring](topics/strings-and-tries/originals/76__2149102883.cpp#L3-L34) · [submission 2149102883](https://leetcode.com/problems/minimum-window-substring/submissions/2149102883/)

Complete original minWindow method. counts stores outstanding multiplicities; matches counts character kinds still missing. The original problem requires nonempty t; this exact method does not add an empty-target guard. Its if-initializers are original C++17 syntax.

### [Prefix sums: count prior sums equal to current - k](topics/windows-and-prefixes/snippets/prefix-sum-frequency.cpp)

Original: [560. Subarray Sum Equals K](topics/windows-and-prefixes/originals/560__2130713437.cpp#L1-L23) · [submission 2130713437](https://leetcode.com/problems/subarray-sum-equals-k/submissions/2130713437/)

Whole original captured code is retained so the two introductory prefix-equation comments stay attached to the method without edits. Seeds counts[0] = 1, queries before inserting the current prefix, and keeps the original int accumulator/count types.

### [Difference array: range capacity and prefix reconstruction](topics/windows-and-prefixes/snippets/difference-array-capacity.cpp)

Original: [3355. Zero Array Transformation I](topics/windows-and-prefixes/originals/3355__2119740763.cpp#L3-L19) · [submission 2119740763](https://leetcode.com/problems/zero-array-transformation-i/submissions/2119740763/)

Complete original isZeroArray method. Each inclusive range increments diffs[left] and decrements diffs[right+1]; its prefix sum is the available decrement capacity. The n+1 allocation retains the closing marker past the last element. Queries offer independent optional decrements, so the check is capacity>=nums[i], not equality. Runs in O(n+q) time with O(n) auxiliary space under the original valid-index contract.

### [Unique-character window: jump past the previous occurrence](topics/windows-and-prefixes/snippets/window-last-seen-character.cpp)

Original: [3. Longest Substring Without Repeating Characters](topics/windows-and-prefixes/originals/3__2027316499.cpp#L3-L17) · [submission 2027316499](https://leetcode.com/problems/longest-substring-without-repeating-characters/submissions/2027316499/)

Complete original lengthOfLongestSubstring method. Last-seen indexes remain in the hash map, and left=max(left,last+1) prevents an old occurrence from moving the window backward. Expected linear time with alphabet-sized map state, plus the original by-value string copy. contains requires C++20; the unqualified max call and all names are preserved.

## Keep undominated or ordered candidates

[Algorithms, costs, and tricks](topics/monotonic-and-heaps/README.md)

### [Monotonic stack: histogram rectangle boundaries](topics/monotonic-and-heaps/snippets/histogram-monotonic-stack.cpp)

Original: [84. Largest Rectangle in Histogram](topics/monotonic-and-heaps/originals/84__2146612938.cpp#L3-L28) · [submission 2146612938](https://leetcode.com/problems/largest-rectangle-in-histogram/submissions/2146612938/)

Complete original largestRectangleArea method. Stores bar indices, pops strictly higher bars when a smaller bar arrives, and flushes the remaining stack against the end of the histogram. Keeps the original int area arithmetic; it is not a widened general-purpose implementation. Requires the original LeetCode vector, stack, and algorithm compilation context.

### [Monotonic deque: prefix-sum shortest subarray](topics/monotonic-and-heaps/snippets/shortest-subarray-monotonic-deque.cpp)

Original: [862. Shortest Subarray with Sum at Least K](topics/monotonic-and-heaps/originals/862__2152907567.cpp#L3-L26) · [submission 2152907567](https://leetcode.com/problems/shortest-subarray-with-sum-at-least-k/submissions/2152907567/)

Complete original shortestSubarray method. The original deque direction is intentional: new indices enter at the front, dominated newest indices leave the front, and qualifying oldest indices leave the back. The source uses vector<int> prefixes exactly as submitted. Prefix sums and their differences use int and can overflow for large totals; this original has not been corrected. Requires the original LeetCode vector, deque, algorithm, and INT_MAX compilation context.

### [MedianFinder: two ordered multisets with indexed removal](topics/monotonic-and-heaps/snippets/sliding-median-finder-struct.cpp)

Original: [480. Sliding Window Median](topics/monotonic-and-heaps/originals/480__2150661436.cpp#L7-L69) · [submission 2150661436](https://leetcode.com/problems/sliding-window-median/submissions/2150661436/)

Complete original nested MedianFinder struct, including aliases, members, methods, private label, and indentation. The left multiset is descending; the right multiset is ascending. Original source has vector, set, unordered_map, and utility includes and a medianSlidingWindow wrapper; these remain in the full original source rather than being copied into this contiguous struct slice. Uses contains, so it retains its original C++20 requirement. findMedian assumes at least one stored element. Indices identify active elements and must not be reused while still present. This helper uses ordered multisets rather than priority_queue heaps.

## Aggregate and update ranges

[Algorithms, costs, and tricks](topics/range-queries/README.md)

### [Fenwick tree: original NumArray class (307)](topics/range-queries/snippets/fenwick-307.cpp)

Original: [307. Range Sum Query - Mutable](topics/range-queries/originals/307__2152356890.cpp#L1-L44) · [submission 2152356890](https://leetcode.com/problems/range-sum-query-mutable/submissions/2152356890/)

Requires the original C++ environment for std::vector and unqualified vector. Public indices are zero-based; sumRange uses inclusive bounds. query(-1) returns zero. Update indices must be valid, and sums/deltas remain int as in the original. Includes the complete original class, preserving the linear build and assignment-to-delta update. The LeetCode instantiation comment after the class is outside this fragment.

### [Fenwick tree: initially-one frequency tree (327)](topics/range-queries/snippets/fenwick-327.cpp)

Original: [327. Count of Range Sum](topics/range-queries/originals/327__2152424852.cpp#L2-L27) · [submission 2152424852](https://leetcode.com/problems/count-of-range-sum/submissions/2152424852/)

Requires std::vector. Every position starts at one, not zero. add is a zero-based delta update and getSum is an inclusive prefix sum; getSum(-1) returns zero. Valid indices are required. The original caller supplies sorted prefix sums, retains duplicates and removes the current occurrence before counting. Complete nested struct only; no dependency on outer Solution fields. Original indentation retained.

### [Lazy segment tree: range assignment and maximum (699)](topics/range-queries/snippets/lazy-segment-tree-699.cpp)

Original: [699. Falling Squares](topics/range-queries/originals/699__2155079538.cpp#L5-L77) · [submission 2155079538](https://leetcode.com/problems/falling-squares/submissions/2155079538/)

Requires std::vector and std::max. Construct with positive n; original calls use node 0 and segment [0, n-1], with inclusive query/update bounds. lazy == 0 means no pending assignment, so this original helper is for the positive-height assignments in Falling Squares and does not support arbitrary zero assignments correctly. Coordinate compression and interval conversion [l, r-1] belong to the caller. Complete nested struct only; no dependency on outer global/mapping fields. Original indentation retained.

### [Merge-sort tree: count values strictly smaller than val (315)](topics/range-queries/snippets/merge-sort-tree-315.cpp)

Original: [315. Count of Smaller Numbers After Self](topics/range-queries/originals/315__2150760829.cpp#L2-L56) · [submission 2150760829](https://leetcode.com/problems/count-of-smaller-numbers-after-self/submissions/2150760829/)

Requires std::vector, std::merge and std::lower_bound. Static, inclusive range queries count values strictly less than val. The public query returns zero for an empty tree or invalid range instead of clipping bounds. This original earlier variant has the n > 0 constructor guard and accepts std::vector<T>. No point-update operation is provided. Complete original template and nested struct from submission 2150760829. Selected over 2150813916 because that later constructor calls build even when n == 0. Original indentation retained.

### [Order-statistic segment tree: consume kth empty position (406)](topics/range-queries/snippets/order-statistic-segment-tree-406.cpp)

Original: [406. Queue Reconstruction by Height](topics/range-queries/originals/406__2152399602.cpp#L2-L47) · [submission 2152399602](https://leetcode.com/problems/queue-reconstruction-by-height/submissions/2152399602/)

Requires std::vector and positive n. Every leaf starts available. updateAndFind(0, 0, n-1, k) selects and removes the zero-based kth available position; 0 <= k < remaining count is required. Queue reconstruction additionally relies on the original caller sorting height ascending and equal-height k descending. Complete nested struct only; no dependency on outer Solution fields. Original indentation retained.

### [Ordered product-prefix aggregate segment tree (3525)](topics/range-queries/snippets/ordered-product-segment-tree-3525.cpp)

Original: [3525. Find X Value of Array II](topics/range-queries/originals/3525__2150176033.cpp#L1-L85) · [submission 2150176033](https://leetcode.com/problems/find-x-value-of-array-ii/submissions/2150176033/)

Requires the original environment for unqualified vector, array, ceil and log2. Assumes n > 0, 1 <= k <= 5 and nonnegative values; MAXK is 6 and slot k stores the interval product. query/update calls use node 1 and segment [0, n-1]. Queries must be valid nonempty inclusive ranges. mergePre must retain left-to-right order: the aggregate counts prefixes, so swapping child order changes results. Complete original top-level SegmentTree class. No outer Solution fields are required; the original Solution calling loop is outside this fragment.

### [Lazy segment tree: range-chmin updates and range-min queries](topics/range-queries/snippets/segment-tree-range-chmin.cpp)

Original: [1851. Minimum Interval to Include Each Query](topics/range-queries/originals/1851__2168532079.cpp#L2-L81) · [submission 2168532079](https://leetcode.com/submissions/detail/2168532079/)

Complete original nested SegmentTree definition, including tree, lazy, capacity, public methods, private overloads, and index helpers. Pending updates compose with min; INT_MAX means no pending bound and is the disjoint-query identity. The original caller allocates maxEnd+1 raw coordinates and makes point queries. Initialization/storage are linear in that coordinate capacity, with logarithmic updates and queries. No coordinate compression, bounds checks, or interface changes were added.


## Compose connectivity and traversal

[Algorithms, costs, and tricks](topics/dsu-and-graphs/README.md)

### [Multi-source BFS by levels](topics/dsu-and-graphs/snippets/bfs-multi-source-rotting-oranges.cpp)

Original: [994. Rotting Oranges](topics/dsu-and-graphs/originals/994__2155965323.cpp#L3-L49) · [submission 2155965323](https://leetcode.com/problems/rotting-oranges/submissions/2155965323/)

Complete original orangesRotting method. Seeds every rotten orange and counts levels while modifying the input grid.

### [BFS: unweighted shortest path through states](topics/dsu-and-graphs/snippets/bfs-open-lock.cpp)

Original: [752. Open the Lock](topics/dsu-and-graphs/originals/752__2156069275.cpp#L3-L43) · [submission 2156069275](https://leetcode.com/problems/open-the-lock/submissions/2156069275/)

Complete original openLock method. Preserves its string-state construction and visited-on-enqueue behavior. This is ordinary BFS, not Dijkstra.

### [Boundary-started DFS](topics/dsu-and-graphs/snippets/dfs-boundary-surrounded-regions.cpp)

Original: [130. Surrounded Regions](topics/dsu-and-graphs/originals/130__2156047108.cpp#L3-L40) · [submission 2156047108](https://leetcode.com/problems/surrounded-regions/submissions/2156047108/)

Complete original solve method with its local dfs lambda and boundary starts. Modifies the board.

### [DFS graph cloning with old-to-new mapping](topics/dsu-and-graphs/snippets/dfs-clone-graph.cpp)

Original: [133. Clone Graph](topics/dsu-and-graphs/originals/133__2155372665.cpp#L1-L50) · [submission 2155372665](https://leetcode.com/problems/clone-graph/submissions/2155372665/)

Complete original captured code, including the commented LeetCode Node definition and full Solution. An actual Node definition is supplied by LeetCode.

### [DFS: count connected grid components](topics/dsu-and-graphs/snippets/dfs-count-islands.cpp)

Original: [200. Number of Islands](topics/dsu-and-graphs/originals/200__2155362152.cpp#L3-L38) · [submission 2155362152](https://leetcode.com/problems/number-of-islands/submissions/2155362152/)

Complete original numIslands method with its local dfs lambda. Modifies the input grid.

### [DFS: aggregate connected-component size](topics/dsu-and-graphs/snippets/dfs-island-area.cpp)

Original: [695. Max Area of Island](topics/dsu-and-graphs/originals/695__2155365320.cpp#L3-L40) · [submission 2155365320](https://leetcode.com/problems/max-area-of-island/submissions/2155365320/)

Complete original maxAreaOfIsland method with its local dfs lambda. Modifies the input grid.

### [Memoized DFS: longest path in a grid DAG](topics/dsu-and-graphs/snippets/dfs-memo-longest-increasing-path.cpp)

Original: [329. Longest Increasing Path in a Matrix](topics/dp-and-backtracking/originals/329__2139455187.cpp#L1-L56) · [submission 2139455187](https://leetcode.com/problems/longest-increasing-path-in-a-matrix/submissions/2139455187/)

Complete original Solution, retaining the dp member, dfs method, visited set, and all original syntax. The initial prev = -1 assumes nonnegative matrix values; dp.resize does not reset existing cells on repeated calls to one Solution object. The original contains call requires C++20.

### [Reverse DFS: reachability from two sets of boundaries](topics/dsu-and-graphs/snippets/dfs-reverse-pacific-atlantic.cpp)

Original: [417. Pacific Atlantic Water Flow](topics/dsu-and-graphs/originals/417__2156035451.cpp#L3-L71) · [submission 2156035451](https://leetcode.com/problems/pacific-atlantic-water-flow/submissions/2156035451/)

Complete original pacificAtlantic method with its local dfs lambda. Retains the original two-bit reachability mask.

### [Directed cycle detection with visiting and visited](topics/dsu-and-graphs/snippets/directed-cycle-dfs.cpp)

Original: [207. Course Schedule](topics/dsu-and-graphs/originals/207__2139396834.cpp#L1-L44) · [submission 2139396834](https://leetcode.com/problems/course-schedule/submissions/2139396834/)

Complete original Solution, retaining both canFinish and dfs. Its auto parameters and contains calls are original C++20 syntax.

### [Directed graph: incoming and outgoing relationships](topics/dsu-and-graphs/snippets/directed-in-out-degree-town-judge.cpp)

Original: [997. Find the Town Judge](topics/dsu-and-graphs/originals/997__2155347510.cpp#L3-L28) · [submission 2155347510](https://leetcode.com/problems/find-the-town-judge/submissions/2155347510/)

Complete original findJudge method, preserving its adjacency maps and candidate selection.

### [Kruskal MST: skip or force an edge](topics/dsu-and-graphs/snippets/kruskal-critical-and-pseudo-critical-edges.cpp)

Original: [1489. Find Critical and Pseudo-Critical Edges in Minimum Spanning Tree](topics/dsu-and-graphs/originals/1489__2162346068.cpp#L1-L98) · [submission 2162346068](https://leetcode.com/problems/find-critical-and-pseudo-critical-edges-in-minimum-spanning-tree/submissions/2162346068/)

Complete original Solution, including its DSU and buildMstWithSkip lambda; all helper dependencies retained unchanged.

### [Kruskal MST: Manhattan complete graph](topics/dsu-and-graphs/snippets/kruskal-min-cost-connect-points.cpp)

Original: [1584. Min Cost to Connect All Points](topics/dsu-and-graphs/originals/1584__2162051692.cpp#L43-L69) · [submission 2162051692](https://leetcode.com/problems/min-cost-to-connect-all-points/submissions/2162051692/)

Complete original minCostConnectPoints method. Requires the original UnionFind struct from union-find-struct.cpp. Creates every undirected edge, sorts by weight, then selects edges with DSU.

### [Reverse-time DSU connectivity](topics/dsu-and-graphs/snippets/reverse-dsu-last-day-to-cross.cpp)

Original: [1970. Last Day Where You Can Still Cross](topics/dsu-and-graphs/originals/1970__2168377479.cpp#L1-L85) · [submission 2168377479](https://leetcode.com/problems/last-day-where-you-can-still-cross/submissions/2168377479/)

Complete original Solution, including the duplicate public: label exactly as submitted. Adds cells in reverse and joins virtual top/bottom nodes.

### [Kahn topological traversal and cycle detection](topics/dsu-and-graphs/snippets/topological-sort-kahn.cpp)

Original: [207. Course Schedule](topics/dsu-and-graphs/originals/207__2139404121.cpp#L3-L33) · [submission 2139404121](https://leetcode.com/problems/course-schedule/submissions/2139404121/)

Complete original canFinish method. Returns whether all courses were processed; does not return an ordering.

### [UnionFind: union by size and path compression](topics/dsu-and-graphs/snippets/union-find-struct.cpp)

Original: [1584. Min Cost to Connect All Points](topics/dsu-and-graphs/originals/1584__2162051692.cpp#L2-L41) · [submission 2162051692](https://leetcode.com/problems/min-cost-to-connect-all-points/submissions/2162051692/)

Complete original nested UnionFind struct. Used by the Kruskal minCostConnectPoints function in kruskal-min-cost-connect-points.cpp; original indentation preserved.

### [Dijkstra: finalize on minimum-heap pop](topics/dsu-and-graphs/snippets/dijkstra-network-delay.cpp)

Original: [743. Network Delay Time](topics/dsu-and-graphs/originals/743__2158089044.cpp#L3-L32) · [submission 2158089044](https://leetcode.com/problems/network-delay-time/submissions/2158089044/)

Complete original networkDelayTime method, including adjacency construction and the unreachable -1 return. A vertex is finalized on its first heap pop; later entries for that vertex are skipped. The original has no tentative-distance table and can retain O(E) candidate paths. Requires nonnegative weights, the original int-range bounds, standard-library includes, and C++20 contains. No names, types, checks, or formatting have been changed.

### [Minimax Dijkstra: minimize the largest height on a path](topics/dsu-and-graphs/snippets/dijkstra-minimax-grid.cpp)

Original: [778. Swim in Rising Water](topics/dsu-and-graphs/originals/778__2159581294.cpp#L3-L42) · [submission 2159581294](https://leetcode.com/problems/swim-in-rising-water/submissions/2159581294/)

Complete original swimInWater method. The heap key is the maximum height encountered so far, and a transition uses max(currentTime, nextHeight). The original i*r+j visited key is preserved and assumes the problem’s square grid; use of contains retains the C++20 requirement. Includes and class context are supplied by the original LeetCode harness. This source is minimax Dijkstra, not Prim.

### [Second arrival: two distinct time labels with red-light waits](topics/dsu-and-graphs/snippets/two-distinct-arrival-times.cpp)

Original: [2045. Second Minimum Time to Reach Destination](topics/dsu-and-graphs/originals/2045__2158128996.cpp#L3-L44) · [submission 2158128996](https://leetcode.com/problems/second-minimum-time-to-reach-destination/submissions/2158128996/)

Complete original secondMinimum method. Keeps two distinct arrival times per vertex, waits through a red traffic-light phase, and propagates with a deque under the original uniform edge-time and synchronized-light rules. Vertices may be revisited. This is not Yen’s simple-path algorithm: there are no root/spur paths or exclusion sets. INT_MAX and the original problem’s guaranteed second arrival remain unchanged.

### [Tarjan lowlink: bridges in an undirected graph](topics/dsu-and-graphs/snippets/tarjan-bridges.cpp)

Original: [1192. Critical Connections in a Network](topics/dsu-and-graphs/originals/1192__2158532377.cpp#L1-L50) · [submission 2158532377](https://leetcode.com/problems/critical-connections-in-a-network/submissions/2158532377/)

Full original Solution class, preserving disc, low, parent, adj, time, the DFS helper, and public entry point. A tree edge is a bridge exactly when low[child]>disc[parent]. The parent-by-vertex skip relies on the original simple-graph contract, and recursion can be deep. Member traversal state is not reset for independent reuse of the same object; no initialization changes or parallel-edge support were added.

### [Tarjan lowlink: articulation points in an island](topics/dsu-and-graphs/snippets/tarjan-articulation-grid.cpp)

Original: [1568. Minimum Number of Days to Disconnect Island](topics/dsu-and-graphs/originals/1568__2158580259.cpp#L1-L87) · [submission 2158580259](https://leetcode.com/problems/minimum-number-of-days-to-disconnect-island/submissions/2158580259/)

Full original Solution class for minDays. Non-root articulation uses low[child]>=disc[parent]; a DFS root needs more than one DFS child. parentX and parentY denote the component DFS root, while the parent vector stores immediate parents. Includes the original island/land-count special cases, redundant checks, unused variables, and double semicolon. Traversal members assume the original one-call object lifecycle.

### [Hierholzer: consume directed edges and reverse postorder](topics/dsu-and-graphs/snippets/hierholzer-itinerary.cpp)

Original: [332. Reconstruct Itinerary](topics/dsu-and-graphs/originals/332__2157586346.cpp#L3-L29) · [submission 2157586346](https://leetcode.com/problems/reconstruct-itinerary/submissions/2157586346/)

Complete original findItinerary method. Reverse-sorts destinations, consumes the smallest available destination from the vector back, appends a vertex only after its outgoing edges are exhausted, and reverses the resulting path. The original starts at JFK and assumes the problem’s valid Eulerian-itinerary guarantee. Repeated tickets remain distinct edges; vertices may be revisited. Recursion can use O(E) frames.

### [BFS: scan each reachable jump interval only beyond the frontier](topics/dsu-and-graphs/snippets/bfs-monotone-jump-frontier.cpp)

Original: [1871. Jump Game VII](topics/dsu-and-graphs/originals/1871__2012395473.cpp#L3-L30) · [submission 2012395473](https://leetcode.com/problems/jump-game-vii/submissions/2012395473/)

Complete original canReach method. A deque stores reachable zero positions, while farthest records the largest already-scanned endpoint so overlapping jump ranges are not rescanned. Each position is scanned at most once, giving O(n) time and O(n) queue storage. Preserves size_t queue entries, int loop indexes, and the original valid jump-range/start-cell assumptions. This is unweighted BFS.


## Propagate summaries and reconnect pointers

[Algorithms, costs, and tricks](topics/trees-and-lists/README.md)

### [Postorder DFS: height summary and diameter](topics/trees-and-lists/snippets/dfs-diameter.cpp)

Original: [543. Diameter of Binary Tree](topics/trees-and-lists/originals/543__2140582704.cpp#L14-L31) · [submission 2140582704](https://leetcode.com/problems/diameter-of-binary-tree/submissions/2140582704/)

Complete original diameterOfBinaryTree method, including its local dfs lambda. Requires TreeNode. The lambda returns height in nodes; result counts diameter edges through left + right.

### [Postorder DFS: return one branch, update the full path](topics/trees-and-lists/snippets/dfs-maximum-path-sum.cpp)

Original: [124. Binary Tree Maximum Path Sum](topics/trees-and-lists/originals/124__2153370936.cpp#L14-L32) · [submission 2153370936](https://leetcode.com/problems/binary-tree-maximum-path-sum/submissions/2153370936/)

Complete original maxPathSum method, including its local traverse lambda. Requires the LeetCode TreeNode type. Negative child gains are clamped to zero; INT_MIN preserves all-negative-tree behavior. Assumes a nonempty tree, as in the original problem.

### [Reverse full k-node groups and recurse](topics/trees-and-lists/snippets/reverse-k-group.cpp)

Original: [25. Reverse Nodes in k-Group](topics/trees-and-lists/originals/25__2144552684.cpp#L13-L38) · [submission 2144552684](https://leetcode.com/problems/reverse-nodes-in-k-group/submissions/2144552684/)

Complete original reverseKGroup method. Requires ListNode and its own method name for recursion. First checks that a full group exists; an incomplete final group remains unchanged. Assumes k >= 1, as in the original problem, and uses recursion per group.

### [In-place linked-list reversal](topics/trees-and-lists/snippets/reverse-linked-list.cpp)

Original: [206. Reverse Linked List](topics/trees-and-lists/originals/206__2143560010.cpp#L13-L24) · [submission 2143560010](https://leetcode.com/problems/reverse-linked-list/submissions/2143560010/)

Complete original reverseList method. Requires ListNode. Rewires the existing next pointers, retaining the original while(current) formatting and tmp variable.

## Memoize states and restore choices

[Algorithms, costs, and tricks](topics/dp-and-backtracking/README.md)

### [Backtracking: choose, recurse, undo](topics/dp-and-backtracking/snippets/backtrack-n-queens.cpp)

Original: [51. N-Queens](topics/dp-and-backtracking/originals/51__2164697200.cpp#L3-L50) · [submission 2164697200](https://leetcode.com/problems/n-queens/submissions/2164697200/)

Complete original solveNQueens method with its local valid and recursive lambdas. Keeps the original upper-right check col <= n, which can read the string terminator at column n, and the original unused recursive j parameter and shadowing loop variable. No boundary cleanup or rewriting has been applied.

### [Two-index memoization: skip or match](topics/dp-and-backtracking/snippets/memo-distinct-subsequences.cpp)

Original: [115. Distinct Subsequences](topics/dp-and-backtracking/originals/115__2133267031.cpp#L1-L29) · [submission 2133267031](https://leetcode.com/problems/distinct-subsequences/submissions/2133267031/)

Whole original Solution is retained because helper depends on the memoization member and numDistinct entry point. Keeps the original packed (i,j) key and int counts. memoization is not cleared between repeated numDistinct calls on the same object; preserve the original single-call/problem constraints when copying.

### [Memoized grid DFS with a class-level table](topics/dp-and-backtracking/snippets/memo-longest-increasing-path.cpp)

Original: [329. Longest Increasing Path in a Matrix](topics/dp-and-backtracking/originals/329__2139455187.cpp#L1-L56) · [submission 2139455187](https://leetcode.com/problems/longest-increasing-path-in-a-matrix/submissions/2139455187/)

Whole original Solution is retained because dfs depends on the dp member and longestIncreasingPath setup. Includes the original visited set, packed key, and C++20 contains call. The initial prev = -1 assumes the original nonnegative matrix values. dp.resize does not reset existing cells on repeat calls to the same Solution object.

### [Maximum product subarray: retain both extrema](topics/dp-and-backtracking/snippets/maximum-product-two-states.cpp)

Original: [152. Maximum Product Subarray](topics/dp-and-backtracking/originals/152__2000724011.cpp#L3-L19) · [submission 2000724011](https://leetcode.com/problems/maximum-product-subarray/submissions/2000724011/)

Complete original maxProduct method. Saves both previous maximum and minimum before updating either state, because multiplying a negative value swaps their roles. Runs in O(n) time and O(1) state. The source assumes nonempty input and retains int multiplication under the original product bounds.

### [Kadane: update the best before discarding a negative prefix](topics/dp-and-backtracking/snippets/kadane-maximum-subarray.cpp)

Original: [53. Maximum Subarray](topics/dp-and-backtracking/originals/53__2000625681.cpp#L3-L15) · [submission 2000625681](https://leetcode.com/problems/maximum-subarray/submissions/2000625681/)

Complete original maxSubArray method. The best starts at INT_MIN, is updated before the running sum resets, and therefore retains the largest element for all-negative nonempty input. O(n) time and O(1) state. Original int arithmetic, nonempty-input contract, and unqualified max remain unchanged.

### [Word search: mark a board cell, recurse, then restore it](topics/dp-and-backtracking/snippets/word-search-mark-restore.cpp)

Original: [79. Word Search](topics/dp-and-backtracking/originals/79__2168591618.cpp#L3-L38) · [submission 2168591618](https://leetcode.com/submissions/detail/2168591618/)

Complete original exist method. Temporarily replaces a matched board cell with #, explores four neighbors, then restores that cell. The bitwise | operations evaluate every recursive branch, including after a successful one; the unused uint64_t key is preserved. The board alphabet must exclude #, and the original board is nonempty. Recursion uses path-length state and can perform exponential search.


## Reuse prefixes and encode strings

[Algorithms, costs, and tricks](topics/strings-and-tries/README.md)

### [KMP: buildLps helper](topics/strings-and-tries/snippets/kmp-build-lps-helper.cpp)

Original: [214. Shortest Palindrome](topics/strings-and-tries/originals/214__2163593115.cpp#L31-L46) · [submission 2163593115](https://leetcode.com/problems/shortest-palindrome/submissions/2163593115/)

Complete original buildLps member function from Shortest Palindrome, with its original names and indentation. Returns the longest proper prefix/suffix length for every prefix. The associated full original class is also retained in shortest-palindrome-kmp.cpp. Requires the original std::vector and std::string declarations/includes. Keeps original int lengths and indices.

### [KMP: prefix construction and substring search](topics/strings-and-tries/snippets/kmp-search.cpp)

Original: [28. Find the Index of the First Occurrence in a String](topics/strings-and-tries/originals/28__2163524870.cpp#L1-L40) · [submission 2163524870](https://leetcode.com/problems/find-the-index-of-the-first-occurrence-in-a-string/submissions/2163524870/)

Full original Solution, including the original baab/000 comments and wrapper. strStr builds the needle LPS array inline, then uses it to recover the matched prefix on a mismatch. Assumes a nonempty needle as in the original problem constraints; the source has no empty-needle guard. Keeps original int indices and original unqualified string signature. Relies on LeetCode-provided standard-library includes.

### [WordFilter: combined suffix and prefix trie](topics/strings-and-tries/snippets/prefix-suffix-trie.cpp)

Original: [745. Prefix and Suffix Search](topics/strings-and-tries/originals/745__2164622907.cpp#L1-L61) · [submission 2164622907](https://leetcode.com/problems/prefix-and-suffix-search/submissions/2164622907/)

Full original source is retained so that the nested Node, Trie, owning trie field, constructor, query wrapper, and usage comment remain together. Inserts every suffix + "{" + word and searches suffix + "{" + prefix; later words overwrite node indices. The { separator must not occur in words; original lowercase-word constraints supply that condition. Construction expands every suffix and can consume substantial memory. Keeps its original unique_ptr ownership and original standard-library context.

### [KMP application: shortest palindrome](topics/strings-and-tries/snippets/shortest-palindrome-kmp.cpp)

Original: [214. Shortest Palindrome](topics/strings-and-tries/originals/214__2163593115.cpp#L1-L47) · [submission 2163593115](https://leetcode.com/problems/shortest-palindrome/submissions/2163593115/)

Full original Solution, retaining the original Russian index/character comments, tab characters, wrapper, shortestPalindrome, and buildLps helper. Builds LPS on s + "#" + reverse(s) to find the palindromic prefix. The # delimiter must be absent from the input; original lowercase-string constraints supply that condition. Relies on LeetCode-provided standard-library includes. This file intentionally overlaps the exact buildLps helper extraction from the same submission.

### [Trie: value-owned child nodes](topics/strings-and-tries/snippets/trie-prefix-tree.cpp)

Original: [208. Implement Trie (Prefix Tree)](topics/strings-and-tries/originals/208__2167350538.cpp#L1-L58) · [submission 2167350538](https://leetcode.com/problems/implement-trie-prefix-tree/submissions/2167350538/)

Full original source, including class wrapper, nested Node, all methods, and the LeetCode usage comment. Nodes store child nodes by value in unordered_map<char, Node>, and leaf marks complete words. contains retains the original C++20 requirement. The original insert accepts its string by value. Relies on LeetCode-provided standard-library includes and string alias.

## Combine lookup, order, and frequency

[Algorithms, costs, and tricks](topics/design-structures/README.md)

### [MyHashMap: fixed buckets with separate chaining](topics/design-structures/snippets/custom-hash-map.cpp)

Original: [706. Design HashMap](topics/design-structures/originals/706__2144621524.cpp#L1-L48) · [submission 2144621524](https://leetcode.com/problems/design-hashmap/submissions/2144621524/)

Full original source, including class wrapper and LeetCode usage comment. The original hash table has exactly 32 list buckets and does not resize. Keys and values follow the original nonnegative LeetCode problem contract; -1 is the missing-value sentinel. No rehashing: crowded buckets make operations linear in bucket length. Relies on LeetCode-provided standard-library includes.

### [FreqStack: frequency-group stacks](topics/design-structures/snippets/frequency-stack.cpp)

Original: [895. Maximum Frequency Stack](topics/design-structures/originals/895__2146639743.cpp#L1-L40) · [submission 2146639743](https://leetcode.com/problems/maximum-frequency-stack/submissions/2146639743/)

Full original source, including all original includes (including set), class wrapper, and LeetCode usage comment. route tracks current frequencies; freqs stores the push order at each attained frequency. pop assumes the stack is nonempty. The original maps retain empty groups and zero-frequency entries. The source retains its original includes and has not been made independently compilable.

### [LFUCache: frequency lists and iterator map](topics/design-structures/snippets/lfu-cache.cpp)

Original: [460. LFU Cache](topics/design-structures/originals/460__2144968388.cpp#L1-L77) · [submission 2144968388](https://leetcode.com/problems/lfu-cache/submissions/2144968388/)

Full original source, preserving its original includes, class wrapper, update helper, and LeetCode usage comment. Maintains one list per frequency, with least-recent ties evicted from the back of the minimum-frequency list. Original capacity guard is exactly capacity == 0; negative capacities are outside the problem contract. Empty frequency buckets are retained in storage. This is the original implementation, not a generic cache interface.

### [LRUCache: list and iterator map](topics/design-structures/snippets/lru-cache.cpp)

Original: [146. LRU Cache](topics/design-structures/originals/146__2143986850.cpp#L1-L45) · [submission 2143986850](https://leetcode.com/problems/lru-cache/submissions/2143986850/)

Full original source, including class wrapper and LeetCode usage comment. Most-recent entries are moved to the front with list::splice; eviction removes the back entry. Assumes positive capacity; inserting into a zero-capacity cache reaches values.back() on an empty list. contains retains the original C++20 requirement. Relies on LeetCode-provided standard-library includes.

### [RandomizedSet: dense values with swap-tail deletion](topics/design-structures/snippets/randomized-set-swap-tail.cpp)

Original: [380. Insert Delete GetRandom O(1)](topics/design-structures/originals/380__2125968160.cpp#L1-L46) · [submission 2125968160](https://leetcode.com/problems/insert-delete-getrandom-o1/submissions/2125968160/)

Full original RandomizedSet source, including its LeetCode usage comment. A value-to-index map tracks a dense vector; deletion swaps the last value into the removed slot and updates its index. Hash operations are expected constant time, and getRandom assumes a nonempty set. The original rand()%size can be biased and uses the existing RNG state; neither behavior has been rewritten. contains requires C++20.


## Keep a feasible greedy frontier

[Algorithms, costs, and tricks](topics/greedy-and-intervals/README.md)

### [Interval scheduling: keep earliest finishing intervals](topics/greedy-and-intervals/snippets/earliest-finish-intervals.cpp)

Original: [435. Non-overlapping Intervals](topics/greedy-and-intervals/originals/435__2167400289.cpp#L3-L19) · [submission 2167400289](https://leetcode.com/problems/non-overlapping-intervals/submissions/2167400289/)

Complete original eraseOverlapIntervals method. Sorts the input by end time and assumes nonempty input, as in the original problem. auto& last aliases intervals[0], so last = intervals[i] overwrites that first element; this original mutation is preserved. Touching endpoints are compatible.

### [Sort and merge closed intervals](topics/greedy-and-intervals/snippets/merge-intervals.cpp)

Original: [56. Merge Intervals](topics/greedy-and-intervals/originals/56__2167385466.cpp#L3-L16) · [submission 2167385466](https://leetcode.com/problems/merge-intervals/submissions/2167385466/)

Complete original merge method. Sorts the input intervals in place. Touching intervals are merged because the condition is result.back()[1] >= interval[0]. Empty input returns an empty result.

### [Two pointers: discard the shorter container boundary](topics/greedy-and-intervals/snippets/two-pointer-container.cpp)

Original: [11. Container With Most Water](topics/greedy-and-intervals/originals/11__2147803818.cpp#L3-L19) · [submission 2147803818](https://leetcode.com/problems/container-with-most-water/submissions/2147803818/)

Complete original maxArea method. Each step records the current area and moves the shorter boundary, moving left on equal heights. Runs in O(n) time and O(1) auxiliary space. Width, heights, multiplication, and the result remain int under the original problem bounds.


## Collapse choices into counts

[Algorithms, costs, and tricks](topics/math-and-bits/README.md)

### [Multiplicity counting: all distinct, one pair, all equal](topics/math-and-bits/snippets/three-sum-multiplicity-cases.cpp)

Original: [923. 3Sum With Multiplicity](topics/math-and-bits/originals/923__2140530076.cpp#L25-L33) · [submission 2140530076](https://leetcode.com/problems/3sum-with-multiplicity/submissions/2140530076/)

Literal branch chain from inside the original sorted two-pointer threeSumMulti scan. Requires the surrounding arr, i, j, k, counts, result, and MOD variables and the original scan to avoid duplicate triples. Preserves 1LL promotion and divisions by 2 and 6 before modulo; this is a fragment, not a standalone function.

### [4Sum II: count complements of pair sums](topics/math-and-bits/snippets/four-sum-pair-frequency.cpp)

Original: [454. 4Sum II](topics/math-and-bits/originals/454__2025540323.cpp#L3-L19) · [submission 2025540323](https://leetcode.com/problems/4sum-ii/submissions/2025540323/)

Complete original fourSumCount method. Stores all nums3+nums4 sum frequencies, then adds the count for each negated nums1+nums2 sum. Uses expected quadratic time and quadratic map storage for equal-length arrays. operator[] inserts absent complements with zero count; sums and the result remain int under the source constraints.

### [Bitwise-AND triples: aggregate ordered-pair masks](topics/math-and-bits/snippets/bitwise-and-pair-frequency.cpp)

Original: [982. Triples with Bitwise AND Equal To Zero](topics/math-and-bits/originals/982__2168564891.cpp#L3-L21) · [submission 2168564891](https://leetcode.com/submissions/detail/2168564891/)

Complete original countTriplets method. Counts every ordered pair mask, including repeated indexes, and combines each mask frequency with compatible third values. For D distinct masks, expected work is O(n squared+nD), with O(D) hash-map storage. The original int keys, frequencies, result, and bounds remain unchanged.


