# Trees and lists

[All topics](../../README.md) · [Source index](../../SOURCES.md) · [Coverage](../../COVERAGE.md)

## Main algorithms and structures

Choose what crosses an edge: a pointer, an ancestor constraint, or a completed subtree summary. The complete catalog of **28 problems / 36 submissions** is last; every implementation link opens unchanged captured code.

Here `n,m` are node counts, `h` tree height, `w` maximum width, `N` total nodes across `k` lists, and `B` serialized bytes. Hash operations are expected constant-time. Space includes recursion and temporary containers; newly allocated output is stated separately. A skewed tree can have `h=n`.

| Algorithm / data structure | Recognition trigger | Time in these sources | Space in these sources | Direct implementations |
|---|---|---|---|---|
| Iterative link reversal | Reverse a chain while preserving node identity | O(n) | O(1) | [In-place reversal](originals/206__2143560010.cpp) |
| Allocation-based reverse construction | Build a reversed value sequence | O(n) | O(n) newly allocated nodes; original head is reused | [Allocation variant](originals/206__2126014226.cpp) |
| Block verification + reversal + recursive suffix | Reverse only complete k-node groups | O(n) | O(ceil(n/k)) call frames, not O(1) | [k-group reversal](originals/25__2144552684.cpp) |
| Midpoint + reverse + weave/compare | Pair the start with the end without indexing | O(n) | O(1); input links are modified | [Reorder](originals/143__2143673583.cpp), [palindrome](originals/234__2126051007.cpp) |
| Pointer container + visited set/map | Retrieve nodes from the far end and avoid reuse | Expected O(n) | O(n) pointers and visited state | [Deque + set](originals/143__2143663379.cpp), [stack + map](originals/143__1211639660.cpp) |
| Floyd fast/slow pointers | Detect a cycle without storing visited nodes | O(n) until null or meeting | O(1) | [Cycle detection](originals/141__2143629142.cpp) |
| Length pass + positional pass | Select a node by index from an end or middle | O(n) | O(1); middle source writes a fixed 100-int array | [Remove nth from end](originals/19__2143696811.cpp), [middle by length](originals/876__765344670.cpp) |
| Dummy head + ordered splicing | Merge two sorted chains, reusing nodes | O(n+m) | O(1) temporary node/pointers | [Two-list merge](originals/21__2143594529.cpp) |
| All-nodes min-heap | Order every node from multiple lists | O(k + N log(N+1)) | O(N) heap | [Heap of every node](originals/23__2144522916.cpp) |
| FIFO pairwise merge schedule | Compose a two-list merge over many inputs | O(k + N log(k+1)) | O(k) head queue; O(1) per merge | [Pairwise merge queue](originals/23__2144097838.cpp) |
| Pointer-to-clone map | Copy identity-dependent next/random edges | Expected O(n) | O(n) map + O(n) output nodes | [Two-pass deep copy](originals/138__2143802245.cpp) |
| Carry state + appended output list | Add digit streams without integer conversion | O(max(n,m)) | O(1) working state + O(max(n,m)) output nodes | [Digit addition](originals/2__2143813487.cpp) |
| Structural DFS | Compare, invert, or measure a tree | O(n) for one tree; O(n+m) equality upper bound | O(h) frames; equality O(h₁+h₂) upper bound | [Equality](originals/100__2140598575.cpp), [invert](originals/226__2140574036.cpp), [height](originals/104__2140575615.cpp) |
| Ancestor bounds / path aggregate | Validity depends on all ancestors | O(n) | O(h) frames | [Exclusive BST bounds](originals/98__2140737519.cpp), [ancestor maximum](originals/1448__2140724204.cpp) |
| Postorder numerical summaries | Parent needs child height, gain, or sum/count | O(n) | O(h) frames | [Balance](originals/110__2140593789.cpp), [diameter](originals/543__2140582704.cpp), [path gain](originals/124__2153370936.cpp), [sum/count](originals/2265__2137363284.cpp) |
| Queue with frozen level length | Output belongs to a whole depth layer | O(n) | O(w) queue/level buffer; output O(n) levels or O(h) view | [Level order](originals/102__2140704978.cpp), [right view](originals/199__2140707899.cpp) |
| Inorder counting / BST-directed descent | Rank by sorted traversal or find target split | Kth source O(n); LCA O(h) | O(h) recursive frames in both | [Full inorder kth](originals/230__2140766874.cpp), [recursive LCA](originals/235__2140699724.cpp) |
| Preorder cursor + inorder index map | Reconstruct distinct-valued tree from traversals | Expected O(n) | O(n) map + O(h) frames + O(n) output; one extra unused node allocated | [Traversal reconstruction](originals/105__2141508524.cpp) |
| Null-marked preorder codec | Serialize shape and values unambiguously | O(B+n) encode/decode | O(B+h) streams/string copies + O(n) decoded nodes | [Preorder codec](originals/297__2153777400.cpp), [equivalent codec](originals/297__2141912475.cpp) |
| Unique IDs + paired traversal codec | Traversal reconstruction must allow duplicate values | Expected O(B+n) encode/decode | O(B+n+h) buffers/maps/frames + O(n) decoded nodes | [Indexed inorder/preorder codec](originals/297__2141671426.cpp) |
| Candidate DFS + structural equality | Find an exact subtree without preprocessing | O(nm) worst case | O(h₁+h₂) frames upper bound | [Repeated matching](originals/572__2140623050.cpp) |
| Postorder greedy coverage + pointer set | A local placement covers parent/self/children | Expected O(n) | O(n) covered set + O(h) frames | [Camera placement](originals/968__2155106387.cpp) |

