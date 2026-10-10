# Windows and prefixes

[All topics](../../README.md) · [Source index](../../SOURCES.md) · [Coverage](../../COVERAGE.md)

**13 captured problems · 17 accepted submission records.** Every linked implementation below is an unchanged captured source file. These notes describe the code; they do not replace it with a common API.

## Pattern reminders

### Prefix cancellation

- **Cue:** A subarray sum becomes a difference of two prefix values.
- **Idea and invariant:** 560 counts previous prefixes equal to current minus target before recording the current prefix. The zero prefix is present once, allowing subarrays beginning at index zero. 238 separately accumulates products on each side of an index.
- **Cost in these sources:** 560: expected O(n) time and O(n) hash-map storage. 238: O(n) time and O(n) prefix/suffix storage in the captured source.
- **Read the originals:** [560. Subarray Sum Equals K — 2130713437](originals/560__2130713437.cpp); [238. Product of Array Except Self — 2130701387](originals/238__2130701387.cpp).

### Positive-value windows

- **Cue:** Expanding increases the sum and moving left decreases it.
- **Idea and invariant:** 209 shrinks while the target is met. 1658 converts removing two ends into keeping the longest middle with sum total minus x. 1477 combines the current target-sum window with the best earlier disjoint one. Positivity supplies the required monotonicity.
- **Cost in these sources:** O(n) time because each pointer only advances. 209 and 1658 use O(1) window state; 1477 keeps O(n) prefix-best state.
- **Read the originals:** [209. Minimum Size Subarray Sum — 2130694109](originals/209__2130694109.cpp); [1658. Minimum Operations to Reduce X to Zero — 2150943873](originals/1658__2150943873.cpp); [1477. Find Two Non-overlapping Sub-arrays Each With Target Sum — 2145013796](originals/1477__2145013796.cpp).

### Character counts and controlled invalidity

