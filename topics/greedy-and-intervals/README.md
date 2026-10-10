# Greedy and intervals

Your useful recurring pattern is to make one local choice provably harmless, then batch it or preserve just the boundary that matters. The unusual source-specific cases (1520 and 621) are retained rather than replaced by a more familiar textbook solution.

## Pattern map

| Template / source | Invariant or exchange argument | Useful when | Time / extra space |
|---|---|---|---|
| `minSquaredDifference` / 2333 | Lowering a larger positive difference saves more square cost | Many identical unit reductions | O(n+D) / O(D) |
| `eraseOverlapIntervals` / 435 | Keep the compatible interval with earliest finish | Maximum count of nonoverlapping intervals | O(n log n) / O(n) including copy |
| `mergeIntervals` / 56 | Output before its last interval is finalized | Union of closed intervals | O(n log n) / O(n) |
| `insertInterval` / 57 | Overlaps form one consecutive block | Insert into already sorted, disjoint intervals | O(n) / O(n) including copy |
| `minimumCandy` / 135 | Meet left and right lower bounds independently | Neighbor inequalities on a line | O(n) / O(n) |
| `leastScheduleLength` / 621 | Use most frequent distinct types in each cooldown round | Unit tasks, one shared cooldown | O(T log(s+1)) / O(s) |
| `maxClosedSubstrings` / 1520 | Global counts exactly fill a group's bounding span | Character-complete, nonoverlapping substrings | O(n+s²) / O(s), excluding output |
| `maxNonOverlappingPalindromes` / 2472 | Earliest feasible finish after checking lengths k,k+1 | Maximum number of disjoint long-enough palindromes | O(nk) / O(1) |
| `countBoundedSubsequences` / 1498 | Fix the minimum; freely choose the bounded interior | Count indexed subsequences by min+max | O(n log n) / O(n) |

D is the largest difference, T the task count, and s the distinct-character count. For 1520, s≤26. Hash-map work is expected; sorting and copying costs are included where relevant. `templates.hpp` takes sorting inputs by value so the caller's containers are unchanged.

## 1. Bucket leveling: convex marginal benefit

For a positive difference d, one reduction saves:

```text
d² − (d−1)² = 2d−1

height 4:  ##       move two items downward together
height 3:  ###  ->  #####
```

The largest d always gives the best next saving. Your 2333 submission stores frequencies and moves `min(operations, count[d])` items to d−1, descending by height. The template uses a dense vector instead of `unordered_map`; the source also probes every height, so both depend on D. The input here is the already-computed vector of nonnegative differences, which keeps the reusable leveling kernel separate from the task's two arrays.

**Pitfalls:** this is O(n+D), not O(n log n). Use a different representation for a huge sparse value range. Stop at zero; excess operations need not be spent. Compute differences with `abs(1LL*a-b)` and combine budgets with `1LL*k1+k2` before narrowing anything. This helper requires differences to fit nonnegative `int`, a modest D, and the full squared sum to fit `long long`; even a wide square may overflow after multiplication by its count.

## 2. Interval endpoint semantics change by task

```text
[1,2] [2,3]
435: both may be kept           end <= next start
 56: merge to [1,3]             end >= next start
```

For 435, exchange any first chosen interval for the earliest-finishing one: no later interval becomes less available. Sort by end, keep a scalar `lastEnd`, and count rejected intervals. The source uses `auto& last = intervals[0]`; assigning to `last` overwrites the first vector element. The adaptation removes that accidental alias mutation and guards empty input. 435 requires positive-length intervals.

For 56, sort by start and fold into the last output interval. Once the next start is beyond the current end, the current component is complete. Closed intervals may be degenerate; touching still merges.

For 57, sorted disjoint intervals make both start and end sequences monotone. Your two comparators have intentionally opposite argument order:

```cpp
auto left = std::lower_bound(begin, end, addedStart,
    [](const auto& interval, int value) { return interval[1] < value; });
auto right = std::upper_bound(begin, end, addedEnd,
    [](int value, const auto& interval) { return value < interval[0]; });
```

`[left,right)` is exactly the overlap block. Extend to its outer endpoints, erase it, insert the merged interval. Binary search is O(log n), but vector movement and copying make the whole helper O(n). The source mutates both input intervals and `newInterval`; the adaptation copies both. Do not call this on unsorted or overlapping input, and do not use iterators from before `erase` afterward.

