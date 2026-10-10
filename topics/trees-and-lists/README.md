# Trees and lists

[All topics](../../README.md) · [Source index](../../SOURCES.md) · [Coverage](../../COVERAGE.md)

**28 captured problems · 36 accepted submission records.** Every linked implementation below is an unchanged captured source file. These notes describe the code; they do not replace it with a common API.

## Pattern reminders

### Rewire a list without losing the suffix

- **Cue:** Reverse or rearrange an existing chain of nodes.
- **Idea and invariant:** 206 saves the next pointer before reversing a link. The newer 143 finds the midpoint, reverses the second half, then alternates the two chains. 25 first verifies a complete k-node block and reconnects the reversed block to a recursively processed suffix.
- **Cost in these sources:** In-place 206 and the split/reverse 143: O(n) time and O(1) auxiliary state. 25: O(n) time and O(n/k) recursive frames. The other captured list variants have different allocation/container costs.
- **Read the originals:** [206. Reverse Linked List — 2143560010](originals/206__2143560010.cpp); [143. Reorder List — 2143673583](originals/143__2143673583.cpp); [25. Reverse Nodes in k-Group — 2144552684](originals/25__2144552684.cpp).

### Separate pointer identity from value

- **Cue:** Copies must preserve cross-links or merging must reuse existing nodes.
- **Idea and invariant:** 138 creates a clone for each original pointer before assigning next/random edges through the mapping. 21 uses a dummy head to splice the smaller current node. 23 has an all-nodes heap version and a pairwise merge-queue version, rather than only a heap of list heads.
- **Cost in these sources:** 138: expected O(n) time and O(n) mapping/output. 21: O(n+m) time and O(1) auxiliary nodes. The all-nodes heap in 23 takes O(N log N) time and O(N) heap storage. Pairwise queue merging takes O(N log k) time for N nodes in k lists.
- **Read the originals:** [138. Copy List with Random Pointer — 2143802245](originals/138__2143802245.cpp); [21. Merge Two Sorted Lists — 2143594529](originals/21__2143594529.cpp); [23. Merge k Sorted Lists — 2144522916](originals/23__2144522916.cpp).

### Freeze a level or carry an ancestor constraint

- **Cue:** The answer depends on a level boundary, an ancestor maximum, or the BST order.
- **Idea and invariant:** 102 and 199 freeze the queue length for each level. 98 passes exclusive low/high bounds to every descendant. 1448 passes the largest ancestor value. 235 descends until the two targets split across the current BST node.
- **Cost in these sources:** Full traversals take O(n) time, with O(width) BFS space or O(height) recursion. BST ancestor search takes O(height) time.
- **Read the originals:** [102. Binary Tree Level Order Traversal — 2140704978](originals/102__2140704978.cpp); [199. Binary Tree Right Side View — 2140707899](originals/199__2140707899.cpp); [98. Validate Binary Search Tree — 2140737519](originals/98__2140737519.cpp); [1448. Count Good Nodes in Binary Tree — 2140724204](originals/1448__2140724204.cpp); [235. Lowest Common Ancestor of a Binary Search Tree — 2140699724](originals/235__2140699724.cpp).

### Return a subtree summary and update a global answer

- **Cue:** A parent needs only a small summary, while the best answer may pass through a child or the current node.
- **Idea and invariant:** 543 returns height and updates diameter with both child heights. 124 returns the best one-branch gain and updates the best complete path using both nonnegative child gains. 2265 returns sum/count. 968 makes camera decisions after visiting children and tracks which nodes are covered.
- **Cost in these sources:** O(n) time and O(height) recursion for the numerical summaries. The camera source additionally stores up to O(n) covered pointers in a hash set.
- **Read the originals:** [543. Diameter of Binary Tree — 2140582704](originals/543__2140582704.cpp); [124. Binary Tree Maximum Path Sum — 2153370936](originals/124__2153370936.cpp); [2265. Count Nodes Equal to Average of Subtree — 2137363284](originals/2265__2137363284.cpp); [968. Binary Tree Cameras — 2155106387](originals/968__2155106387.cpp).

### A traversal must preserve enough shape information

- **Cue:** Rebuild a tree or serialize it so that null structure and boundaries remain unambiguous.
- **Idea and invariant:** 105 combines preorder order with an inorder value-to-index map, under distinct-value assumptions. The newer 297 writes preorder with explicit null markers; its older format records indexed inorder and preorder. Each format is interpreted by its matching deserializer.
- **Cost in these sources:** 105: expected O(n) time, O(n) map space, and O(height) recursion. The preorder codec visits O(n) tokens; string construction costs depend on its concatenations, and the serialized representation is O(n) tokens.
- **Read the originals:** [105. Construct Binary Tree from Preorder and Inorder Traversal — 2141508524](originals/105__2141508524.cpp); [297. Serialize and Deserialize Binary Tree — 2153777400](originals/297__2153777400.cpp).

## Complete problem and variant index

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
