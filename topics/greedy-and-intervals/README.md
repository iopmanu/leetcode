# Greedy and intervals

[All topics](../../README.md) · [Source index](../../SOURCES.md) · [Coverage](../../COVERAGE.md)

**19 captured problems · 29 accepted submission records.** Every linked implementation below is an unchanged captured source file. These notes describe the code; they do not replace it with a common API.

## Pattern reminders

### Sort by the boundary that determines compatibility

- **Cue:** Choose non-overlapping intervals or merge intervals that touch or overlap.
- **Idea and invariant:** 435 keeps the earliest ending compatible interval. 56 extends the most recent merged interval. 57 binary-searches the overlapping block in sorted disjoint intervals, then erases/inserts it. 729 checks neighboring stored intervals around lower_bound.
- **Cost in these sources:** 435 and 56: O(n log n) including sort. 57 has O(log n) boundary searches but O(n) vector movement, and one variant also sorts. 729: O(log n) per booking in an ordered map.
- **Read the originals:** [435. Non-overlapping Intervals — 2167400289](originals/435__2167400289.cpp); [56. Merge Intervals — 2167385466](originals/56__2167385466.cpp); [57. Insert Interval — 2167382205](originals/57__2167382205.cpp); [729. My Calendar I — 2152937765](originals/729__2152937765.cpp).

### Local inequalities in both directions

- **Cue:** A global assignment is forced by comparisons with neighboring values.
- **Idea and invariant:** 135 starts each child at one candy, enforces the left-neighbor constraint, then enforces the right-neighbor constraint with max. 121 remembers the cheapest earlier buying price. 1877 pairs opposite extremes, with both sorting and frequency-bucket source variants.
- **Cost in these sources:** 135: O(n) time and O(n) storage. 121: O(n) time and O(1) state. 1877 sorting: O(n log n); bucket scanning depends on n and the value range.
- **Read the originals:** [135. Candy — 2163599188](originals/135__2163599188.cpp); [121. Best Time to Buy and Sell Stock — 2127314016](originals/121__2127314016.cpp); [1877. Minimize Maximum Pair Sum in Array — 2140491975](originals/1877__2140491975.cpp).

### Batch identical greedy moves

- **Cue:** The best next operation repeatedly targets the currently largest value.
- **Idea and invariant:** 2333 stores counts of absolute differences and moves a whole available count down one level before visiting the next level. Lowering the largest difference yields the largest decrease in its square.
- **Cost in these sources:** O(n+D) expected time for maximum difference D, rather than one iteration per allowed operation; bucket keys can occupy O(D) space in the captured hash-map scan.
- **Read the originals:** [2333. Minimum Sum of Squared Difference — 2168486798](originals/2333__2168486798.cpp).

### Active events versus compatible predecessors

- **Cue:** The question concerns all active intervals, or weighted choices among compatible earlier intervals.
- **Idea and invariant:** 218 sweeps signed start/end events and emits changes in the active maximum height. 3414 sorts by end, finds the last strictly compatible predecessor, and retains the best score plus lexicographic index tie-break for up to four chosen intervals.
- **Cost in these sources:** 218: O(n log n) time and O(n) active/event storage. 3414: O(n log n) including predecessor searches, with O(n) DP state because the chosen-count bound is four.
- **Read the originals:** [218. The Skyline Problem — 2153355270](originals/218__2153355270.cpp); [3414. Maximum Score of Non-overlapping Intervals — 2139370298](originals/3414__2139370298.cpp).

### Take the earliest qualifying block

- **Cue:** Later choices only need the suffix after the chosen block.
- **Idea and invariant:** 2472 tests palindromes of length k and k+1 and jumps past an accepted block. The source checks palindromes directly; it does not build a palindrome DP table.
- **Cost in these sources:** O(nk) worst-case character comparisons for direct palindrome tests and O(1) auxiliary state.
- **Read the originals:** [2472. Maximum Number of Non-overlapping Palindrome Substrings — 2143088360](originals/2472__2143088360.cpp).

## Complete problem and variant index

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

Sort by end, retain earliest finishing compatible interval and count removals.

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
