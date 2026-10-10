# Range queries

[All topics](../../README.md) · [Source index](../../SOURCES.md) · [Coverage](../../COVERAGE.md)

**7 captured problems · 8 accepted submission records.** Every linked implementation below is an unchanged captured source file. These notes describe the code; they do not replace it with a common API.

## Pattern reminders

### Fenwick prefix sums

- **Cue:** Point changes and many prefix or inclusive range sums.
- **Idea and invariant:** Each tree cell aggregates its low-bit block. In 307, assignment is converted to the difference from the saved array value; an inclusive range is the difference of two prefixes. In 327, the tree counts future prefix sums after removing the current one.
- **Cost in these sources:** 307 builds in O(n), then updates and queries in O(log n), with O(n) storage. 327 includes coordinate sorting and n tree operations: O(n log n) time and O(n) storage.
- **Read the originals:** [307. Range Sum Query - Mutable — 2152356890](originals/307__2152356890.cpp); [327. Count of Range Sum — 2152424852](originals/327__2152424852.cpp).

### Lazy range assignment

- **Cue:** An interval receives one new height, and later intervals need its maximum.
- **Idea and invariant:** 699 compresses square endpoints into elementary intervals. A node maximum represents its full covered interval; a pending assignment replaces the entire child interval when pushed. Touching square boundaries do not create overlap.
- **Cost in these sources:** O(n log n) time for n squares, including compression, and O(n) storage.
- **Read the originals:** [699. Falling Squares — 2155079538](originals/699__2155079538.cpp).

### Order statistics among free positions

- **Cue:** Pick the kth currently free location, then occupy it.
- **Idea and invariant:** 406 stores free counts in children. A zero-based rank goes left when the left count is greater than that rank; otherwise the rank is reduced by the left count. The chosen leaf is removed.
- **Cost in these sources:** O(n log n) time including sorting and O(n) tree storage.
- **Read the originals:** [406. Queue Reconstruction by Height — 2152399602](originals/406__2152399602.cpp).

### A sorted vector at every node

- **Cue:** Static range queries ask how many elements are below a threshold.
- **Idea and invariant:** 315 stores the sorted values of each segment. A fully covered node answers with lower_bound; the query combines disjoint covered nodes.
- **Cost in these sources:** O(n log n) build and storage; O(log squared n) per count query and O(n log squared n) for the full solution.
- **Read the originals:** [315. Count of Smaller Numbers After Self — 2150813916](originals/315__2150813916.cpp).

### Ordered aggregate merging

- **Cue:** A range summary depends on the order of multiplication and on all prefix outcomes.
- **Idea and invariant:** 3525 stores a segment product and counts of prefix-product remainders. A merged prefix either stays in the left segment or contains all of the left plus a prefix of the right. Left and right cannot be swapped. The captured array has six slots and uses slot k for the full product.
- **Cost in these sources:** O(nk) build, O(k log n) per update/query, and O(nk) storage; the source problem bounds k by 5.
- **Read the originals:** [3525. Find X Value of Array II — 2150176033](originals/3525__2150176033.cpp).

### Lazy range-chmin and point coverage queries

- **Cue:** Every interval offers a candidate cost to all points it contains; later queries ask for the cheapest covering interval.
- **Idea and invariant:** [1851](originals/1851__2168532079.cpp) composes pending bounds with min. Each interval updates its inclusive coordinate range with its length, and a point query returns the cheapest covering length or INT_MAX.
- **Cost in this source:** The coordinate capacity is M=maxEnd+1. Allocation/initialization costs O(M) time and space; I interval updates and Q point queries add O((I+Q) log M) time. The original deliberately retains its raw-coordinate arrays and custom lazy helpers.

## Complete problem and variant index

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
