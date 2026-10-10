# Windows and prefixes

Your recurring move is to store just enough history: frequency deficits, a last-invalid boundary, or counts of previous prefix sums. All examples below come from your submitted code.

## Choose the invariant first

| Situation | State to keep | Template | Time / extra space |
|---|---|---|---|
| Shortest substring containing a multiset | Required counts minus window counts | `minWindow` (76) | O(n+m) / O(256) |
| Exact multiset in a fixed-size window | Same deficits plus window length | `containsPermutation` (567) | O(n+m) / O(256) |
| Longest substring with at most k replacements | Frequencies and historical maximum | `longestReplacementWindow` (424) | O(n) / O(256) |
| At most k zeroes | Count zeroes, shrink until valid | `longestOnes` (1004) | O(n) / O(1) |
| Delete exactly one element | At most one zero, subtract one | `longestOnesAfterDeletion` (1493) | O(n) / O(1) |
| Shortest sum at least target, nonnegative values | Current sum; shrink while sufficient | `minSubarrayLength` (209) | O(n) / O(1) |
| Remove from two ends | Keep the longest middle summing to total−x | `minEndRemovals` (1658) | O(n) / O(1) |
| Count target sums, including negative values | Counts of earlier prefix sums | `countSubarraysSum` (560) | Expected O(n) / O(n) |
| Both exact extrema required | Last invalid, last minimum, last maximum | `countFixedBoundSubarrays` (2444) | O(n) / O(1) |
| Product excluding one index | Exclusive prefix × exclusive suffix | `productExceptSelf` (238) | O(n) / O(n) |
| Two disjoint target-sum windows | Current positive window + best earlier length | `minTwoTargetLengths` (1477) | O(n) / O(n) |
| Prefix maximum near suffix minimum | Suffix minima and running maximum | `firstStableIndex` (3903, 3904) | O(n) / O(n) |
| Concatenation of equal-length words | One frequency window for each word offset | `findWordConcatenations` (30) | Expected O(nw+mw) / O(m) |

Here n is input length, m is target length/word count as applicable, and w is word length. Word hashing and equality read up to w bytes; `string_view` avoids allocation, not hashing cost. Hash-table complexities are expected, not worst-case guarantees. The word search returns positions grouped by offset, just like your submission; sort the result only if the caller needs global order.

## 1. Deficit counts: zero crossings do the work

For LC 76, `counts[ch] = required[ch] − currentWindow[ch]`:

```text
positive  -> still missing copies
zero      -> exactly enough
negative  -> surplus copies

enter: --counts[ch] == 0  => one distinct requirement became satisfied
leave: ++counts[ch] > 0   => a requirement became unsatisfied
```

Expand right. Once every requirement is satisfied, repeatedly record and shrink left. For LC 567, enforce the pattern's fixed length instead: satisfying every requirement then means an exact permutation, including multiplicities. Empty target is explicitly handled (`""` for minimum cover; `true` for empty permutation), whereas the source relies on a nonempty target.

**When useful:** covering constraints are per-symbol multiplicities. **Pitfall:** do not replace the source's repeated shrinking in minimum-window search with one shrink; that can miss the shortest answer. Counts are case-sensitive bytes, not Unicode code points. The adaptation uses 256 slots and casts to `unsigned char` before indexing. `"A"` and `"a"` differ.

## 2. True windows versus lazy length tracking

LC 1004 has both explicit shrinking and a one-step lazy variant in your history. The template uses the explicit `while (zeroes > k)` form, so the retained window is actually valid. LC 1493 reuses it and subtracts one because deletion is mandatory: `[1,1,1]` returns 2, not 3.

LC 424 deliberately keeps a historical `maxCount`. It may exceed the current window's true maximum after moving left. That is safe for the **maximum achievable length**, because a new larger length is established only when a new sufficient frequency has occurred. It is not a guarantee that the final stored interval itself is a valid witness. Your earlier submission recomputes the current maximum with `max_element`; the later one avoids that scan.

```text
window length − maximum same-character count = replacements needed
```

**Pitfalls:** stale-maximum logic is specific to this maximization problem. Do not transplant it into minimum-cover counting or return its final boundaries as an optimal actual substring. Binary helpers require 0/1 values and nonnegative budgets.

## 3. Positive/nonnegative sum windows and the complement trick

For LC 209, adding on the right never decreases the sum; removing on the left never increases it. This monotonicity justifies discarding left endpoints after testing them. LC 1658 changes the question before scanning:

```text
removed prefix | longest retained middle | removed suffix
        removed total x  <=>  middle total = totalSum − x
answer = n − longestMiddleLength
```

