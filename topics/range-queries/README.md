# Range queries

[All topics](../../README.md) · [Source index](../../SOURCES.md) · [Coverage](../../COVERAGE.md)

## Main algorithms and structures

Choose the summary a range must return, then the update it must support. These links open the captured implementation or an unchanged source excerpt; they are not a common replacement API. Here n is the array/event count, k is the modulus, I/Q are interval/query counts, and M is the largest raw endpoint plus one. Space includes the built structure and recursion, excluding returned answers.

| Structure / recognition trigger | Time in the captured implementation | Extra space | Direct implementation |
|---|---|---|---|
| Fenwick tree: additive point changes, prefix/range sums, or a frequency histogram | Mutable-array build O(n), update/prefix/range O(log n); frequency-tree constructor O(n log n), complete compressed counting O(n log n) | O(n) | [Linear build and assignment-to-delta](snippets/fenwick-307.cpp) · [Full mutable array](originals/307__2152356890.cpp) · [Frequency tree](snippets/fenwick-327.cpp) · [Full counting composition](originals/327__2152424852.cpp) |
| Merge-sort tree: static index range plus a value threshold | Build O(n log n); count query O(log² n); all suffix queries O(n log² n) | O(n log n) | [Sorted-vector nodes](snippets/merge-sort-tree-315.cpp) · [Full source](originals/315__2150760829.cpp) |
| Count segment tree: select and remove the kth available position | Build O(n); selection/removal O(log n); reconstruction including sort O(n log n) | O(n) | [Rank descent](snippets/order-statistic-segment-tree-406.cpp) · [Full source](originals/406__2152399602.cpp) |
| Lazy assignment + maximum: overwrite an interval and query its highest point | O(log n) per range operation; compressed event processing O(n log n) including sort | O(n) | [Assignment tree](snippets/lazy-segment-tree-699.cpp) · [Full compression/event loop](originals/699__2155079538.cpp) |
| Lazy chmin + point query: intervals offer costs to covered coordinates | Initialization O(M); O(log M) per update/in-range point query; total O(M + (I+Q) log M) | O(M), not O(I+Q) | [Range-chmin tree](snippets/segment-tree-range-chmin.cpp) · [Full raw-coordinate source](originals/1851__2168532079.cpp) |
| Ordered product/prefix-count segment tree: merge a noncommutative summary | Build O(nk); update/query O(k log n), with k ≤ 5 | O(n) actual fixed six-slot arrays; O(log n) query stack | [Ordered merge](snippets/ordered-product-segment-tree-3525.cpp) · [Full source](originals/3525__2150176033.cpp) |

## Combinations and tricks

### Prefix differences + a future-only frequency tree

- **Recognize:** Count subarrays whose sum lies in a numeric interval, rather than return one range sum.
- **Compose:** Prefix sums turn a subarray into two endpoints; sorted prefix values turn numeric bounds into ranks; a Fenwick tree counts the eligible later endpoints.
- **Invariant:** Remove the current prefix before querying [current+lower, current+upper], so only later positions contribute. Use lower_bound at the lower edge and upper_bound at the inclusive upper edge.
- **Tradeoff / source:** [The captured composition](originals/327__2152424852.cpp) retains duplicate values in the sorted vector and initializes every slot to one. Repeated removals use the first equal slot, which can become negative; the total over an entire equal-value block still represents the remaining multiplicity. It is not a deduplicated-rank frequency template. Prefix arithmetic is long long; the result remains int.

### Greedy order + kth free-slot descent

- **Recognize:** An item's final position is specified by how many qualifying items must precede it.
- **Compose:** Sort heights ascending, equal-height ranks descending; use a segment tree of free-slot counts to place each person.
- **Invariant:** A free slot will be occupied by a sufficiently tall person later. At each node, a zero-based rank goes left if leftCount > rank; otherwise subtract leftCount and go right. Decrement counts along that same descent.
- **Tradeoff / source:** [Sorting and placement together](originals/406__2152399602.cpp) avoid O(n) vector insertion per person, but the tie order is part of the proof, not an interchangeable sort preference.

### Endpoint compression + range maximum + assignment

- **Recognize:** Coordinates are large, but changes happen only at known interval boundaries.
- **Compose:** Sort/deduplicate square endpoints; represent elementary gaps between endpoints; query the landing maximum and assign maximum+side to the footprint.
- **Invariant:** The footprint is [leftIndex, rightIndex-1]. Two squares that only touch at an endpoint must not stack. Assignment replaces the entire covered height, and newer assignments replace older pending assignments.
- **Tradeoff / source:** [Falling-square composition](originals/699__2155079538.cpp) uses O(n) coordinate storage rather than storage proportional to coordinate magnitude. Zero is the no-pending-assignment marker, safe for its positive landing heights; the member coordinate map/counter assume the original one-call object lifecycle.

### Match the lazy tag to its algebra

- **Recognize:** Many interval updates can be deferred until a queried path needs them.
- **Compose:** Choose both the node aggregate and how pending updates combine. [Assignment/max](originals/699__2155079538.cpp) overwrites pending tags; [chmin/point coverage](originals/1851__2168532079.cpp) combines them with min.
- **Invariant:** Pushing a tag must preserve the same answer as applying its update to every covered point. INT_MAX means both “no covering interval” and “no pending bound” in the chmin source.
- **Tradeoff:** The interval-coverage implementation allocates two arrays of 4M ints over raw coordinates. Large sparse endpoints are therefore expensive even with few intervals. Its actual source is a lazy tree, with no compression or sweep/heap substitution; an out-of-domain point returns no result.

### Ordered summaries + a small remainder domain

