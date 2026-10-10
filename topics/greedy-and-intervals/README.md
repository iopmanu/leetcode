# Greedy and intervals

[All topics](../../README.md) · [Source index](../../SOURCES.md) · [Coverage](../../COVERAGE.md)

**19 captured problems · 29 accepted submission records.** Every linked implementation below is an unchanged captured source file. These notes describe the code; they do not replace it with a common API.

## Main algorithms and structures

A greedy choice needs an exchange argument or a dominance invariant; sorted input alone is not the proof. Here `n` is item/interval count, `D` a scanned integer value range, `a` the alphabet size, and `B=15` the captured bit count. Space excludes returned output but includes temporary copies; usual library sorting uses O(log n) stack. Hash-map costs are expected-time.

| Algorithm / structure | What it maintains | Time in these implementations | Auxiliary space / mutation | Direct implementation |
| --- | --- | --- | --- | --- |
| Shorter-boundary elimination | A shorter container endpoint cannot improve after width decreases | O(n) | O(1) | [Opposing boundaries](originals/11__2147803818.cpp) |
| Sorted interval fold | The last result interval is the union of the current overlapping run | O(n log n) | O(log n) sort stack + O(n) output; sorts input | [Merge intervals](originals/56__2167385466.cpp) |
| Overlap-boundary binary searches | Locate the contiguous block touched by one new interval | O(log n) search + O(n) vector movement; sorting variant O(n log n) | O(1) search state; up to O(n) reallocation and O(n) returned copy; mutates both arguments | [Insert into sorted intervals](originals/57__2167382205.cpp), [variant with extra sort](originals/57__2167379680.cpp) |
| Earliest-finish interval selection | Keep the compatible interval leaving the earliest next start | O(n log n) | O(log n) sort stack; sorts input and overwrites its first interval | [Minimum interval removals](originals/435__2167400289.cpp) |
| Ordered interval map | Disjoint bookings ordered by their start times | O(log n) per booking | O(n) persistent map | [Neighbor conflict checks](originals/729__2152937765.cpp) |
| Sweep events + ordered multiset | Active heights, including duplicate buildings and baseline zero | O(n log n) | O(n) events + active heights, plus O(n) output | [Skyline sweep](originals/218__2153355270.cpp) |
| Weighted-interval predecessor DP | Best score and lexicographic index path for each prefix and count≤4 | O(n log n), since count/path lengths are bounded by 4 | O(n) predecessor/DP state; appends indices to and sorts input | [Weighted compatible intervals](originals/3414__2139370298.cpp) |
| Prefix minimum / boundary-gap scan | Best earlier buy price, or previous occupied position | O(n) | O(1) | [Best one-transaction profit](originals/121__2127314016.cpp), [occupied-seat gaps](originals/849__1284774909.cpp) |
| Two directional constraint passes | Minimum assignment satisfying both neighbor inequalities | O(n) | O(n) assignment array | [Candy counts](originals/135__2163599188.cpp) |
| Sort + pair extremes | Consume the heaviest item, pairing with the lightest when appropriate | O(n log n) | O(log n) sort stack; mutates input | [Capacity-limited pairs](originals/881__2147809080.cpp), [minimum worst pair sum](originals/1877__2140485732.cpp) |
| Frequency buckets over a value range | Count remaining values at the smallest/largest current level | Expected O(n+D), with D=max−min+1 | O(D) hash keys in worst case, including inserted zero counts | [Bucket pairing](originals/1877__2140491975.cpp) |
| Sort by marginal reward / cost | Take highest-value units or cheapest remaining deficits first | O(n log n) | Units: O(log n) sort stack and input mutation; bags: O(n) copied pairs | [Truck units](originals/1710__2119475867.cpp), [fill cheapest deficits](originals/2279__2119511298.cpp) |
| Batch highest-level reductions | Move all affordable count from a difference level to the next | Expected O(n+D), D=maximum difference | O(D+1) hash keys due to dense level scan | [Squared-difference reduction](originals/2333__2168486798.cpp) |
| Restrict the candidate set | Any common domino value must occur on the first domino | O(n) for two candidate scans | O(1) | [Two domino candidates](originals/1007__2157541300.cpp) |
| Earliest short palindrome | Accept the first qualifying block of length k or k+1 | O(nk) worst-case comparisons | O(1) scan state; by-value string can add O(n) | [Direct palindrome tests](originals/2472__2143088360.cpp) |
| Character-span closure | Counts of selected characters exactly fill their bounding interval | O(n+a²), a≤26, including copied output characters | O(a) summaries/deque; by-value string can add O(n), plus O(n) output | [Closed substring selection](originals/1520__2146064854.cpp) |
| High-to-low bit partition refinement | Earlier bit-optimal groups constrain later reorderings | O(Bn), B=15 in source | O(n+B) live group copies and result | [Power-array refinement](originals/4059__2147456833.cpp) |