## Combinations and tricks

### Save the suffix before changing the link

- **Recognize:** A mutation changes the very edge needed to reach unprocessed nodes.
- **Compose:** Save `current->next`, point `current->next` at the reversed prefix, then advance both frontiers. For k-groups, first prove that k nodes exist; reverse exactly that block, then attach its old head to the recursively processed suffix.
- **Invariant:** `prev` owns the completed reversed prefix and `current` still reaches every unprocessed node. After a block reversal, its old head is the tail and therefore the correct reconnection point.
- **Tradeoff / trap:** Block preflight prevents partially reversing a short final group. Recursing once per group adds O(n/k) stack. The older “reverse” source allocates new nodes except for the original head, so it does not preserve every node's identity or provide O(1) additional storage.
- **Originals:** [Iterative reversal](originals/206__2143560010.cpp), [verified blocks](originals/25__2144552684.cpp), [allocation-based variant](originals/206__2126014226.cpp).

### Midpoint + reversed suffix turns end-to-end pairing into a forward scan

- **Recognize:** Desired comparisons or output alternate between the first and last remaining node.
- **Compose:** Find the midpoint with two speeds, reverse the second half, then weave the two chains or compare them in lockstep. The reorder source explicitly cuts at `slow->next` before reversing.
- **Invariant:** The two reorder chains are disjoint; save both next pointers before weaving so neither suffix is lost. Comparing a reversed half pairs symmetric original positions.
- **Tradeoff / trap:** The palindrome source never restores the list, even on early failure. The container-based reorder variants spend O(n) extra space and rely on visited checks plus a final null link to prevent cycles. [Middle by length](originals/876__765344670.cpp) is a separate two-pass implementation, not a fast/slow example, and its unused fixed array relies on at most 100 nodes.
- **Originals:** [Split/reverse/weave](originals/143__2143673583.cpp), [palindrome comparison](originals/234__2126051007.cpp), [deque + visited](originals/143__2143663379.cpp), [stack + visited](originals/143__1211639660.cpp).

### Separate identity creation from edge wiring

- **Recognize:** Values may repeat, while random/cross edges must target exactly the corresponding copied node.
- **Compose:** Allocate one clone per original pointer in a first pass. In a second pass, map each original `next` and `random` target to its clone. For ordinary output construction, a dummy head removes the empty-prefix special case.
- **Invariant:** Before assigning any copied edge, every non-null target already has an identity in the map. Null lookups default-insert a null mapping in this source. In digit addition, the appended prefix contains all completed low-order digits and the carry is the only unfinished arithmetic state.
- **Tradeoff / trap:** A map keyed by values would merge distinct nodes. Copying allocates output nodes; two-list merging instead splices original nodes. The digit-add and merge implementations delete their temporary dummy heads, but removing the nth node only unlinks it and does not delete it.
- **Originals:** [Random-pointer clone](originals/138__2143802245.cpp), [carry + append](originals/2__2143813487.cpp), [dummy-head merge](originals/21__2143594529.cpp), [two-pass unlink](originals/19__2143696811.cpp).

