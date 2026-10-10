# Search and sort

[All topics](../../README.md) · [Source index](../../SOURCES.md) · [Coverage](../../COVERAGE.md)

**21 captured problems · 51 accepted submission records.** Every linked implementation below is an unchanged captured source file. These notes describe the code; they do not replace it with a common API.

## Pattern reminders

### Binary-search boundaries

- **Cue:** The answer is a first feasible value, an insertion position, or a location in sorted data.
- **Idea and invariant:** Each loop preserves a candidate interval and removes only positions whose comparison or feasibility result rules them out. 410 searches a maximum partition sum, 1011 a capacity, and 875 a speed; their feasibility checks scan the input.
- **Cost in these sources:** Ordinary search is O(log n). Answer search is O(n log R), where R is the searched numeric range. The implementations usually use O(1) auxiliary space.
- **Read the originals:** [35. Search Insert Position — 2146678224](originals/35__2146678224.cpp); [704. Binary Search — 2146675354](originals/704__2146675354.cpp); [410. Split Array Largest Sum — 2146752727](originals/410__2146752727.cpp); [1011. Capacity To Ship Packages Within D Days — 2146696311](originals/1011__2146696311.cpp); [875. Koko Eating Bananas — 2146691389](originals/875__2146691389.cpp).

### Search after identifying structure

- **Cue:** A mountain, rotation, or two-array partition exposes a locally monotone decision.
- **Idea and invariant:** 4 partitions the shorter array and checks the two cross-boundaries. 1095 locates the mountain peak before searching slopes. 33 finds a pivot and searches virtual sorted indices. 81 must shrink equal ambiguous boundaries.
- **Cost in these sources:** 4 is O(log min(m,n)); the mountain and distinct rotated searches are O(log n). Duplicate-heavy 81 can degrade to O(n).
- **Read the originals:** [4. Median of Two Sorted Arrays — 2147722433](originals/4__2147722433.cpp); [1095. Find in Mountain Array — 2147557289](originals/1095__2147557289.cpp); [33. Search in Rotated Sorted Array — 2146701709](originals/33__2146701709.cpp); [81. Search in Rotated Sorted Array II — 2146739961](originals/81__2146739961.cpp).

### Selection versus full ordering

- **Cue:** Only one rank or the top k values are needed.
- **Idea and invariant:** 215 and 347 include partition-based selection; only the partition containing the target rank is pursued. Other captured variants use a full heap, sorting, or a bounded ordered set, with different operation costs.
- **Cost in these sources:** Partition selection is O(n) on favorable/average partitions and O(n squared) worst case; these sources use deterministic pivots. Full sort is O(n log n), full heap extraction depends on extracted count, and a bounded size-k set costs O(n log k) after frequency counting.
- **Read the originals:** [215. Kth Largest Element in an Array — 2144679787](originals/215__2144679787.cpp); [347. Top K Frequent Elements — 2133013441](originals/347__2133013441.cpp); [658. Find K Closest Elements — 2127298849](originals/658__2127298849.cpp).

### Counting across sorted halves

- **Cue:** The pair predicate becomes monotone after sorting two halves.
- **Idea and invariant:** 493 counts cross-half pairs satisfying left > 2 * right with a separate advancing pointer before the ordinary merge. Counting uses widened arithmetic in the captured comparison.
- **Cost in these sources:** O(n log n) time, O(n) merge storage, and O(log n) recursion depth.
- **Read the originals:** [493. Reverse Pairs — 2150875619](originals/493__2150875619.cpp).

### Use values as positions

- **Cue:** Relevant values are restricted to a small indexable range.
- **Idea and invariant:** 41 discards out-of-range values and marks seen positions by sign. 287 has a sign-marking solution plus captured set-based alternatives. These original algorithms can mutate the input.
- **Cost in these sources:** The sign-marking solutions take O(n) time and O(1) auxiliary space; hash-based variants store up to O(n) values.
- **Read the originals:** [41. First Missing Positive — 2142829718](originals/41__2142829718.cpp); [287. Find the Duplicate Number — 2143946691](originals/287__2143946691.cpp).