## Combinations and tricks

### Match the sort key to the decision being proved

- **Recognize:** Intervals must be merged, selected without overlap, or inserted into an already disjoint sequence.
- **Compose:** [Sort by start + union fold](originals/56__2167385466.cpp), [sort by end + earliest-finish selection](originals/435__2167400289.cpp), or [binary searches + vector edit](originals/57__2167382205.cpp).
- **Invariant:** A merged run extends only its final right edge; an earliest-finishing retained interval leaves at least as much room as any alternative; sorted disjoint intervals make overlap endpoints searchable.
- **Tradeoff / trap:** Boundary semantics differ: merge/insert treat touching closed intervals as connected, while the removal source permits one interval to begin when the previous one ends. Insert's O(log n) searches do not eliminate O(n) erase/insert movement or the returned copy of its reference parameter. The removal source binds `last` to `intervals[0]`, so selecting a new interval also overwrites that first input element.

### Reduce online overlap checks to two neighbors

- **Recognize:** Accepted intervals remain disjoint, and one new booking is tested at a time.
- **Compose:** Ordered map keyed by start + `lower_bound` + predecessor/successor checks in [the calendar source](originals/729__2152937765.cpp).
- **Invariant:** Only the first existing start at or after the new start, and its predecessor, can conflict; all other intervals are separated by these neighbors.
- **Tradeoff / trap:** The source uses half-open bookings, so an end equal to another start is allowed. The argument requires the map to remain disjoint after every successful insertion; it is not a general overlap-counting structure.

### Turn endpoints into events, then maintain the active extremum

- **Recognize:** Output changes only at interval starts/ends, and the answer depends on all currently active intervals.
- **Compose:** Signed events + custom tie ordering + descending multiset in [the skyline source](originals/218__2153355270.cpp).
- **Invariant:** Start events are positive, end events negative; descending signed height at equal x processes taller starts first and lower ends first. The multiset maximum is the visible height, and an output point is emitted only when it changes.
- **Tradeoff / trap:** Erase exactly one matching height through an iterator, preserving duplicate buildings. Baseline zero keeps maximum lookup valid after the last real building ends. This source stores all events and all active heights, both O(n).

### Add weights and tie-breaking to interval compatibility

- **Recognize:** Maximizing count is insufficient because intervals carry scores, a selection limit, and a deterministic answer tie-break.
- **Compose:** Sort by end + binary-searched predecessor + bounded-count DP + sorted original-index paths in [the weighted source](originals/3414__2139370298.cpp).
- **Invariant:** Taking interval i uses the best state strictly before its start; skipping it preserves the previous prefix state. Equal scores compare paths in original-index order, not finishing-time order.
- **Tradeoff / trap:** Compatibility here is strict `previousEnd < currentStart`, unlike the calendar/removal conventions. O(n) DP space relies on the source's fixed four-interval limit; each cell owns a small vector. Appending original indices and sorting modifies the caller's interval data.