### The merge schedule determines the bound

- **Recognize:** A two-input operation is correct, but it must be applied across many lists.
- **Compose:** One source pushes **every node** into a heap and relinks popped nodes. The other queues nonempty heads, repeatedly merges the first two chains, and appends the result to the queue.
- **Invariant:** Each heap extraction is the next global value; each queued chain remains sorted. FIFO pairing forms a near-balanced merge tree by number of original lists, so a node participates in O(log k) merges.
- **Tradeoff / trap:** The actual heap has N entries, giving O(N log N) work and O(N) memory. Do not attribute the usual k-head heap's O(N log k) bound to it. Pairwise merging needs O(k) head storage and destroys the original link organization; both variants reuse nodes.
- **Originals:** [All-node heap](originals/23__2144522916.cpp), [FIFO merge composition](originals/23__2144097838.cpp), [two-list building block](originals/21__2143594529.cpp).

### Send ancestor constraints down; send subtree summaries up

- **Recognize:** A condition depends either on the root-to-node path or on all descendants, not just the immediate parent/children.
- **Compose:** BST validation narrows exclusive bounds at every edge; good-node counting carries the maximum ancestor value. Height and balance recurse into both children before combining their summaries.
- **Invariant:** Every node lies inside all inherited BST bounds. A returned height summarizes a fully processed subtree; a failed balance flag suppresses later traversal work. Bounds begin one unit beyond the signed-int range in `long long`, admitting `INT_MIN` and `INT_MAX` as valid values.
- **Tradeoff / trap:** Testing only parent-child order misses a descendant that violates an older ancestor. Tree recursion is O(h), not automatically O(log n). BST LCA uses order to descend one branch, but the kth-smallest source continues its entire inorder traversal after finding k.
- **Originals:** [Inherited bounds](originals/98__2140737519.cpp), [path maximum](originals/1448__2140724204.cpp), [balance summary](originals/110__2140593789.cpp), [LCA split](originals/235__2140699724.cpp), [full inorder count](originals/230__2140766874.cpp).

### Return an extendable answer; record a completed answer separately

- **Recognize:** A best path may join both children, but a path extended by the parent cannot branch twice.
- **Compose:** Diameter returns one height and records `left+right`. Maximum path sum clips negative child gains, records `left+value+right`, but returns only `value+max(left,right)`. Subtree averages return the sufficient pair `(sum,count)`.
- **Invariant:** The return value is legal to attach through the single parent edge. The shared answer considers completed candidates that may have both branches; `INT_MIN` initialization preserves all-negative path answers.
- **Tradeoff / trap:** Returning a two-branch path to the parent would create a fork rather than a simple path. Average calculation uses integer division under the source's nonnegative-value contract. Its `result` is a class member initialized once and **not reset** by `averageOfSubtree`, so reusing one object accumulates prior answers; the other linked summaries use per-call locals.
- **Originals:** [Diameter](originals/543__2140582704.cpp), [maximum path](originals/124__2153370936.cpp), [sum/count with retained member](originals/2265__2137363284.cpp).

### Freeze the frontier before processing a level

- **Recognize:** You need one vector or one representative per depth.
- **Compose:** Save the queue length before enqueuing any children, then pop exactly that many nodes. With left-before-right child insertion, `queue.back()` at the start is the current level's rightmost node.
- **Invariant:** At each outer-loop entry, the queue is exactly one complete level in left-to-right order. Newly enqueued nodes belong to the next level, even though they share the same queue during processing.
- **Tradeoff / trap:** Reading `back()` after adding children mixes levels. Queue memory is O(width), while recursion elsewhere follows O(height); wide and skewed trees stress different resources. Level-order output itself stores all n values.
- **Originals:** [Frozen-size BFS](originals/102__2140704978.cpp), [rightmost representative](originals/199__2140707899.cpp).

### Serialize enough structure to make decoding deterministic