- **Cue:** A window has a fixed multiset, a bounded replacement budget, or a bounded number of zeros.
- **Idea and invariant:** 567 tracks a fixed-length permutation window. 30 scans each word-length offset in whole-word steps. 424 keeps a historical maximum frequency; 1493 and one 1004 variant use single-step lazy shrink, so their current window is not always an ordinary fully valid window.
- **Cost in these sources:** Character/zero windows are linear time with alphabet-sized or constant state. 30 advances O(n) word steps across offsets, but substring construction and hashing cost O(word length) per step.
- **Read the originals:** [567. Permutation in String — 2131779135](originals/567__2131779135.cpp); [30. Substring with Concatenation of All Words — 2153818347](originals/30__2153818347.cpp); [424. Longest Repeating Character Replacement — 2131743704](originals/424__2131743704.cpp); [1493. Longest Subarray of 1's After Deleting One Element — 2127345655](originals/1493__2127345655.cpp); [1004. Max Consecutive Ones III — 2127149237](originals/1004__2127149237.cpp).

### Remember the last obstruction

- **Cue:** Count valid starts for every right endpoint without enumerating subarrays.
- **Idea and invariant:** 2444 keeps the last invalid element and latest occurrences of both required bounds. Valid starts lie after the invalid position and no later than both bound positions. 3903 and 3904 combine prefix maximum with precomputed suffix minimum.
- **Cost in these sources:** 2444: O(n) time and O(1) state. The stable-index implementations: O(n) time and O(n) suffix storage.
- **Read the originals:** [2444. Count Subarrays With Fixed Bounds — 2153831199](originals/2444__2153831199.cpp); [3903. Smallest Stable Index I — 2130500850](originals/3903__2130500850.cpp); [3904. Smallest Stable Index II — 2131704501](originals/3904__2131704501.cpp).

## Complete problem and variant index

All captured submissions are retained, including equivalent resubmissions and exact duplicates. Submission IDs distinguish files; they are not rankings of quality. The source itself is authoritative when a note is too brief.

### 30. Substring with Concatenation of All Words

[Problem](https://leetcode.com/problems/substring-with-concatenation-of-all-words/) · Tags: Sliding windows, Strings, Frequency maps, Views

For every word-length offset, slide in word-sized steps and shrink only when current word count exceeds required count.

**Captured variants:** One observed approach.

- [Original 2153818347](originals/30__2153818347.cpp) · [LeetCode submission](https://leetcode.com/problems/substring-with-concatenation-of-all-words/submissions/2153818347/)

### 209. Minimum Size Subarray Sum

[Problem](https://leetcode.com/problems/minimum-size-subarray-sum/) · Tags: Sliding windows

Expand positive-number sum, shrink while reaching target, record shortest.

**Captured variants:** One observed approach.

- [Original 2130694109](originals/209__2130694109.cpp) · [LeetCode submission](https://leetcode.com/problems/minimum-size-subarray-sum/submissions/2130694109/)

### 238. Product of Array Except Self

[Problem](https://leetcode.com/problems/product-of-array-except-self/) · Tags: Prefix/suffix aggregates

Build explicit left and right product arrays with identity 1, multiply exclusive prefixes/suffixes.

**Captured variants:** One observed approach.

- [Original 2130701387](originals/238__2130701387.cpp) · [LeetCode submission](https://leetcode.com/problems/product-of-array-except-self/submissions/2130701387/)

### 424. Longest Repeating Character Replacement

[Problem](https://leetcode.com/problems/longest-repeating-character-replacement/) · Tags: Sliding windows, Stale maximum

Maintain maximum character count seen while expanding; shift left once when window-maxCount>k, retain maximal feasible length.

**Captured variants:** One observed approach.

- [Original 2131743704](originals/424__2131743704.cpp) · [LeetCode submission](https://leetcode.com/problems/longest-repeating-character-replacement/submissions/2131743704/)
- [Original 2131736709](originals/424__2131736709.cpp) · [LeetCode submission](https://leetcode.com/problems/longest-repeating-character-replacement/submissions/2131736709/)
- [Original 2027329669](originals/424__2027329669.cpp) · [LeetCode submission](https://leetcode.com/problems/longest-repeating-character-replacement/submissions/2027329669/)

### 560. Subarray Sum Equals K

[Problem](https://leetcode.com/problems/subarray-sum-equals-k/) · Tags: Prefix sums, Hash maps, Counting

Count prior prefixes equal current-k before adding current; zero prefix seeded once.

**Captured variants:** Two equivalent sources; latest find avoids inserting missing queried sums.

- [Original 2130713437](originals/560__2130713437.cpp) · [LeetCode submission](https://leetcode.com/problems/subarray-sum-equals-k/submissions/2130713437/)
- [Original 2025473825](originals/560__2025473825.cpp) · [LeetCode submission](https://leetcode.com/problems/subarray-sum-equals-k/submissions/2025473825/)

### 567. Permutation in String

[Problem](https://leetcode.com/problems/permutation-in-string/) · Tags: Sliding windows, Frequency deficit

Maintain fixed-length window, decrement requirement deficits on entering, increment on leaving; count distinct requirements that have become satisfied.

**Captured variants:** One observed approach.

- [Original 2131779135](originals/567__2131779135.cpp) · [LeetCode submission](https://leetcode.com/problems/permutation-in-string/submissions/2131779135/)

### 1004. Max Consecutive Ones III

[Problem](https://leetcode.com/problems/max-consecutive-ones-iii/) · Tags: Sliding windows

Track zero budget and maintain longest window; explicit shrink variant and single-step lazy-shrink variant.

**Captured variants:** [2127149237](originals/1004__2127149237.cpp) while shrink plus validity check; [2027338195](originals/1004__2027338195.cpp) mutable budget and single shrink.

- [Original 2127149237](originals/1004__2127149237.cpp) · [LeetCode submission](https://leetcode.com/problems/max-consecutive-ones-iii/submissions/2127149237/)
- [Original 2027338195](originals/1004__2027338195.cpp) · [LeetCode submission](https://leetcode.com/problems/max-consecutive-ones-iii/submissions/2027338195/)

### 1477. Find Two Non-overlapping Sub-arrays Each With Target Sum

[Problem](https://leetcode.com/problems/find-two-non-overlapping-sub-arrays-each-with-target-sum/) · Tags: Sliding windows, Dynamic programming, Prefix best

Find target-sum positive windows; dp[prefix] stores shortest prior target window, combine current with dp[left] for nonoverlap.

**Captured variants:** One observed approach.

- [Original 2145013796](originals/1477__2145013796.cpp) · [LeetCode submission](https://leetcode.com/problems/find-two-non-overlapping-sub-arrays-each-with-target-sum/submissions/2145013796/)

### 1493. Longest Subarray of 1's After Deleting One Element

[Problem](https://leetcode.com/problems/longest-subarray-of-1s-after-deleting-one-element/) · Tags: Sliding windows, Lazy shrink

Track at most one zero, shift left once when invalid, record window length minus required deletion.

**Captured variants:** One observed approach.

- [Original 2127345655](originals/1493__2127345655.cpp) · [LeetCode submission](https://leetcode.com/problems/longest-subarray-of-1s-after-deleting-one-element/submissions/2127345655/)

### 1658. Minimum Operations to Reduce X to Zero

[Problem](https://leetcode.com/problems/minimum-operations-to-reduce-x-to-zero/) · Tags: Sliding windows, Complement transformation

Removing prefix and suffix becomes keeping longest middle subarray of sum total-x; positive-value sliding window finds it.

**Captured variants:** One observed approach.

- [Original 2150943873](originals/1658__2150943873.cpp) · [LeetCode submission](https://leetcode.com/problems/minimum-operations-to-reduce-x-to-zero/submissions/2150943873/)

### 2444. Count Subarrays With Fixed Bounds

[Problem](https://leetcode.com/problems/count-subarrays-with-fixed-bounds/) · Tags: Sliding windows, Last-seen indices, Counting

For each right endpoint, count starts after last invalid value and no later than both latest min/max occurrences.

**Captured variants:** One observed approach.

- [Original 2153831199](originals/2444__2153831199.cpp) · [LeetCode submission](https://leetcode.com/problems/count-subarrays-with-fixed-bounds/submissions/2153831199/)

### 3903. Smallest Stable Index I

[Problem](https://leetcode.com/problems/smallest-stable-index-i/) · Tags: Prefix/suffix aggregates

Suffix-minimum array plus running prefix maximum tests first stable boundary.

**Captured variants:** Same approach as 3904, different initialization.

- [Original 2130500850](originals/3903__2130500850.cpp) · [LeetCode submission](https://leetcode.com/problems/smallest-stable-index-i/submissions/2130500850/)

### 3904. Smallest Stable Index II

[Problem](https://leetcode.com/problems/smallest-stable-index-ii/) · Tags: Prefix/suffix aggregates

Precompute suffix minima, scan prefix maximum, return first boundary where their gap<=k.

**Captured variants:** Same structural approach as 3903.

- [Original 2131704501](originals/3904__2131704501.cpp) · [LeetCode submission](https://leetcode.com/problems/smallest-stable-index-ii/submissions/2131704501/)
