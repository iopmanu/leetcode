# Trees and linked lists

A small set of pointer invariants explains most of these collected solutions:
keep the untouched suffix reachable, return one useful subtree summary, and keep
ownership separate from traversal links. The helpers in [templates.hpp](templates.hpp)
are adaptations of the accepted submissions listed below, not judge wrappers.

## Choose the pattern

| Need | Helper / invariant | Time | Extra space |
|---|---|---:|---:|
| Reverse a chain | `reverseList`: reversed prefix + untouched suffix | O(n) | O(1) |
| Alternate front/back nodes | `reorderList`: split, reverse, weave | O(n) | O(1) |
| Merge disjoint sorted chains | `mergeSortedLists`: dummy + output tail | O(n + m) | O(1) |
| Reverse complete blocks | `reverseKGroup`: probe before rewiring | O(n) | O(n/k) stack |
| Remove from the end | `removeNthFromEnd`: length → forward index | O(n) | O(1) |
| Clone aliases | `copyRandomList`: identity map, then wire | Expected O(n) | O(n) |
| Several tree aggregates | `measureTree`: postorder summary | O(n) | O(h) stack |
| Validate all BST descendants | `isValidBst`: exclusive ancestor bounds | O(n) | O(h) stack |
| Reconstruct unique-valued tree | `buildTree`: preorder cursor + inorder range | Expected O(n) | O(n) map + O(h) stack |
| Preserve shape and values | `serializeTree` / `deserializeTree`: preorder + null tokens | O(n) | O(n) text + O(h) stack |
| Cover a tree with cameras | `minimumCameras`: three coverage states | O(n) | O(h) stack |

Here `n` is nodes, `h` is tree height. Output nodes are excluded from auxiliary
space. Expected bounds refer to hash tables; pathological collisions can be worse.
The recursive helpers are intended for ordinary contest-depth inputs. A path-shaped
tree or huge number of groups can exhaust the C++ call stack.

## 1. Rewire lists without losing nodes

### Reverse: save the edge before overwriting it

```text
before: prev → reversed prefix    current → next → untouched suffix
step:   next = current->next; current->next = prev
then:   prev = current; current = next
```

The latest source for **206** is the three-pointer, in-place version. Its older
accepted variant allocates new nodes for most of the reversal; acceptance does not
make that variant O(1)-space. The handbook deliberately uses the latest approach.

```cpp
auto* head = new patterns::ListNode(1, new patterns::ListNode(2));
head = patterns::reverseList(head); // Update the owning head pointer.
patterns::destroyList(head);
```

### Reorder: split first, then reverse and weave

Source **143** has both materialized-node/visited-set versions and an in-place
version. In the in-place version, `slow` ends the first half; that half is at least
as long as the second half.

```text
1 → 2 → 3 → 4 → 5
split:    1 → 2 → 3 → null       4 → 5 → null
reverse:  1 → 2 → 3 → null       5 → 4 → null
weave:    1 → 5 → 2 → 4 → 3 → null
```

Save both next pointers before interleaving. The `slow->next = nullptr` cut is part
of correctness: omitting it can leave a cycle. No node values are copied.

### Dummy/sentinel: one predecessor even when the head changes

**21** appends the smaller current node after an output tail. A local dummy gives
both an initially empty output and head replacement the same control flow. The
source allocates and deletes a dummy dynamically; the reusable helper puts it on
the stack and drops a dead branch that checked a known-nonnull tail.

**19** actually counts the length, then removes forward index `length - n`; it is
not a fast/slow two-pointer submission. The adaptation keeps that approach but
starts at a dummy and deletes the unlinked node. Validate `1 <= n <= length` before
mutating anything. If a caller uses an arena or external node owner, remove the
`delete` and transfer responsibility explicitly.

**25** first probes `k` nodes. Only a complete block can be reversed. The old head
becomes the block's tail, so attach the recursively processed suffix there:

```text
[a → b → c] → rest    becomes    [c → b → a] → reverseKGroup(rest, k)
                                            ^ old head is new tail
```

The source is recursive: its total auxiliary space is O(n/k), not O(1). `k == 1`
has an early return in the helper to avoid pointless recursion.

### Merge k lists: read the implementation, not the task title