- **Recognize:** Values alone do not identify tree shape, especially when duplicates are allowed.
- **Compose:** Null-marked preorder emits a value followed by left and right subtrees, with `#` for every null. The alternative assigns unique node IDs, serializes indexed inorder and preorder, then rebuilds using an ID-to-inorder-position map.
- **Invariant:** A preorder parser consumes exactly one subtree before returning; explicit nulls determine where a missing child ends. In paired-traversal reconstruction, the preorder cursor chooses the root and its inorder pivot separates left/right ranges.
- **Tradeoff / trap:** The simple reconstruction source assumes distinct **values**; the old codec uses **IDs** so equal values remain distinct. The formats are incompatible. Count actual serialized bytes B, stream/input-string copies, maps, and O(h) recursive frames. Both standalone reconstruction variants allocate an unused root before the recursive build and read `preorder[0]`, relying on nonempty input.
- **Originals:** [Null-marked codec](originals/297__2153777400.cpp), [indexed traversal codec](originals/297__2141671426.cpp), [distinct-value reconstruction](originals/105__2141508524.cpp), [equivalent reconstruction](originals/105__2141508275.cpp).

### Postorder makes a coverage decision only when its children are settled

- **Recognize:** Placing a resource at one node also covers its parent and direct children.
- **Compose:** Visit both children first. If either child is uncovered, place a camera at the current node and mark current/parent/children covered; also place one for an uncovered root. Seed the covered set with null.
- **Invariant:** After a subtree is processed, uncovered demand can remain only at its root. A camera at the parent of an uncovered child covers at least that child's demand and can also help the sibling/ancestor, which motivates the greedy choice.
- **Tradeoff / trap:** This captured implementation uses a pointer set of up to O(n) elements, not a constant-state three-value return. By contrast, [subtree matching](originals/572__2140623050.cpp) repeatedly recomputes structural equality at candidate roots, producing O(nm) worst-case work rather than one summarized postorder pass.
- **Originals:** [Coverage-set greedy](originals/968__2155106387.cpp), [structural equality](originals/100__2140598575.cpp), [candidate-root search](originals/572__2140623050.cpp).

## Problem and source appendix


All captured submissions are retained, including equivalent resubmissions and exact duplicates. Submission IDs distinguish files; they are not rankings of quality. The source itself is authoritative when a note is too brief.

### 2. Add Two Numbers

