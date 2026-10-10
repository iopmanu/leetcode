# Range queries, frequency counting, and ordered aggregates

These patterns come from your submitted C++ solutions. The code keeps your zero-based public indices, inclusive recursive ranges, vector-backed structs, camelCase names, and straightforward loops. It adds explicit contracts where LeetCode constraints previously supplied them.

- [Reusable C++20 implementations](templates.hpp)
- [Deterministic and seeded differential tests](test.cpp)
- [Merge counting and sorting](../search-and-sort/README.md), including your reverse-pairs solution

## Pick the structure by its invariant

| Need | Pattern here | Build | Operation | Space |
|---|---|---:|---:|---:|
| Point add/assignment, range sum | `FenwickSum` | O(n) | O(log n) | O(n) |
| Select the kth remaining position | `OrderStatisticTree` | O(n) | O(log n) | O(n) |
| Range assignment, range maximum | `RangeAssignMaxTree` | O(n) | O(log n) | O(n) |
| Count static values below a threshold in a range | `MergeSortTree<T>` | O(n log n) | O(log² n) | O(n log n) |
| Point assignment, prefix-product histogram of a range | `ProductPrefixTree` | O(nk) | O(k log n) | O(nk) |
| Count subarray sums in a value interval | `countRangeSum` | — | O(n log n) total | O(n) |
| Simulate falling squares | `fallingSquares` | — | O(n log n) total | O(n) |
| Count all subarray products modulo k | `countProductRemainders` | — | O(nk) total | O(k) |

Here k is the modulus, not an order-statistic rank. Bounds use the usual nonempty-input convention; empty inputs are supported.

### Shared contracts

All public range queries use **inclusive** `[l, r]`. `l > r` means empty and returns the relevant identity; empty updates do nothing. A nonempty range must satisfy `0 <= l <= r < n`, otherwise it throws `std::out_of_range`. No implicit clamping.

- Empty sum/count: `0`; empty max: `std::numeric_limits<long long>::lowest()`.
- Fenwick `query(-1) == 0`; other prefix endpoints must be in `[0, n-1]`.
- Invalid order-statistic ranks return `-1` and never change counts.
- Negative sizes, negative counts, nonpositive moduli, and nonpositive square sides are rejected. Count overflow is checked in the order-statistic tree.
- Storage sizes are checked against `INT_MAX / 4`, keeping recursive node indices in `int`. Allocation can still fail if memory is insufficient. Product-tree storage is practical only for modest k.
- Fenwick sums, intermediate partial sums, deltas, and range differences must fit `long long`. Widening is not arbitrary-precision arithmetic. Other helpers' bounded `int` inputs and checked lengths keep their arithmetic within `long long`.
- `MergeSortTree<T>` requires sortable, copyable/default-constructible values, with `<` forming a strict weak ordering.

## 1. Fenwick: store aligned sum blocks

Your 307 implementation uses one-based internal storage, with a zero-based public API. Internal cell `tree[i]` stores the last `lowbit(i)` values ending at internal index i.

```text
internal cell  block of public indices
1              [0]
2              [0 1]
3                  [2]
4              [0 1 2 3]
8              [0 1 2 3 4 5 6 7]

query(6): internal 7 -> 6 -> 4 -> 0
          [6] + [4..5] + [0..3]
```

- **Prefix:** subtract `i & -i` to remove the current block.
- **Point add:** add `i & -i` to visit each containing block.
- **Assignment:** keep `arr`, calculate `delta = newValue - arr[index]`, then add the delta.
- **Linear construction:** initialize `tree[i]` from the input and forward each accumulated cell once to `i + lowbit(i)`. No O(n log n) sequence of insertions is needed.
- **Range sum:** `query(r) - query(l - 1)`. The `-1` identity eliminates a special branch at the left edge.

```cpp
patterns::FenwickSum sums(std::vector<long long>{1, 3, 5});
sums.update(1, 2);           // [1,2,5]
sums.add(0, -4);             // [-3,2,5]
long long x = sums.sumRange(0, 2);  // 4
```

**Use it for:** mutable sums or frequencies on an ordered, compressed value domain. Negative values are fine for sums; finding a kth element by cumulative counts requires nonnegative frequencies and is a different contract.

**Generalization from 307:** adds a public `add`, retains assignment as `update`, widens stored values/deltas/sums, fixes member-initialization ordering, and checks indices. `arr` is updated by both mutation paths so later assignments remain correct.

### Prefix differences + compression: 327

