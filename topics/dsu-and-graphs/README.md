# DSU and graphs

[All topics](../../README.md) · [Source index](../../SOURCES.md) · [Coverage](../../COVERAGE.md)

## Main algorithms and structures

Choose by the information that must survive a traversal: component identity, distance, dependency order, or a cut/path certificate. Links open actual captured implementations or unchanged excerpts. Let V/E be vertices/edges, N = rows×cols, U the number of DSU operations, q query count, and α the inverse Ackermann function. Space includes constructed adjacency and recursion, excluding returned answers. Hash-based bounds are expected; string costs are stated separately where they matter.

| Algorithm / structure | Recognition trigger and actual time | Extra space | Direct implementation |
|---|---|---|---|
| DFS with visited state / flood fill | Components, area, perimeter, cloning, or one reachability search: O(V+E); four-neighbor grid O(N) | O(V) traversal state; constructed adjacency or unfinished clone-neighbor buffers can add O(E); grid recursion can be O(N) | [Flood-fill excerpt](snippets/dfs-count-islands.cpp) · [In-place islands](originals/200__2155362152.cpp) · [Separate visited](originals/200__2125964378.cpp) · [Area](originals/695__2155365320.cpp) · [Perimeter](originals/463__2155358279.cpp) · [Clone](originals/133__2155372665.cpp) |
| FIFO BFS, including multiple sources | Equal-cost moves or simultaneous spread: O(V+E), grid O(N); lock has at most 10,000 constant-length states | O(V), grid O(N), plus an explicit adjacency list if built | [Lock BFS](snippets/bfs-open-lock.cpp) · [Full lock source](originals/752__2156069275.cpp) · [Multi-source BFS](snippets/bfs-multi-source-rotting-oranges.cpp) · [Full grid source](originals/994__2155965323.cpp) |
| Kahn indegree removal / active-path DFS | Dependency ordering or directed-cycle detection: O(V+E) | O(V+E) | [Kahn excerpt](snippets/topological-sort-kahn.cpp) · [Cycle decision](originals/207__2156079641.cpp) · [Ordering](originals/210__2156096010.cpp) · [Active-path DFS](originals/207__2139396834.cpp) |
| Leaf-layer peeling | Center of a connected tree: O(V+E) = O(V) | O(V) | [Full tree-center source](originals/310__2157055776.cpp) |
| DSU with path compression + correct union-by-size | Connectivity under unions: O(V + U α(V)) total | O(V) | [Balanced DSU excerpt](snippets/union-find-struct.cpp) · [Reverse activation](originals/1970__2168377479.cpp) · [Component-size queries](originals/803__2159893078.cpp) |
| DSU with arbitrary linking / broken size bookkeeping | Same connectivity interface, weaker guarantee: compression-only O((V+U) log(V+1)) conservative total; uncompressed variant O(V+UV) worst case | O(V), including potentially linear recursive find depth | [Compression without balancing](originals/684__2156418430.cpp) · [No compression](originals/684__2156418332.cpp) · [Incorrect size update](originals/721__2156447414.cpp) |
| Kruskal: sort edges, union distinct roots | MST/threshold connectivity: O(E log E + V + E α(V)); complete point graph creates Θ(V²) edges, hence O(V² log V) | O(V+E); complete point graph O(V²) | [Kruskal excerpt](snippets/kruskal-min-cost-connect-points.cpp) · [Full point graph](originals/1584__2162051692.cpp) · [Grid threshold edges](originals/778__2159591195.cpp) |
| Heap-finalized Dijkstra, additive or minimax | Nonnegative distances: O((V+E) log(E+1)); grid bottleneck version O(N log(N+1)) | O(V+E), including O(E) queued candidates; grid O(N) | [Additive excerpt](snippets/dijkstra-network-delay.cpp) · [Full network source](originals/743__2158089044.cpp) · [Minimax excerpt](snippets/dijkstra-minimax-grid.cpp) · [Full minimax source](originals/778__2159581294.cpp) |
| Two distinct arrival labels with FIFO propagation | Second arrival under uniform edge duration and synchronized lights: O(V+E) under those timing rules | O(V+E) | [Two-label excerpt](snippets/two-distinct-arrival-times.cpp) · [Full timing source](originals/2045__2158128996.cpp) |
| Lowlink DFS: discovery times + earliest reachable ancestor | Single-edge/single-vertex cuts: O(V+E); implicit grid O(N) | O(V+E); grid O(N) including recursion | [Bridge excerpt](snippets/tarjan-bridges.cpp) · [Full bridges](originals/1192__2158532377.cpp) · [Articulation excerpt](snippets/tarjan-articulation-grid.cpp) · [Full grid articulation](originals/1568__2158580259.cpp) |
| Hierholzer with ordered outgoing edges | Use every ticket exactly once: O(E log E) sort bound + O(E) traversal for fixed-length airport codes | O(E), including adjacency, recursion and path | [Postorder walk excerpt](snippets/hierholzer-itinerary.cpp) · [Full source](originals/332__2157586346.cpp) |
| Monotone scanned frontier + BFS | Reachable moves cover overlapping index intervals: O(n) total scan, not one full interval scan per pop | O(n) | [Frontier excerpt](snippets/bfs-monotone-jump-frontier.cpp) · [Full source](originals/1871__2012395473.cpp) |
| Degree statistics + pair correction | Degree-sum thresholds: O(E+V log V+q(V+D)), D distinct endpoint pairs; judge lookup O(V+E) upper bound | O(V+D) for corrected pairs; judge source stores lists, O(V+E) | [Parallel-edge correction](originals/1782__2162018515.cpp) · [Stored in/out lists](originals/997__2155347510.cpp) |
| Bounded neighbor candidates | Four distinct vertices with additive scores: expected O(V+E) upper bound; at most nine candidate pairs per central edge | O(V), at most three stored neighbors per used vertex | [Top-three candidate source](originals/2242__2161904938.cpp) |
| Repeated reachability queues without a visited guard | Actual DAG source costs O(V²+E+P+q), P all enqueued path prefixes across starts; P can be exponential | O(V²+E+W), W the largest queue; W can also be exponential | [Unguarded original](originals/1462__2156120061.cpp) |

