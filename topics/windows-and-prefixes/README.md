# Windows and prefixes

[All topics](../../README.md) · [Source index](../../SOURCES.md) · [Coverage](../../COVERAGE.md)

**21 captured problems · 25 accepted submission records.** Every linked implementation below is an unchanged captured source file. These notes describe the code; they do not replace it with a common API.

## Main algorithms and structures

Choose a window only when moving its boundaries has the monotonicity the proof needs. Prefix methods handle more general signed data. Here `n` is input length, `m` pattern length, `a` the character alphabet size, `W` word count, `L` word length, `u` distinct words, and `q` range updates. Space excludes returned output, but explicitly notes the captured by-value string parameters: calling them with lvalue strings can add linear copies. Hash bounds are expected-time.

| Algorithm / structure | What it maintains | Time in these implementations | Auxiliary space / copies | Direct implementation |
| --- | --- | --- | --- | --- |
| Last-seen index map | Left boundary stays after the latest duplicate inside the window | Expected O(n) | O(a) map; by-value string can add O(n) | [Distinct-character window](originals/3__2027316499.cpp) |
| Positive-sum shrinking window | Shrink while the target is reached, or while an exact target is exceeded | O(n) | O(1) | [Shortest sum threshold](originals/209__2130694109.cpp), [longest retained middle](originals/1658__2150943873.cpp) |
| Window + prefix-best DP | Best completed target-sum interval before each boundary | O(n) | O(n) DP | [Two disjoint target intervals](originals/1477__2145013796.cpp) |
| Fixed-length frequency matching | Count-map equality / zero crossings replace comparing entire windows | Expected O(n+m) | O(a) maps; by-value strings can add O(n+m); anagram output O(n) | [Permutation deficit counts](originals/567__2131779135.cpp), [anagram equality counts](originals/438__2025506346.cpp) |
| Offset-aligned word windows | Each word-length residue class is scanned in whole-word steps | Expected O((n+W)L), including string-view hashing/equality | O(u) map entries; by-value input string can add O(n), plus result indices | [Word multiset window](originals/30__2153818347.cpp) |
| Historical-maximum frequency window | Best attainable width, with a nondecreasing frequency upper bound | Expected O(n) | O(a) map; by-value string can add O(n) | [Lazy character replacement](originals/424__2131743704.cpp) |
| Exact-maximum frequency window | Current maximum frequency is recomputed after changes | Expected O(na) due to map scans; O(n) for the fixed alphabet | O(a) map; by-value string can add O(n) | [Recomputed maximum variant](originals/424__2131736709.cpp) |
| Zero-budget window | Number of zeros or remaining flips governs boundary movement | O(n) | O(1) | [Fully checked candidate windows](originals/1004__2127149237.cpp), [single-step lazy shrink](originals/1004__2027338195.cpp), [mandatory one deletion](originals/1493__2127345655.cpp) |
| Prefix-sum frequency map | Count earlier prefixes equal to current prefix minus target | Expected O(n), O(n²) pathological hashing | O(n) | [Lookup then insert](originals/560__2130713437.cpp) |
| Prefix-sum extrema | Largest absolute subarray sum is the gap between prefix extremes | O(n) | O(1) | [Minimum and maximum prefixes](originals/1749__2000684155.cpp) |
| Prefix/suffix aggregate arrays | Precompute what is excluded by one index or lies beyond a boundary | O(n) | O(n) temporary arrays; product also returns O(n) output | [Two product arrays](originals/238__2130701387.cpp), [suffix minimum + prefix maximum](originals/3904__2131704501.cpp) |
| Last-obstruction / last-required indices | Count valid starts ending at each right boundary | O(n) | O(1) | [Fixed-bound subarray count](originals/2444__2153831199.cpp) |
| Difference array + prefix reconstruction | Two endpoint edits represent each range's available coverage | O(n+q) | O(n) | [Range decrement capacity](originals/3355__2119740763.cpp), [weighted booking additions](originals/1109__2169282143.cpp) |
| Positive-product shrinking window | Count every valid suffix ending at the current right edge | O(n) | O(1) | [Product threshold](originals/713__2169623873.cpp) · [exact excerpt](snippets/positive-product-window.cpp) |
| Fixed-length predicate count / distinct-value sum | Update outgoing/incoming contributions; map size certifies distinctness | Vowels O(n); distinct sum expected O(n) | Vowels O(1) set + O(n) by-value input copy; distinct sum O(k) map | [Vowel count](originals/1456__2169572072.cpp), [distinct sum](originals/2461__2169620244.cpp) |