- **Recognize:** A query counts outcomes of prefixes, and joining two ranges changes every right-prefix outcome.
- **Compose:** Store the full segment product plus counts for each prefix-product remainder; merge left prefixes unchanged and extend each right prefix by the full left product.
- **Invariant:** Each merged prefix either ends in the left interval or includes all of the left followed by a right prefix. Preserve left-to-right order in both build and query.
- **Tradeoff / source:** [The actual merge and suffix-query composition](originals/3525__2150176033.cpp) reserve slot k for the full product in an array of length six. Thus k ≤ 5 is structural; supporting an arbitrary modulus would require a different representation. Multiplication alone is commutative, but this richer prefix summary is not.

### Index decomposition + value search

- **Recognize:** Restrict both where an element occurs and how its value compares with a threshold.
- **Compose:** A segment tree decomposes the index range; each covered node's sorted vector answers the value condition with lower_bound.
- **Invariant:** Covered nodes partition the requested range, so their counts add without overlap. lower_bound counts strictly smaller values, preserving duplicate semantics.
- **Tradeoff / source:** [Suffix counting](originals/315__2150813916.cpp) is O(n log² n), not the O(n log n) of a different merge-counting solution. The [other captured variant](originals/315__2150760829.cpp) guards construction of an empty input; the newer constructor relies on the original nonempty constraint.

## Problem and source appendix

All captured submissions are retained, including equivalent resubmissions and exact duplicates. Submission IDs distinguish files; they are not rankings of quality. The source itself is authoritative when a note is too brief.

### 307. Range Sum Query - Mutable

[Problem](https://leetcode.com/problems/range-sum-query-mutable/) · Tags: Fenwick tree, Prefix sums, Point updates

Fenwick O(n) construction copies values then propagates each tree cell to parent; point assignment converted to delta, inclusive range via two prefixes.

**Captured variants:** One observed approach.

- [Original 2152356890](originals/307__2152356890.cpp) · [LeetCode submission](https://leetcode.com/problems/range-sum-query-mutable/submissions/2152356890/)

### 315. Count of Smaller Numbers After Self

[Problem](https://leetcode.com/problems/count-of-smaller-numbers-after-self/) · Tags: Merge-sort tree, Range counting

Each segment-tree node stores merged sorted subarray; range count-less-than uses lower_bound at fully covered nodes.

**Captured variants:** Two equivalent merge-sort tree variants, not Fenwick/merge counting sources.

- [Original 2150813916](originals/315__2150813916.cpp) · [LeetCode submission](https://leetcode.com/problems/count-of-smaller-numbers-after-self/submissions/2150813916/)
- [Original 2150760829](originals/315__2150760829.cpp) · [LeetCode submission](https://leetcode.com/problems/count-of-smaller-numbers-after-self/submissions/2150760829/)

### 327. Count of Range Sum

[Problem](https://leetcode.com/problems/count-of-range-sum/) · Tags: Fenwick tree, Coordinate compression, Prefix sums

Preload all prefix sums, remove current prefix, count future prefixes in [current+lower,current+upper] via Fenwick.

**Captured variants:** One actual Fenwick source, no merge-sort counting here.

- [Original 2152424852](originals/327__2152424852.cpp) · [LeetCode submission](https://leetcode.com/problems/count-of-range-sum/submissions/2152424852/)

### 406. Queue Reconstruction by Height

[Problem](https://leetcode.com/problems/queue-reconstruction-by-height/) · Tags: Segment tree, Order statistics, Greedy

Sort by height ascending, equal height k descending; count tree tracks free positions, choose and remove kth free slot.

**Captured variants:** One observed approach.

- [Original 2152399602](originals/406__2152399602.cpp) · [LeetCode submission](https://leetcode.com/problems/queue-reconstruction-by-height/submissions/2152399602/)

### 699. Falling Squares

[Problem](https://leetcode.com/problems/falling-squares/) · Tags: Segment tree, Lazy propagation, Coordinate compression

Range assignment and range maximum over compressed elementary x-intervals; landing height = current max + square side.

**Captured variants:** One observed approach.

- [Original 2155079538](originals/699__2155079538.cpp) · [LeetCode submission](https://leetcode.com/problems/falling-squares/submissions/2155079538/)

### 1851. Minimum Interval to Include Each Query

[Problem](https://leetcode.com/problems/minimum-interval-to-include-each-query/) · Tags: Lazy segment tree, Range chmin, Point queries

Build a segment tree over raw coordinates from 0 through the largest interval endpoint. Each interval applies its inclusive length as a range-chmin update. A query reads the minimum stored length at one coordinate and converts INT_MAX to -1.

**Original-code context:** This source uses neither coordinate compression nor a heap. With M=maxEnd+1, initialization and storage are O(M), and I interval updates plus Q point queries cost O((I+Q) log M). It assumes a nonempty interval list and retains int coordinate arithmetic. INT_MAX is both the no-result and no-pending-update sentinel.

**Captured variants:** One captured custom lazy segment-tree implementation.

- [Original 2168532079](originals/1851__2168532079.cpp) · [LeetCode submission](https://leetcode.com/submissions/detail/2168532079/)

### 3525. Find X Value of Array II

[Problem](https://leetcode.com/problems/find-x-value-of-array-ii/) · Tags: Segment tree, Noncommutative aggregates, Modular products

Each node stores full product modulo k plus counts of prefix-product remainders; ordered merge keeps left prefixes and extends full left by right prefixes.

**Captured variants:** One source; important richer aggregation pattern.

- [Original 2150176033](originals/3525__2150176033.cpp) · [LeetCode submission](https://leetcode.com/problems/find-x-value-of-array-ii/submissions/2150176033/)