## Combinations and tricks

### Reverse deletions + DSU + virtual boundary nodes

- **Recognize:** A sequence removes cells/edges, while the question asks when connectivity disappears or how many items lose support.
- **Compose:** Apply removals first, replay them backward as additions, and join each restored cell to active neighbors. Virtual nodes represent a whole boundary.
- **Invariant:** After restoring an event, DSU describes exactly that earlier active grid. Top/bottom root equality answers crossing; the roof component's growth answers restored support.
- **Tradeoff / sources:** [Crossing](originals/1970__2168377479.cpp) takes O(N α(N)); its [older source](originals/1970__2168371581.cpp) adds flood-fill bookkeeping. [Brick restoration](originals/803__2159893078.cpp) takes O((N+H) α(N)) for H hits and O(N) auxiliary space, subtracts the restored brick itself from roof-size growth, and clamps at zero. It relies on distinct hit positions and skips originally empty cells. This is offline processing, not general online deletion support.

### Sorted edges + connectivity, then optional counterfactual trials

- **Recognize:** Find a cheapest spanning structure, the first threshold connecting two endpoints, or whether an edge belongs to every/some optimal structure.
- **Compose:** Sort weighted edges and union different roots. For classification, compute a baseline MST and repeat with one edge forbidden or forced.
- **Invariant:** DSU is the forest of accepted edges. The first threshold joining the grid corners is the minimum possible bottleneck. Excluding an edge tests necessity; forcing it tests compatibility with the optimum.
- **Tradeoff / sources:** [Complete Manhattan graph](originals/1584__2162051692.cpp) explicitly pays Θ(V²) edge storage. [Grid threshold/Kruskal](originals/778__2159591195.cpp) has only O(N) edges. [Excluded/forced trials](originals/1489__2162346413.cpp) cost O(E(V+E α(V))+E log E), simplified to O(E² α(V)+E log E) for the connected input, with O(V+E) space; this is repeated Kruskal rather than a linear-time edge-classification method. The [other trial variant](originals/1489__2162346068.cpp) explicitly skips every forced edge by ID.

### Component identities + metadata, with deduplication at the join

- **Recognize:** Several references describe the same entity/component, or one change touches multiple neighboring components.
- **Compose:** Map emails/cells to IDs, union known connections, then group by root or aggregate neighboring root sizes.
- **Invariant:** Connectivity belongs to roots; component size must be updated on the winning root. A candidate cell adds each distinct neighboring component once, even if several sides touch it.
- **Tradeoff / sources:** [Largest-island aggregation](originals/827__2158599452.cpp) uses a four-neighbor root set, O(N α(N)) time and O(N) space. Both [account source A](originals/721__2156447414.cpp) and [source B](originals/721__2156444531.cpp) update size on the losing root: connectivity still works, but the intended balancing guarantee does not. Account merging also sorts grouped addresses, and its string_view metadata depends on the unchanged input strings. The [cycle-edge source](originals/684__2156418430.cpp) has compression but no balancing at all.

### Mark on discovery + implicit neighbors + distance layers

- **Recognize:** Equal-cost moves form a large implicit graph, or multiple initial sources spread at the same speed.
- **Compose:** Generate neighbors only when a state is processed; mark them when enqueued; seed all sources at distance zero and freeze each current layer when measuring time.
- **Invariant:** The first enqueue fixes the shortest unweighted distance. Registering a visited state before following edges also prevents cyclic DFS/clone recursion from repeating it.
- **Tradeoff / sources:** [Lock BFS](originals/752__2156069275.cpp) and [simultaneous grid spread](originals/994__2155965323.cpp) maintain this invariant. [Word mutation](originals/127__2157580907.cpp) erases dictionary entries on enqueue and costs expected O(wL²) for w length-L words and a fixed alphabet, counting O(L) string hashing; storage is O(wL). The [older word source](originals/127__2157579775.cpp) inserts absent generated strings through operator[] and allows duplicate queued states. [Graph cloning](originals/133__2155372665.cpp) registers each new clone before recursing.

### Expand BFS state, then discard dominated resource labels

