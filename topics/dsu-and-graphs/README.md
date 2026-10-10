# DSU and graphs

These are extractions from your submitted code, keeping your `std::` usage, camelCase names, small helper structs, and direct loops. The common thread is **assign ownership of a state as soon as you discover it**: a DSU root owns a component, a BFS enqueue owns a vertex's shortest distance, and a flood-fill mark owns a cell.

## Copy-ready pieces

Include `templates.hpp`; all names are in `patterns` and there are no other topic dependencies.

| Piece | Contract | Time | Extra space |
|---|---|---|---|
| `DSU(n)`; `find`, `uni`, `componentSize`, `componentCount` | Dense ids `[0,n)`; `uni` returns whether a merge occurred | Initialization O(n); amortized O(α(n)) per find/union | O(n) |
| `kruskal(n, edges)` | Undirected edges; returns cost, original edge indices, and `connected` | O(V + E log E + E α(V)) | O(V + E) |
| `multiSourceBfs(graph, sources)` | Directed or undirected unit edges; unreachable distance is −1 | O(V + E + S), S = number of source entries | O(V) |
| `topologicalOrder(graph)` | Directed `u → v` means u precedes v; cycle returns `nullopt` | O(V + E) | O(V) |
| `consumeIsland(grid, row, col)` | Rectangular 0/1 grid; changes this 4-connected island to 0 and returns its area | O(A) for A cells reached | O(A) |

Vertex counts, grid dimensions/area, and distances must fit `int`; ids/endpoints must be valid. Graph routines deliberately avoid repeated bounds checks. DSU rejects negative sizes. The Kruskal cost and every intermediate sum must fit `long long`. A disconnected result is a minimum spanning **forest**, and must not be mistaken for an MST. By convention, the empty graph has a connected empty result; an empty topological order is a valid DAG, distinct from `nullopt`.

## 1. DSU: only roots own a current size