The templates permit nonnegative values for 209/1658 and use `long long` sums. The empty retained middle is valid; zero-filled middles are retained when they improve the answer. `minSubarrayLength` requires a strictly positive target. `minEndRemovals` returns −1 for an impossible removal sum.

**Negative numbers break these sum windows.** Example `[1,-1,3]`, target 3: shrinking the first valid full window removes 1, drops the sum below target, and misses the length-one `[3]`. Use prefix-based methods appropriate to the question instead. LC 560 below counts exact sums with signed values; it is not a shortest-at-least-target solver.

## 4. Prefix counts: query before insertion

```text
P[right+1] − P[left] = target
P[left] = P[right+1] − target

counts[0] = 1                 // empty prefix
answer += counts[current-target]
++counts[current]             // only after the query
```

The map contains only **earlier** prefixes when queried. Inserting first would incorrectly count an empty subarray when target is zero. Duplicate prefixes represent different valid left endpoints, so use counts rather than a set. For `[1,-1,0]`, target 0, the answer is 3. Both keys and answer are widened; 100,000 zeroes have 5,000,050,000 zero-sum subarrays.

## 5. Last-seen indices count valid starts directly

LC 2444 needs the last location of each bound and the last value outside the allowed range:

```text
            valid starting positions
lastBad  | (........................] | ... right
                      min(lastMin,lastMax)

new subarrays = max(0, min(lastMin,lastMax) − lastBad)
```

Every counted start excludes the bad value and includes at least one occurrence of both extrema. The bounds can be equal; then each all-equal run contributes its triangular number. This is the actual last-seen pattern in the inspected sources; no unrelated distinct-character-window implementation is claimed.

## 6. Prefix/suffix identities and best-so-far composition

LC 238 uses identity-padded arrays, with `left[i]` the product before i and `right[i+1]` the product after i:

```text
nums:   a   b   c   d
              ^ exclude c
result[2] = (a*b) * d
```

No division, so one or several zeroes work. The source stores both arrays explicitly; so does this template. An empty input returns empty; a singleton returns `{1}`. **All intermediate prefix/suffix products, not just final answers, must fit `long long`.** Two zeroes can make every final answer zero while an earlier prefix still overflows.

LC 1477 stores `best[i]`, the shortest target-sum window wholly inside `[0,i)`. When `[left,right]` hits the target, combine its length with `best[left]`. That exclusive boundary proves nonoverlap. This helper retains the source's **strictly positive** array and target assumptions; zeroes can create multiple target windows ending together, which need different handling.

LC 3903/3904 uses `prefixMax([0,i]) − suffixMin([i,n)) <= k`. Notice index i belongs to **both** sides, unlike the exclusive boundaries above. The adaptation handles empty input and widens subtraction; it does not redefine the source condition as an ordinary disjoint split.

## 7. Word-sized strides, borrowed views

LC 30 splits the scan into w residue classes:

```text
w=3
start 0: [0..2] [3..5] [6..8] ...
start 1:  [1..3] [4..6] [7..9] ...
start 2:   [2..4] [5..7] [8..10] ...
```

Within one offset, the window contains only known words and never exceeds any word quota after shrinking. An unknown word resets it. On overcounting the entering word, remove words from the left until its quota fits. Count duplicate words, not just distinct types.

The template rejects empty words and unequal lengths, and returns empty for an empty word list. `string_view` keys borrow from text/words only during the call; inputs must remain alive and unchanged for that call, and no views escape. All inputs are read-only.

## Adaptation and bounds checklist

- Source techniques remain intact. Changes: explicit headers/namespace, empty-input guards, byte-safe arrays, wide sums/counts/products, nonmutating inputs, and clear contracts. LC 1493 uses the explicit LC 1004 window rather than its original lazy scan.
- Sizes/indexes must fit `int` with room for `n+1`; numeric totals, `prefix−target`, and every intermediate product must fit `long long`. Widening delays overflow; it does not make arithmetic unbounded.
- Nonnegative/positive and binary-array assumptions are caller preconditions, not a hidden validation pass.
- Tests use deterministic examples plus 600 seeded cases against independent quadratic/exhaustive references, including signed sums, duplicates, empty inputs, byte 255, mandatory deletion, word offsets, and wide counts.

## Compile and verify

From this folder:

```sh
g++ -std=c++20 -O2 -Wall -Wextra -Werror test.cpp -o /tmp/pattern-test
/tmp/pattern-test
g++ -std=c++20 -O1 -g -Wall -Wextra -Werror -fsanitize=address,undefined -fno-omit-frame-pointer test.cpp -o /tmp/pattern-test-sanitized
/tmp/pattern-test-sanitized
```