- **Recognize:** Reaching the same cell with different collected items or remaining energy changes the legal future.
- **Compose:** Queue (cell, item mask, energy, moves); recharge on designated cells; store best energy for each (cell, mask).
- **Invariant:** FIFO traversal considers no-later arrivals first. An already reached equal cell/mask with at least as much energy dominates a candidate; a later higher-energy arrival may still need exploration.
- **Tradeoff / source:** [The classroom implementation](originals/3568__2131979696.cpp) has O(N·2^t·(e+1)) conservative time and queue-space bounds for t items and energy e. The best-energy table alone is O(N·2^t), but it can admit multiple improvements and the code does not remove already queued stale states. Position-only visited state would be incorrect.

### Reverse the reachability question toward the boundary

- **Recognize:** Many interior cells ask whether they can reach a small set of exits or an exterior region.
- **Compose:** Traverse from boundary seeds through reversed legal moves; use one bit per destination class when several answers must be intersected.
- **Invariant:** [Ocean reachability](originals/417__2156035451.cpp) moves uphill in reverse and visits each cell once per ocean bit; a cell enters the answer when both bits are present. [Surrounded-region marking](originals/130__2156047108.cpp) preserves every border-connected region before flipping the rest.
- **Tradeoff:** Both are O(N) time and O(N) worst-case auxiliary space including recursion. Reversing the movement inequality is essential; running a forward search separately from every cell would discard the shared-work advantage.

### Distinguish dependency removal, active paths, and unrestricted revisits

- **Recognize:** A directed graph may contain cycles, or queries repeatedly ask for reachability.
- **Compose:** [Kahn](originals/207__2156079641.cpp) removes zero-indegree vertices; [ordering](originals/210__2156096010.cpp) records that removal order; [DFS cycle detection](originals/207__2139396834.cpp) distinguishes active recursion from finished nodes.
- **Invariant:** Kahn can finish all vertices exactly when no dependency cycle remains. A back edge to an active DFS node certifies a cycle; an edge to a finished node does not.
- **Tradeoff:** Queue layers are unnecessary for topological order. [Repeated reachability](originals/1462__2156120061.cpp) writes a reachability matrix but never uses it to suppress enqueue, so it revisits once per path on a DAG and can fail to terminate on a cycle. Its time is not O(V(V+E)). By contrast, [ratio-product DFS](originals/399__2156998589.cpp) uses a fresh visited set per query: O(q(V+E)) graph work and O(V+E) space, plus string hashing/copying.

### Change the path aggregate, keep minimum-first finalization

- **Recognize:** Minimize either a nonnegative sum or the largest obstacle on a route.
- **Compose:** A min-heap orders candidate labels; extend an additive path with distance+weight, or a bottleneck path with max(current, nextHeight).
- **Invariant:** The first minimum-label pop of an unvisited vertex finalizes its optimum under the corresponding monotone path extension. Later entries for that vertex are skipped.
- **Tradeoff / sources:** [Network delay](originals/743__2158089044.cpp) has no tentative-distance array and can retain O(E) candidates, so use its O((V+E) log(E+1)) bound. [Grid minimax](originals/778__2159581294.cpp) uses the square-grid key i*rows+j; it is not a rectangular-grid flattening convention. Both retain int arithmetic and C++20 contains. The [sorted-edge alternative](originals/778__2159591195.cpp) solves the same bottleneck goal via connectivity.

### Two distinct labels + synchronized departure waiting

- **Recognize:** Need the second distinct arrival time, allowing revisits, with one edge duration and globally synchronized lights.
- **Compose:** Store the two smallest distinct arrivals per vertex; before extending a label, advance through a red phase, then add the common edge duration.
- **Invariant:** Equal times never create a second label. Under these rules, the arrival time depends on walk length and increases with each step, so FIFO processing admits at most two useful labels per vertex.
- **Tradeoff / source:** [The captured two-label algorithm](originals/2045__2158128996.cpp) is O(V+E) time/space under that timing model. Its deque is not valid for arbitrary weighted edges; it finds walks, not second-best simple paths, and contains no Yen root/spur decomposition. INT_MAX remains the missing-label sentinel.

### Lowlink + the correct edge/vertex separation test

- **Recognize:** Determine whether removing one edge or one vertex disconnects an undirected graph.
- **Compose:** DFS discovery times, parent links, and the lowest discovery time reachable through descendants and a back edge.
- **Invariant:** A tree edge is a bridge when low[child] > disc[parent]. A non-root vertex is an articulation point when low[child] ≥ disc[parent] for some child; the DFS root instead needs more than one DFS child.
- **Tradeoff / sources:** [Bridge source](originals/1192__2158532377.cpp) skips the parent by vertex and assumes no parallel edges. [Grid articulation source](originals/1568__2158580259.cpp) also counts components and handles at most two land cells separately. Their recursion may be linear, and their member state is not reset for independent reuse of one object.

### Consume edges + append on completion

- **Recognize:** Every directed edge must be used exactly once, with lexical preference among valid itineraries.
- **Compose:** Reverse-sort each outgoing list, consume its smallest destination from the back, append a vertex only after its outgoing edges are exhausted, then reverse the whole path.
- **Invariant:** The algorithm consumes tickets rather than marking vertices visited. Postorder lets a locally exhausted detour be spliced into the final Eulerian walk.
- **Tradeoff / source:** [The itinerary implementation](originals/332__2157586346.cpp) fixes JFK as the start and relies on the promised valid itinerary; it does not check general Eulerian feasibility. Sorting dominates at O(E log E), and recursion/path/adjacency need O(E) space.