The latest **23** submission pushes **every node** into a heap: O(N log N) time and
O(N) heap storage. Its older collected variant repeatedly merges two chains using
a queue: O(N log k) time and O(k) queued heads. The reusable building block here is
`mergeSortedLists`; there is no misleading “head-only O(log k) heap” attributed to
the latest submission.

**146** is another useful ownership contrast: the collected LRU uses `std::list`
and `splice`, not hand-written raw-pointer sentinel nodes. Moving one node within
a list preserves its iterator. The companion key-to-iterator map is only valid
for that list instance; ordinary memberwise copying would copy stale iterators.
Capacity zero also needs a guard before accessing `back()`.

## 2. Clone identity first, relationships second

Source **138** separates two concerns:

1. Allocate exactly one clone per original node; map original address → clone.
2. Resolve every `next` and `random` pointer through that complete map.

```text
original: A → B → C       random: A ↘ C, B ↗ A
mapping:  A ↔ A'  B ↔ B'  C ↔ C'
clone:    A'→ B'→ C'      random edges stay entirely inside the clone
```

A repeated value is not an identity. Never key the map by `val`. Self-random and
backward random edges need no special handling once every clone exists.

The helper explicitly maps `nullptr` to `nullptr`; the source relies on
`unordered_map::operator[]` inserting a null value. A temporary vector of
`unique_ptr` owners prevents leaks if allocating or resolving a target throws.
The `next` chain must be finite and acyclic, and random targets must belong to it
or be null. An external random target throws `std::out_of_range`.

`destroyRandomList` follows only `next`. Random links are aliases, not extra
ownership edges. Deleting through both would double-free nodes.

## 3. One postorder pass, several summaries

The collected **104**, **110**, **543**, **124**, and **2265** all ask children for a
small summary and combine it at the parent. `measureTree` shows the shared shape:

```text
       node
      /    \
  left      right
     summaries ↑
 combine locally; return only what the parent needs
```

For child heights `L` and `R`:

- Height: `1 + max(L, R)`, with null height `0`
- Diameter through this node: `L + R`; take the maximum over all nodes
- Balanced: both children balanced and `abs(L - R) <= 1`
- Sum/count: `left + right + current`

Height counts **nodes**, while diameter counts **edges**. The leaf therefore has
height `1` and diameter `0`.

For maximum path sum (**124**), distinguish a return value from a global candidate:

```cpp
leftGain = std::max(0LL, left.downwardGain);
rightGain = std::max(0LL, right.downwardGain);
through = node->val + leftGain + rightGain; // Can use both children.
downward = node->val + std::max(leftGain, rightGain); // Parent gets one branch.
```

A returned path cannot fork and then connect to the parent. Clamp child gains,
not the node value: an all-negative tree's answer is its least-negative node.
The reusable empty-tree result uses `std::nullopt` for maximum path sum rather
than pretending that an empty path is a valid node path.

For **2265**, `(sum, count)` supports `sum / count == node->val`. The collected
problem uses nonnegative values. In C++, division of negative integers truncates
toward zero; it is not mathematical floor. The helper exports sum/count instead
of silently extending that problem-specific average rule.

`measureTree` fuses independent source summaries and widens sums to `long long`.
Unlike mutable fields in some submissions, its state is local to each call.
It computes the whole tree rather than short-circuiting once imbalance is found.

## 4. BST bounds come from every ancestor

Checking only `left->val < node->val < right->val` is insufficient:

```text
       10
      /  \
     5   15
        /
       6       locally below 15, but illegally below ancestor 10
```

Source **98** passes an exclusive interval `(low, high)`:

- Require `low < value < high`
- Left receives `(low, value)`
- Right receives `(value, high)`

Duplicates are invalid under this contract. Bounds start one beyond the full
`int` range, using `long long` arithmetic so `INT_MIN` and `INT_MAX` remain legal
keys. Do not compute `INT_MIN - 1` in `int` first.

## 5. Reconstruction and serialization encode different assumptions

### Preorder + inorder: source 105

Preorder's next unused value is the root. Its unique position in inorder splits
that subtree into left and right ranges. Build left before right because that is
the order the preorder cursor consumes.

```text
preorder: root | left subtree | right subtree
inorder:  left subtree | root | right subtree
```

The helper uses half-open inorder intervals `[start, end)`, validates input size,
unique inorder keys and pivot membership, and cleans partially built trees on
failure. Empty traversals return null. It removes the source's unused initial
`new TreeNode(preorder[0])`, which was leaked and also made empty input unsafe.