Verification in the build environment used `ASAN_OPTIONS=detect_leaks=0` for the sanitizer run because LeakSanitizer cannot operate under ptrace there. AddressSanitizer and UndefinedBehaviorSanitizer remained enabled; leak checking was not completed. On a normal local environment, try the command above with leak detection left enabled.

The tests were written before the implementations. Neutral stubs produced failing behavioral checks; the implementations then passed the same checks. No LeetCode harness, external libraries, or other handbook topics are needed. Helpers are `inline` in namespace `patterns`; include `templates.hpp` and call only the pieces you need.

## Exact source map

These are the inspected submissions, not algorithms inferred from problem titles. Multiple links show observed variants.

- [76. Minimum Window Substring](https://leetcode.com/problems/minimum-window-substring/) · inventory row 88 · [submission 2149102883](https://leetcode.com/problems/minimum-window-substring/submissions/2149102883/), [submission 2131820578](https://leetcode.com/problems/minimum-window-substring/submissions/2131820578/)
- [567. Permutation in String](https://leetcode.com/problems/permutation-in-string/) · inventory row 188 · [submission 2131779135](https://leetcode.com/problems/permutation-in-string/submissions/2131779135/)
- [424. Longest Repeating Character Replacement](https://leetcode.com/problems/longest-repeating-character-replacement/) · inventory row 189 · [submission 2131743704](https://leetcode.com/problems/longest-repeating-character-replacement/submissions/2131743704/), [submission 2131736709](https://leetcode.com/problems/longest-repeating-character-replacement/submissions/2131736709/), [submission 2027329669](https://leetcode.com/problems/longest-repeating-character-replacement/submissions/2027329669/)
- [1004. Max Consecutive Ones III](https://leetcode.com/problems/max-consecutive-ones-iii/) · inventory row 201 · [submission 2127149237](https://leetcode.com/problems/max-consecutive-ones-iii/submissions/2127149237/), [submission 2027338195](https://leetcode.com/problems/max-consecutive-ones-iii/submissions/2027338195/)
- [1493. Longest Subarray of 1's After Deleting One Element](https://leetcode.com/problems/longest-subarray-of-1s-after-deleting-one-element/) · inventory row 198 · [submission 2127345655](https://leetcode.com/problems/longest-subarray-of-1s-after-deleting-one-element/submissions/2127345655/)
- [209. Minimum Size Subarray Sum](https://leetcode.com/problems/minimum-size-subarray-sum/) · inventory row 193 · [submission 2130694109](https://leetcode.com/problems/minimum-size-subarray-sum/submissions/2130694109/)
- [1658. Minimum Operations to Reduce X to Zero](https://leetcode.com/problems/minimum-operations-to-reduce-x-to-zero/) · inventory row 81 · [submission 2150943873](https://leetcode.com/problems/minimum-operations-to-reduce-x-to-zero/submissions/2150943873/)
- [560. Subarray Sum Equals K](https://leetcode.com/problems/subarray-sum-equals-k/) · inventory row 191 · [submission 2130713437](https://leetcode.com/problems/subarray-sum-equals-k/submissions/2130713437/), [submission 2025473825](https://leetcode.com/problems/subarray-sum-equals-k/submissions/2025473825/)
- [2444. Count Subarrays With Fixed Bounds](https://leetcode.com/problems/count-subarrays-with-fixed-bounds/) · inventory row 69 · [submission 2153831199](https://leetcode.com/problems/count-subarrays-with-fixed-bounds/submissions/2153831199/)
- [238. Product of Array Except Self](https://leetcode.com/problems/product-of-array-except-self/) · inventory row 192 · [submission 2130701387](https://leetcode.com/problems/product-of-array-except-self/submissions/2130701387/)
- [1477. Find Two Non-overlapping Sub-arrays Each With Target Sum](https://leetcode.com/problems/find-two-non-overlapping-sub-arrays-each-with-target-sum/) · inventory row 136 · [submission 2145013796](https://leetcode.com/problems/find-two-non-overlapping-sub-arrays-each-with-target-sum/submissions/2145013796/)
- [3903. Smallest Stable Index I](https://leetcode.com/problems/smallest-stable-index-i/) · inventory row 195 · [submission 2130500850](https://leetcode.com/problems/smallest-stable-index-i/submissions/2130500850/)
- [3904. Smallest Stable Index II](https://leetcode.com/problems/smallest-stable-index-ii/) · inventory row 190 · [submission 2131704501](https://leetcode.com/problems/smallest-stable-index-ii/submissions/2131704501/)
- [30. Substring with Concatenation of All Words](https://leetcode.com/problems/substring-with-concatenation-of-all-words/) · inventory row 70 · [submission 2153818347](https://leetcode.com/problems/substring-with-concatenation-of-all-words/submissions/2153818347/)