### Process a frontier only once

- **Recognize:** Newly reachable positions offer overlapping ranges, or a tree's next outer layer appears while processing its current one.
- **Compose:** [Interval-jump BFS](originals/1871__2012395473.cpp) scans only beyond farthest, the already-scanned endpoint. [Tree-center peeling](originals/310__2157055776.cpp) snapshots the current leaf count before adding newly exposed leaves.
- **Invariant:** Jump indexes never need to be tested twice; a frozen leaf layer removes equal distance from every tree boundary. These are different uses of a monotone frontier, not weighted shortest paths.
- **Tradeoff:** The jump source is O(n) time/O(n) space despite large allowed jump intervals. Leaf peeling is O(V) on the connected-tree contract and stops at one or two centers; applying it to an arbitrary cyclic graph would not preserve that guarantee.

### Count with a simple statistic, then repair only its overcount

- **Recognize:** A degree sum almost answers a pair query, except shared edges contribute twice.
- **Compose:** Sort degrees and count above-threshold sums with two pointers; keep multiplicity per distinct endpoint pair and subtract only false positives.
- **Invariant:** Correct pair coverage is degree[u]+degree[v]-sharedCount. Subtract when the raw sum exceeds q but the corrected sum does not; already-invalid pairs are left alone.
- **Tradeoff / source:** [The captured correction](originals/1782__2162018515.cpp) scans all distinct shared pairs for every query, giving O(E+V log V+q(V+D)) time and O(V+D) auxiliary space. Collapsing parallel edges to mere adjacency would lose required counts.

### Fix the middle, bound the endpoint candidates

- **Recognize:** A short fixed-length sequence has additive endpoint scores and only a few distinctness exclusions.
- **Compose:** Fix each central edge b–c; retain the three highest-scoring neighbors of each vertex; test at most 3×3 choices for endpoints a and d.
- **Invariant:** For an endpoint choice, at most two neighbors can be forbidden by the other selected vertices, so three candidates suffice. Check a != c, d != b, and a != d explicitly.
- **Tradeoff / source:** [The bounded-candidate implementation](originals/2242__2161904938.cpp) sorts at most four entries on each neighbor insertion, so preprocessing and edge enumeration are expected linear, not full adjacency sorting. The cap of three depends on this four-vertex problem; it is not a general longest-path method.

## Problem and source appendix

All captured submissions are retained, including equivalent resubmissions and exact duplicates. Submission IDs distinguish files; they are not rankings of quality. The source itself is authoritative when a note is too brief.

### 127. Word Ladder