## Combinations and tricks

### Select the window proof before selecting the data structure

- **Recognize:** A contiguous interval must meet a sum target, and you need shortest/longest length rather than all pairs.
- **Compose:** Running sum + two forward-only pointers in [the shortest-threshold source](originals/209__2130694109.cpp) or [the longest-middle source](originals/1658__2150943873.cpp).
- **Invariant:** Positive values make expansion increase the sum and shrinking decrease it, so a discarded left endpoint never needs to return.
- **Tradeoff / trap:** This reasoning does not extend to negative values. For signed exact-sum counting, the actual [prefix-frequency implementation](originals/560__2130713437.cpp) is appropriate; for signed shortest-threshold search, see the captured [prefix deque](../monotonic-and-heaps/originals/862__2152907567.cpp). These solve different objectives, not interchangeable APIs.

### Turn two-ended removal into one retained interval

- **Recognize:** Operations remove a prefix and a suffix; minimizing removed elements is awkward if both ends are considered independently.
- **Compose:** Total sum − removed target + longest exact-sum middle window in [the end-removal source](originals/1658__2150943873.cpp).
- **Invariant:** Every allowed removal corresponds to exactly one retained contiguous middle, and minimizing removed length is maximizing retained length.
- **Tradeoff / trap:** The source handles total below the target by returning −1. A zero retained sum permits an empty middle; do not accidentally exclude that case. The positive-input contract is essential to its window scan.

### Combine a current window with an already finished optimum

- **Recognize:** Need two nonoverlapping target-sum intervals, minimizing their total length.
- **Compose:** Positive-value exact-sum window + prefix-best lengths in [the two-interval source](originals/1477__2145013796.cpp).
- **Invariant:** `dp[t]` stores the shortest target interval entirely before boundary t. A current `[left,right]` pairs only with `dp[left]`, which proves disjointness without pair enumeration.
- **Tradeoff / trap:** Carry `dp[right]` forward before considering the current window, and combine against the earlier boundary rather than the current best. The extra O(n) DP is part of the implementation; it is not a constant-space sliding window.

### Count prefix differences without counting the current prefix twice

- **Recognize:** Count all subarrays with a fixed sum, including with negative entries.
- **Compose:** Running prefix + frequency map initialized with one zero prefix in [the retained counting source](originals/560__2130713437.cpp).
- **Invariant:** Before inserting current prefix P, the map contains only earlier endpoints; occurrences of `P−target` correspond one-to-one to valid nonempty intervals ending here.
- **Tradeoff / trap:** Query before inserting, especially for target zero. The [older variant](originals/560__2025473825.cpp) uses `operator[]` for lookup and therefore creates missing zero-count keys; both variants still use O(n) space. Prefix extremes in [the absolute-sum source](originals/1749__2000684155.cpp) need only two values because they optimize a difference instead of counting every matching prefix.

### Match multisets by boundary crossings, then lift characters to words

- **Recognize:** Order inside a fixed-size window does not matter, but multiplicities do.
- **Compose:** Count maps + a matched-category counter in [anagrams](originals/438__2025506346.cpp) and [permutation detection](originals/567__2131779135.cpp); whole-word offsets + `string_view` keys in [word concatenation](originals/30__2153818347.cpp).
- **Invariant:** Entering/leaving a character updates only its equality crossing. For words, only the incoming word can create an excess count; shrink until that excess disappears, and reset at an unknown word.
- **Tradeoff / trap:** Examine both directions of a count crossing in the anagram source. Word views do not allocate substrings, but hashing/comparing L characters is still O(L); the by-value source string may be copied once. All words must have equal nonzero length, and the referenced strings must stay alive while views are stored.

### Keep a best width even when the current window is temporarily invalid