Let `prefix[j] - prefix[i]` be the subarray sum for `i < j`. The allowed interval becomes:

```text
lower <= prefix[j] - prefix[i] <= upper
prefix[i] + lower <= prefix[j] <= prefix[i] + upper
```

Your submission preloads all prefix sums, then visits them chronologically. **Remove the current prefix first**; the Fenwick tree then counts only strictly future endpoints. Use `lower_bound` for the inclusive lower value and `upper_bound - 1` for the inclusive upper value.

A subtle source detail: the original keeps duplicate coordinates and initially sets every sorted slot to one. Every removal uses the first equal slot. That slot can become negative, but queries cover whole equal-value blocks, whose total is still correct. The handbook deliberately deduplicates coordinates and initializes each coordinate with its actual frequency. This makes the frequency invariant explicit and keeps each count nonnegative.

`countRangeSum({0,0,0}, 0, 0)` returns 6. The empty prefix is essential, and removing it before counting excludes the empty subarray. The result is `long long`; `lower > upper` returns zero.

**Provenance boundary:** the retrieved 327 source is this Fenwick approach. A merge-sort counting solution for 327 is not claimed as one of your submitted variants.

## 2. A count tree turns selection into descent

In 406, each leaf starts at one: its queue position is free. Each internal node stores the number of remaining positions in its interval.

```text
counts = [1,0,1,1]       select zero-based k=1
          sum=3
         /     \
     sum=1     sum=2      k >= leftCount: go right with k=0
     /  \       /  \
    1    0     1    1    result: index 2
```

The decisive condition is `leftCount > k`, **not** `leftCount >= k`.

- `kth(k)` observes without changing the tree.
- `updateAndFind(k)` returns the position and removes one occurrence.
- `add(index, delta)` supports reinsertion or general nonnegative frequencies.

For queue reconstruction, sort by **height ascending, then k descending**. Smaller people already placed do not affect the next person's taller-or-equal count. Reserve the kth free position for that person; the earlier free positions are for people still to come. Descending k for equal heights avoids placing an equal-height person earlier than intended.

**Generalization from 406:** guards the empty build, validates rank before touching the tree, supports weighted counts and reinsertion, and exposes non-destructive selection. The source decrements nodes during selection; the handbook uses selection plus a point decrement for clarity, still O(log n). No negative counts are allowed because they break cumulative selection.

## 3. Lazy assignment: a pending value is not a sentinel

Your 699 tree stores the maximum height of each interval. A full-cover assignment overwrites the aggregate and remembers the assignment; a partial operation pushes that assignment to both children first.

```text
assign [0..3] = 0        node: max=0, hasLazy=true, lazy=0
assign [1..2] = -5       push zero before descending
leaves afterward         0    -5    -5     0
```

The invariant is: **the parent's aggregate is current; its descendants may lag only while a pending assignment explains their state**. A newer assignment replaces an older one. This is assignment composition, not range addition.

The source's `lazy != 0` works with its positive-height updates. A reusable assignment tree needs `hasLazy`: zero, negatives, and even `LLONG_MIN` are legitimate values. The no-overlap query identity must be negative infinity, not zero, when values can be negative.

### Compress cells, not just points

For a square with left endpoint L and side S, its horizontal footprint is half-open `[L, L+S)`. Sort and deduplicate **both** endpoints. Leaf i represents the elementary interval `[coords[i], coords[i+1])`.

```text
coords:     1       3          6
cells:        [1,3)    [3,6)
square A:     =====             [1,3)
square B:              =====    [3,6)
```

Query and assign the inclusive index interval `[rank(L), rank(L+S)-1]`. Merely touching at an endpoint does not cause stacking. Landing height is `rangeMax + side`, then the entire footprint is assigned that height.

**Generalization from 699:** separate lazy flags, negative maximum identity, checked wrappers, exactly `coords.size()-1` meaningful cells, widened coordinate addition and height, and local compression state. Local state also makes repeated `fallingSquares` calls independent; the source stores its mapping and running coordinate index on `Solution`.

**Compression pitfall:** ranks preserve order, not distance. Cell widths are irrelevant for maximum height. Area, covered length, or spatial sums must retain the actual coordinate differences.

## 4. Merge-sort tree: binary search inside covered nodes

Your two 315 sources store a sorted vector at each segment-tree node. Build leaves, then merge the child vectors. A range query decomposes its interval into O(log n) nodes; `lower_bound(value)` counts strictly smaller elements within each covered node.