[Problem](https://leetcode.com/problems/word-ladder/) · Tags: BFS, Implicit word graph

Latest source mutates every character through a–z and erases dictionary entries at enqueue. Older source uses map/string IDs and visited on dequeue.

**Original-code context:** The older enumerate[current] lookup inserts missing generated words, and visited-on-pop permits duplicate queued states. The newer set/erase version removes a word when it is enqueued, avoiding both sources of extra work.

**Captured variants:** 2 accepted C++ submissions retained; distinctions are described above.

- [Original 2157580907](originals/127__2157580907.cpp) · [LeetCode submission](https://leetcode.com/problems/word-ladder/submissions/2157580907/)
- [Original 2157579775](originals/127__2157579775.cpp) · [LeetCode submission](https://leetcode.com/problems/word-ladder/submissions/2157579775/)

### 130. Surrounded Regions

[Problem](https://leetcode.com/problems/surrounded-regions/) · Tags: Graphs, Flood fill

Mark border-connected cells then flip only unmarked interior cells.

**Captured variants:** One approach.

- [Original 2156047108](originals/130__2156047108.cpp) · [LeetCode submission](https://leetcode.com/problems/surrounded-regions/submissions/2156047108/)

### 133. Clone Graph

[Problem](https://leetcode.com/problems/clone-graph/) · Tags: Graphs, DFS, Hash maps

Memoized graph cloning creates clone and registers it before recursive neighbor traversal to terminate cycles.

**Captured variants:** One observed approach.

- [Original 2155372665](originals/133__2155372665.cpp) · [LeetCode submission](https://leetcode.com/problems/clone-graph/submissions/2155372665/)

### 200. Number of Islands

[Problem](https://leetcode.com/problems/number-of-islands/) · Tags: Graphs, Flood fill

Count unvisited land seeds and flood-fill each connected component.

**Captured variants:** [2155362152](originals/200__2155362152.cpp) in-place; [2125964378](originals/200__2125964378.cpp) separate visited.

- [Original 2155362152](originals/200__2155362152.cpp) · [LeetCode submission](https://leetcode.com/problems/number-of-islands/submissions/2155362152/)
- [Original 2125964378](originals/200__2125964378.cpp) · [LeetCode submission](https://leetcode.com/problems/number-of-islands/submissions/2125964378/)

### 207. Course Schedule

[Problem](https://leetcode.com/problems/course-schedule/) · Tags: Graphs, Topological sort, DFS

Kahn indegrees plus queue; separate recursive active-path/done cycle detection.

**Captured variants:** [2156079641](originals/207__2156079641.cpp) Kahn residual-indegree check; [2139404121](originals/207__2139404121.cpp) Kahn processed count; [2139396834](originals/207__2139396834.cpp) DFS cycle detection.

- [Original 2156079641](originals/207__2156079641.cpp) · [LeetCode submission](https://leetcode.com/problems/course-schedule/submissions/2156079641/)
- [Original 2139404121](originals/207__2139404121.cpp) · [LeetCode submission](https://leetcode.com/problems/course-schedule/submissions/2139404121/)
- [Original 2139396834](originals/207__2139396834.cpp) · [LeetCode submission](https://leetcode.com/problems/course-schedule/submissions/2139396834/)

### 210. Course Schedule II

[Problem](https://leetcode.com/problems/course-schedule-ii/) · Tags: Topological ordering, Kahn

Build prerequisite-to-course edges and indegrees, queue all zero-indegree nodes, decrement neighbors and output order if all courses processed.

**Original-code context:** Two versions differ by layer batching; layering is unnecessary for topological order but harmless. Size mismatch signals a cycle.

**Captured variants:** 2 accepted C++ submissions retained; distinctions are described above.

- [Original 2156096010](originals/210__2156096010.cpp) · [LeetCode submission](https://leetcode.com/problems/course-schedule-ii/submissions/2156096010/)
- [Original 2139425292](originals/210__2139425292.cpp) · [LeetCode submission](https://leetcode.com/problems/course-schedule-ii/submissions/2139425292/)

### 310. Minimum Height Trees

[Problem](https://leetcode.com/problems/minimum-height-trees/) · Tags: Tree centers, Leaf peeling

Peel each complete current leaf layer until at most two vertices remain; these are the minimum-height tree roots.

**Original-code context:** The source handles n==1 separately and subtracts a full initial queue layer from the remaining count before processing newly formed leaves. It relies on the original connected-tree contract.

**Captured variants:** 1 accepted C++ submission retained; distinctions are described above.

- [Original 2157055776](originals/310__2157055776.cpp) · [LeetCode submission](https://leetcode.com/problems/minimum-height-trees/submissions/2157055776/)

### 332. Reconstruct Itinerary

[Problem](https://leetcode.com/problems/reconstruct-itinerary/) · Tags: Eulerian path, Hierholzer, Lexicographic order

Reverse-sort destinations, repeatedly consume smallest remaining destination from vector.back, append vertex after exhausting outgoing edges, then reverse path.

**Original-code context:** Edges, not vertices, are consumed. Postorder reversal is essential; this is not greedy append-on-arrival path construction.

**Captured variants:** 1 accepted C++ submission retained; distinctions are described above.

- [Original 2157586346](originals/332__2157586346.cpp) · [LeetCode submission](https://leetcode.com/problems/reconstruct-itinerary/submissions/2157586346/)

### 399. Evaluate Division

[Problem](https://leetcode.com/problems/evaluate-division/) · Tags: Weighted graph, DFS, Ratio products

Build reciprocal weighted edges for equations, DFS per query and multiply edge ratios along a found path.

**Original-code context:** Each query gets its own visited set; a missing variable yields -1. The original follows any consistent ratio path, without optimizing path length.

**Captured variants:** 1 accepted C++ submission retained; distinctions are described above.

- [Original 2156998589](originals/399__2156998589.cpp) · [LeetCode submission](https://leetcode.com/problems/evaluate-division/submissions/2156998589/)

### 417. Pacific Atlantic Water Flow

[Problem](https://leetcode.com/problems/pacific-atlantic-water-flow/) · Tags: Graphs, Reverse reachability, Bitmask states

DFS uphill from both oceans; each cell carries one bit per origin; append when both bits first present.

**Captured variants:** One approach.

- [Original 2156035451](originals/417__2156035451.cpp) · [LeetCode submission](https://leetcode.com/problems/pacific-atlantic-water-flow/submissions/2156035451/)

### 463. Island Perimeter

[Problem](https://leetcode.com/problems/island-perimeter/) · Tags: Graphs, Flood fill, Coordinate packing

DFS land cells and count outgoing edges to water/outside; pack coordinate pair into uint64 key.

**Captured variants:** One observed approach.

- [Original 2155358279](originals/463__2155358279.cpp) · [LeetCode submission](https://leetcode.com/problems/island-perimeter/submissions/2155358279/)

### 684. Redundant Connection

[Problem](https://leetcode.com/problems/redundant-connection/) · Tags: DSU, Cycle detection

Scan edges; first edge whose endpoints already share root is redundant. Otherwise unite components.

**Original-code context:** Two sources compress find paths; submission 2156418332 recurses without compression. None uses union-by-size or union-by-rank.

**Captured variants:** 3 accepted C++ submissions retained; distinctions are described above.

- [Original 2156418430](originals/684__2156418430.cpp) · [LeetCode submission](https://leetcode.com/problems/redundant-connection/submissions/2156418430/)
- [Original 2156418332](originals/684__2156418332.cpp) · [LeetCode submission](https://leetcode.com/problems/redundant-connection/submissions/2156418332/)
- [Original 2156418215](originals/684__2156418215.cpp) · [LeetCode submission](https://leetcode.com/problems/redundant-connection/submissions/2156418215/)

### 695. Max Area of Island

[Problem](https://leetcode.com/problems/max-area-of-island/) · Tags: Graphs, Flood fill

In-place DFS clears visited land and sums recursive component area.

**Captured variants:** One observed approach.

- [Original 2155365320](originals/695__2155365320.cpp) · [LeetCode submission](https://leetcode.com/problems/max-area-of-island/submissions/2155365320/)

### 721. Accounts Merge

[Problem](https://leetcode.com/problems/accounts-merge/) · Tags: DSU, Email connectivity

Enumerate distinct emails, unite emails within each account, group by root, and sort addresses with account name first.

**Original-code context:** Both accepted sources update size on the losing root after attaching it. Connectivity still works, but the size values do not implement the intended union-by-size rule; do not infer a balanced-DSU complexity guarantee from these fields. The string_view references remain tied to the original accounts input.

**Captured variants:** 2 accepted C++ submissions retained; distinctions are described above.

- [Original 2156447414](originals/721__2156447414.cpp) · [LeetCode submission](https://leetcode.com/problems/accounts-merge/submissions/2156447414/)
- [Original 2156444531](originals/721__2156444531.cpp) · [LeetCode submission](https://leetcode.com/problems/accounts-merge/submissions/2156444531/)

### 743. Network Delay Time

[Problem](https://leetcode.com/problems/network-delay-time/) · Tags: Graphs, Dijkstra, Min-heap

Build a directed weighted adjacency list and pop the minimum queued path. The first pop of an unvisited vertex finalizes its shortest distance; duplicate heap entries are skipped. The maximum finalized distance is the network delay, or -1 when fewer than n vertices are reached.

**Original-code context:** This original uses visited-on-pop rather than a tentative-distance table. Nonnegative edge weights justify finalization. Heap storage can include O(E) candidate paths; time is O((V+E) log(E+1)) with expected constant-time hash operations. Distances and additions remain int, and unordered_set::contains requires C++20.

**Captured variants:** One captured min-heap Dijkstra implementation.

- [Original 2158089044](originals/743__2158089044.cpp) · [LeetCode submission](https://leetcode.com/problems/network-delay-time/submissions/2158089044/)

### 752. Open the Lock

[Problem](https://leetcode.com/problems/open-the-lock/) · Tags: Graphs, BFS, Implicit state

BFS over four-wheel strings; generate modular +/-1 neighbors; mark visited when enqueuing.

**Captured variants:** One BFS approach.

- [Original 2156069275](originals/752__2156069275.cpp) · [LeetCode submission](https://leetcode.com/problems/open-the-lock/submissions/2156069275/)

### 778. Swim in Rising Water

[Problem](https://leetcode.com/problems/swim-in-rising-water/) · Tags: Graphs, Minimax Dijkstra, DSU, Kruskal

Submission 2159581294 minimizes the maximum height along a path with a min-heap and nextTime = max(currentTime, nextHeight). Submission 2159591195 assigns each neighboring-cell edge the maximum endpoint height, sorts those edges, and joins components until the two corners connect.

**Original-code context:** These are two observed approaches, not Prim. Both take O(rc log(rc)) time and O(rc) storage on the grid. The minimax source flattens a cell as i*r+j, preserving the square-grid assumption of this problem; it is not a rectangular-grid indexing convention. The sorted-edge source handles the one-cell grid before processing edges. The minimax source uses C++20 contains.

**Captured variants:** 2159581294 is minimax Dijkstra; 2159591195 is sorted-edge DSU/Kruskal connectivity.

- [Original 2159591195](originals/778__2159591195.cpp) · [LeetCode submission](https://leetcode.com/problems/swim-in-rising-water/submissions/2159591195/)
- [Original 2159581294](originals/778__2159581294.cpp) · [LeetCode submission](https://leetcode.com/problems/swim-in-rising-water/submissions/2159581294/)

### 803. Bricks Falling When Hit

[Problem](https://leetcode.com/problems/bricks-falling-when-hit/) · Tags: DSU, Offline reverse processing, Grid connectivity

Remove all hit bricks, build DSU for remaining grid plus roof sentinel, restore hits in reverse and measure roof component size increase minus restored brick.

**Original-code context:** The roof component includes a sentinel, and the size increase also includes the restored brick: subtract 1 and clamp at 0. Hits on originally empty cells are skipped. The original problem supplies distinct hit positions; repeated hits are not counted separately by this implementation.

**Captured variants:** 1 accepted C++ submission retained; distinctions are described above.

- [Original 2159893078](originals/803__2159893078.cpp) · [LeetCode submission](https://leetcode.com/problems/bricks-falling-when-hit/submissions/2159893078/)

### 827. Making A Large Island

[Problem](https://leetcode.com/problems/making-a-large-island/) · Tags: DSU, Grid components, Distinct-root aggregation

DFS groups land into DSU components. For each zero, collect distinct adjacent component roots and add their sizes plus 1.

**Original-code context:** Deduplicate neighboring roots before summing sizes. The four accepted variants retain the same component-based method, with differences in includes, comments, and bookkeeping.

**Captured variants:** 4 accepted C++ submissions retained; distinctions are described above.

- [Original 2158599452](originals/827__2158599452.cpp) · [LeetCode submission](https://leetcode.com/problems/making-a-large-island/submissions/2158599452/)
- [Original 2158599274](originals/827__2158599274.cpp) · [LeetCode submission](https://leetcode.com/problems/making-a-large-island/submissions/2158599274/)
- [Original 2158599142](originals/827__2158599142.cpp) · [LeetCode submission](https://leetcode.com/problems/making-a-large-island/submissions/2158599142/)
- [Original 2158598652](originals/827__2158598652.cpp) · [LeetCode submission](https://leetcode.com/problems/making-a-large-island/submissions/2158598652/)

### 994. Rotting Oranges

[Problem](https://leetcode.com/problems/rotting-oranges/) · Tags: Graphs, Multi-source BFS

Seed all rotten cells, process queue levels, count fresh cells and return elapsed waves or -1.

**Captured variants:** Two equivalent container/syntax versions.

- [Original 2155965323](originals/994__2155965323.cpp) · [LeetCode submission](https://leetcode.com/problems/rotting-oranges/submissions/2155965323/)
- [Original 2011741235](originals/994__2011741235.cpp) · [LeetCode submission](https://leetcode.com/problems/rotting-oranges/submissions/2011741235/)

### 997. Find the Town Judge

[Problem](https://leetcode.com/problems/find-the-town-judge/) · Tags: Graphs, Degrees

Store incoming/outgoing trust lists and find incoming n-1 with no outgoing edges.

**Captured variants:** One observed approach.

- [Original 2155347510](originals/997__2155347510.cpp) · [LeetCode submission](https://leetcode.com/problems/find-the-town-judge/submissions/2155347510/)

### 1192. Critical Connections in a Network

[Problem](https://leetcode.com/problems/critical-connections-in-a-network/) · Tags: Lowlink, Bridges, DFS

Undirected DFS with discovery/low times and parent array; tree edge is bridge when low[child]>disc[parent].

**Original-code context:** The bridge test is strict low[child]>disc[parent], unlike the non-root articulation test. Skipping the parent by vertex assumes the original simple graph; parallel-edge handling is not present. Member vectors and time are initialized for the original one-call object lifecycle and are not reset for independent reuse.

**Captured variants:** 1 accepted C++ submission retained; distinctions are described above.

- [Original 2158532377](originals/1192__2158532377.cpp) · [LeetCode submission](https://leetcode.com/problems/critical-connections-in-a-network/submissions/2158532377/)

### 1462. Course Schedule IV

[Problem](https://leetcode.com/problems/course-schedule-iv/) · Tags: Reachability, Repeated queue traversal

For every source, traverse outgoing edges and mark reachable[source][current]; then answer stored reachability queries.

**Original-code context:** No visited/reachable guard before enqueue. On a DAG may revisit vertices once per path, with potentially exponential work; on a cyclic general graph may not terminate. Do not describe this exact implementation as O(V*(V+E)) until a visited guard is added.

**Captured variants:** 1 accepted C++ submission retained; distinctions are described above.

- [Original 2156120061](originals/1462__2156120061.cpp) · [LeetCode submission](https://leetcode.com/problems/course-schedule-iv/submissions/2156120061/)

### 1489. Find Critical and Pseudo-Critical Edges in Minimum Spanning Tree

[Problem](https://leetcode.com/problems/find-critical-and-pseudo-critical-edges-in-minimum-spanning-tree/) · Tags: DSU, Graphs, Minimum spanning trees

Run Kruskal baseline, then per-edge excluded and forced trials to distinguish critical and pseudo-critical edges.

**Captured variants:** Two near-identical submissions; [2162346068](originals/1489__2162346068.cpp) skips force unconditionally by id; [2162346413](originals/1489__2162346413.cpp) only explicit skip when force>0.

- [Original 2162346413](originals/1489__2162346413.cpp) · [LeetCode submission](https://leetcode.com/problems/find-critical-and-pseudo-critical-edges-in-minimum-spanning-tree/submissions/2162346413/)
- [Original 2162346068](originals/1489__2162346068.cpp) · [LeetCode submission](https://leetcode.com/problems/find-critical-and-pseudo-critical-edges-in-minimum-spanning-tree/submissions/2162346068/)

### 1568. Minimum Number of Days to Disconnect Island

[Problem](https://leetcode.com/problems/minimum-number-of-days-to-disconnect-island/) · Tags: Lowlink, Articulation points, Grid DFS

Grid DFS computes discovery and lowlink times, counts land components, and identifies articulation points. Return 0 when the island is already disconnected, the land count for at most two land cells, 1 when an articulation point exists, and 2 otherwise.

**Original-code context:** A DFS root is an articulation point only with more than one DFS child; a non-root uses low[child]>=disc[parent]. The parentX/parentY parameters identify the component DFS root, while the parent vector stores the immediate parent. Member traversal state is not reset for independent reuse.

**Captured variants:** 1 accepted C++ submission retained; distinctions are described above.

- [Original 2158580259](originals/1568__2158580259.cpp) · [LeetCode submission](https://leetcode.com/problems/minimum-number-of-days-to-disconnect-island/submissions/2158580259/)

### 1584. Min Cost to Connect All Points

[Problem](https://leetcode.com/problems/min-cost-to-connect-all-points/) · Tags: Graphs, Minimum spanning trees, DSU

Enumerate complete Manhattan graph, sort weighted edges, Kruskal until n-1 merges.

**Captured variants:** Three same Kruskal approach variants; latest removes coordinate map and duplicate edges.

- [Original 2162051692](originals/1584__2162051692.cpp) · [LeetCode submission](https://leetcode.com/problems/min-cost-to-connect-all-points/submissions/2162051692/)
- [Original 2162050952](originals/1584__2162050952.cpp) · [LeetCode submission](https://leetcode.com/problems/min-cost-to-connect-all-points/submissions/2162050952/)
- [Original 2162050421](originals/1584__2162050421.cpp) · [LeetCode submission](https://leetcode.com/problems/min-cost-to-connect-all-points/submissions/2162050421/)

### 1782. Count Pairs Of Nodes

[Problem](https://leetcode.com/problems/count-pairs-of-nodes/) · Tags: Graph degrees, Two pointers, Parallel-edge correction

Degrees, sorted degree sums counted with two pointers; subtract false positives for node pairs sharing parallel edges.

**Original-code context:** Correction checks q < degree[u]+degree[v] but q+sharedCount >= that sum. Do not discard multiplicity of parallel edges.

**Captured variants:** 1 accepted C++ submission retained; distinctions are described above.

- [Original 2162018515](originals/1782__2162018515.cpp) · [LeetCode submission](https://leetcode.com/problems/count-pairs-of-nodes/submissions/2162018515/)

### 1871. Jump Game VII

[Problem](https://leetcode.com/problems/jump-game-vii/) · Tags: BFS, Monotone scanned frontier

Uses deque<size_t> of reachable zero indices. For each popped index scans [max(i+minJump,farthest+1),min(i+maxJump,n-1)], then advances farthest.

**Original-code context:** farthest records the already-scanned endpoint and avoids scanning overlapping jump intervals repeatedly. Actual code has no weights or priority queue: it is not Dijkstra, Prim or Yen.

**Captured variants:** 1 accepted C++ submission retained; distinctions are described above.

- [Original 2012395473](originals/1871__2012395473.cpp) · [LeetCode submission](https://leetcode.com/problems/jump-game-vii/submissions/2012395473/)

### 1970. Last Day Where You Can Still Cross

[Problem](https://leetcode.com/problems/last-day-where-you-can-still-cross/) · Tags: DSU, Offline queries, Grid graphs

Reverse time turns deletions into activations; connect active neighbors and two virtual boundary nodes.

**Captured variants:** [2168377479](originals/1970__2168377479.cpp) compact DSU; [2168371581](originals/1970__2168371581.cpp) same DSU with redundant initial grid DFS/flood-fill bookkeeping. Not two different asymptotic algorithms.

- [Original 2168377479](originals/1970__2168377479.cpp) · [LeetCode submission](https://leetcode.com/problems/last-day-where-you-can-still-cross/submissions/2168377479/)
- [Original 2168371581](originals/1970__2168371581.cpp) · [LeetCode submission](https://leetcode.com/problems/last-day-where-you-can-still-cross/submissions/2168371581/)

### 2045. Second Minimum Time to Reach Destination

[Problem](https://leetcode.com/problems/second-minimum-time-to-reach-destination/) · Tags: Graphs, Two arrival labels, BFS, Traffic-light timing

Keep the two smallest distinct arrival times for each vertex. A deque propagates arrivals; on a red phase, departure waits until the next green phase before adding the uniform edge-traversal time. Equal arrival times do not create a second label.

**Original-code context:** This is a two-label shortest-arrival walk algorithm, not Yen. It permits revisiting vertices and has no root/spur path construction, path exclusions, or simple-path enumeration. The deque approach relies on the original uniform edge time and synchronized traffic lights. INT_MAX remains the missing-label sentinel, and the original problem guarantees a second arrival.

**Captured variants:** One captured deque-based implementation with two distinct distance labels.

- [Original 2158128996](originals/2045__2158128996.cpp) · [LeetCode submission](https://leetcode.com/problems/second-minimum-time-to-reach-destination/submissions/2158128996/)

### 2242. Maximum Score of a Node Sequence

[Problem](https://leetcode.com/problems/maximum-score-of-a-node-sequence/) · Tags: Graphs, Top-three neighbors, Candidate enumeration

Keep the three highest-scoring neighbors of each vertex. Enumerate each central edge b–c and pairs a from top3[b], d from top3[c].

**Original-code context:** Distinctness checks a!=c, b!=d, a!=d are essential. Actual code is bounded neighbor enumeration, not shortest paths.

**Captured variants:** 1 accepted C++ submission retained; distinctions are described above.

- [Original 2161904938](originals/2242__2161904938.cpp) · [LeetCode submission](https://leetcode.com/problems/maximum-score-of-a-node-sequence/submissions/2161904938/)

### 3568. Minimum Moves to Clean the Classroom

[Problem](https://leetcode.com/problems/minimum-moves-to-clean-the-classroom/) · Tags: Graphs, BFS, Bitmask states, Dominance pruning

BFS (row,col,trash_mask,energy,moves); recharge cells restore energy; keep best energy for each position/mask.

**Captured variants:** One observed approach.

- [Original 2131979696](originals/3568__2131979696.cpp) · [LeetCode submission](https://leetcode.com/problems/minimum-moves-to-clean-the-classroom/submissions/2131979696/)
