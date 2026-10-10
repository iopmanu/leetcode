# Original snippets for contests and interviews

Every `.cpp` below is an **unchanged contiguous fragment** of one of your captured LeetCode submissions. Names, types, indentation, comments, helper choices, and original quirks are preserved. No new namespace, validation layer, `optional`, or modernized interface has been added.

A snippet may need its original class context, standard includes, a LeetCode node definition, or another helper. Read the short context beside it before copying. [All originals](SOURCES.md) retain the complete submitted program.

These are source fragments, not a newly designed standalone C++ library. `tools/verify_snippets.py` checks exact source equality, not algorithm correctness on arbitrary inputs.

## Missing requested graph implementations

Dijkstra, Prim, and Yen have not been added: their original code was not captured before authenticated access was blocked. All three captured 1584 variants are Kruskal. The missing graph sources are listed in [COVERAGE.md](COVERAGE.md). They can be added unchanged when the original code becomes available.

## [design-structures](topics/design-structures/README.md)

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

## [dp-and-backtracking](topics/dp-and-backtracking/README.md)

### [Backtracking: choose, recurse, undo](topics/dp-and-backtracking/snippets/backtrack-n-queens.cpp)

Original: [51. N-Queens](topics/dp-and-backtracking/originals/51__2164697200.cpp#L3-L50) · [submission 2164697200](https://leetcode.com/problems/n-queens/submissions/2164697200/)

Complete original solveNQueens method with its local valid and recursive lambdas. Keeps the original upper-right check col <= n, which can read the string terminator at column n, and the original unused recursive j parameter and shadowing loop variable. No boundary cleanup or rewriting has been applied.

### [Two-index memoization: skip or match](topics/dp-and-backtracking/snippets/memo-distinct-subsequences.cpp)

Original: [115. Distinct Subsequences](topics/dp-and-backtracking/originals/115__2133267031.cpp#L1-L29) · [submission 2133267031](https://leetcode.com/problems/distinct-subsequences/submissions/2133267031/)

Whole original Solution is retained because helper depends on the memoization member and numDistinct entry point. Keeps the original packed (i,j) key and int counts. memoization is not cleared between repeated numDistinct calls on the same object; preserve the original single-call/problem constraints when copying.

### [Memoized grid DFS with a class-level table](topics/dp-and-backtracking/snippets/memo-longest-increasing-path.cpp)

Original: [329. Longest Increasing Path in a Matrix](topics/dp-and-backtracking/originals/329__2139455187.cpp#L1-L56) · [submission 2139455187](https://leetcode.com/problems/longest-increasing-path-in-a-matrix/submissions/2139455187/)

Whole original Solution is retained because dfs depends on the dp member and longestIncreasingPath setup. Includes the original visited set, packed key, and C++20 contains call. The initial prev = -1 assumes the original nonnegative matrix values. dp.resize does not reset existing cells on repeat calls to the same Solution object.

## [dsu-and-graphs](topics/dsu-and-graphs/README.md)

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

## [greedy-and-intervals](topics/greedy-and-intervals/README.md)

### [Interval scheduling: keep earliest finishing intervals](topics/greedy-and-intervals/snippets/earliest-finish-intervals.cpp)

Original: [435. Non-overlapping Intervals](topics/greedy-and-intervals/originals/435__2167400289.cpp#L3-L19) · [submission 2167400289](https://leetcode.com/problems/non-overlapping-intervals/submissions/2167400289/)

Complete original eraseOverlapIntervals method. Sorts the input by end time and assumes nonempty input, as in the original problem. auto& last aliases intervals[0], so last = intervals[i] overwrites that first element; this original mutation is preserved. Touching endpoints are compatible.

### [Sort and merge closed intervals](topics/greedy-and-intervals/snippets/merge-intervals.cpp)

Original: [56. Merge Intervals](topics/greedy-and-intervals/originals/56__2167385466.cpp#L3-L16) · [submission 2167385466](https://leetcode.com/problems/merge-intervals/submissions/2167385466/)

Complete original merge method. Sorts the input intervals in place. Touching intervals are merged because the condition is result.back()[1] >= interval[0]. Empty input returns an empty result.

## [math-and-bits](topics/math-and-bits/README.md)

### [Multiplicity counting: all distinct, one pair, all equal](topics/math-and-bits/snippets/three-sum-multiplicity-cases.cpp)

Original: [923. 3Sum With Multiplicity](topics/math-and-bits/originals/923__2140530076.cpp#L25-L33) · [submission 2140530076](https://leetcode.com/problems/3sum-with-multiplicity/submissions/2140530076/)

Literal branch chain from inside the original sorted two-pointer threeSumMulti scan. Requires the surrounding arr, i, j, k, counts, result, and MOD variables and the original scan to avoid duplicate triples. Preserves 1LL promotion and divisions by 2 and 6 before modulo; this is a fragment, not a standalone function.

## [monotonic-and-heaps](topics/monotonic-and-heaps/README.md)

### [Monotonic stack: histogram rectangle boundaries](topics/monotonic-and-heaps/snippets/histogram-monotonic-stack.cpp)

Original: [84. Largest Rectangle in Histogram](topics/monotonic-and-heaps/originals/84__2146612938.cpp#L3-L28) · [submission 2146612938](https://leetcode.com/problems/largest-rectangle-in-histogram/submissions/2146612938/)

Complete original largestRectangleArea method. Stores bar indices, pops strictly higher bars when a smaller bar arrives, and flushes the remaining stack against the end of the histogram. Keeps the original int area arithmetic; it is not a widened general-purpose implementation. Requires the original LeetCode vector, stack, and algorithm compilation context.

### [Monotonic deque: prefix-sum shortest subarray](topics/monotonic-and-heaps/snippets/shortest-subarray-monotonic-deque.cpp)

Original: [862. Shortest Subarray with Sum at Least K](topics/monotonic-and-heaps/originals/862__2152907567.cpp#L3-L26) · [submission 2152907567](https://leetcode.com/problems/shortest-subarray-with-sum-at-least-k/submissions/2152907567/)

Complete original shortestSubarray method. The original deque direction is intentional: new indices enter at the front, dominated newest indices leave the front, and qualifying oldest indices leave the back. The source uses vector<int> prefixes exactly as submitted. Prefix sums and their differences use int and can overflow for large totals; this original has not been corrected. Requires the original LeetCode vector, deque, algorithm, and INT_MAX compilation context.

### [MedianFinder: two ordered multisets with indexed removal](topics/monotonic-and-heaps/snippets/sliding-median-finder-struct.cpp)

Original: [480. Sliding Window Median](topics/monotonic-and-heaps/originals/480__2150661436.cpp#L7-L69) · [submission 2150661436](https://leetcode.com/problems/sliding-window-median/submissions/2150661436/)

Complete original nested MedianFinder struct, including aliases, members, methods, private label, and indentation. The left multiset is descending; the right multiset is ascending. Original source has vector, set, unordered_map, and utility includes and a medianSlidingWindow wrapper; these remain in the full original source rather than being copied into this contiguous struct slice. Uses contains, so it retains its original C++20 requirement. findMedian assumes at least one stored element. Indices identify active elements and must not be reused while still present. This helper uses ordered multisets rather than priority_queue heaps.

## [range-queries](topics/range-queries/README.md)

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

## [search-and-sort](topics/search-and-sort/README.md)

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

## [strings-and-tries](topics/strings-and-tries/README.md)

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

## [trees-and-lists](topics/trees-and-lists/README.md)

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

## [windows-and-prefixes](topics/windows-and-prefixes/README.md)

### [Sliding window: satisfy counts, then shrink](topics/windows-and-prefixes/snippets/minimum-covering-window.cpp)

Original: [76. Minimum Window Substring](topics/strings-and-tries/originals/76__2149102883.cpp#L3-L34) · [submission 2149102883](https://leetcode.com/problems/minimum-window-substring/submissions/2149102883/)

Complete original minWindow method. counts stores outstanding multiplicities; matches counts character kinds still missing. The original problem requires nonempty t; this exact method does not add an empty-target guard. Its if-initializers are original C++17 syntax.

### [Prefix sums: count prior sums equal to current - k](topics/windows-and-prefixes/snippets/prefix-sum-frequency.cpp)

Original: [560. Subarray Sum Equals K](topics/windows-and-prefixes/originals/560__2130713437.cpp#L1-L23) · [submission 2130713437](https://leetcode.com/problems/subarray-sum-equals-k/submissions/2130713437/)

Whole original captured code is retained so the two introductory prefix-equation comments stay attached to the method without edits. Seeds counts[0] = 1, queries before inserting the current prefix, and keeps the original int accumulator/count types.