- **Recognize:** Only the maximum length matters, and a stale upper bound can safely prevent the maintained width from shrinking.
- **Compose:** Historical maximum count + single-step shrink in [replacement](originals/424__2131743704.cpp), or a lazy zero budget in [the alternative flips source](originals/1004__2027338195.cpp).
- **Invariant:** The maintained width can grow only when the budget test permits a longer candidate; once an achievable width exists, an invalid extension shifts rather than enlarges it. Historical frequency need not equal the present window's true maximum.
- **Tradeoff / trap:** Do not use the lazy window as a promised valid answer interval. The [other replacement variant](originals/424__2131736709.cpp) explicitly recomputes the maximum and shrinks fully, costing O(a) per scan. [Mandatory deletion](originals/1493__2127345655.cpp) records `right−left`, not `right−left+1`, so even an all-ones input loses one element.

### Count valid starts using the last obstruction

- **Recognize:** Every valid interval must contain both required values and exclude any value outside their bounds.
- **Compose:** Last invalid index + last minimum occurrence + last maximum occurrence in [the fixed-bounds source](originals/2444__2153831199.cpp).
- **Invariant:** For each right endpoint, valid starts lie strictly after the last invalid index and at or before the earlier of the two required occurrences. Add `max(0, min(lastMin,lastMax)−lastInvalid)`.
- **Tradeoff / trap:** This counts all starts in O(1) work without storing them. The source accumulates in `long`; its wide-count behavior depends on the target platform's `long` width, despite returning `long long`.

### Choose summaries that reconstruct exactly what the query needs

- **Recognize:** Repeated queries need all values except one position, both sides of a split, or total coverage from many ranges.
- **Compose:** [Exclusive left/right products](originals/238__2130701387.cpp), [prefix maximum + suffix minimum](originals/3904__2131704501.cpp), or [difference endpoints + prefix coverage](originals/3355__2119740763.cpp). The added [booking source](originals/1109__2169282143.cpp) uses the same endpoints with seat weights: +weight at first−1 and −weight at last, then prefixes into a separate output vector.
- **Invariant:** Product identities are 1; the stable-index comparison includes index i in both summaries; a range `[l,r]` contributes +1 at l and −1 at r+1.
- **Tradeoff / trap:** The product source really allocates two full helper arrays, not just output. Coverage describes available independent decrements, so capacity at least `nums[i]` is sufficient; it does not require applying every query to every covered element. Numeric aggregates remain the integer types shown in the originals.

### Count all endings after restoring a multiplicative invariant

- **Recognize:** All factors are positive and every suffix of a feasible window also has product below a strict threshold.
- **Compose:** Running product + shrinking left boundary + bulk suffix count in [the original product window](originals/713__2169623873.cpp).
- **Invariant:** After division restores `current < k`, exactly `right-left+1` nonempty suffixes of that window end at `right` and qualify. Each index enters and leaves once. An empty window contributes zero.
- **Tradeoff / trap:** Positivity is essential; zeros make division invalid and negative factors break monotonicity. The source retains `int` multiplication and result storage, relying on its original bounded inputs. It is the multiplicative counterpart of the positive-sum window, not a rule for arbitrary signed arrays.
- **Exact code:** [Literal product-window method](snippets/positive-product-window.cpp).

### Keep the objective and the feasibility certificate in separate summaries

- **Recognize:** Every candidate has a fixed length, but its value and validity need different information.
- **Compose:** In [distinct-window sums](originals/2461__2169620244.cpp), update a running sum and a frequency map together; erase zero counts so map size equals the number of live distinct values. [Vowel windows](originals/1456__2169572072.cpp) need only a scalar count because membership in the fixed vowel set is an independent contribution.
- **Invariant:** Both summaries describe exactly the current k elements. A length-k window is all-distinct precisely when it contains k live keys. Adding and removing the same value correctly leaves its frequency unchanged.
- **Tradeoff / trap:** Both implementations initialize the first full window and require `1 <= k <= n`. Distinct sums start their best at zero under positive-value constraints, and their subtraction occurs in `int` before reaching the `long long` accumulator. The vowel source takes its string by value and retains C++20 `contains`.
- **Exact code:** [Sum + distinctness certificate](snippets/fixed-window-distinct-sum.cpp), [incoming/outgoing predicate count](snippets/fixed-window-vowel-count.cpp).

## Problem and source appendix


