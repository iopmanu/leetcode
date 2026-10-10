# DSU and graphs

[All topics](../../README.md) · [Source index](../../SOURCES.md) · [Coverage](../../COVERAGE.md)

**32 captured problems · 49 accepted submission records.** Every linked implementation below is an unchanged captured source file. These notes describe the code; they do not replace it with a common API.

## Pattern reminders

### Connectivity with DSU

- **Cue:** Repeatedly join components, or undo a sequence of deletions by replaying it backward.
- **Idea and invariant:** 1970 activates land in reverse order and joins neighboring active cells plus virtual top/bottom nodes. Parent roots identify components; path compression and size-based union maintain the forest. Kruskal accepts an edge only when it joins two roots.
- **Cost in these sources:** 1970 uses O(rc alpha(rc)) time and O(rc) storage for r by c cells. 1584 explicitly builds O(n squared) edges, so its sort is O(n squared log n). 1489 repeats excluded/forced Kruskal trials, giving O(E squared alpha(V) + E log E).
- **Read the originals:** [1970. Last Day Where You Can Still Cross — 2168377479](originals/1970__2168377479.cpp); [1584. Min Cost to Connect All Points — 2162051692](originals/1584__2162051692.cpp); [1489. Find Critical and Pseudo-Critical Edges in Minimum Spanning Tree — 2162346413](originals/1489__2162346413.cpp).

### Breadth-first distance layers

- **Cue:** Each move has equal cost, or several starting cells spread simultaneously.
- **Idea and invariant:** 752 marks configurations on enqueue. 994 seeds every rotten cell, then freezes each queue level before counting another minute. A state is first reached at its shortest unweighted distance.
- **Cost in these sources:** O(V+E) on an explicit graph. Grid flood/BFS is O(rc) with O(rc) worst-case storage; the lock graph has at most 10,000 configurations.
- **Read the originals:** [752. Open the Lock — 2156069275](originals/752__2156069275.cpp); [994. Rotting Oranges — 2155965323](originals/994__2155965323.cpp).

### Traversal state and cycles

- **Cue:** Reachability, components, prerequisite cycles, or cloning a cyclic graph.
- **Idea and invariant:** 207 offers both residual-indegree Kahn traversal and active-path DFS. 133 registers a clone before following neighbors. Grid traversals mark a cell before recursion; 417 stores one reachability bit per ocean.
- **Cost in these sources:** O(V+E) time and O(V) state for adjacency-list traversal; grid variants use O(rc) time and worst-case recursion/state.
- **Read the originals:** [207. Course Schedule — 2156079641](originals/207__2156079641.cpp); [133. Clone Graph — 2155372665](originals/133__2155372665.cpp); [200. Number of Islands — 2155362152](originals/200__2155362152.cpp); [417. Pacific Atlantic Water Flow — 2156035451](originals/417__2156035451.cpp).

### A position is not the whole BFS state

- **Cue:** Collected items and remaining energy change what future moves are possible.
- **Idea and invariant:** 3568 queues position, trash mask, energy, and distance. For the same position/mask, a state reached with no more energy can be discarded. Recharging restores the full energy budget.
- **Cost in these sources:** A conservative state bound is O(rc * 2^t * e), where t is trash count and e is the energy budget. The best-energy table has O(rc * 2^t) entries; queued improvements can be larger.
- **Read the originals:** [3568. Minimum Moves to Clean the Classroom — 2131979696](originals/3568__2131979696.cpp).

### Finalize a weighted or minimax path when its heap entry wins

- **Cue:** Nonnegative edge weights, or a path cost defined by its largest height.
- **Idea and invariant:** [743](originals/743__2158089044.cpp) finalizes a vertex on its first minimum-heap pop and skips later entries for the same vertex. [778](originals/778__2159581294.cpp) uses the same minimum-first structure with max(currentTime, nextHeight) instead of additive edge cost.
- **Cost in these sources:** The network-delay source has no tentative-distance table and can queue O(E) candidates: O((V+E) log(E+1)) time and O(V+E) storage, assuming expected constant-time hashing. The grid minimax source uses O(rc log(rc)) time and O(rc) storage.
- **Original-code context:** Both use C++20 contains. Network-delay distances remain int. The minimax visited key is i*r+j, preserving the square-grid contract.

### Distinct arrival labels and synchronized waiting

- **Cue:** A second distinct arrival time is required, with one travel duration for every edge and synchronized traffic lights.
- **Idea and invariant:** [2045](originals/2045__2158128996.cpp) stores two distinct arrival labels per vertex, waits through a red phase before traversing the next edge, and enqueues improved labels. The deque exploits the original uniform timing rules; it is not a general weighted-graph priority queue.
- **Original-code context:** Walks may revisit vertices. This implementation is not Yen: it does not enumerate simple paths, build root/spur deviations, or exclude path prefixes. INT_MAX remains the original missing-label sentinel.

### Lowlink separates bridges from articulation points

- **Cue:** Which single edge or vertex disconnects an undirected component?
- **Idea and invariant:** [1192](originals/1192__2158532377.cpp) marks a tree edge as a bridge when low[child]>disc[parent]. [1568](originals/1568__2158580259.cpp) uses low[child]>=disc[parent] for a non-root articulation point and more than one DFS child for a root.
- **Cost and context:** O(V+E) time and O(V+E) adjacency/traversal storage for the graph source; O(rc) grid work/state for the island source. Recursion depth can be linear. Original member-state initialization assumes one call per object; the graph source skips parent vertices and assumes no parallel edges.

### Consume edges, then reverse the finished walk

- **Cue:** An itinerary must use every directed ticket exactly once with lexicographically smallest choices.
- **Idea and invariant:** [332](originals/332__2157586346.cpp) reverse-sorts each destination list, removes its smallest remaining endpoint from the back, and appends vertices after exhausting outgoing edges. Reversing the postorder path produces the itinerary.
- **Cost and context:** O(E log E) sorting bound and O(E) traversal, plus the original string/hash costs. Recursion and adjacency storage are O(E). The source fixes JFK as the start and relies on the promised Eulerian itinerary.

## Complete problem and variant index

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