## Complete problem and variant index

All captured submissions are retained, including equivalent resubmissions and exact duplicates. Submission IDs distinguish files; they are not rankings of quality. The source itself is authoritative when a note is too brief.

### 4. Median of Two Sorted Arrays

[Problem](https://leetcode.com/problems/median-of-two-sorted-arrays/) · Tags: Binary search, Order statistics

Partition smaller sorted array so left side has ceil(total/2), enforce maxLeft<=minRight across both arrays.

**Captured variants:** Three equivalent partition implementations, with names/comments/return fallback changes.

- [Original 2147722433](originals/4__2147722433.cpp) · [LeetCode submission](https://leetcode.com/problems/median-of-two-sorted-arrays/submissions/2147722433/)
- [Original 2147703761](originals/4__2147703761.cpp) · [LeetCode submission](https://leetcode.com/problems/median-of-two-sorted-arrays/submissions/2147703761/)
- [Original 1621118867](originals/4__1621118867.cpp) · [LeetCode submission](https://leetcode.com/problems/median-of-two-sorted-arrays/submissions/1621118867/)

### 33. Search in Rotated Sorted Array

[Problem](https://leetcode.com/problems/search-in-rotated-sorted-array/) · Tags: Binary search, Rotated arrays

Find rotation pivot, then binary-search virtual sorted indices mapped by modulo.

**Captured variants:** Three pivot-plus-search submissions; two older correct midpoint implementations.

- [Original 2146701709](originals/33__2146701709.cpp) · [LeetCode submission](https://leetcode.com/problems/search-in-rotated-sorted-array/submissions/2146701709/)
- [Original 2125939691](originals/33__2125939691.cpp) · [LeetCode submission](https://leetcode.com/problems/search-in-rotated-sorted-array/submissions/2125939691/)
- [Original 2011698957](originals/33__2011698957.cpp) · [LeetCode submission](https://leetcode.com/problems/search-in-rotated-sorted-array/submissions/2011698957/)

### 35. Search Insert Position

[Problem](https://leetcode.com/problems/search-insert-position/) · Tags: Binary search, Lower bound

Inclusive search eliminates >=target to the right and returns insertion index left.

**Captured variants:** One observed approach.

- [Original 2146678224](originals/35__2146678224.cpp) · [LeetCode submission](https://leetcode.com/problems/search-insert-position/submissions/2146678224/)

### 41. First Missing Positive

[Problem](https://leetcode.com/problems/first-missing-positive/) · Tags: In-place marking, Hash maps

Normalize outside [1,n] to n+1, mark seen values by negating slot value-1, return first positive slot. Older builds membership map and scans positive candidates.

**Captured variants:** [2142829718](originals/41__2142829718.cpp) bounded sign marking; [2142586270](originals/41__2142586270.cpp)/[1214762629](originals/41__1214762629.cpp) membership map candidate scan.

- [Original 2142829718](originals/41__2142829718.cpp) · [LeetCode submission](https://leetcode.com/problems/first-missing-positive/submissions/2142829718/)
- [Original 2142586270](originals/41__2142586270.cpp) · [LeetCode submission](https://leetcode.com/problems/first-missing-positive/submissions/2142586270/)
- [Original 1214762629](originals/41__1214762629.cpp) · [LeetCode submission](https://leetcode.com/problems/first-missing-positive/submissions/1214762629/)

### 69. Sqrt(x)

[Problem](https://leetcode.com/problems/sqrtx/) · Tags: Binary search, Integer arithmetic

Inclusive binary search for floor square root; return last feasible right boundary.

**Captured variants:** One observed approach.

- [Original 2146686635](originals/69__2146686635.cpp) · [LeetCode submission](https://leetcode.com/problems/sqrtx/submissions/2146686635/)

### 74. Search a 2D Matrix

[Problem](https://leetcode.com/problems/search-a-2d-matrix/) · Tags: Binary search, Index mapping

Binary search row-major matrix as virtual flat array.

**Captured variants:** Two equivalent submissions.

- [Original 2146688351](originals/74__2146688351.cpp) · [LeetCode submission](https://leetcode.com/problems/search-a-2d-matrix/submissions/2146688351/)
- [Original 2127411724](originals/74__2127411724.cpp) · [LeetCode submission](https://leetcode.com/problems/search-a-2d-matrix/submissions/2127411724/)

### 81. Search in Rotated Sorted Array II

[Problem](https://leetcode.com/problems/search-in-rotated-sorted-array-ii/) · Tags: Binary search, Rotated arrays

Shrink ambiguous equal boundaries; otherwise identify sorted half and retain matching target interval.

**Captured variants:** Two equivalent variants.

- [Original 2146739961](originals/81__2146739961.cpp) · [LeetCode submission](https://leetcode.com/problems/search-in-rotated-sorted-array-ii/submissions/2146739961/)
- [Original 2146727441](originals/81__2146727441.cpp) · [LeetCode submission](https://leetcode.com/problems/search-in-rotated-sorted-array-ii/submissions/2146727441/)

### 153. Find Minimum in Rotated Sorted Array

[Problem](https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/) · Tags: Binary search, Rotated arrays

Find first index on low sorted run by comparing middle with fixed final value or current right value.

**Captured variants:** [2146698709](originals/153__2146698709.cpp) compares nums.back(); [2024485741](originals/153__2024485741.cpp) compares nums[right].

- [Original 2146698709](originals/153__2146698709.cpp) · [LeetCode submission](https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/submissions/2146698709/)
- [Original 2127418311](originals/153__2127418311.cpp) · [LeetCode submission](https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/submissions/2127418311/)
- [Original 2024485741](originals/153__2024485741.cpp) · [LeetCode submission](https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/submissions/2024485741/)

### 215. Kth Largest Element in an Array

[Problem](https://leetcode.com/problems/kth-largest-element-in-an-array/) · Tags: Quickselect, Sorting, Heaps

Hoare-style partition around middle element, recurse only partition containing zero-based target n-k; alternatives sort and max heap.

**Captured variants:** Five quickselect variants differ only base cases/return style; [2132966164](originals/215__2132966164.cpp) full sort; [2132965197](originals/215__2132965197.cpp) full max heap.

- [Original 2144679787](originals/215__2144679787.cpp) · [LeetCode submission](https://leetcode.com/problems/kth-largest-element-in-an-array/submissions/2144679787/)
- [Original 2144679621](originals/215__2144679621.cpp) · [LeetCode submission](https://leetcode.com/problems/kth-largest-element-in-an-array/submissions/2144679621/)
- [Original 2144679073](originals/215__2144679073.cpp) · [LeetCode submission](https://leetcode.com/problems/kth-largest-element-in-an-array/submissions/2144679073/)
- [Original 2144678866](originals/215__2144678866.cpp) · [LeetCode submission](https://leetcode.com/problems/kth-largest-element-in-an-array/submissions/2144678866/)
- [Original 2132995910](originals/215__2132995910.cpp) · [LeetCode submission](https://leetcode.com/problems/kth-largest-element-in-an-array/submissions/2132995910/)
- [Original 2132966164](originals/215__2132966164.cpp) · [LeetCode submission](https://leetcode.com/problems/kth-largest-element-in-an-array/submissions/2132966164/)
- [Original 2132965197](originals/215__2132965197.cpp) · [LeetCode submission](https://leetcode.com/problems/kth-largest-element-in-an-array/submissions/2132965197/)

### 287. Find the Duplicate Number

[Problem](https://leetcode.com/problems/find-the-duplicate-number/) · Tags: In-place marking, Hash sets

Latest marks sign at value-1 to detect repeated value; older uses seen set.

**Captured variants:** [2143946691](originals/287__2143946691.cpp) sign marking; three seen-set variants, two exact duplicates.

- [Original 2143946691](originals/287__2143946691.cpp) · [LeetCode submission](https://leetcode.com/problems/find-the-duplicate-number/submissions/2143946691/)
- [Original 2143814563](originals/287__2143814563.cpp) · [LeetCode submission](https://leetcode.com/problems/find-the-duplicate-number/submissions/2143814563/)
- [Original 2140565463](originals/287__2140565463.cpp) · [LeetCode submission](https://leetcode.com/problems/find-the-duplicate-number/submissions/2140565463/)
- [Original 1212846979](originals/287__1212846979.cpp) · [LeetCode submission](https://leetcode.com/problems/find-the-duplicate-number/submissions/1212846979/)

### 344. Reverse String

[Problem](https://leetcode.com/problems/reverse-string/) · Tags: Two pointers

Swap inward in place.

**Captured variants:** One approach.

- [Original 2147725168](originals/344__2147725168.cpp) · [LeetCode submission](https://leetcode.com/problems/reverse-string/submissions/2147725168/)

### 347. Top K Frequent Elements

[Problem](https://leetcode.com/problems/top-k-frequent-elements/) · Tags: Quickselect, Heaps, Ordered sets, Frequency maps

Count values then select top k by frequency; actual alternatives full max heap and bounded ordered set.

**Captured variants:** [2133013441](originals/347__2133013441.cpp) quickselect; [2127429766](originals/347__2127429766.cpp) full max heap; [2025491048](originals/347__2025491048.cpp) bounded size-k set.

- [Original 2133013441](originals/347__2133013441.cpp) · [LeetCode submission](https://leetcode.com/problems/top-k-frequent-elements/submissions/2133013441/)
- [Original 2127429766](originals/347__2127429766.cpp) · [LeetCode submission](https://leetcode.com/problems/top-k-frequent-elements/submissions/2127429766/)
- [Original 2025491048](originals/347__2025491048.cpp) · [LeetCode submission](https://leetcode.com/problems/top-k-frequent-elements/submissions/2025491048/)

### 374. Guess Number Higher or Lower

[Problem](https://leetcode.com/problems/guess-number-higher-or-lower/) · Tags: Binary search, Interactive APIs

Inclusive search steered by sign of guess(mid).

**Captured variants:** One observed approach.

- [Original 2146681577](originals/374__2146681577.cpp) · [LeetCode submission](https://leetcode.com/problems/guess-number-higher-or-lower/submissions/2146681577/)

### 410. Split Array Largest Sum

[Problem](https://leetcode.com/problems/split-array-largest-sum/) · Tags: Binary search, Greedy feasibility

First feasible maximum partition sum, using greedy breaks; predicate currently returns true when infeasible.

**Captured variants:** Three equivalent approaches, one extra unused vector.

- [Original 2146752727](originals/410__2146752727.cpp) · [LeetCode submission](https://leetcode.com/problems/split-array-largest-sum/submissions/2146752727/)
- [Original 2139584888](originals/410__2139584888.cpp) · [LeetCode submission](https://leetcode.com/problems/split-array-largest-sum/submissions/2139584888/)
- [Original 2139584401](originals/410__2139584401.cpp) · [LeetCode submission](https://leetcode.com/problems/split-array-largest-sum/submissions/2139584401/)

### 493. Reverse Pairs

[Problem](https://leetcode.com/problems/reverse-pairs/) · Tags: Merge sort, Pair counting

Sort halves recursively, count cross pairs with monotone two pointers against 2*right, then ordinary merge.

**Captured variants:** One source; separate counting pass before merge.

- [Original 2150875619](originals/493__2150875619.cpp) · [LeetCode submission](https://leetcode.com/problems/reverse-pairs/submissions/2150875619/)

### 658. Find K Closest Elements

[Problem](https://leetcode.com/problems/find-k-closest-elements/) · Tags: Two pointers, Heaps, Selection

Sorted array drops farther endpoint until k remain; older keeps closest k by max heap of (distance,value), then sorts.

**Captured variants:** [2127298849](originals/658__2127298849.cpp) two-pointer trimming; [2127164573](originals/658__2127164573.cpp) bounded max heap.

- [Original 2127298849](originals/658__2127298849.cpp) · [LeetCode submission](https://leetcode.com/problems/find-k-closest-elements/submissions/2127298849/)
- [Original 2127164573](originals/658__2127164573.cpp) · [LeetCode submission](https://leetcode.com/problems/find-k-closest-elements/submissions/2127164573/)

### 704. Binary Search

[Problem](https://leetcode.com/problems/binary-search/) · Tags: Binary search

Inclusive exact-match search returning -1 when absent.

**Captured variants:** One observed approach.

- [Original 2146675354](originals/704__2146675354.cpp) · [LeetCode submission](https://leetcode.com/problems/binary-search/submissions/2146675354/)

### 852. Peak Index in a Mountain Array

[Problem](https://leetcode.com/problems/peak-index-in-a-mountain-array/) · Tags: Binary search, Unimodal search

Compare midpoint with neighbors to choose mountain slope or identify peak.

**Captured variants:** Two equivalent submissions except unreachable/fallback return.

- [Original 2147513687](originals/852__2147513687.cpp) · [LeetCode submission](https://leetcode.com/problems/peak-index-in-a-mountain-array/submissions/2147513687/)
- [Original 2147512689](originals/852__2147512689.cpp) · [LeetCode submission](https://leetcode.com/problems/peak-index-in-a-mountain-array/submissions/2147512689/)

### 875. Koko Eating Bananas

[Problem](https://leetcode.com/problems/koko-eating-bananas/) · Tags: Binary search, Integer arithmetic

First feasible speed with sum of integer ceilings.

**Captured variants:** Four equivalent first-true variants; latest includes early false.

- [Original 2146691389](originals/875__2146691389.cpp) · [LeetCode submission](https://leetcode.com/problems/koko-eating-bananas/submissions/2146691389/)
- [Original 2139503155](originals/875__2139503155.cpp) · [LeetCode submission](https://leetcode.com/problems/koko-eating-bananas/submissions/2139503155/)
- [Original 2139502841](originals/875__2139502841.cpp) · [LeetCode submission](https://leetcode.com/problems/koko-eating-bananas/submissions/2139502841/)
- [Original 2024503988](originals/875__2024503988.cpp) · [LeetCode submission](https://leetcode.com/problems/koko-eating-bananas/submissions/2024503988/)

### 1011. Capacity To Ship Packages Within D Days

[Problem](https://leetcode.com/problems/capacity-to-ship-packages-within-d-days/) · Tags: Binary search, Greedy feasibility

First feasible capacity between maximum weight and total weight; simulate sequential loading.

**Captured variants:** [2146696311](originals/1011__2146696311.cpp) closed first-true while left<right; [2024526301](originals/1011__2024526301.cpp) inclusive elimination while low<=high returns low.

- [Original 2146696311](originals/1011__2146696311.cpp) · [LeetCode submission](https://leetcode.com/problems/capacity-to-ship-packages-within-d-days/submissions/2146696311/)
- [Original 2024526301](originals/1011__2024526301.cpp) · [LeetCode submission](https://leetcode.com/problems/capacity-to-ship-packages-within-d-days/submissions/2024526301/)

### 1095. Find in Mountain Array

[Problem](https://leetcode.com/problems/find-in-mountain-array/) · Tags: Binary search, Unimodal search

Find peak, binary-search ascending half first then descending half.

**Captured variants:** [2147557289](originals/1095__2147557289.cpp) binary peak; [2147556354](originals/1095__2147556354.cpp) ternary peak narrowing accepted but has fragile endpoint handling.

- [Original 2147557289](originals/1095__2147557289.cpp) · [LeetCode submission](https://leetcode.com/problems/find-in-mountain-array/submissions/2147557289/)
- [Original 2147556354](originals/1095__2147556354.cpp) · [LeetCode submission](https://leetcode.com/problems/find-in-mountain-array/submissions/2147556354/)