```text
input:               [5,2,6,1]
node vectors:        [1,2,5,6]
                    /         \
                 [2,5]       [1,6]
                 /   \       /   \
               [5]   [2]   [6]   [1]
```

For “smaller after self,” query `[i+1,n-1]` with threshold `nums[i]`. Equal elements are excluded. An empty suffix returns zero.

**Use it for:** many static range-count queries with different positions and thresholds. It is not a point-update structure: changing a value would invalidate sorted vectors along its path. Full use for 315 costs O(n log² n), despite the O(n log n) construction.

**Generalization from 315:** adopts the older source's `vector<T>` constructor and empty guard; the newer constructor hardcodes `vector<int>` and builds unconditionally. The handbook drops the unnecessary retained input copy and throws on invalid nonempty ranges instead of silently returning zero. Both retrieved submissions are the same algorithmic family, not Fenwick or merge-count alternatives.

## 5. Ordered aggregates: product plus prefix histogram

3525 provides a useful example where the merge is associative but **not commutative**. A node stores:

- `product`: product of the whole segment modulo k
- `counts[r]`: number of **nonempty prefixes starting at that segment's left boundary** whose product is r modulo k

For adjacent segments A then B:

```text
prefix of A+B = prefix contained in A
             OR all of A followed by a nonempty prefix of B

result.product = A.product * B.product mod k
result.counts  = A.counts
result.counts[A.product * r mod k] += B.counts[r]  for every r
```

This is associative because concatenating segments is associative. It is not commutative: modulo 5, `[2,3]` has prefix products `[2,1]`, while `[3,2]` has `[3,1]`. Always merge query fragments in physical left-to-right order.

The empty identity has `product = 1 % k` and all-zero counts. The `% k` matters for k=1. A histogram alone is insufficient; the complete left product is needed to transform the right histogram.

```cpp
patterns::ProductPrefixTree tree({2, 3, 4}, 5);
tree.update(1, 7);
auto prefixes = tree.query(1, 2);  // range [7,4]: products 2 and 3
long long answer = prefixes.counts[3];  // 1
```

For the original queries, perform the point assignment and query `[start,n-1]`, then read the requested remainder. This counts possible right endpoints with a fixed left boundary. It does **not** count every subarray inside the queried range.

**Generalization from 3525:** replaces the fixed six-element array, with product hidden at index k, by a named aggregate and dynamic histogram; uses `4*n` storage instead of floating-point `log2(n)` sizing; deliberately changes the source's root-1/children-`2*node,2*node+1` indexing to the chapter's root-0/children-`2*node+1,2*node+2` convention; supports empty ranges and checked indices; widens counts; normalizes negative residues; and promotes remainder multiplication before taking `% k`. The dynamic version exposes the O(k) merge cost and O(nk) space that were constants under the original small-modulus bound.

### Related 3524 pattern: all subarrays ending here

For immutable all-subarray counting, your 3524 source uses rolling DP instead:

- `dp[r]`: subarrays ending at the preceding position with product remainder r
- Start the one-element subarray at `value % k`
- Extend every previous state into `next[r * value % k]`
- Replace `dp`, then add it to the global answer

Invariant: each subarray ending here appears once, either as a singleton or an extension. This is O(nk) time and O(k) memory; no tree is needed. The handbook normalizes negative residues and multiplies two normalized residues, avoiding unnecessary large-value multiplication.

## 6. Adjacent source patterns: choose a simpler structure when possible

### 493: count before merging sorted halves

Your reverse-pairs submission recursively sorts the left and right halves. Before ordinary merging, it walks two pointers. If `L[i] > 2LL * R[j]`, all `nLeft-i` remaining left values qualify, so count them and advance j; otherwise advance i. Keep the threshold-counting pass separate from the ordinary value-order merge. The factor comparison and sort ordering are different predicates.

It is O(n log n) time and O(n) peak auxiliary space, and it sorts the input as a side effect. The member result must be reset for repeated calls. See [search and sort](../search-and-sort/README.md) for the reusable implementation. This source is actual merge counting; 315 is a merge-sort **tree**.

### 218: sweep active heights instead of building a range tree

Your skyline source converts each building into `(left,+height)` and `(right,-height)`, sorts by x ascending then signed height descending, and keeps a descending `multiset` with ground height zero.

At the same x, starts precede ends; taller starts precede shorter starts; shorter ends precede taller ends. This tie order prevents transient skyline points at one coordinate. Emit a point only when the maximum active height changes. Remove **one iterator** for an ending building, not every equal height. Time O(n log n), space O(n).