All captured submissions are retained, including equivalent resubmissions and exact duplicates. Submission IDs distinguish files; they are not rankings of quality. The source itself is authoritative when a note is too brief.

### 3. Longest Substring Without Repeating Characters

[Problem](https://leetcode.com/problems/longest-substring-without-repeating-characters/) · Tags: Sliding window, Last-seen indexes

Stores the last index per character in unordered_map<char,int>. On a repeat, left=max(left,last+1); updates the best right-left+1.

**Original-code context:** Use of max prevents the left boundary moving backward.

**Captured variants:** 1 accepted C++ submission retained; distinctions are described above.

- [Original 2027316499](originals/3__2027316499.cpp) · [LeetCode submission](https://leetcode.com/problems/longest-substring-without-repeating-characters/submissions/2027316499/)

### 30. Substring with Concatenation of All Words

[Problem](https://leetcode.com/problems/substring-with-concatenation-of-all-words/) · Tags: Sliding windows, Strings, Frequency maps, Views

For every word-length offset, slide in word-sized steps and shrink only when current word count exceeds required count. Keys are string_view values into existing strings, not allocated substrings; hashing still reads word characters. The by-value input string can add a full copy.

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

Historical-maximum variants shift left once when window-maxCount>k and retain maximal feasible length. The 2131736709 variant instead recomputes max_element over the count map and fully shrinks, taking O(na) expected work for alphabet size a rather than O(n) expected map updates.

**Captured variants:** Two historical-maximum variants and one recomputed-maximum variant.

- [Original 2131743704](originals/424__2131743704.cpp) · [LeetCode submission](https://leetcode.com/problems/longest-repeating-character-replacement/submissions/2131743704/)
- [Original 2131736709](originals/424__2131736709.cpp) · [LeetCode submission](https://leetcode.com/problems/longest-repeating-character-replacement/submissions/2131736709/)
- [Original 2027329669](originals/424__2027329669.cpp) · [LeetCode submission](https://leetcode.com/problems/longest-repeating-character-replacement/submissions/2027329669/)

### 438. Find All Anagrams in a String

[Problem](https://leetcode.com/problems/find-all-anagrams-in-a-string/) · Tags: Fixed-size window, Frequency matching

Maintains orig/current unordered_map<char,int> and a count of characters whose frequencies match. Updates matches on each entering and leaving character.

**Original-code context:** Preserve both equality-crossing cases when incrementing and decrementing frequencies.

**Captured variants:** 1 accepted C++ submission retained; distinctions are described above.

- [Original 2025506346](originals/438__2025506346.cpp) · [LeetCode submission](https://leetcode.com/problems/find-all-anagrams-in-a-string/submissions/2025506346/)

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

### 713. Subarray Product Less Than K

[Problem](https://leetcode.com/problems/subarray-product-less-than-k/) · Tags: Sliding window, Positive product, Counting endings

Maintain the product of the current window, divide out its left edge while the product reaches k, and add the number of valid suffixes ending at each right edge.

**Original-code context:** O(n) time and O(1) auxiliary space. Strictly positive factors make the product monotone as the window grows and permit exact division; zero or negative inputs require a different argument. The original product and result use int. For k <= 1, emptied windows contribute zero; no special-case guard was added.

**Captured variants:** One Accepted C++ submission added on 11 October 2026.

- [Original 2169623873](originals/713__2169623873.cpp) · [LeetCode submission](https://leetcode.com/submissions/detail/2169623873/)

### 1004. Max Consecutive Ones III

[Problem](https://leetcode.com/problems/max-consecutive-ones-iii/) · Tags: Sliding windows

Track zero budget and maintain longest window; explicit shrink variant and single-step lazy-shrink variant.

**Captured variants:** [2127149237](originals/1004__2127149237.cpp) while shrink plus validity check; [2027338195](originals/1004__2027338195.cpp) mutable budget and single shrink.

- [Original 2127149237](originals/1004__2127149237.cpp) · [LeetCode submission](https://leetcode.com/problems/max-consecutive-ones-iii/submissions/2127149237/)
- [Original 2027338195](originals/1004__2027338195.cpp) · [LeetCode submission](https://leetcode.com/problems/max-consecutive-ones-iii/submissions/2027338195/)

### 1109. Corporate Flight Bookings

[Problem](https://leetcode.com/problems/corporate-flight-bookings/) · Tags: Difference array, Inclusive range updates, Prefix reconstruction

Convert each one-based inclusive booking to a positive event at first-1 and a negative event at last; prefix-sum the events into per-flight totals.

**Original-code context:** O(n+q) time for n flights and q bookings. The source allocates a separate n+1 difference vector and n-element output vector, so it uses O(n) auxiliary space plus O(n) output. The sentinel slot at index n makes bookings through the last flight safe. This is the existing difference-array idea applied to weighted additions.

**Captured variants:** One Accepted C++ submission added on 11 October 2026.

- [Original 2169282143](originals/1109__2169282143.cpp) · [LeetCode submission](https://leetcode.com/submissions/detail/2169282143/)

### 1456. Maximum Number of Vowels in a Substring of Given Length

[Problem](https://leetcode.com/problems/maximum-number-of-vowels-in-a-substring-of-given-length/) · Tags: Fixed-length window, Predicate count

Count vowels in the first k characters, then adjust one scalar for the entering and leaving characters and retain the maximum.

**Original-code context:** O(n) scan and fixed five-character set storage; the by-value string parameter can add O(n) copying time and space. The vowels member and C++20 contains call remain unchanged. Assumes 1 <= k <= s.size().

**Captured variants:** One Accepted C++ submission added on 11 October 2026.

- [Original 2169572072](originals/1456__2169572072.cpp) · [LeetCode submission](https://leetcode.com/submissions/detail/2169572072/)

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

### 1749. Maximum Absolute Sum of Any Subarray

[Problem](https://leetcode.com/problems/maximum-absolute-sum-of-any-subarray/) · Tags: Prefix-sum extrema

Tracks the minimum and maximum prefix sum starting from zero; returns their difference.

**Original-code context:** This particular implementation uses prefix extrema rather than two separate Kadane runs.

**Captured variants:** 1 accepted C++ submission retained; distinctions are described above.

- [Original 2000684155](originals/1749__2000684155.cpp) · [LeetCode submission](https://leetcode.com/problems/maximum-absolute-sum-of-any-subarray/submissions/2000684155/)

### 2444. Count Subarrays With Fixed Bounds

[Problem](https://leetcode.com/problems/count-subarrays-with-fixed-bounds/) · Tags: Sliding windows, Last-seen indices, Counting

For each right endpoint, count starts after last invalid value and no later than both latest min/max occurrences.

**Captured variants:** One observed approach.

- [Original 2153831199](originals/2444__2153831199.cpp) · [LeetCode submission](https://leetcode.com/problems/count-subarrays-with-fixed-bounds/submissions/2153831199/)

### 2461. Maximum Sum of Distinct Subarrays With Length K

[Problem](https://leetcode.com/problems/maximum-sum-of-distinct-subarrays-with-length-k/) · Tags: Fixed-length window, Frequency map, Running sum

Initialize a length-k frequency map and sum; slide by subtracting the outgoing value, adding the incoming one, and erasing zero-frequency keys. A map size of k identifies all-distinct windows.

**Original-code context:** Expected O(n) time and O(k) map space, with at most k+1 temporary keys during an update. The sum/result are long long, but the difference nums[i] - nums[i-k] is computed as int first. Requires 1 <= k <= n; result starts at zero under the original positive-value contract.

**Captured variants:** One Accepted C++ submission added on 11 October 2026.

- [Original 2169620244](originals/2461__2169620244.cpp) · [LeetCode submission](https://leetcode.com/submissions/detail/2169620244/)

### 3355. Zero Array Transformation I

[Problem](https://leetcode.com/problems/zero-array-transformation-i/) · Tags: Difference array, Prefix sums

Range-difference array, prefix-sum available decrement coverage, require coverage>=nums[i].

**Original-code context:** O(n+q), O(n); this is capacity comparison, not applying every query decrement compulsorily.

**Captured variants:** 1 accepted C++ submission captured; all original versions are retained.

- [Original 2119740763](originals/3355__2119740763.cpp) · [LeetCode submission](https://leetcode.com/problems/zero-array-transformation-i/submissions/2119740763/)

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