## 3. Two passes: satisfy both directions

LC 135 starts with one candy everywhere. A left-to-right pass sets the minimum satisfying the left neighbor. A right-to-left pass takes `max(existing, rightNeighbor+1)` whenever the current rating is larger. Taking `max` preserves the first pass.

```text
ratings:       1  0  2
initial:       1  1  1
left -> right: 1  1  2
right -> left: 2  1  2
```

Equal ratings impose no ordering. The final sum uses `0LL`; an increasing chain has a triangular total. This is useful whenever a line's constraints separate into directional lower bounds.

## 4. Heap rounds, not an invented scheduler formula

LC 621's inspected implementation uses a max-heap of remaining counts. Pop up to `cooldown+1` **distinct task types** into a temporary vector, then decrement and reinsert them. Reinserting during the round could select the same type twice too soon.

```text
A A A B B B, cooldown=2
A B idle | A B idle | A B
 full round   full     final round has no trailing idle
```

Count a full round unless the heap becomes empty, when only executed tasks count. The helper returns a length, not a concrete schedule. The tests use the independent counting lower-bound formula as an oracle; that formula is not claimed to be the user's submitted method. The problem assumes unit execution time, one processor, and a uniform cooldown.

## 5. Character spans: the actual 1520 trick

For each lowercase character, store `(first,last,totalCount)` and iterate characters in first-appearance order. Push each record to the front of a deque. Scan deque prefixes, which correspond to suffixes of appearance order, accumulating the bounding interval and total counts.

```text
sum(global counts of selected characters) == right−left+1
                         |
                  no foreign character can be inside
```

Every selected character's full span is inside the bounding interval. Equality means those characters occupy every position there, so the interval is closed under all character occurrences. Stop at the first equality, emit that substring, and clear pending records. This preserves the source's choice of short inner candidates instead of mechanically selecting outer character spans.

For `adefaddaccc`, the result is `e`, `f`, `ccc`: choosing the broad `a...a` span would sacrifice useful inner choices. Emitted intervals cannot contain a not-yet-processed character, because that would violate the count equality, so future candidates occur after them. The test oracle enumerates every closed interval and checks both maximum count and minimum total length.

**Bounds:** the fixed alphabet is ASCII `a`–`z`; the template rejects anything else. The source's deque aggregation is O(s²), not a general linear interval algorithm for an unbounded alphabet. Do not relabel it as a standard sorted-by-end solution that was never submitted.

## 6. Why k and k+1 palindrome lengths suffice

Every palindrome of length ≥k can shed matching outer pairs until its length is either k or k+1. Therefore an optimum can be replaced with palindromes of those two lengths without reducing its count or creating overlap.

Scan starts left-to-right; check k first, then k+1. The first hit finishes as early as any candidate not yet considered: a later start with minimum length k cannot finish sooner. Take it and jump beyond it.

```text
[ palindrome length 7 ]   k=4
  [ palindrome length 5 ]  <- same parity, sufficient
```

The helper compares characters directly, retaining the source's O(nk) approach. It does not claim Manacher-style preprocessing. Use positive k; k larger than the string yields zero. The original unsigned `s.size()-k` is replaced with guarded signed indices.

## 7. Counting with fixed minimum: 2^(right−left)

Sort. If `nums[left]+nums[right] <= target`, every subset of indices in `(left,right]`, together with `left`, is valid:

```text
left [ optional ... optional ] right
fixed      right−left independent include/exclude choices
                    => 2^(right−left)
```

The right endpoint is optional too; it is only the largest permitted candidate. Assigning each nonempty subsequence to its smallest chosen sorted index prevents double-counting even when values repeat. If the sum is too large, decrease right; otherwise add the precomputed power and increment left. The adaptation widens the endpoint sum and uses an integer modulus constant, replacing source `pow(10,9)+7`. Counts are modulo 1,000,000,007.

## Small source-backed tricks worth remembering

- **1877, pair extremes:** after sorting an even-sized array, pair smallest with largest to minimize the largest pair sum. Your history contains both sorting and a frequency-map scan from the minimum and maximum numeric values. The latter is O(n+valueRange), not O(n) on arbitrary sparse values. The source starts the answer at zero because task values are positive; for generalized negative values start at the first pair sum. Widen pair addition. This does not need another wrapper.
- **121, prefix minimum:** update the cheapest earlier/current price, then maximize `price−minimum`. Zero means choosing no trade. A single pass is O(n) time and O(1) space. Updating the minimum first permits a zero-profit same-index candidate, which does not change the optimum. Widen subtraction outside the original price bounds.