### Preorder + null markers: source 297

```text
     2                encoded: 2 1 # # 3 # #
    / \
   1   3              grammar: tree := # | integer tree tree
```

Null markers encode the shape, so duplicate values are fine. The older collected
codec encodes both traversals with assigned node IDs, precisely because raw
values need not be unique. Prefer the shorter collected null-marker approach.

The helper adds strict integer/token validation and rejects truncated data or
trailing tokens. `TreeOwner` guards partial results when an exception occurs.

```cpp
patterns::TreeOwner tree(
    patterns::buildTree({2, 1, 3}, {1, 2, 3}), patterns::destroyTree);
auto encoded = patterns::serializeTree(tree.get());
patterns::TreeOwner copy(patterns::deserializeTree(encoded), patterns::destroyTree);
```

Do not separately delete an owned child's pointer. Every nonnull node must occur
under exactly one owning root. These helpers do not accept DAGs or cyclic graphs.

## 6. Cameras: compress the source's covered set into three states

The actual **968** source runs postorder, places a camera if a child is uncovered,
and tracks coverage in an `unordered_set<TreeNode*>`. Null is pre-covered. At the
root it also handles the case where the root itself remains uncovered.

The helper's three-state return is an explicit **adaptation**, not the literal
submitted code:

```text
child needsCamera → put camera here → hasCamera
otherwise any child hasCamera      → covered
otherwise                          → needsCamera
null                               → covered
```

Why put the camera at an uncovered child's parent? A camera can only reach that
child from the child, its children, or its parent. Descendants have already been
settled. Placing it at the parent covers the child and can also cover the parent's
other child and own parent. Deferring farther upward cannot reach the child.
After DFS, a `needsCamera` root gets one final camera. This removes O(n) hash-set
storage while retaining the source's greedy decision.

## Adaptation ledger

- Standalone `ListNode`, `RandomNode`, `TreeNode` and destruction helpers replace
  judge-provided structures. All ordinary links remain raw, non-owning pointers.
- **206/143:** select the collected in-place variants; reuse reversal as a helper.
- **21/19:** stack dummy; remove dead branching; validate removal and delete the
  detached node. Source **19** did not release it.
- **25:** validate positive `k`; early return for `k == 1`; retain source recursion.
- **138:** explicit null entry, checked lookup, exception-safe temporary owners.
- **104/110/543/124/2265:** combine source postorder summaries; widen arithmetic;
  define empty maximum-path behavior. No persistent mutable answer fields.
- **98:** preserve exclusive bounds, remove unreachable code.
- **105/297:** define malformed/empty input, remove unused allocation, guard partial
  construction; half-open reconstruction ranges and exact integer parsing.
- **968:** documented three-state compression of the actual covered-set source.
- **23/146:** source-specific lessons only; no extra problem wrapper is supplied.

## Tests and ownership checks

From this folder:

```sh
g++ -std=c++20 -O2 -Wall -Wextra -Werror test.cpp -o /tmp/trees-test
/tmp/trees-test
g++ -std=c++20 -O1 -g -Wall -Wextra -Werror \
  -fsanitize=address,undefined -fno-omit-frame-pointer test.cpp -o /tmp/trees-asan
ASAN_OPTIONS=detect_leaks=1 /tmp/trees-asan
```

Deterministic cases include empty lists/trees, integer-extreme BST keys, duplicate
keys, malformed serialization and traversal input, odd reorder, incomplete
k-groups, and clone alias identity. Seed `0x7ee123` drives 300 list-model trials
and 140 tree trials. Camera answers are compared with all camera subsets;
maximum sums with all simple paths; reconstruction and codec with source shapes.
Every created list/tree is destroyed, including separate clones.

Strict compilation and AddressSanitizer/UndefinedBehaviorSanitizer passed in the
build environment. LeakSanitizer itself cannot run there under ptrace; the
successful sandbox sanitizer run used `ASAN_OPTIONS=detect_leaks=0`. Run with leak
detection enabled in an unrestricted local process for an actual leak check.

## Collected source links

These are the accepted code records read for this topic. A link may require the
LeetCode account that owns the submission.