### 729: disjoint intervals need only two neighbors

Your calendar source stores `start -> end` in an ordered map. `lower_bound(start)` finds the successor; only it and the predecessor can conflict with a new booking, because the stored intervals are already pairwise disjoint.

- Conflict with successor when `successor.start < end`
- Conflict with predecessor when `predecessor.end > start`

Intervals are half-open `[start,end)`, so touching is allowed. Require `start < end` in a generalized wrapper. Each booking is O(log n) and total storage is O(n). These sweep/map patterns are documented here without presenting them as generic segment trees.

## Exact source trail

These are the retrieved submissions used for this chapter. Links identify evidence; implementations above are intentionally generalized, not represented as verbatim submissions.

| Task | Retrieved submission(s) | Observed pattern |
|---|---|---|
| [307. Range Sum Query - Mutable](https://leetcode.com/problems/range-sum-query-mutable/) | [2152356890](https://leetcode.com/problems/range-sum-query-mutable/submissions/2152356890/) | O(n)-build Fenwick, assignment via delta |
| [327. Count of Range Sum](https://leetcode.com/problems/count-of-range-sum/) | [2152424852](https://leetcode.com/problems/count-of-range-sum/submissions/2152424852/) | Preload/remove future-prefix Fenwick |
| [406. Queue Reconstruction by Height](https://leetcode.com/problems/queue-reconstruction-by-height/) | [2152399602](https://leetcode.com/problems/queue-reconstruction-by-height/submissions/2152399602/) | Destructive kth-free count tree |
| [699. Falling Squares](https://leetcode.com/problems/falling-squares/) | [2155079538](https://leetcode.com/problems/falling-squares/submissions/2155079538/) | Compressed range assignment/range max |
| [315. Count of Smaller Numbers After Self](https://leetcode.com/problems/count-of-smaller-numbers-after-self/) | [2150813916](https://leetcode.com/problems/count-of-smaller-numbers-after-self/submissions/2150813916/), [2150760829](https://leetcode.com/problems/count-of-smaller-numbers-after-self/submissions/2150760829/) | Two merge-sort-tree variants |
| [3525. Find X Value of Array II](https://leetcode.com/problems/find-x-value-of-array-ii/) | [2150176033](https://leetcode.com/problems/find-x-value-of-array-ii/submissions/2150176033/) | Ordered product/prefix-count tree |
| [3524. Find X Value of Array I](https://leetcode.com/problems/find-x-value-of-array-i/) | [2148463117](https://leetcode.com/problems/find-x-value-of-array-i/submissions/2148463117/) | Rolling product-remainder DP |
| [493. Reverse Pairs](https://leetcode.com/problems/reverse-pairs/) | [2150875619](https://leetcode.com/problems/reverse-pairs/submissions/2150875619/) | Merge counting, maintained in search-and-sort |
| [218. The Skyline Problem](https://leetcode.com/problems/the-skyline-problem/) | [2153355270](https://leetcode.com/problems/the-skyline-problem/submissions/2153355270/) | Signed events + active-height multiset |
| [729. My Calendar I](https://leetcode.com/problems/my-calendar-i/) | [2152937765](https://leetcode.com/problems/my-calendar-i/submissions/2152937765/) | Ordered disjoint-interval map |

## Verification

From this directory:

```sh
g++ -std=c++20 -O2 -Wall -Wextra -Werror -pedantic test.cpp -o /tmp/range-queries-test
/tmp/range-queries-test
g++ -std=c++20 -O1 -g -Wall -Wextra -Werror -pedantic \
    -fsanitize=address,undefined -fno-omit-frame-pointer test.cpp -o /tmp/range-queries-sanitized
/tmp/range-queries-sanitized
```

Eight test groups compare against direct sums, frequency scans, vector assignments, linear threshold counts, explicit prefix products, all subarray sums, unit-cell square simulation, and all subarray products. Seeds are fixed in `test.cpp`. Targeted cases cover duplicate coordinates, invalid ranks, empty inputs, touching footprints, zero/negative lazy tags, `LLONG_MIN` assignments, k=1, modulus larger than the source's fixed bound, noncommutative order, widened arithmetic, and rejected invalid operations.

In the authoring environment, ASan and UBSan passed with `ASAN_OPTIONS=detect_leaks=0`; LeakSanitizer itself could not run under the environment's ptrace instrumentation. Leak checking is therefore not claimed.