## Contracts and tests

- Container/string sizes fit `int` with room for `n+1` and `k+1`; arithmetic totals fit `long long`.
- Interval corners are ordered. Insertion additionally requires sorted strictly separated intervals. Sorting helpers copy; other inputs are read-only.
- Greedy arguments are task-specific: earliest finish maximizes **count**, not total interval value; the scheduler assumes one shared cooldown; convex bucket leveling assumes unit independent reductions.
- Deterministic examples plus 500 seeded cases compare against one-move-at-a-time reduction, exhaustive interval subsets, graph-component merging, candy assignments, scheduler counting, closed-interval DP, palindrome DP, and subsequence masks.

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

- [2333. Minimum Sum of Squared Difference](https://leetcode.com/problems/minimum-sum-of-squared-difference/) · inventory row 1 · [submission 2168486798](https://leetcode.com/problems/minimum-sum-of-squared-difference/submissions/2168486798/)
- [435. Non-overlapping Intervals](https://leetcode.com/problems/non-overlapping-intervals/) · inventory row 3 · [submission 2167400289](https://leetcode.com/problems/non-overlapping-intervals/submissions/2167400289/), [submission 2139752268](https://leetcode.com/problems/non-overlapping-intervals/submissions/2139752268/)
- [56. Merge Intervals](https://leetcode.com/problems/merge-intervals/) · inventory row 4 · [submission 2167385466](https://leetcode.com/problems/merge-intervals/submissions/2167385466/), [submission 2126107082](https://leetcode.com/problems/merge-intervals/submissions/2126107082/)
- [57. Insert Interval](https://leetcode.com/problems/insert-interval/) · inventory row 5 · [submission 2167382205](https://leetcode.com/problems/insert-interval/submissions/2167382205/), [submission 2167379680](https://leetcode.com/problems/insert-interval/submissions/2167379680/)
- [135. Candy](https://leetcode.com/problems/candy/) · inventory row 16 · [submission 2163599188](https://leetcode.com/problems/candy/submissions/2163599188/)
- [621. Task Scheduler](https://leetcode.com/problems/task-scheduler/) · inventory row 139 · [submission 2144706913](https://leetcode.com/problems/task-scheduler/submissions/2144706913/)
- [1520. Maximum Number of Non-Overlapping Substrings](https://leetcode.com/problems/maximum-number-of-non-overlapping-substrings/) · inventory row 134 · [submission 2146064854](https://leetcode.com/problems/maximum-number-of-non-overlapping-substrings/submissions/2146064854/)
- [2472. Maximum Number of Non-overlapping Palindrome Substrings](https://leetcode.com/problems/maximum-number-of-non-overlapping-palindrome-substrings/) · inventory row 157 · [submission 2143088360](https://leetcode.com/problems/maximum-number-of-non-overlapping-palindrome-substrings/submissions/2143088360/)
- [1498. Number of Subsequences That Satisfy the Given Sum Condition](https://leetcode.com/problems/number-of-subsequences-that-satisfy-the-given-sum-condition/) · inventory row 174 · [submission 2140461426](https://leetcode.com/problems/number-of-subsequences-that-satisfy-the-given-sum-condition/submissions/2140461426/)
- [1877. Minimize Maximum Pair Sum in Array](https://leetcode.com/problems/minimize-maximum-pair-sum-in-array/) · inventory row 173 · [submission 2140491975](https://leetcode.com/problems/minimize-maximum-pair-sum-in-array/submissions/2140491975/), [submission 2140491229](https://leetcode.com/problems/minimize-maximum-pair-sum-in-array/submissions/2140491229), [submission 2140485732](https://leetcode.com/problems/minimize-maximum-pair-sum-in-array/submissions/2140485732/)
- [121. Best Time to Buy and Sell Stock](https://leetcode.com/problems/best-time-to-buy-and-sell-stock/) · inventory row 199 · [submission 2127314016](https://leetcode.com/problems/best-time-to-buy-and-sell-stock/submissions/2127314016/)