Your [1970. Last Day Where You Can Still Cross](https://leetcode.com/problems/last-day-where-you-can-still-cross/) solution ([submission 2168377479](https://leetcode.com/problems/last-day-where-you-can-still-cross/submissions/2168377479/)) supplies the recurring `parent` / `size` / `find` / `uni` helper.

```text
Before find(3):       After find(3):
3 → 2 → 0            3 ───→ 0
    1 → 0            2 ───→ 0
                     1 ───→ 0
Only size[0] is authoritative for this component.
```

- `parent[root] == root`; `find` preserves connectivity while shortening paths.
- Union links the smaller root under the larger root, then adds root sizes.
- `size[i]` may be stale if i is not a root. Use `componentSize(i)` for a query.
- Repeated union and self-union do nothing. The boolean merge result removes Kruskal's separate pair of `find` calls.
- Path compression is inappropriate for an undo/rollback DSU without extra bookkeeping; no rollback template is claimed here.

**Your reverse-time trick:** deletion is hard for a normal DSU; activation is easy. In 1970, start with all cells inactive, restore `cells[d]`, union active neighbors, and test two virtual nodes.

```text
virtual top = 0
     │ links to active row-0 cells
cell id(r,c) = r * cols + c + 1
     │ links to active last-row cells
virtual bottom = rows * cols + 1
```

After restoring `cells[d]`, the grid equals the forward grid after d floods. That is why returning d is correct, rather than d+1. An inactive cell must never connect its neighbors. With N cells the sweep takes O(N α(N)) time and O(N) space, including the activity grid.

**Changes from source:** iterative two-pass compression replaces recursive `find`; `uni` now returns `bool` rather than `void`; `componentSize`/`componentCount` are added; the duplicate `public:` is removed. Public vectors preserve the familiar helper shape, but callers must not modify them.

## 2. Kruskal: sort first, merge only different components

Your [1584. Min Cost to Connect All Points](https://leetcode.com/problems/min-cost-to-connect-all-points/) ([submission 2162051692](https://leetcode.com/problems/min-cost-to-connect-all-points/submissions/2162051692/)) builds Manhattan edges for `i < j`, sorts them, and stops after V−1 successful merges. The extracted version accepts an edge list rather than rebuilding a problem-specific complete graph.

```text
sorted edge   different roots?   action
(1,2,-1)            yes          add, merge
(0,2, 2)            yes          add, merge
(0,1, 4)             no          would form a cycle
```

**Invariant:** accepted edges form a forest. Each selected edge is a cheapest available connection across some current component cut, so the forest can be extended to an MST of its connected component. Equal weights do not require special handling for finding one MST; their order can change which optimal tree is returned.

The helper keeps original edge positions, handles parallel edges, rejects self-loops through `uni`, and supports negative weights. Equal-weight ties use original index for reproducible output. For a complete Manhattan graph, E is Θ(V²): edge generation and storage are quadratic, and sorting costs O(V² log V). Widen coordinates **before** subtraction when generating weights.

Your [1489. Find Critical and Pseudo-Critical Edges in Minimum Spanning Tree](https://leetcode.com/problems/find-critical-and-pseudo-critical-edges-in-minimum-spanning-tree/) ([submission 2162346413](https://leetcode.com/problems/find-critical-and-pseudo-critical-edges-in-minimum-spanning-tree/submissions/2162346413/)) reuses the same sweep:

1. Compute the connected baseline MST cost.
2. Exclude one edge. If connection becomes impossible or cost increases, it is critical.
3. Otherwise force that edge first, then finish Kruskal. Equal baseline cost makes it pseudo-critical.

This is an adaptation recipe, not an additional force/exclude API in the header. Preserve original edge ids while sorting; count actual merges; reject a forced self-loop. The source's `force > 0` skip condition should read `force >= 0`: id zero is valid. In the submitted constraints, DSU already rejects re-adding forced edge zero, so this is a clarity/generalization fix, not a claimed wrong answer. The source sorts once, then does O(E) sweeps: O(E log E + E·V + E² α(V)) including each fresh DSU initialization.

**Changes from source:** `unify/query` from 1584 become `uni/find`; `WeightedEdge` replaces positional vectors; cost is widened; unused coordinate-packing helper is dropped; explicit connectivity replaces ambiguous zero/sentinel returns. No coordinate-to-id map is used, so equal-position points remain separate vertices.

## 3. BFS and topological order: a queue has two different meanings

In [752. Open the Lock](https://leetcode.com/problems/open-the-lock/) ([submission 2156069275](https://leetcode.com/problems/open-the-lock/submissions/2156069275/)), the queue holds states with known shortest distances. In [994. Rotting Oranges](https://leetcode.com/problems/rotting-oranges/) ([submission 2155965323](https://leetcode.com/problems/rotting-oranges/submissions/2155965323/)), many states start at distance zero.

```text
sources:          A       D       distance 0
                  ↓       ↓
next wave:        B ←─────┘       distance 1
                  ↓
                  C               distance 2
```

Set the visited marker/distance **before enqueueing**, including every source. Otherwise two parents can schedule the same vertex. With unit edges, FIFO order processes nondecreasing distances; the first discovery is optimal. Duplicate sources are harmless. With weighted edges, this BFS contract no longer applies.

**Changes from source:** one explicit adjacency-list helper replaces lock-string/grid neighbor generation. Distances replace level-sized batches and the source's `time = -1` convention. To recover rotting time, take the maximum reachable fresh-cell distance and reject any unreachable fresh cell. For implicit states, keep the same queue/mark order and generate neighbors on demand.

[207. Course Schedule](https://leetcode.com/problems/course-schedule/) ([Kahn submission 2139404121](https://leetcode.com/problems/course-schedule/submissions/2139404121/), [DFS submission 2139396834](https://leetcode.com/problems/course-schedule/submissions/2139396834/)) uses the queue differently: only vertices with **no remaining incoming edges** are ready. For each prerequisite pair `[course, prerequisite]`, add `prerequisite → course`.

- Decrement an outgoing neighbor's indegree once per stored edge; enqueue only when it reaches zero.
- If fewer than V vertices are removed, the remainder contains a cycle.
- Parallel edges work only if indegree construction and decrementing both retain their multiplicity.
- Kahn does not need level batching for cycle detection. The extracted function returns the ordering, not only a yes/no answer.
- Your DFS alternative distinguishes active-path (`visiting`) from finished (`visited`). Encountering a finished node is safe; encountering an active node is a directed cycle.

## 4. Grid traversal: mark once, change the direction when useful

`consumeIsland` combines the area accumulation from [695. Max Area of Island](https://leetcode.com/problems/max-area-of-island/) ([submission 2155365320](https://leetcode.com/problems/max-area-of-island/submissions/2155365320/)) with the consume-once rule in [200. Number of Islands](https://leetcode.com/problems/number-of-islands/) ([submission 2155362152](https://leetcode.com/problems/number-of-islands/submissions/2155362152/)). Scan every grid cell and call it on remaining land to obtain component counts or maximum area.

**Changes from source:** an explicit stack avoids recursive call-stack exhaustion; empty input and out-of-range starts return 0; cells turn to water when scheduled, not when popped. The helper mutates its input. Copy the grid if the original must survive. Rectangular binary input is a precondition; diagonal contact does not connect islands.

Other directly observed adaptations:

- [130. Surrounded Regions](https://leetcode.com/problems/surrounded-regions/) ([submission 2156047108](https://leetcode.com/problems/surrounded-regions/submissions/2156047108/)): flood from the border, preserve reached cells, then flip the rest. The source's temporary `'V'` marker requires an input alphabet that excludes it, and `board[0]` needs an empty-grid guard when generalized.
- [417. Pacific Atlantic Water Flow](https://leetcode.com/problems/pacific-atlantic-water-flow/) ([submission 2156035451](https://leetcode.com/problems/pacific-atlantic-water-flow/submissions/2156035451/)): start at each ocean and walk **uphill** (`nextHeight >= currentHeight`), reversing the water-flow edges. One bit per origin means each `(cell, ocean)` pair is processed once, for O(rows·cols) time/space.
- [133. Clone Graph](https://leetcode.com/problems/clone-graph/) ([submission 2155372665](https://leetcode.com/problems/clone-graph/submissions/2155372665/)): insert `oldToNew[current] = clone` **before** recursing through neighbors. Identity is the node pointer, not its value; cycles and shared neighbors then reuse the same clone. A production wrapper should define ownership of allocated nodes. No owning clone API is included here.

## Tests and verification

`test.cpp` checks edge cases and compares against independent oracles: DSU versus component relabeling, 800 small Kruskal graphs versus exhaustive spanning-tree subsets, 500 BFS graphs versus Floyd–Warshall, 500 topological cases versus three-color DFS, and 400 grid cases versus fixed-point reachability. It also verifies chosen edge ids and the exact flood-fill mutation footprint.

```sh
g++ -std=c++20 -O2 -Wall -Wextra -Werror -pedantic test.cpp -o /tmp/graph-tests
/tmp/graph-tests
g++ -std=c++20 -O1 -g -Wall -Wextra -Werror -pedantic \
  -fsanitize=address,undefined -fno-omit-frame-pointer test.cpp -o /tmp/graph-san
ASAN_OPTIONS=detect_leaks=0 /tmp/graph-san
```

The sanitizer command checks address/undefined behavior; it does **not** verify leaks. LeakSanitizer cannot run under this execution environment's ptrace arrangement. Tests were written first and each feature group failed against an API stub before implementation.