### Satisfy independent directional constraints, then take their maximum

- **Recognize:** Each item needs a minimum assignment depending on both neighbors.
- **Compose:** Initialize all counts to one + left-to-right propagation + right-to-left maximum in [the candy source](originals/135__2163599188.cpp).
- **Invariant:** The first pass satisfies left-neighbor increases. The second repairs right-neighbor increases without lowering any requirement already established by the first pass.
- **Tradeoff / trap:** This is two passes over one O(n) assignment array, not constant auxiliary space. Equal ratings impose no increase; changing strict comparisons changes the problem.

### Pair extremes or consume the cheapest marginal choice

- **Recognize:** Each step removes an extreme, fills one deficit, or buys interchangeable units at a per-unit reward.
- **Compose:** Sorting + opposing pointers in [boats](originals/881__2147809080.cpp) and [pair sums](originals/1877__2140485732.cpp); sorting by reward/deficit in [truck units](originals/1710__2119475867.cpp) and [bags](originals/2279__2119511298.cpp).
- **Invariant:** The heaviest boat passenger must go now; if the lightest cannot accompany them, nobody can. Pairing opposite extremes limits the worst pair sum. Cheap deficits maximize the number completed with a budget.
- **Tradeoff / trap:** The common proof component is an exchange argument, but the objectives differ. Sort variants mutate input, while bags allocate a pair copy. The truck source subtracts a full box count even on its final partial take; remaining capacity may become negative, then the loop ends.

### Batch repeated greedy moves with frequency levels

- **Recognize:** The next move repeatedly targets the largest difference, and many items share its value.
- **Compose:** Frequency map + descending levels in [squared-difference minimization](originals/2333__2168486798.cpp). The related [pairing source](originals/1877__2140491975.cpp) scans frequencies from both extremes.
- **Invariant:** Reducing d by one saves `2d−1`, so the largest d is always at least as valuable to reduce. Move `min(remainingBudget,count[d])` items together before advancing a level.
- **Tradeoff / trap:** These hash maps are used like dense buckets: `operator[]` inserts missing levels while scanning. Time and space depend on the numeric range D, not only on n or the number of initially distinct values. Sparse huge ranges can make sorting or another implementation preferable; no replacement implementation is claimed here.

### Shrink the proof's candidate family before selecting blocks

- **Recognize:** Valid choices are numerous, but every feasible solution contains a small representative candidate or a locally closed block.
- **Compose:** [Domino candidates from the first pair](originals/1007__2157541300.cpp); [palindrome tests at lengths k and k+1](originals/2472__2143088360.cpp); or [character counts + first/last spans](originals/1520__2146064854.cpp).
- **Invariant:** A common domino value must be on every domino, including the first. A longer palindrome contains a central palindrome of length k or k+1. For character spans, total occurrence count equal to bounding length certifies a block closed under every selected character's occurrences.
- **Tradeoff / trap:** The palindrome source checks characters directly rather than building a DP table; its O(1) scan state excludes the potential by-value string copy. The character-span source uses a deque in first-appearance order and clears it after emitting a closed block; preserve that specific construction instead of substituting a generic interval algorithm.

## Problem and source appendix


All captured submissions are retained, including equivalent resubmissions and exact duplicates. Submission IDs distinguish files; they are not rankings of quality. The source itself is authoritative when a note is too brief.

### 11. Container With Most Water

