# DSU and graphs

[All topics](../../README.md) · [Source index](../../SOURCES.md) · [Coverage](../../COVERAGE.md)

**14 captured problems · 22 accepted submission records.** Every linked implementation below is an unchanged captured source file. These notes describe the code; they do not replace it with a common API.

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

## Complete problem and variant index

All captured submissions are retained, including equivalent resubmissions and exact duplicates. Submission IDs distinguish files; they are not rankings of quality. The source itself is authoritative when a note is too brief.

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

### 695. Max Area of Island

[Problem](https://leetcode.com/problems/max-area-of-island/) · Tags: Graphs, Flood fill

In-place DFS clears visited land and sums recursive component area.

**Captured variants:** One observed approach.

- [Original 2155365320](originals/695__2155365320.cpp) · [LeetCode submission](https://leetcode.com/problems/max-area-of-island/submissions/2155365320/)

### 752. Open the Lock

[Problem](https://leetcode.com/problems/open-the-lock/) · Tags: Graphs, BFS, Implicit state

BFS over four-wheel strings; generate modular +/-1 neighbors; mark visited when enqueuing.

**Captured variants:** One BFS approach.

- [Original 2156069275](originals/752__2156069275.cpp) · [LeetCode submission](https://leetcode.com/problems/open-the-lock/submissions/2156069275/)

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

### 1489. Find Critical and Pseudo-Critical Edges in Minimum Spanning Tree

[Problem](https://leetcode.com/problems/find-critical-and-pseudo-critical-edges-in-minimum-spanning-tree/) · Tags: DSU, Graphs, Minimum spanning trees

Run Kruskal baseline, then per-edge excluded and forced trials to distinguish critical and pseudo-critical edges.

**Captured variants:** Two near-identical submissions; [2162346068](originals/1489__2162346068.cpp) skips force unconditionally by id; [2162346413](originals/1489__2162346413.cpp) only explicit skip when force>0.

- [Original 2162346413](originals/1489__2162346413.cpp) · [LeetCode submission](https://leetcode.com/problems/find-critical-and-pseudo-critical-edges-in-minimum-spanning-tree/submissions/2162346413/)
- [Original 2162346068](originals/1489__2162346068.cpp) · [LeetCode submission](https://leetcode.com/problems/find-critical-and-pseudo-critical-edges-in-minimum-spanning-tree/submissions/2162346068/)

### 1584. Min Cost to Connect All Points

[Problem](https://leetcode.com/problems/min-cost-to-connect-all-points/) · Tags: Graphs, Minimum spanning trees, DSU

Enumerate complete Manhattan graph, sort weighted edges, Kruskal until n-1 merges.

**Captured variants:** Three same Kruskal approach variants; latest removes coordinate map and duplicate edges.

- [Original 2162051692](originals/1584__2162051692.cpp) · [LeetCode submission](https://leetcode.com/problems/min-cost-to-connect-all-points/submissions/2162051692/)
- [Original 2162050952](originals/1584__2162050952.cpp) · [LeetCode submission](https://leetcode.com/problems/min-cost-to-connect-all-points/submissions/2162050952/)
- [Original 2162050421](originals/1584__2162050421.cpp) · [LeetCode submission](https://leetcode.com/problems/min-cost-to-connect-all-points/submissions/2162050421/)

### 1970. Last Day Where You Can Still Cross

[Problem](https://leetcode.com/problems/last-day-where-you-can-still-cross/) · Tags: DSU, Offline queries, Grid graphs

Reverse time turns deletions into activations; connect active neighbors and two virtual boundary nodes.

**Captured variants:** [2168377479](originals/1970__2168377479.cpp) compact DSU; [2168371581](originals/1970__2168371581.cpp) same DSU with redundant initial grid DFS/flood-fill bookkeeping. Not two different asymptotic algorithms.

- [Original 2168377479](originals/1970__2168377479.cpp) · [LeetCode submission](https://leetcode.com/problems/last-day-where-you-can-still-cross/submissions/2168377479/)
- [Original 2168371581](originals/1970__2168371581.cpp) · [LeetCode submission](https://leetcode.com/problems/last-day-where-you-can-still-cross/submissions/2168371581/)

### 3568. Minimum Moves to Clean the Classroom

[Problem](https://leetcode.com/problems/minimum-moves-to-clean-the-classroom/) · Tags: Graphs, BFS, Bitmask states, Dominance pruning

BFS (row,col,trash_mask,energy,moves); recharge cells restore energy; keep best energy for each position/mask.

**Captured variants:** One observed approach.

- [Original 2131979696](originals/3568__2131979696.cpp) · [LeetCode submission](https://leetcode.com/problems/minimum-moves-to-clean-the-classroom/submissions/2131979696/)