- [206. Reverse Linked List](https://leetcode.com/problems/reverse-linked-list/) — [submission 2143560010](https://leetcode.com/problems/reverse-linked-list/submissions/2143560010/), [submission 2126014226](https://leetcode.com/problems/reverse-linked-list/submissions/2126014226/).

- [143. Reorder List](https://leetcode.com/problems/reorder-list/) — [submission 2143673583](https://leetcode.com/problems/reorder-list/submissions/2143673583/), [submission 2143663379](https://leetcode.com/problems/reorder-list/submissions/2143663379/), [submission 1211639660](https://leetcode.com/problems/reorder-list/submissions/1211639660/).

- [21. Merge Two Sorted Lists](https://leetcode.com/problems/merge-two-sorted-lists/) — [submission 2143594529](https://leetcode.com/problems/merge-two-sorted-lists/submissions/2143594529/).

- [19. Remove Nth Node From End of List](https://leetcode.com/problems/remove-nth-node-from-end-of-list/) — [submission 2143696811](https://leetcode.com/problems/remove-nth-node-from-end-of-list/submissions/2143696811/).

- [25. Reverse Nodes in k-Group](https://leetcode.com/problems/reverse-nodes-in-k-group/) — [submission 2144552684](https://leetcode.com/problems/reverse-nodes-in-k-group/submissions/2144552684/).

- [23. Merge k Sorted Lists](https://leetcode.com/problems/merge-k-sorted-lists/) — [submission 2144522916](https://leetcode.com/problems/merge-k-sorted-lists/submissions/2144522916/), [submission 2144097838](https://leetcode.com/problems/merge-k-sorted-lists/submissions/2144097838/).

- [146. LRU Cache](https://leetcode.com/problems/lru-cache/) — [submission 2143986850](https://leetcode.com/problems/lru-cache/submissions/2143986850/).

- [138. Copy List with Random Pointer](https://leetcode.com/problems/copy-list-with-random-pointer/) — [submission 2143802245](https://leetcode.com/problems/copy-list-with-random-pointer/submissions/2143802245/).

- [104. Maximum Depth of Binary Tree](https://leetcode.com/problems/maximum-depth-of-binary-tree/) — [submission 2140575615](https://leetcode.com/problems/maximum-depth-of-binary-tree/submissions/2140575615/).

- [110. Balanced Binary Tree](https://leetcode.com/problems/balanced-binary-tree/) — [submission 2140593789](https://leetcode.com/problems/balanced-binary-tree/submissions/2140593789/).

- [543. Diameter of Binary Tree](https://leetcode.com/problems/diameter-of-binary-tree/) — [submission 2140582704](https://leetcode.com/problems/diameter-of-binary-tree/submissions/2140582704/).

- [124. Binary Tree Maximum Path Sum](https://leetcode.com/problems/binary-tree-maximum-path-sum/) — [submission 2153370936](https://leetcode.com/problems/binary-tree-maximum-path-sum/submissions/2153370936/), [submission 2141514512](https://leetcode.com/problems/binary-tree-maximum-path-sum/submissions/2141514512/).

- [2265. Count Nodes Equal to Average of Subtree](https://leetcode.com/problems/count-nodes-equal-to-average-of-subtree/) — [submission 2137363284](https://leetcode.com/problems/count-nodes-equal-to-average-of-subtree/submissions/2137363284/).

- [98. Validate Binary Search Tree](https://leetcode.com/problems/validate-binary-search-tree/) — [submission 2140737519](https://leetcode.com/problems/validate-binary-search-tree/submissions/2140737519/).

- [105. Construct Binary Tree from Preorder and Inorder Traversal](https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/) — [submission 2141508524](https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/submissions/2141508524/), [submission 2141508275](https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/submissions/2141508275/).

- [297. Serialize and Deserialize Binary Tree](https://leetcode.com/problems/serialize-and-deserialize-binary-tree/) — [submission 2153777400](https://leetcode.com/problems/serialize-and-deserialize-binary-tree/submissions/2153777400/), [submission 2141912475](https://leetcode.com/problems/serialize-and-deserialize-binary-tree/submissions/2141912475/), [submission 2141671426](https://leetcode.com/problems/serialize-and-deserialize-binary-tree/submissions/2141671426/).

- [968. Binary Tree Cameras](https://leetcode.com/problems/binary-tree-cameras/) — [submission 2155106387](https://leetcode.com/problems/binary-tree-cameras/submissions/2155106387/).
