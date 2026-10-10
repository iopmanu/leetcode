# Inspected source index

The entries below link the actual accepted C++ submissions inspected for this handbook. Several submissions can implement the same approach; the count is not a count of unique algorithms. Source pages may require the source account to be signed in.

See [coverage](COVERAGE.md) before interpreting this as a complete account export.

## [range-queries](topics/range-queries/README.md)

### [699. Falling Squares](https://leetcode.com/problems/falling-squares/)

Range assignment and range maximum over compressed elementary x-intervals; landing height = current max + square side.

Accepted source: [2155079538](https://leetcode.com/problems/falling-squares/submissions/2155079538/)

### [327. Count of Range Sum](https://leetcode.com/problems/count-of-range-sum/)

Preload all prefix sums, remove current prefix, count future prefixes in [current+lower,current+upper] via Fenwick.

Accepted source: [2152424852](https://leetcode.com/problems/count-of-range-sum/submissions/2152424852/)

### [406. Queue Reconstruction by Height](https://leetcode.com/problems/queue-reconstruction-by-height/)

Sort by height ascending, equal height k descending; count tree tracks free positions, choose and remove kth free slot.

Accepted source: [2152399602](https://leetcode.com/problems/queue-reconstruction-by-height/submissions/2152399602/)

### [307. Range Sum Query - Mutable](https://leetcode.com/problems/range-sum-query-mutable/)

Fenwick O(n) construction copies values then propagates each tree cell to parent; point assignment converted to delta, inclusive range via two prefixes.

Accepted source: [2152356890](https://leetcode.com/problems/range-sum-query-mutable/submissions/2152356890/)

### [315. Count of Smaller Numbers After Self](https://leetcode.com/problems/count-of-smaller-numbers-after-self/)

Each segment-tree node stores merged sorted subarray; range count-less-than uses lower_bound at fully covered nodes.

Accepted source: [2150813916](https://leetcode.com/problems/count-of-smaller-numbers-after-self/submissions/2150813916/) · [2150760829](https://leetcode.com/problems/count-of-smaller-numbers-after-self/submissions/2150760829/)

### [3525. Find X Value of Array II](https://leetcode.com/problems/find-x-value-of-array-ii/)

Each node stores full product modulo k plus counts of prefix-product remainders; ordered merge keeps left prefixes and extends full left by right prefixes.

Accepted source: [2150176033](https://leetcode.com/problems/find-x-value-of-array-ii/submissions/2150176033/)

## [dsu-and-graphs](topics/dsu-and-graphs/README.md)

### [1970. Last Day Where You Can Still Cross](https://leetcode.com/problems/last-day-where-you-can-still-cross/)

Reverse time turns deletions into activations; connect active neighbors and two virtual boundary nodes.

Accepted source: [2168377479](https://leetcode.com/problems/last-day-where-you-can-still-cross/submissions/2168377479/) · [2168371581](https://leetcode.com/problems/last-day-where-you-can-still-cross/submissions/2168371581/)

### [1489. Find Critical and Pseudo-Critical Edges in Minimum Spanning Tree](https://leetcode.com/problems/find-critical-and-pseudo-critical-edges-in-minimum-spanning-tree/)

Run Kruskal baseline, then per-edge excluded and forced trials to distinguish critical and pseudo-critical edges.

Accepted source: [2162346413](https://leetcode.com/problems/find-critical-and-pseudo-critical-edges-in-minimum-spanning-tree/submissions/2162346413/) · [2162346068](https://leetcode.com/problems/find-critical-and-pseudo-critical-edges-in-minimum-spanning-tree/submissions/2162346068/)

### [1584. Min Cost to Connect All Points](https://leetcode.com/problems/min-cost-to-connect-all-points/)

Enumerate complete Manhattan graph, sort weighted edges, Kruskal until n-1 merges.

Accepted source: [2162051692](https://leetcode.com/problems/min-cost-to-connect-all-points/submissions/2162051692/) · [2162050952](https://leetcode.com/problems/min-cost-to-connect-all-points/submissions/2162050952/) · [2162050421](https://leetcode.com/problems/min-cost-to-connect-all-points/submissions/2162050421/)

### [207. Course Schedule](https://leetcode.com/problems/course-schedule/)

Kahn indegrees plus queue; separate recursive active-path/done cycle detection.

Accepted source: [2156079641](https://leetcode.com/problems/course-schedule/submissions/2156079641/) · [2139404121](https://leetcode.com/problems/course-schedule/submissions/2139404121/) · [2139396834](https://leetcode.com/problems/course-schedule/submissions/2139396834/)

### [752. Open the Lock](https://leetcode.com/problems/open-the-lock/)

BFS over four-wheel strings; generate modular +/-1 neighbors; mark visited when enqueuing.

Accepted source: [2156069275](https://leetcode.com/problems/open-the-lock/submissions/2156069275/)

### [130. Surrounded Regions](https://leetcode.com/problems/surrounded-regions/)

Mark border-connected cells then flip only unmarked interior cells.

Accepted source: [2156047108](https://leetcode.com/problems/surrounded-regions/submissions/2156047108/)

### [417. Pacific Atlantic Water Flow](https://leetcode.com/problems/pacific-atlantic-water-flow/)

DFS uphill from both oceans; each cell carries one bit per origin; append when both bits first present.

Accepted source: [2156035451](https://leetcode.com/problems/pacific-atlantic-water-flow/submissions/2156035451/)

### [994. Rotting Oranges](https://leetcode.com/problems/rotting-oranges/)

Seed all rotten cells, process queue levels, count fresh cells and return elapsed waves or -1.

Accepted source: [2155965323](https://leetcode.com/problems/rotting-oranges/submissions/2155965323/) · [2011741235](https://leetcode.com/problems/rotting-oranges/submissions/2011741235/)

### [133. Clone Graph](https://leetcode.com/problems/clone-graph/)

Memoized graph cloning creates clone and registers it before recursive neighbor traversal to terminate cycles.

Accepted source: [2155372665](https://leetcode.com/problems/clone-graph/submissions/2155372665/)

### [695. Max Area of Island](https://leetcode.com/problems/max-area-of-island/)

In-place DFS clears visited land and sums recursive component area.

Accepted source: [2155365320](https://leetcode.com/problems/max-area-of-island/submissions/2155365320/)

### [200. Number of Islands](https://leetcode.com/problems/number-of-islands/)

Count unvisited land seeds and flood-fill each connected component.

Accepted source: [2155362152](https://leetcode.com/problems/number-of-islands/submissions/2155362152/) · [2125964378](https://leetcode.com/problems/number-of-islands/submissions/2125964378/)

### [463. Island Perimeter](https://leetcode.com/problems/island-perimeter/)

DFS land cells and count outgoing edges to water/outside; pack coordinate pair into uint64 key.

Accepted source: [2155358279](https://leetcode.com/problems/island-perimeter/submissions/2155358279/)

### [997. Find the Town Judge](https://leetcode.com/problems/find-the-town-judge/)

Store incoming/outgoing trust lists and find incoming n-1 with no outgoing edges.

Accepted source: [2155347510](https://leetcode.com/problems/find-the-town-judge/submissions/2155347510/)

### [3568. Minimum Moves to Clean the Classroom](https://leetcode.com/problems/minimum-moves-to-clean-the-classroom/)

BFS (row,col,trash_mask,energy,moves); recharge cells restore energy; keep best energy for each position/mask.

Accepted source: [2131979696](https://leetcode.com/problems/minimum-moves-to-clean-the-classroom/submissions/2131979696/)

## [trees-and-lists](topics/trees-and-lists/README.md)

### [138. Copy List with Random Pointer](https://leetcode.com/problems/copy-list-with-random-pointer/)

Two passes: allocate clone for every original pointer, then wire next/random through pointer mapping.

Accepted source: [2143802245](https://leetcode.com/problems/copy-list-with-random-pointer/submissions/2143802245/)

### [19. Remove Nth Node From End of List](https://leetcode.com/problems/remove-nth-node-from-end-of-list/)

Count length then unlink node at length-n, with head special case.

Accepted source: [2143696811](https://leetcode.com/problems/remove-nth-node-from-end-of-list/submissions/2143696811/)

### [143. Reorder List](https://leetcode.com/problems/reorder-list/)

Latest source splits at midpoint, reverses second half, alternates merge; older sources materialize node pointers and track visited.

Accepted source: [2143673583](https://leetcode.com/problems/reorder-list/submissions/2143673583/) · [2143663379](https://leetcode.com/problems/reorder-list/submissions/2143663379/) · [1211639660](https://leetcode.com/problems/reorder-list/submissions/1211639660/)

### [141. Linked List Cycle](https://leetcode.com/problems/linked-list-cycle/)

Floyd cycle detection advances 1 and 2 until meet or null.

Accepted source: [2143629142](https://leetcode.com/problems/linked-list-cycle/submissions/2143629142/)

### [21. Merge Two Sorted Lists](https://leetcode.com/problems/merge-two-sorted-lists/)

Dummy-head merge links existing nodes then appends remainder.

Accepted source: [2143594529](https://leetcode.com/problems/merge-two-sorted-lists/submissions/2143594529/)

### [206. Reverse Linked List](https://leetcode.com/problems/reverse-linked-list/)

Latest source reverses links with prev/current/tmp; older source creates reversed copies after reusing original head.

Accepted source: [2143560010](https://leetcode.com/problems/reverse-linked-list/submissions/2143560010/) · [2126014226](https://leetcode.com/problems/reverse-linked-list/submissions/2126014226/)

### [105. Construct Binary Tree from Preorder and Inorder Traversal](https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/)

Inorder value-to-index map plus advancing preorder cursor builds left/right subranges.

Accepted source: [2141508524](https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/submissions/2141508524/) · [2141508275](https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/submissions/2141508275/)

### [230. Kth Smallest Element in a BST](https://leetcode.com/problems/kth-smallest-element-in-a-bst/)

Inorder traversal increments count and records kth visited value.

Accepted source: [2140766874](https://leetcode.com/problems/kth-smallest-element-in-a-bst/submissions/2140766874/)

### [98. Validate Binary Search Tree](https://leetcode.com/problems/validate-binary-search-tree/)

Carry exclusive low/high bounds recursively to validate every descendant.

Accepted source: [2140737519](https://leetcode.com/problems/validate-binary-search-tree/submissions/2140737519/)

### [199. Binary Tree Right Side View](https://leetcode.com/problems/binary-tree-right-side-view/)

Queue complete levels left-to-right and take queue.back at level start for rightmost view.

Accepted source: [2140707899](https://leetcode.com/problems/binary-tree-right-side-view/submissions/2140707899/)

### [102. Binary Tree Level Order Traversal](https://leetcode.com/problems/binary-tree-level-order-traversal/)

Freeze queue length, collect one vector per level, enqueue children.

Accepted source: [2140704978](https://leetcode.com/problems/binary-tree-level-order-traversal/submissions/2140704978/)

### [235. Lowest Common Ancestor of a Binary Search Tree](https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-search-tree/)

Order target values; descend until current value lies between targets.

Accepted source: [2140699724](https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-search-tree/submissions/2140699724/)

### [572. Subtree of Another Tree](https://leetcode.com/problems/subtree-of-another-tree/)

At every root candidate, recursively test structural equality; recurse through host tree otherwise.

Accepted source: [2140623050](https://leetcode.com/problems/subtree-of-another-tree/submissions/2140623050/)

### [100. Same Tree](https://leetcode.com/problems/same-tree/)

Shared result flag checks null mismatch then value equality and both children.

Accepted source: [2140598575](https://leetcode.com/problems/same-tree/submissions/2140598575/)

### [543. Diameter of Binary Tree](https://leetcode.com/problems/diameter-of-binary-tree/)

Return subtree height while updating best path through current node with left+right heights.

Accepted source: [2140582704](https://leetcode.com/problems/diameter-of-binary-tree/submissions/2140582704/)

### [104. Maximum Depth of Binary Tree](https://leetcode.com/problems/maximum-depth-of-binary-tree/)

Return 1+maximum child height, null=0.

Accepted source: [2140575615](https://leetcode.com/problems/maximum-depth-of-binary-tree/submissions/2140575615/)

### [226. Invert Binary Tree](https://leetcode.com/problems/invert-binary-tree/)

Swap child pointers then recurse into both.

Accepted source: [2140574036](https://leetcode.com/problems/invert-binary-tree/submissions/2140574036/)

### [2265. Count Nodes Equal to Average of Subtree](https://leetcode.com/problems/count-nodes-equal-to-average-of-subtree/)

Return pair (sum,count) for subtree and count matching integer average.

Accepted source: [2137363284](https://leetcode.com/problems/count-nodes-equal-to-average-of-subtree/submissions/2137363284/)

### [297. Serialize and Deserialize Binary Tree](https://leetcode.com/problems/serialize-and-deserialize-binary-tree/)

Preorder tokens with explicit null markers reconstruct unique shape; older source encodes indexed inorder and preorder.

Accepted source: [2153777400](https://leetcode.com/problems/serialize-and-deserialize-binary-tree/submissions/2153777400/) · [2141912475](https://leetcode.com/problems/serialize-and-deserialize-binary-tree/submissions/2141912475/) · [2141671426](https://leetcode.com/problems/serialize-and-deserialize-binary-tree/submissions/2141671426/)

### [124. Binary Tree Maximum Path Sum](https://leetcode.com/problems/binary-tree-maximum-path-sum/)

Return best one-branch gain, update best full path through node using both nonnegative child gains.

Accepted source: [2153370936](https://leetcode.com/problems/binary-tree-maximum-path-sum/submissions/2153370936/) · [2141514512](https://leetcode.com/problems/binary-tree-maximum-path-sum/submissions/2141514512/)

### [1448. Count Good Nodes in Binary Tree](https://leetcode.com/problems/count-good-nodes-in-binary-tree/)

Carry maximum root-to-current value and count node if >= prior max.

Accepted source: [2140724204](https://leetcode.com/problems/count-good-nodes-in-binary-tree/submissions/2140724204/)

### [110. Balanced Binary Tree](https://leetcode.com/problems/balanced-binary-tree/)

Compute heights and shared balanced flag; skip later work once imbalance detected.

Accepted source: [2140593789](https://leetcode.com/problems/balanced-binary-tree/submissions/2140593789/)

### [25. Reverse Nodes in k-Group](https://leetcode.com/problems/reverse-nodes-in-k-group/)

Verify complete k-node group, reverse exactly k links, recursively process suffix and attach via old head.

Accepted source: [2144552684](https://leetcode.com/problems/reverse-nodes-in-k-group/submissions/2144552684/)

### [23. Merge k Sorted Lists](https://leetcode.com/problems/merge-k-sorted-lists/)

Latest inserts every node into heap then relinks sorted nodes; older repeatedly dequeues two list heads and enqueues merged list.

Accepted source: [2144522916](https://leetcode.com/problems/merge-k-sorted-lists/submissions/2144522916/) · [2144097838](https://leetcode.com/problems/merge-k-sorted-lists/submissions/2144097838/)

### [2. Add Two Numbers](https://leetcode.com/problems/add-two-numbers/)

Dummy-head output list, add corresponding digits plus carry, process remainders, append final carry.

Accepted source: [2143813487](https://leetcode.com/problems/add-two-numbers/submissions/2143813487/)

### [968. Binary Tree Cameras](https://leetcode.com/problems/binary-tree-cameras/)

Postorder cameras placed when child uncovered, or root itself uncovered; set tracks covered nodes, with null pre-covered.

Accepted source: [2155106387](https://leetcode.com/problems/binary-tree-cameras/submissions/2155106387/)

## [search-and-sort](topics/search-and-sort/README.md)

### [4. Median of Two Sorted Arrays](https://leetcode.com/problems/median-of-two-sorted-arrays/)

Partition smaller sorted array so left side has ceil(total/2), enforce maxLeft<=minRight across both arrays.

Accepted source: [2147722433](https://leetcode.com/problems/median-of-two-sorted-arrays/submissions/2147722433/) · [2147703761](https://leetcode.com/problems/median-of-two-sorted-arrays/submissions/2147703761/) · [1621118867](https://leetcode.com/problems/median-of-two-sorted-arrays/submissions/1621118867/)

### [1095. Find in Mountain Array](https://leetcode.com/problems/find-in-mountain-array/)

Find peak, binary-search ascending half first then descending half.

Accepted source: [2147557289](https://leetcode.com/problems/find-in-mountain-array/submissions/2147557289/) · [2147556354](https://leetcode.com/problems/find-in-mountain-array/submissions/2147556354/)

### [852. Peak Index in a Mountain Array](https://leetcode.com/problems/peak-index-in-a-mountain-array/)

Compare midpoint with neighbors to choose mountain slope or identify peak.

Accepted source: [2147513687](https://leetcode.com/problems/peak-index-in-a-mountain-array/submissions/2147513687/) · [2147512689](https://leetcode.com/problems/peak-index-in-a-mountain-array/submissions/2147512689/)

### [410. Split Array Largest Sum](https://leetcode.com/problems/split-array-largest-sum/)

First feasible maximum partition sum, using greedy breaks; predicate currently returns true when infeasible.

Accepted source: [2146752727](https://leetcode.com/problems/split-array-largest-sum/submissions/2146752727/) · [2139584888](https://leetcode.com/problems/split-array-largest-sum/submissions/2139584888/) · [2139584401](https://leetcode.com/problems/split-array-largest-sum/submissions/2139584401/)

### [81. Search in Rotated Sorted Array II](https://leetcode.com/problems/search-in-rotated-sorted-array-ii/)

Shrink ambiguous equal boundaries; otherwise identify sorted half and retain matching target interval.

Accepted source: [2146739961](https://leetcode.com/problems/search-in-rotated-sorted-array-ii/submissions/2146739961/) · [2146727441](https://leetcode.com/problems/search-in-rotated-sorted-array-ii/submissions/2146727441/)

### [33. Search in Rotated Sorted Array](https://leetcode.com/problems/search-in-rotated-sorted-array/)

Find rotation pivot, then binary-search virtual sorted indices mapped by modulo.

Accepted source: [2146701709](https://leetcode.com/problems/search-in-rotated-sorted-array/submissions/2146701709/) · [2125939691](https://leetcode.com/problems/search-in-rotated-sorted-array/submissions/2125939691/) · [2011698957](https://leetcode.com/problems/search-in-rotated-sorted-array/submissions/2011698957/)

### [153. Find Minimum in Rotated Sorted Array](https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/)

Find first index on low sorted run by comparing middle with fixed final value or current right value.

Accepted source: [2146698709](https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/submissions/2146698709/) · [2127418311](https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/submissions/2127418311/) · [2024485741](https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/submissions/2024485741/)

### [1011. Capacity To Ship Packages Within D Days](https://leetcode.com/problems/capacity-to-ship-packages-within-d-days/)

First feasible capacity between maximum weight and total weight; simulate sequential loading.

Accepted source: [2146696311](https://leetcode.com/problems/capacity-to-ship-packages-within-d-days/submissions/2146696311/) · [2024526301](https://leetcode.com/problems/capacity-to-ship-packages-within-d-days/submissions/2024526301/)

### [875. Koko Eating Bananas](https://leetcode.com/problems/koko-eating-bananas/)

First feasible speed with sum of integer ceilings.

Accepted source: [2146691389](https://leetcode.com/problems/koko-eating-bananas/submissions/2146691389/) · [2139503155](https://leetcode.com/problems/koko-eating-bananas/submissions/2139503155/) · [2139502841](https://leetcode.com/problems/koko-eating-bananas/submissions/2139502841/) · [2024503988](https://leetcode.com/problems/koko-eating-bananas/submissions/2024503988/)

### [74. Search a 2D Matrix](https://leetcode.com/problems/search-a-2d-matrix/)

Binary search row-major matrix as virtual flat array.

Accepted source: [2146688351](https://leetcode.com/problems/search-a-2d-matrix/submissions/2146688351/) · [2127411724](https://leetcode.com/problems/search-a-2d-matrix/submissions/2127411724/)

### [69. Sqrt(x)](https://leetcode.com/problems/sqrtx/)

Inclusive binary search for floor square root; return last feasible right boundary.

Accepted source: [2146686635](https://leetcode.com/problems/sqrtx/submissions/2146686635/)

### [374. Guess Number Higher or Lower](https://leetcode.com/problems/guess-number-higher-or-lower/)

Inclusive search steered by sign of guess(mid).

Accepted source: [2146681577](https://leetcode.com/problems/guess-number-higher-or-lower/submissions/2146681577/)

### [35. Search Insert Position](https://leetcode.com/problems/search-insert-position/)

Inclusive search eliminates >=target to the right and returns insertion index left.

Accepted source: [2146678224](https://leetcode.com/problems/search-insert-position/submissions/2146678224/)

### [704. Binary Search](https://leetcode.com/problems/binary-search/)

Inclusive exact-match search returning -1 when absent.

Accepted source: [2146675354](https://leetcode.com/problems/binary-search/submissions/2146675354/)

### [347. Top K Frequent Elements](https://leetcode.com/problems/top-k-frequent-elements/)

Count values then select top k by frequency; actual alternatives full max heap and bounded ordered set.

Accepted source: [2133013441](https://leetcode.com/problems/top-k-frequent-elements/submissions/2133013441/) · [2127429766](https://leetcode.com/problems/top-k-frequent-elements/submissions/2127429766/) · [2025491048](https://leetcode.com/problems/top-k-frequent-elements/submissions/2025491048/)

### [215. Kth Largest Element in an Array](https://leetcode.com/problems/kth-largest-element-in-an-array/)

Hoare-style partition around middle element, recurse only partition containing zero-based target n-k; alternatives sort and max heap.

Accepted source: [2144679787](https://leetcode.com/problems/kth-largest-element-in-an-array/submissions/2144679787/) · [2144679621](https://leetcode.com/problems/kth-largest-element-in-an-array/submissions/2144679621/) · [2144679073](https://leetcode.com/problems/kth-largest-element-in-an-array/submissions/2144679073/) · [2144678866](https://leetcode.com/problems/kth-largest-element-in-an-array/submissions/2144678866/) · [2132995910](https://leetcode.com/problems/kth-largest-element-in-an-array/submissions/2132995910/) · [2132966164](https://leetcode.com/problems/kth-largest-element-in-an-array/submissions/2132966164/) · [2132965197](https://leetcode.com/problems/kth-largest-element-in-an-array/submissions/2132965197/)

### [493. Reverse Pairs](https://leetcode.com/problems/reverse-pairs/)

Sort halves recursively, count cross pairs with monotone two pointers against 2*right, then ordinary merge.

Accepted source: [2150875619](https://leetcode.com/problems/reverse-pairs/submissions/2150875619/)

### [658. Find K Closest Elements](https://leetcode.com/problems/find-k-closest-elements/)

Sorted array drops farther endpoint until k remain; older keeps closest k by max heap of (distance,value), then sorts.

Accepted source: [2127298849](https://leetcode.com/problems/find-k-closest-elements/submissions/2127298849/) · [2127164573](https://leetcode.com/problems/find-k-closest-elements/submissions/2127164573/)

### [41. First Missing Positive](https://leetcode.com/problems/first-missing-positive/)

Normalize outside [1,n] to n+1, mark seen values by negating slot value-1, return first positive slot. Older builds membership map and scans positive candidates.

Accepted source: [2142829718](https://leetcode.com/problems/first-missing-positive/submissions/2142829718/) · [2142586270](https://leetcode.com/problems/first-missing-positive/submissions/2142586270/) · [1214762629](https://leetcode.com/problems/first-missing-positive/submissions/1214762629/)

### [287. Find the Duplicate Number](https://leetcode.com/problems/find-the-duplicate-number/)

Latest marks sign at value-1 to detect repeated value; older uses seen set.

Accepted source: [2143946691](https://leetcode.com/problems/find-the-duplicate-number/submissions/2143946691/) · [2143814563](https://leetcode.com/problems/find-the-duplicate-number/submissions/2143814563/) · [2140565463](https://leetcode.com/problems/find-the-duplicate-number/submissions/2140565463/) · [1212846979](https://leetcode.com/problems/find-the-duplicate-number/submissions/1212846979/)

### [344. Reverse String](https://leetcode.com/problems/reverse-string/)

Swap inward in place.

Accepted source: [2147725168](https://leetcode.com/problems/reverse-string/submissions/2147725168/)

## [monotonic-and-heaps](topics/monotonic-and-heaps/README.md)

### [321. Create Maximum Number](https://leetcode.com/problems/create-maximum-number/)

Enumerate split of k across arrays, select max subsequence with discard budget, merge by comparing entire remaining suffixes.

Accepted source: [2154885660](https://leetcode.com/problems/create-maximum-number/submissions/2154885660/)

### [84. Largest Rectangle in Histogram](https://leetcode.com/problems/largest-rectangle-in-histogram/)

Increasing stack of indices; on smaller height, popped bar spans after new stack top through i-1; drain at n.

Accepted source: [2146612938](https://leetcode.com/problems/largest-rectangle-in-histogram/submissions/2146612938/) · [2143497674](https://leetcode.com/problems/largest-rectangle-in-histogram/submissions/2143497674/) · [2132956467](https://leetcode.com/problems/largest-rectangle-in-histogram/submissions/2132956467/) · [2132944465](https://leetcode.com/problems/largest-rectangle-in-histogram/submissions/2132944465/)

### [853. Car Fleet](https://leetcode.com/problems/car-fleet/)

Sort cars by position ascending; arrival-time stack pops fleets behind that catch a later slower fleet.

Accepted source: [2146549976](https://leetcode.com/problems/car-fleet/submissions/2146549976/) · [2146548870](https://leetcode.com/problems/car-fleet/submissions/2146548870/)

### [907. Sum of Subarray Minimums](https://leetcode.com/problems/sum-of-subarray-minimums/)

Pop minimum indices and multiply value by left choices and right choices; final i=n drains stack.

Accepted source: [2132055030](https://leetcode.com/problems/sum-of-subarray-minimums/submissions/2132055030/)

### [632. Smallest Range Covering Elements from K Lists](https://leetcode.com/problems/smallest-range-covering-elements-from-k-lists/)

Heap holds one head per list and scalar tracks current maximum; advance current minimum list and improve range.

Accepted source: [2154226064](https://leetcode.com/problems/smallest-range-covering-elements-from-k-lists/submissions/2154226064/)

### [862. Shortest Subarray with Sum at Least K](https://leetcode.com/problems/shortest-subarray-with-sum-at-least-k/)

Newest deque stores candidate prefixes in reverse orientation: newest at front, oldest/minimum at back; pop feasible starts from back and dominated prefixes from front. Older min-heap pops feasible prior prefixes.

Accepted source: [2152907567](https://leetcode.com/problems/shortest-subarray-with-sum-at-least-k/submissions/2152907567/) · [2152891991](https://leetcode.com/problems/shortest-subarray-with-sum-at-least-k/submissions/2152891991/) · [2152436083](https://leetcode.com/problems/shortest-subarray-with-sum-at-least-k/submissions/2152436083/)

### [901. Online Stock Span](https://leetcode.com/problems/online-stock-span/)

Stack holds (price,span); pop <=price and combine spans before pushing new price.

Accepted source: [2146501827](https://leetcode.com/problems/online-stock-span/submissions/2146501827/)

### [739. Daily Temperatures](https://leetcode.com/problems/daily-temperatures/)

Keep unresolved decreasing temperatures by index; warmer incoming value resolves waiting distances.

Accepted source: [2146492152](https://leetcode.com/problems/daily-temperatures/submissions/2146492152/) · [2131986928](https://leetcode.com/problems/daily-temperatures/submissions/2131986928/) · [2025552405](https://leetcode.com/problems/daily-temperatures/submissions/2025552405/)

### [735. Asteroid Collision](https://leetcode.com/problems/asteroid-collision/)

Only right-moving stack top and incoming left-moving item can collide; pop weaker until incoming destroyed or no conflict.

Accepted source: [2146489128](https://leetcode.com/problems/asteroid-collision/submissions/2146489128/) · [2025582812](https://leetcode.com/problems/asteroid-collision/submissions/2025582812/)

### [480. Sliding Window Median](https://leetcode.com/problems/sliding-window-median/)

Two balanced multisets of (value,index) plus maps index->iterator support insertion, deletion, and median.

Accepted source: [2150661436](https://leetcode.com/problems/sliding-window-median/submissions/2150661436/)

### [295. Find Median from Data Stream](https://leetcode.com/problems/find-median-from-data-stream/)

Max-heap lower half and min-heap upper half; rebalance size difference to left=right or left=right+1.

Accepted source: [2150573901](https://leetcode.com/problems/find-median-from-data-stream/submissions/2150573901/) · [2144767620](https://leetcode.com/problems/find-median-from-data-stream/submissions/2144767620/) · [2133767286](https://leetcode.com/problems/find-median-from-data-stream/submissions/2133767286/)

### [621. Task Scheduler](https://leetcode.com/problems/task-scheduler/)

Consume up to n+1 distinct most-frequent task types per round, reinsert remaining counts, count full round unless terminal.

Accepted source: [2144706913](https://leetcode.com/problems/task-scheduler/submissions/2144706913/)

### [239. Sliding Window Maximum](https://leetcode.com/problems/sliding-window-maximum/)

Max heap of (value,index), discard expired entries only when they reach top.

Accepted source: [2149742695](https://leetcode.com/problems/sliding-window-maximum/submissions/2149742695/) · [2024277288](https://leetcode.com/problems/sliding-window-maximum/submissions/2024277288/)

### [42. Trapping Rain Water](https://leetcode.com/problems/trapping-rain-water/)

Two-pointer boundary maxima accumulate water at lower endpoint; alternate decreasing stack pops basin bottom and computes bounded layer.

Accepted source: [2147811654](https://leetcode.com/problems/trapping-rain-water/submissions/2147811654/) · [2143469631](https://leetcode.com/problems/trapping-rain-water/submissions/2143469631/) · [2142850361](https://leetcode.com/problems/trapping-rain-water/submissions/2142850361/) · [2131909942](https://leetcode.com/problems/trapping-rain-water/submissions/2131909942/) · [2131872743](https://leetcode.com/problems/trapping-rain-water/submissions/2131872743/) · [2131851296](https://leetcode.com/problems/trapping-rain-water/submissions/2131851296/)

### [1046. Last Stone Weight](https://leetcode.com/problems/last-stone-weight/)

Repeatedly remove two largest weights and reinsert positive difference.

Accepted source: [2144668025](https://leetcode.com/problems/last-stone-weight/submissions/2144668025/)

### [703. Kth Largest Element in a Stream](https://leetcode.com/problems/kth-largest-element-in-a-stream/)

Maintain size-k min heap so root is kth largest seen.

Accepted source: [2144654284](https://leetcode.com/problems/kth-largest-element-in-a-stream/submissions/2144654284/)

### [378. Kth Smallest Element in a Sorted Matrix](https://leetcode.com/problems/kth-smallest-element-in-a-sorted-matrix/)

Scan every matrix value maintaining k smallest in max heap.

Accepted source: [2126186308](https://leetcode.com/problems/kth-smallest-element-in-a-sorted-matrix/submissions/2126186308/)

## [windows-and-prefixes](topics/windows-and-prefixes/README.md)

### [2444. Count Subarrays With Fixed Bounds](https://leetcode.com/problems/count-subarrays-with-fixed-bounds/)

For each right endpoint, count starts after last invalid value and no later than both latest min/max occurrences.

Accepted source: [2153831199](https://leetcode.com/problems/count-subarrays-with-fixed-bounds/submissions/2153831199/)

### [30. Substring with Concatenation of All Words](https://leetcode.com/problems/substring-with-concatenation-of-all-words/)

For every word-length offset, slide in word-sized steps and shrink only when current word count exceeds required count.

Accepted source: [2153818347](https://leetcode.com/problems/substring-with-concatenation-of-all-words/submissions/2153818347/)

### [567. Permutation in String](https://leetcode.com/problems/permutation-in-string/)

Maintain fixed-length window, decrement requirement deficits on entering, increment on leaving; count distinct requirements that have become satisfied.

Accepted source: [2131779135](https://leetcode.com/problems/permutation-in-string/submissions/2131779135/)

### [424. Longest Repeating Character Replacement](https://leetcode.com/problems/longest-repeating-character-replacement/)

Maintain maximum character count seen while expanding; shift left once when window-maxCount>k, retain maximal feasible length.

Accepted source: [2131743704](https://leetcode.com/problems/longest-repeating-character-replacement/submissions/2131743704/) · [2131736709](https://leetcode.com/problems/longest-repeating-character-replacement/submissions/2131736709/) · [2027329669](https://leetcode.com/problems/longest-repeating-character-replacement/submissions/2027329669/)

### [3904. Smallest Stable Index II](https://leetcode.com/problems/smallest-stable-index-ii/)

Precompute suffix minima, scan prefix maximum, return first boundary where their gap<=k.

Accepted source: [2131704501](https://leetcode.com/problems/smallest-stable-index-ii/submissions/2131704501/)

### [560. Subarray Sum Equals K](https://leetcode.com/problems/subarray-sum-equals-k/)

Count prior prefixes equal current-k before adding current; zero prefix seeded once.

Accepted source: [2130713437](https://leetcode.com/problems/subarray-sum-equals-k/submissions/2130713437/) · [2025473825](https://leetcode.com/problems/subarray-sum-equals-k/submissions/2025473825/)

### [238. Product of Array Except Self](https://leetcode.com/problems/product-of-array-except-self/)

Build explicit left and right product arrays with identity 1, multiply exclusive prefixes/suffixes.

Accepted source: [2130701387](https://leetcode.com/problems/product-of-array-except-self/submissions/2130701387/)

### [209. Minimum Size Subarray Sum](https://leetcode.com/problems/minimum-size-subarray-sum/)

Expand positive-number sum, shrink while reaching target, record shortest.

Accepted source: [2130694109](https://leetcode.com/problems/minimum-size-subarray-sum/submissions/2130694109/)

### [3903. Smallest Stable Index I](https://leetcode.com/problems/smallest-stable-index-i/)

Suffix-minimum array plus running prefix maximum tests first stable boundary.

Accepted source: [2130500850](https://leetcode.com/problems/smallest-stable-index-i/submissions/2130500850/)

### [1658. Minimum Operations to Reduce X to Zero](https://leetcode.com/problems/minimum-operations-to-reduce-x-to-zero/)

Removing prefix and suffix becomes keeping longest middle subarray of sum total-x; positive-value sliding window finds it.

Accepted source: [2150943873](https://leetcode.com/problems/minimum-operations-to-reduce-x-to-zero/submissions/2150943873/)

### [1477. Find Two Non-overlapping Sub-arrays Each With Target Sum](https://leetcode.com/problems/find-two-non-overlapping-sub-arrays-each-with-target-sum/)

Find target-sum positive windows; dp[prefix] stores shortest prior target window, combine current with dp[left] for nonoverlap.

Accepted source: [2145013796](https://leetcode.com/problems/find-two-non-overlapping-sub-arrays-each-with-target-sum/submissions/2145013796/)

### [1493. Longest Subarray of 1's After Deleting One Element](https://leetcode.com/problems/longest-subarray-of-1s-after-deleting-one-element/)

Track at most one zero, shift left once when invalid, record window length minus required deletion.

Accepted source: [2127345655](https://leetcode.com/problems/longest-subarray-of-1s-after-deleting-one-element/submissions/2127345655/)

### [1004. Max Consecutive Ones III](https://leetcode.com/problems/max-consecutive-ones-iii/)

Track zero budget and maintain longest window; explicit shrink variant and single-step lazy-shrink variant.

Accepted source: [2127149237](https://leetcode.com/problems/max-consecutive-ones-iii/submissions/2127149237/) · [2027338195](https://leetcode.com/problems/max-consecutive-ones-iii/submissions/2027338195/)

## [strings-and-tries](topics/strings-and-tries/README.md)

### [208. Implement Trie (Prefix Tree)](https://leetcode.com/problems/implement-trie-prefix-tree/)

Walk value-owned hash-map children, set terminal flag only after full insertion.

Accepted source: [2167350538](https://leetcode.com/problems/implement-trie-prefix-tree/submissions/2167350538/)

### [745. Prefix and Suffix Search](https://leetcode.com/problems/prefix-and-suffix-search/)

Insert every suffix+separator+word; query suffix+separator+prefix, storing latest index on each visited node.

Accepted source: [2164622907](https://leetcode.com/problems/prefix-and-suffix-search/submissions/2164622907/)

### [214. Shortest Palindrome](https://leetcode.com/problems/shortest-palindrome/)

KMP prefix-function on s+separator+reverse(s) gives longest palindromic prefix; prepend reversed leftover suffix.

Accepted source: [2163593115](https://leetcode.com/problems/shortest-palindrome/submissions/2163593115/)

### [459. Repeated Substring Pattern](https://leetcode.com/problems/repeated-substring-pattern/)

A nonzero final border length and divisibility by n-border detect repeating period.

Accepted source: [2163579090](https://leetcode.com/problems/repeated-substring-pattern/submissions/2163579090/)

### [686. Repeated String Match](https://leetcode.com/problems/repeated-string-match/)

Run KMP against virtual repetitions via a[i%n], stopping after finite bound; convert matched end index to repeat count.

Accepted source: [2163561881](https://leetcode.com/problems/repeated-string-match/submissions/2163561881/)

### [28. Find the Index of the First Occurrence in a String](https://leetcode.com/problems/find-the-index-of-the-first-occurrence-in-a-string/)

Inline prefix-function build then fallback-driven linear first-match scan.

Accepted source: [2163524870](https://leetcode.com/problems/find-the-index-of-the-first-occurrence-in-a-string/submissions/2163524870/)

### [125. Valid Palindrome](https://leetcode.com/problems/valid-palindrome/)

Skip nonalphanumeric symbols at both ends and compare normalized characters.

Accepted source: [2147738982](https://leetcode.com/problems/valid-palindrome/submissions/2147738982/)

### [1541. Minimum Insertions to Balance a Parentheses String](https://leetcode.com/problems/minimum-insertions-to-balance-a-parentheses-string/)

Consume close parentheses in pairs; insert missing close or matching opening; account for remaining opens.

Accepted source: [2167345569](https://leetcode.com/problems/minimum-insertions-to-balance-a-parentheses-string/submissions/2167345569/)

### [1021. Remove Outermost Parentheses](https://leetcode.com/problems/remove-outermost-parentheses/)

Adjust depth before a close and after an open so only inner symbols are emitted.

Accepted source: [2166675238](https://leetcode.com/problems/remove-outermost-parentheses/submissions/2166675238/)

### [921. Minimum Add to Make Parentheses Valid](https://leetcode.com/problems/minimum-add-to-make-parentheses-valid/)

Track unmatched opens and missing openings, then sum them.

Accepted source: [2164607113](https://leetcode.com/problems/minimum-add-to-make-parentheses-valid/submissions/2164607113/)

### [1614. Maximum Nesting Depth of the Parentheses](https://leetcode.com/problems/maximum-nesting-depth-of-the-parentheses/)

Single depth counter and running maximum; stack contents are unnecessary.

Accepted source: [2155954786](https://leetcode.com/problems/maximum-nesting-depth-of-the-parentheses/submissions/2155954786/)

### [856. Score of Parentheses](https://leetcode.com/problems/score-of-parentheses/)

Stack of partial frame scores; closing frame contributes max(1,2*inside) to parent.

Accepted source: [2162881009](https://leetcode.com/problems/score-of-parentheses/submissions/2162881009/)

### [1807. Evaluate the Bracket Pairs of a String](https://leetcode.com/problems/evaluate-the-bracket-pairs-of-a-string/)

Map knowledge to nonowning string_views; scan bracket key spans and substitute value or ?.

Accepted source: [2154370092](https://leetcode.com/problems/evaluate-the-bracket-pairs-of-a-string/submissions/2154370092/)

### [953. Verifying an Alien Dictionary](https://leetcode.com/problems/verifying-an-alien-dictionary/)

Build character rank and compare adjacent words at first difference, rejecting a longer word preceding its prefix.

Accepted source: [2155353571](https://leetcode.com/problems/verifying-an-alien-dictionary/submissions/2155353571/)

### [1096. Brace Expansion II](https://leetcode.com/problems/brace-expansion-ii/)

Grammar item handles letter or brace group, term concatenates Cartesian products, eval unions comma-separated terms.

Accepted source: [2153362638](https://leetcode.com/problems/brace-expansion-ii/submissions/2153362638/)

### [394. Decode String](https://leetcode.com/problems/decode-string/)

Save outer partial string and multiplier at [, expand current substring at ].

Accepted source: [2146593107](https://leetcode.com/problems/decode-string/submissions/2146593107/)

### [71. Simplify Path](https://leetcode.com/problems/simplify-path/)

Split path on /, ignore empty/dot, pop for dotdot, join surviving components.

Accepted source: [2146563687](https://leetcode.com/problems/simplify-path/submissions/2146563687/)

### [242. Valid Anagram](https://leetcode.com/problems/valid-anagram/)

Count both strings and compare every key/count in both directions.

Accepted source: [2130658997](https://leetcode.com/problems/valid-anagram/submissions/2130658997/)

### [49. Group Anagrams](https://leetcode.com/problems/group-anagrams/)

Sort each string as canonical anagram key and group original strings.

Accepted source: [2127402160](https://leetcode.com/problems/group-anagrams/submissions/2127402160/)

### [76. Minimum Window Substring](https://leetcode.com/problems/minimum-window-substring/)

Track distinct unsatisfied/satisfied requirements; shrink while all covered and save minimum boundaries.

Accepted source: [2149102883](https://leetcode.com/problems/minimum-window-substring/submissions/2149102883/) · [2131820578](https://leetcode.com/problems/minimum-window-substring/submissions/2131820578/)

### [8. String to Integer (atoi)](https://leetcode.com/problems/string-to-integer-atoi/)

Skip spaces, parse optional sign, accumulate digits while checking against sign-specific integer limit.

Accepted source: [2126227733](https://leetcode.com/problems/string-to-integer-atoi/submissions/2126227733/)

### [1190. Reverse Substrings Between Each Pair of Parentheses](https://leetcode.com/problems/reverse-substrings-between-each-pair-of-parentheses/)

Keep output positions of opening parentheses; reverse output suffix at each close.

Accepted source: [2154897406](https://leetcode.com/problems/reverse-substrings-between-each-pair-of-parentheses/submissions/2154897406/)

## [dp-and-backtracking](topics/dp-and-backtracking/README.md)

### [132. Palindrome Partitioning II](https://leetcode.com/problems/palindrome-partitioning-ii/)

Build palindrome table, then memoize minimum cuts from each suffix with terminal -1 to cancel last separator.

Accepted source: [2165701086](https://leetcode.com/problems/palindrome-partitioning-ii/submissions/2165701086/)

### [301. Remove Invalid Parentheses](https://leetcode.com/problems/remove-invalid-parentheses/)

Memoized (index,open balance) generates unique valid suffixes; longest remaining strings minimize removals.

Accepted source: [2165615628](https://leetcode.com/problems/remove-invalid-parentheses/submissions/2165615628/)

### [37. Sudoku Solver](https://leetcode.com/problems/sudoku-solver/)

Track used digits per row/column/box; place, recurse, erase on failure.

Accepted source: [2164710608](https://leetcode.com/problems/sudoku-solver/submissions/2164710608/)

### [51. N-Queens](https://leetcode.com/problems/n-queens/)

Place one queen per row; scan three upward attack directions; undo after recursive visit.

Accepted source: [2164697200](https://leetcode.com/problems/n-queens/submissions/2164697200/)

### [940. Distinct Subsequences II](https://leetcode.com/problems/distinct-subsequences-ii/)

Count subsequences including empty by doubling previous count, subtracting count before previous occurrence; subtract empty at end.

Accepted source: [2133936040](https://leetcode.com/problems/distinct-subsequences-ii/submissions/2133936040/)

### [115. Distinct Subsequences](https://leetcode.com/problems/distinct-subsequences/)

Memoize matching target prefix inside source prefix; choose skip or consume matching character.

Accepted source: [2133267031](https://leetcode.com/problems/distinct-subsequences/submissions/2133267031/)

### [329. Longest Increasing Path in a Matrix](https://leetcode.com/problems/longest-increasing-path-in-a-matrix/)

Memoize longest increasing path from each cell; strictly increasing values provide acyclic dependency.

Accepted source: [2139455187](https://leetcode.com/problems/longest-increasing-path-in-a-matrix/submissions/2139455187/)

### [3524. Find X Value of Array I](https://leetcode.com/problems/find-x-value-of-array-i/)

Rolling remainder counts for all subarrays ending at current position; add singleton then extend prior endings and accumulate totals.

Accepted source: [2148463117](https://leetcode.com/problems/find-x-value-of-array-i/submissions/2148463117/)

### [64. Minimum Path Sum](https://leetcode.com/problems/minimum-path-sum/)

Initialize first row/column; each cell cost plus min(top,left).

Accepted source: [2126173167](https://leetcode.com/problems/minimum-path-sum/submissions/2126173167/) · [2126172428](https://leetcode.com/problems/minimum-path-sum/submissions/2126172428)

### [1621. Number of Sets of K Non-Overlapping Line Segments](https://leetcode.com/problems/number-of-sets-of-k-non-overlapping-line-segments/)

Memoize point index, remaining segment count, and whether a segment is open; close at same point to permit shared endpoints.

Accepted source: [2144058402](https://leetcode.com/problems/number-of-sets-of-k-non-overlapping-line-segments/submissions/2144058402/)

### [4058. Maximum Pulse Value After One Subarray Rotation](https://leetcode.com/problems/maximum-pulse-value-after-one-subarray-rotation/)

Alternating base sum plus best nonnegative segment gain over each adjacent-pair parity.

Accepted source: [2147436566](https://leetcode.com/problems/maximum-pulse-value-after-one-subarray-rotation/submissions/2147436566/)

## [greedy-and-intervals](topics/greedy-and-intervals/README.md)

### [2333. Minimum Sum of Squared Difference](https://leetcode.com/problems/minimum-sum-of-squared-difference/)

Frequency buckets lowered from largest difference to zero; batches identical greedy moves.

Accepted source: [2168486798](https://leetcode.com/problems/minimum-sum-of-squared-difference/submissions/2168486798/)

### [435. Non-overlapping Intervals](https://leetcode.com/problems/non-overlapping-intervals/)

Sort by end, retain earliest finishing compatible interval and count removals.

Accepted source: [2167400289](https://leetcode.com/problems/non-overlapping-intervals/submissions/2167400289/) · [2139752268](https://leetcode.com/problems/non-overlapping-intervals/submissions/2139752268/)

### [56. Merge Intervals](https://leetcode.com/problems/merge-intervals/)

Sort then fold into result.back(), extending overlapping intervals.

Accepted source: [2167385466](https://leetcode.com/problems/merge-intervals/submissions/2167385466/) · [2126107082](https://leetcode.com/problems/merge-intervals/submissions/2126107082/)

### [57. Insert Interval](https://leetcode.com/problems/insert-interval/)

Find overlapping block with lower_bound on interval ends and upper_bound on interval starts; erase and insert merged interval.

Accepted source: [2167382205](https://leetcode.com/problems/insert-interval/submissions/2167382205/) · [2167379680](https://leetcode.com/problems/insert-interval/submissions/2167379680/)

### [135. Candy](https://leetcode.com/problems/candy/)

Initialize all ones, enforce increasing-neighbor constraints left-to-right and right-to-left with max.

Accepted source: [2163599188](https://leetcode.com/problems/candy/submissions/2163599188/)

### [4059. Lexicographically Largest Power Array](https://leetcode.com/problems/lexicographically-largest-power-array/)

Process bits from high to low; refine active prefix groups into ones then zeros, freezing groups after first zero block.

Accepted source: [2147456833](https://leetcode.com/problems/lexicographically-largest-power-array/submissions/2147456833/) · [2147456124](https://leetcode.com/problems/lexicographically-largest-power-array/submissions/2147456124/)

### [2472. Maximum Number of Non-overlapping Palindrome Substrings](https://leetcode.com/problems/maximum-number-of-non-overlapping-palindrome-substrings/)

Scan left-to-right checking only length k and k+1 palindromes, take first qualifying block, jump past it.

Accepted source: [2143088360](https://leetcode.com/problems/maximum-number-of-non-overlapping-palindrome-substrings/submissions/2143088360/)

### [3414. Maximum Score of Non-overlapping Intervals](https://leetcode.com/problems/maximum-score-of-non-overlapping-intervals/)

Sort intervals by end; precompute last strictly compatible predecessor; DP over allowed count<=4 and prefix, preserving score and lexicographically smallest original-index path.

Accepted source: [2139370298](https://leetcode.com/problems/maximum-score-of-non-overlapping-intervals/submissions/2139370298/)

### [1520. Maximum Number of Non-Overlapping Substrings](https://leetcode.com/problems/maximum-number-of-non-overlapping-substrings/)

Collect each character first/last/count in first-appearance order; deque suffix aggregation checks whether contained character counts exactly fill its bounding interval, emits then clears.

Accepted source: [2146064854](https://leetcode.com/problems/maximum-number-of-non-overlapping-substrings/submissions/2146064854/)

### [729. My Calendar I](https://leetcode.com/problems/my-calendar-i/)

Disjoint interval map by start; lower_bound identifies successor, predecessor checks other possible conflict.

Accepted source: [2152937765](https://leetcode.com/problems/my-calendar-i/submissions/2152937765/)

### [218. The Skyline Problem](https://leetcode.com/problems/the-skyline-problem/)

Encode start positive and end negative, order same-x events descending signed height, maintain max active height, emit changes.

Accepted source: [2153355270](https://leetcode.com/problems/the-skyline-problem/submissions/2153355270/)

### [121. Best Time to Buy and Sell Stock](https://leetcode.com/problems/best-time-to-buy-and-sell-stock/)

Track lowest price so far and best sell-minus-minimum profit.

Accepted source: [2127314016](https://leetcode.com/problems/best-time-to-buy-and-sell-stock/submissions/2127314016/)

### [1877. Minimize Maximum Pair Sum in Array](https://leetcode.com/problems/minimize-maximum-pair-sum-in-array/)

Pair smallest with largest, maximizing pair sum over pairs.

Accepted source: [2140491975](https://leetcode.com/problems/minimize-maximum-pair-sum-in-array/submissions/2140491975/) · [2140491229](https://leetcode.com/problems/minimize-maximum-pair-sum-in-array/submissions/2140491229) · [2140485732](https://leetcode.com/problems/minimize-maximum-pair-sum-in-array/submissions/2140485732/)

## [design-structures](topics/design-structures/README.md)

### [981. Time Based Key-Value Store](https://leetcode.com/problems/time-based-key-value-store/)

Key maps to ordered timestamp/value map; upper_bound then predecessor finds most recent <=timestamp.

Accepted source: [2146746974](https://leetcode.com/problems/time-based-key-value-store/submissions/2146746974/) · [2024512612](https://leetcode.com/problems/time-based-key-value-store/submissions/2024512612/)

### [895. Maximum Frequency Stack](https://leetcode.com/problems/maximum-frequency-stack/)

Latest keeps stack per frequency and per-value frequency; pop last value at highest frequency. Older maintains ordered set by (-frequency,-latest_timestamp,value).

Accepted source: [2146639743](https://leetcode.com/problems/maximum-frequency-stack/submissions/2146639743/) · [2146625292](https://leetcode.com/problems/maximum-frequency-stack/submissions/2146625292/)

### [150. Evaluate Reverse Polish Notation](https://leetcode.com/problems/evaluate-reverse-polish-notation/)

Push operands, pop right then left for binary operator.

Accepted source: [2146465049](https://leetcode.com/problems/evaluate-reverse-polish-notation/submissions/2146465049/) · [2025562806](https://leetcode.com/problems/evaluate-reverse-polish-notation/submissions/2025562806/)

### [155. Min Stack](https://leetcode.com/problems/min-stack/)

Store minimum-so-far beside each value or in parallel stack.

Accepted source: [2146461553](https://leetcode.com/problems/min-stack/submissions/2146461553/) · [2025573166](https://leetcode.com/problems/min-stack/submissions/2025573166/)

### [225. Implement Stack using Queues](https://leetcode.com/problems/implement-stack-using-queues/)

Push into spare queue then move old queue behind it; swap so front is newest.

Accepted source: [2146459626](https://leetcode.com/problems/implement-stack-using-queues/submissions/2146459626/)

### [232. Implement Queue using Stacks](https://leetcode.com/problems/implement-queue-using-stacks/)

Input stack for push; transfer all to output stack only when output empty.

Accepted source: [2146457265](https://leetcode.com/problems/implement-queue-using-stacks/submissions/2146457265/)

### [682. Baseball Game](https://leetcode.com/problems/baseball-game/)

Maintain score history with cancel/double/sum-of-last-two commands.

Accepted source: [2145817863](https://leetcode.com/problems/baseball-game/submissions/2145817863/)

### [460. LFU Cache](https://leetcode.com/problems/lfu-cache/)

Latest frequency->list buckets and key->iterator map use MRU-front/LRU-back within a frequency, tracking minFreq. Older ordered set sorts (frequency,time,key,value).

Accepted source: [2144968388](https://leetcode.com/problems/lfu-cache/submissions/2144968388/) · [2144919830](https://leetcode.com/problems/lfu-cache/submissions/2144919830/)

### [355. Design Twitter](https://leetcode.com/problems/design-twitter/)

Store append-only posts by user; scan followed and own posts into size-10 min heap, reverse output.

Accepted source: [2144760383](https://leetcode.com/problems/design-twitter/submissions/2144760383/)

### [706. Design HashMap](https://leetcode.com/problems/design-hashmap/)

Fixed 32 buckets, each list of key/value pairs; scan chain for upsert/get/remove.

Accepted source: [2144621524](https://leetcode.com/problems/design-hashmap/submissions/2144621524/)

### [146. LRU Cache](https://leetcode.com/problems/lru-cache/)

List MRU-front/LRU-back with key->iterator map; splice hit to front, evict back when full.

Accepted source: [2143986850](https://leetcode.com/problems/lru-cache/submissions/2143986850/)

## [math-and-bits](topics/math-and-bits/README.md)

### [810. Chalkboard XOR Game](https://leetcode.com/problems/chalkboard-xor-game/)

XOR all values and return zero-XOR or even parity.

Accepted source: [2166697803](https://leetcode.com/problems/chalkboard-xor-game/submissions/2166697803/)

### [3498. Reverse Degree of a String](https://leetcode.com/problems/reverse-degree-of-a-string/)

Map lowercase character to reverse alphabet weight and multiply by one-based index.

Accepted source: [2147499756](https://leetcode.com/problems/reverse-degree-of-a-string/submissions/2147499756/) · [2147499695](https://leetcode.com/problems/reverse-degree-of-a-string/submissions/2147499695/)

### [836. Rectangle Overlap](https://leetcode.com/problems/rectangle-overlap/)

Positive-area rectangle intersection equals strict overlap on both axes.

Accepted source: [2141366410](https://leetcode.com/problems/rectangle-overlap/submissions/2141366410/)

### [1401. Circle and Rectangle Overlapping](https://leetcode.com/problems/circle-and-rectangle-overlapping/)

Closest rectangle point to circle center obtained by clamping both coordinates; compare squared distance.

Accepted source: [2146448826](https://leetcode.com/problems/circle-and-rectangle-overlapping/submissions/2146448826/) · [2146448651](https://leetcode.com/problems/circle-and-rectangle-overlapping/submissions/2146448651/)

### [835. Image Overlap](https://leetcode.com/problems/image-overlap/)

For every pair of nonzero pixel coordinates, count translation vector; maximum frequency is best overlap.

Accepted source: [2140447101](https://leetcode.com/problems/image-overlap/submissions/2140447101/) · [2140436041](https://leetcode.com/problems/image-overlap/submissions/2140436041)

### [923. 3Sum With Multiplicity](https://leetcode.com/problems/3sum-with-multiplicity/)

Sort, walk distinct value triples using frequencies, add product/choose2/choose3 multiplicities.

Accepted source: [2140530076](https://leetcode.com/problems/3sum-with-multiplicity/submissions/2140530076/)

### [1498. Number of Subsequences That Satisfy the Given Sum Condition](https://leetcode.com/problems/number-of-subsequences-that-satisfy-the-given-sum-condition/)

Sort; when minimum+maximum fits, all subsets of interior elements yield 2^(right-left) valid subsequences with fixed minimum.

Accepted source: [2140461426](https://leetcode.com/problems/number-of-subsequences-that-satisfy-the-given-sum-condition/submissions/2140461426/)

### [3483. Unique 3-Digit Even Numbers](https://leetcode.com/problems/unique-3-digit-even-numbers/)

Enumerate hundreds,tens,even units using decrement/restore counts, avoiding leading zero and duplicate values.

Accepted source: [2138479064](https://leetcode.com/problems/unique-3-digit-even-numbers/submissions/2138479064/)

### [3871. Count Commas in Range II](https://leetcode.com/problems/count-commas-in-range-ii/)

Each decimal comma threshold contributes max(0,n-threshold+1); five hardcoded powers of 1000.

Accepted source: [2136687887](https://leetcode.com/problems/count-commas-in-range-ii/submissions/2136687887/)

### [3870. Count Commas in Range](https://leetcode.com/problems/count-commas-in-range/)

Counts numbers at first comma threshold under original small range.

Accepted source: [2134960323](https://leetcode.com/problems/count-commas-in-range/submissions/2134960323/)

### [3876. Construct Uniform Parity Array II](https://leetcode.com/problems/construct-uniform-parity-array-ii/)

Scan minimum odd and even; return all-even or minimum odd below minimum even.

Accepted source: [2131978781](https://leetcode.com/problems/construct-uniform-parity-array-ii/submissions/2131978781/) · [2131975505](https://leetcode.com/problems/construct-uniform-parity-array-ii/submissions/2131975505/)

### [3875. Construct Uniform Parity Array I](https://leetcode.com/problems/construct-uniform-parity-array-i/)

Actual implementation returns true for every input.

Accepted source: [2128397234](https://leetcode.com/problems/construct-uniform-parity-array-i/submissions/2128397234/)

### [906. Super Palindromes](https://leetcode.com/problems/super-palindromes/)

Generate odd/even palindromic roots by mirroring half, square them, and test numeric palindrome in target range.

Accepted source: [2163458920](https://leetcode.com/problems/super-palindromes/submissions/2163458920/)