[Problem](https://leetcode.com/problems/container-with-most-water/) · Tags: Greedy, Two pointers

Two end pointers, update area, advance the shorter boundary.

**Original-code context:** O(n) time, O(1) auxiliary space; variants differ only in pointer types/tie direction.

**Captured variants:** 3 accepted C++ submissions captured; all original versions are retained.

- [Original 2147803818](originals/11__2147803818.cpp) · [LeetCode submission](https://leetcode.com/problems/container-with-most-water/submissions/2147803818/)
- [Original 2126025093](originals/11__2126025093.cpp) · [LeetCode submission](https://leetcode.com/problems/container-with-most-water/submissions/2126025093/)
- [Original 2024244275](originals/11__2024244275.cpp) · [LeetCode submission](https://leetcode.com/problems/container-with-most-water/submissions/2024244275/)

### 56. Merge Intervals

[Problem](https://leetcode.com/problems/merge-intervals/) · Tags: Intervals, Sorting

Sort then fold into result.back(), extending overlapping intervals.

**Captured variants:** Two equivalent loop organizations.

- [Original 2167385466](originals/56__2167385466.cpp) · [LeetCode submission](https://leetcode.com/problems/merge-intervals/submissions/2167385466/)
- [Original 2126107082](originals/56__2126107082.cpp) · [LeetCode submission](https://leetcode.com/problems/merge-intervals/submissions/2126107082/)

### 57. Insert Interval

[Problem](https://leetcode.com/problems/insert-interval/) · Tags: Intervals, Binary search

Find overlapping block with lower_bound on interval ends and upper_bound on interval starts; erase and insert merged interval.

**Captured variants:** [2167382205](originals/57__2167382205.cpp) relies on sorted input; [2167379680](originals/57__2167379680.cpp) redundantly sorts.

- [Original 2167382205](originals/57__2167382205.cpp) · [LeetCode submission](https://leetcode.com/problems/insert-interval/submissions/2167382205/)
- [Original 2167379680](originals/57__2167379680.cpp) · [LeetCode submission](https://leetcode.com/problems/insert-interval/submissions/2167379680/)

### 121. Best Time to Buy and Sell Stock

[Problem](https://leetcode.com/problems/best-time-to-buy-and-sell-stock/) · Tags: Greedy, Prefix minima

Track lowest price so far and best sell-minus-minimum profit.

**Captured variants:** One observed approach.

- [Original 2127314016](originals/121__2127314016.cpp) · [LeetCode submission](https://leetcode.com/problems/best-time-to-buy-and-sell-stock/submissions/2127314016/)

### 135. Candy

[Problem](https://leetcode.com/problems/candy/) · Tags: Greedy, Two passes

Initialize all ones, enforce increasing-neighbor constraints left-to-right and right-to-left with max.

**Captured variants:** One observed approach.

- [Original 2163599188](originals/135__2163599188.cpp) · [LeetCode submission](https://leetcode.com/problems/candy/submissions/2163599188/)

### 218. The Skyline Problem

[Problem](https://leetcode.com/problems/the-skyline-problem/) · Tags: Sweep line, Ordered multiset

Encode start positive and end negative, order same-x events descending signed height, maintain max active height, emit changes.

**Captured variants:** One observed approach.

- [Original 2153355270](originals/218__2153355270.cpp) · [LeetCode submission](https://leetcode.com/problems/the-skyline-problem/submissions/2153355270/)

### 435. Non-overlapping Intervals

[Problem](https://leetcode.com/problems/non-overlapping-intervals/) · Tags: Greedy, Intervals

Sort by end, retain earliest finishing compatible interval and count removals. The source binds last by reference to intervals[0], then assigns subsequent selected intervals through that reference, additionally overwriting the first input interval.

**Captured variants:** Two equivalent submissions.

- [Original 2167400289](originals/435__2167400289.cpp) · [LeetCode submission](https://leetcode.com/problems/non-overlapping-intervals/submissions/2167400289/)
- [Original 2139752268](originals/435__2139752268.cpp) · [LeetCode submission](https://leetcode.com/problems/non-overlapping-intervals/submissions/2139752268/)

### 729. My Calendar I

[Problem](https://leetcode.com/problems/my-calendar-i/) · Tags: Intervals, Ordered map

Disjoint interval map by start; lower_bound identifies successor, predecessor checks other possible conflict.

**Captured variants:** One observed approach.

- [Original 2152937765](originals/729__2152937765.cpp) · [LeetCode submission](https://leetcode.com/problems/my-calendar-i/submissions/2152937765/)

### 849. Maximize Distance to Closest Person

[Problem](https://leetcode.com/problems/maximize-distance-to-closest-person/) · Tags: Gap scan, Boundary cases

Tracks the previous occupied seat, uses full lengths for leading/trailing empty stretches, and half the distance for interior gaps.

**Original-code context:** Uses size_t left=-1 as an unsigned sentinel; this is intentional source behavior that should not be silently normalized.

**Captured variants:** 1 accepted C++ submission retained; distinctions are described above.

- [Original 1284774909](originals/849__1284774909.cpp) · [LeetCode submission](https://leetcode.com/problems/maximize-distance-to-closest-person/submissions/1284774909/)

### 881. Boats to Save People

[Problem](https://leetcode.com/problems/boats-to-save-people/) · Tags: Greedy, Sorting, Two pointers

Sort; lightest/heaviest pointers; pair if feasible, otherwise consume heaviest alone.

**Original-code context:** All three versions implement the same greedy idea; sorting mutates input; O(n log n).

**Captured variants:** 3 accepted C++ submissions captured; all original versions are retained.

- [Original 2147809080](originals/881__2147809080.cpp) · [LeetCode submission](https://leetcode.com/problems/boats-to-save-people/submissions/2147809080/)
- [Original 2140480045](originals/881__2140480045.cpp) · [LeetCode submission](https://leetcode.com/problems/boats-to-save-people/submissions/2140480045/)
- [Original 2140479869](originals/881__2140479869.cpp) · [LeetCode submission](https://leetcode.com/problems/boats-to-save-people/submissions/2140479869/)

### 1007. Minimum Domino Rotations For Equal Row

[Problem](https://leetcode.com/problems/minimum-domino-rotations-for-equal-row/) · Tags: Candidate restriction, Greedy

Only tops[0] and bottoms[0] can be the common value; test each candidate, reject if a domino has neither, and minimize rotation counts.

**Original-code context:** Counters named topRotation/bottomRotation count target matches on corresponding side rather than rotations of that side; min of the two remains correct.

**Captured variants:** 1 accepted C++ submission retained; distinctions are described above.

- [Original 2157541300](originals/1007__2157541300.cpp) · [LeetCode submission](https://leetcode.com/problems/minimum-domino-rotations-for-equal-row/submissions/2157541300/)

### 1520. Maximum Number of Non-Overlapping Substrings

[Problem](https://leetcode.com/problems/maximum-number-of-non-overlapping-substrings/) · Tags: Greedy, Intervals, Character spans

Collect each character first/last/count in first-appearance order; deque suffix aggregation checks whether contained character counts exactly fill its bounding interval, emits then clears.

**Captured variants:** One observed approach.

- [Original 2146064854](originals/1520__2146064854.cpp) · [LeetCode submission](https://leetcode.com/problems/maximum-number-of-non-overlapping-substrings/submissions/2146064854/)

### 1710. Maximum Units on a Truck

[Problem](https://leetcode.com/problems/maximum-units-on-a-truck/) · Tags: Greedy, Sorting

Sort by units per box ascending, traverse descending, take min(capacity, box count).

**Original-code context:** O(n log n). Subtracts full box count from remaining capacity even for final partial type; can become negative but loop immediately ends, so this does not affect result.

**Captured variants:** 1 accepted C++ submission captured; all original versions are retained.

- [Original 2119475867](originals/1710__2119475867.cpp) · [LeetCode submission](https://leetcode.com/problems/maximum-units-on-a-truck/submissions/2119475867/)

### 1877. Minimize Maximum Pair Sum in Array

[Problem](https://leetcode.com/problems/minimize-maximum-pair-sum-in-array/) · Tags: Greedy, Two pointers, Counting

Pair smallest with largest, maximizing pair sum over pairs.

**Captured variants:** [2140491975](originals/1877__2140491975.cpp) frequency buckets over min..max; [2140485732](originals/1877__2140485732.cpp) sorting and opposing pointers.

- [Original 2140491975](originals/1877__2140491975.cpp) · [LeetCode submission](https://leetcode.com/problems/minimize-maximum-pair-sum-in-array/submissions/2140491975/)
- [Original 2140491229](originals/1877__2140491229.cpp) · [LeetCode submission](https://leetcode.com/problems/minimize-maximum-pair-sum-in-array/submissions/2140491229)
- [Original 2140485732](originals/1877__2140485732.cpp) · [LeetCode submission](https://leetcode.com/problems/minimize-maximum-pair-sum-in-array/submissions/2140485732/)

### 2279. Maximum Bags With Full Capacity of Rocks

[Problem](https://leetcode.com/problems/maximum-bags-with-full-capacity-of-rocks/) · Tags: Greedy, Sorting, Capacity deficits

Pair capacity/current rocks; sort by missing capacity; spend on cheapest deficits first.

**Original-code context:** O(n log n), O(n) auxiliary pair vector; zero-deficit bags counted naturally.

**Captured variants:** 1 accepted C++ submission captured; all original versions are retained.

- [Original 2119511298](originals/2279__2119511298.cpp) · [LeetCode submission](https://leetcode.com/problems/maximum-bags-with-full-capacity-of-rocks/submissions/2119511298/)

### 2333. Minimum Sum of Squared Difference

[Problem](https://leetcode.com/problems/minimum-sum-of-squared-difference/) · Tags: Greedy, Counting

Frequency buckets lowered from largest difference to zero; batches identical greedy moves.

**Captured variants:** One observed approach.

- [Original 2168486798](originals/2333__2168486798.cpp) · [LeetCode submission](https://leetcode.com/problems/minimum-sum-of-squared-difference/submissions/2168486798/)

### 2472. Maximum Number of Non-overlapping Palindrome Substrings

[Problem](https://leetcode.com/problems/maximum-number-of-non-overlapping-palindrome-substrings/) · Tags: Greedy, Palindromes

Scan left-to-right checking only length k and k+1 palindromes, take first qualifying block, jump past it.

**Captured variants:** One greedy approach, no DP table in source.

- [Original 2143088360](originals/2472__2143088360.cpp) · [LeetCode submission](https://leetcode.com/problems/maximum-number-of-non-overlapping-palindrome-substrings/submissions/2143088360/)

### 3414. Maximum Score of Non-overlapping Intervals

[Problem](https://leetcode.com/problems/maximum-score-of-non-overlapping-intervals/) · Tags: Dynamic programming, Weighted intervals, Binary search, Tie breaking

Sort intervals by end; precompute last strictly compatible predecessor; DP over allowed count<=4 and prefix, preserving score and lexicographically smallest original-index path.

**Captured variants:** One observed approach.

- [Original 2139370298](originals/3414__2139370298.cpp) · [LeetCode submission](https://leetcode.com/problems/maximum-score-of-non-overlapping-intervals/submissions/2139370298/)

### 4059. Lexicographically Largest Power Array

[Problem](https://leetcode.com/problems/lexicographically-largest-power-array/) · Tags: Greedy, Bitwise, Partition refinement

Process bits from high to low; refine active prefix groups into ones then zeros, freezing groups after first zero block.

**Captured variants:** Two exact code duplicates.

- [Original 2147456833](originals/4059__2147456833.cpp) · [LeetCode submission](https://leetcode.com/problems/lexicographically-largest-power-array/submissions/2147456833/)
- [Original 2147456124](originals/4059__2147456124.cpp) · [LeetCode submission](https://leetcode.com/problems/lexicographically-largest-power-array/submissions/2147456124/)