[Problem](https://leetcode.com/problems/add-two-numbers/) · Tags: Linked lists, Arithmetic

Dummy-head output list, add corresponding digits plus carry, process remainders, append final carry.

**Captured variants:** One observed approach.

- [Original 2143813487](originals/2__2143813487.cpp) · [LeetCode submission](https://leetcode.com/problems/add-two-numbers/submissions/2143813487/)

### 19. Remove Nth Node From End of List

[Problem](https://leetcode.com/problems/remove-nth-node-from-end-of-list/) · Tags: Linked lists

Count length then unlink node at length-n, with head special case.

**Captured variants:** One two-pass approach.

- [Original 2143696811](originals/19__2143696811.cpp) · [LeetCode submission](https://leetcode.com/problems/remove-nth-node-from-end-of-list/submissions/2143696811/)

### 21. Merge Two Sorted Lists

[Problem](https://leetcode.com/problems/merge-two-sorted-lists/) · Tags: Linked lists, Merge

Dummy-head merge links existing nodes then appends remainder.

**Captured variants:** One observed approach.

- [Original 2143594529](originals/21__2143594529.cpp) · [LeetCode submission](https://leetcode.com/problems/merge-two-sorted-lists/submissions/2143594529/)

### 23. Merge k Sorted Lists

[Problem](https://leetcode.com/problems/merge-k-sorted-lists/) · Tags: Linked lists, Heaps, Pairwise merge

Latest inserts every node into heap then relinks sorted nodes; older repeatedly dequeues two list heads and enqueues merged list.

**Captured variants:** [2144522916](originals/23__2144522916.cpp) all-nodes heap; [2144097838](originals/23__2144097838.cpp) pairwise merge queue.

- [Original 2144522916](originals/23__2144522916.cpp) · [LeetCode submission](https://leetcode.com/problems/merge-k-sorted-lists/submissions/2144522916/)
- [Original 2144097838](originals/23__2144097838.cpp) · [LeetCode submission](https://leetcode.com/problems/merge-k-sorted-lists/submissions/2144097838/)

### 25. Reverse Nodes in k-Group

[Problem](https://leetcode.com/problems/reverse-nodes-in-k-group/) · Tags: Linked lists, Reversal, Recursion

Verify complete k-node group, reverse exactly k links, recursively process suffix and attach via old head.

**Captured variants:** One observed approach.

- [Original 2144552684](originals/25__2144552684.cpp) · [LeetCode submission](https://leetcode.com/problems/reverse-nodes-in-k-group/submissions/2144552684/)

### 98. Validate Binary Search Tree

[Problem](https://leetcode.com/problems/validate-binary-search-tree/) · Tags: Trees, DFS, Bounds

Carry exclusive low/high bounds recursively to validate every descendant.

**Captured variants:** One observed approach.

- [Original 2140737519](originals/98__2140737519.cpp) · [LeetCode submission](https://leetcode.com/problems/validate-binary-search-tree/submissions/2140737519/)

### 100. Same Tree

[Problem](https://leetcode.com/problems/same-tree/) · Tags: Trees, DFS

Shared result flag checks null mismatch then value equality and both children.

**Captured variants:** One observed approach.

- [Original 2140598575](originals/100__2140598575.cpp) · [LeetCode submission](https://leetcode.com/problems/same-tree/submissions/2140598575/)

### 102. Binary Tree Level Order Traversal

[Problem](https://leetcode.com/problems/binary-tree-level-order-traversal/) · Tags: Trees, BFS

Freeze queue length, collect one vector per level, enqueue children.

**Captured variants:** One observed approach.

- [Original 2140704978](originals/102__2140704978.cpp) · [LeetCode submission](https://leetcode.com/problems/binary-tree-level-order-traversal/submissions/2140704978/)

### 104. Maximum Depth of Binary Tree

[Problem](https://leetcode.com/problems/maximum-depth-of-binary-tree/) · Tags: Trees, Recursion

Return 1+maximum child height, null=0.

**Captured variants:** One observed approach.

- [Original 2140575615](originals/104__2140575615.cpp) · [LeetCode submission](https://leetcode.com/problems/maximum-depth-of-binary-tree/submissions/2140575615/)

### 105. Construct Binary Tree from Preorder and Inorder Traversal

[Problem](https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/) · Tags: Trees, Recursion, Hash maps

Inorder value-to-index map plus advancing preorder cursor builds left/right subranges.

**Captured variants:** Two equivalent submissions differ only final range size source.

- [Original 2141508524](originals/105__2141508524.cpp) · [LeetCode submission](https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/submissions/2141508524/)
- [Original 2141508275](originals/105__2141508275.cpp) · [LeetCode submission](https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/submissions/2141508275/)

### 110. Balanced Binary Tree

[Problem](https://leetcode.com/problems/balanced-binary-tree/) · Tags: Trees, Postorder

Compute heights and shared balanced flag; skip later work once imbalance detected.

**Captured variants:** One observed approach.

- [Original 2140593789](originals/110__2140593789.cpp) · [LeetCode submission](https://leetcode.com/problems/balanced-binary-tree/submissions/2140593789/)

### 124. Binary Tree Maximum Path Sum

[Problem](https://leetcode.com/problems/binary-tree-maximum-path-sum/) · Tags: Trees, Postorder, Dynamic programming

Return best one-branch gain, update best full path through node using both nonnegative child gains.

**Captured variants:** Two equivalent implementations.

- [Original 2153370936](originals/124__2153370936.cpp) · [LeetCode submission](https://leetcode.com/problems/binary-tree-maximum-path-sum/submissions/2153370936/)
- [Original 2141514512](originals/124__2141514512.cpp) · [LeetCode submission](https://leetcode.com/problems/binary-tree-maximum-path-sum/submissions/2141514512/)

### 138. Copy List with Random Pointer

[Problem](https://leetcode.com/problems/copy-list-with-random-pointer/) · Tags: Linked lists, Hash maps, Graph copy

Two passes: allocate clone for every original pointer, then wire next/random through pointer mapping.

**Captured variants:** One observed approach.

- [Original 2143802245](originals/138__2143802245.cpp) · [LeetCode submission](https://leetcode.com/problems/copy-list-with-random-pointer/submissions/2143802245/)

### 141. Linked List Cycle

[Problem](https://leetcode.com/problems/linked-list-cycle/) · Tags: Linked lists, Fast slow pointers

Floyd cycle detection advances 1 and 2 until meet or null.

**Captured variants:** One observed approach.

- [Original 2143629142](originals/141__2143629142.cpp) · [LeetCode submission](https://leetcode.com/problems/linked-list-cycle/submissions/2143629142/)

### 143. Reorder List

[Problem](https://leetcode.com/problems/reorder-list/) · Tags: Linked lists, Fast slow pointers, Reversal

Latest source splits at midpoint, reverses second half, alternates merge; older sources materialize node pointers and track visited.

**Captured variants:** [2143673583](originals/143__2143673583.cpp) O(1) split/reverse/weave; [2143663379](originals/143__2143663379.cpp) deque+set; [1211639660](originals/143__1211639660.cpp) stack+map.

- [Original 2143673583](originals/143__2143673583.cpp) · [LeetCode submission](https://leetcode.com/problems/reorder-list/submissions/2143673583/)
- [Original 2143663379](originals/143__2143663379.cpp) · [LeetCode submission](https://leetcode.com/problems/reorder-list/submissions/2143663379/)
- [Original 1211639660](originals/143__1211639660.cpp) · [LeetCode submission](https://leetcode.com/problems/reorder-list/submissions/1211639660/)

### 199. Binary Tree Right Side View

[Problem](https://leetcode.com/problems/binary-tree-right-side-view/) · Tags: Trees, BFS

Queue complete levels left-to-right and take queue.back at level start for rightmost view.

**Captured variants:** One observed approach.

- [Original 2140707899](originals/199__2140707899.cpp) · [LeetCode submission](https://leetcode.com/problems/binary-tree-right-side-view/submissions/2140707899/)

### 206. Reverse Linked List

[Problem](https://leetcode.com/problems/reverse-linked-list/) · Tags: Linked lists, Reversal

Latest source reverses links with prev/current/tmp; older source creates reversed copies after reusing original head.

**Captured variants:** [2143560010](originals/206__2143560010.cpp) in-place; [2126014226](originals/206__2126014226.cpp) allocation-based, materially different.

- [Original 2143560010](originals/206__2143560010.cpp) · [LeetCode submission](https://leetcode.com/problems/reverse-linked-list/submissions/2143560010/)
- [Original 2126014226](originals/206__2126014226.cpp) · [LeetCode submission](https://leetcode.com/problems/reverse-linked-list/submissions/2126014226/)

### 226. Invert Binary Tree

[Problem](https://leetcode.com/problems/invert-binary-tree/) · Tags: Trees, Recursion

Swap child pointers then recurse into both.

**Captured variants:** One observed approach.

- [Original 2140574036](originals/226__2140574036.cpp) · [LeetCode submission](https://leetcode.com/problems/invert-binary-tree/submissions/2140574036/)

### 230. Kth Smallest Element in a BST

[Problem](https://leetcode.com/problems/kth-smallest-element-in-a-bst/) · Tags: Trees, DFS, Order statistics

Inorder traversal increments count and records kth visited value.

**Captured variants:** One observed approach.

- [Original 2140766874](originals/230__2140766874.cpp) · [LeetCode submission](https://leetcode.com/problems/kth-smallest-element-in-a-bst/submissions/2140766874/)

### 234. Palindrome Linked List

[Problem](https://leetcode.com/problems/palindrome-linked-list/) · Tags: Linked lists, Midpoint, Reversal

Slow/fast midpoint, reverse second half, compare opposing halves.

**Original-code context:** O(n), O(1); modifies list and never restores reversed links.

**Captured variants:** 1 accepted C++ submission captured; all original versions are retained.

- [Original 2126051007](originals/234__2126051007.cpp) · [LeetCode submission](https://leetcode.com/problems/palindrome-linked-list/submissions/2126051007/)

### 235. Lowest Common Ancestor of a Binary Search Tree

[Problem](https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-search-tree/) · Tags: Trees, BST, Search

Order target values; descend until current value lies between targets.

**Captured variants:** One observed approach.

- [Original 2140699724](originals/235__2140699724.cpp) · [LeetCode submission](https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-search-tree/submissions/2140699724/)

### 297. Serialize and Deserialize Binary Tree

[Problem](https://leetcode.com/problems/serialize-and-deserialize-binary-tree/) · Tags: Trees, Serialization, Parsing

Preorder tokens with explicit null markers reconstruct unique shape; older source encodes indexed inorder and preorder.

**Captured variants:** [2153777400](originals/297__2153777400.cpp) and [2141912475](originals/297__2141912475.cpp) same preorder # grammar; [2141671426](originals/297__2141671426.cpp) indexed inorder|preorder representation.

- [Original 2153777400](originals/297__2153777400.cpp) · [LeetCode submission](https://leetcode.com/problems/serialize-and-deserialize-binary-tree/submissions/2153777400/)
- [Original 2141912475](originals/297__2141912475.cpp) · [LeetCode submission](https://leetcode.com/problems/serialize-and-deserialize-binary-tree/submissions/2141912475/)
- [Original 2141671426](originals/297__2141671426.cpp) · [LeetCode submission](https://leetcode.com/problems/serialize-and-deserialize-binary-tree/submissions/2141671426/)

### 543. Diameter of Binary Tree

[Problem](https://leetcode.com/problems/diameter-of-binary-tree/) · Tags: Trees, Postorder, Dynamic programming

Return subtree height while updating best path through current node with left+right heights.

**Captured variants:** One observed approach.

- [Original 2140582704](originals/543__2140582704.cpp) · [LeetCode submission](https://leetcode.com/problems/diameter-of-binary-tree/submissions/2140582704/)

### 572. Subtree of Another Tree

[Problem](https://leetcode.com/problems/subtree-of-another-tree/) · Tags: Trees, DFS

At every root candidate, recursively test structural equality; recurse through host tree otherwise.

**Captured variants:** One observed approach.

- [Original 2140623050](originals/572__2140623050.cpp) · [LeetCode submission](https://leetcode.com/problems/subtree-of-another-tree/submissions/2140623050/)

### 876. Middle of the Linked List

[Problem](https://leetcode.com/problems/middle-of-the-linked-list/) · Tags: List length, Two passes

Traverses the list to get length, resets tmp=head, then advances length/2 nodes and returns tmp.

**Original-code context:** Actual original is not fast/slow pointers. It writes values into fixed int array[100] even though the values are never read; original constraints bound the list size. The source includes commented-out earlier length handling, preserved unchanged.

**Captured variants:** 1 accepted C++ submission retained; distinctions are described above.

- [Original 765344670](originals/876__765344670.cpp) · [LeetCode submission](https://leetcode.com/problems/middle-of-the-linked-list/submissions/765344670/)

### 968. Binary Tree Cameras

[Problem](https://leetcode.com/problems/binary-tree-cameras/) · Tags: Trees, Greedy, Postorder

Postorder cameras placed when child uncovered, or root itself uncovered; set tracks covered nodes, with null pre-covered.

**Captured variants:** One observed approach.

- [Original 2155106387](originals/968__2155106387.cpp) · [LeetCode submission](https://leetcode.com/problems/binary-tree-cameras/submissions/2155106387/)

### 1448. Count Good Nodes in Binary Tree

[Problem](https://leetcode.com/problems/count-good-nodes-in-binary-tree/) · Tags: Trees, DFS, Path aggregates

Carry maximum root-to-current value and count node if >= prior max.

**Captured variants:** One source; earlier capture blocked but now code is present.

- [Original 2140724204](originals/1448__2140724204.cpp) · [LeetCode submission](https://leetcode.com/problems/count-good-nodes-in-binary-tree/submissions/2140724204/)

### 2265. Count Nodes Equal to Average of Subtree

[Problem](https://leetcode.com/problems/count-nodes-equal-to-average-of-subtree/) · Tags: Trees, Postorder aggregates

Return pair (sum,count) for subtree and count matching integer average.

**Captured variants:** One observed approach.

- [Original 2137363284](originals/2265__2137363284.cpp) · [LeetCode submission](https://leetcode.com/problems/count-nodes-equal-to-average-of-subtree/submissions/2137363284/)
