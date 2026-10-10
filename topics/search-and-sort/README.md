# Search and sort: decide what can be discarded

These templates are derived from your observed Accepted C++ submissions. They retain your `std::` qualification, camelCase names, signed indices, inclusive search intervals, and straightforward loops. This is a reusable adaptation, not a verbatim archive. Exact sources and every material generalization are listed below.

[Templates](templates.hpp) · [Executable tests](test.cpp) · Namespace: `patterns::search`

## Choose the pattern

| Need | Template | Time | Extra space |
|---|---|---:|---:|
| Exact key in sorted data | `binarySearch(nums, target)` | O(log n) | O(1) |
| First value ≥ / > target | `lowerBound` / `upperBound` | O(log n) | O(1) |
| Smallest feasible integer | `firstTrue(left, right, check)` | O(log range) predicate calls | O(1) |
| Distinct rotated sorted array | `searchRotated` | O(log n) | O(1) |
| Rotated array with duplicates | `searchRotatedWithDuplicates` | O(n) worst case | O(1) |
| One order statistic | `quickselect` / `kthLargest` | O(n²) worst case; typically linear | O(1) |
| Full sorted order | `mergeSort` | O(n log n) | O(n) plus O(log n) recursion |
| Original pairs `i < j`, `a[i] > 2*a[j]` | `countReversePairs` | O(n log n) | O(n) plus O(log n) recursion |

Vector sizes must fit in `int`. Sorted-input APIs assume the stated order; they do not spend O(n) validating it. Search functions do not mutate input. Selection and merge functions do.

## 1. Binary search is an invariant, not a memorized loop

### Inclusive exact match

Your #704 loop keeps every possible match inside `[left, right]`. Test `mid`, then discard it along with one impossible side:

```text
                 candidate interval
known too small | left ... mid ... right | known too large
                         /     \
                  right=mid-1  left=mid+1
```

`left <= right` means a one-element candidate interval still needs testing. Missing keys return `-1`; duplicates may return any matching index.

### Lower and upper bound: preserve the answer after the loop

Your #35 implementation never returns early on equality:

```cpp
if (nums[mid] < target) left = mid + 1;
else right = mid - 1;
// return left;
```

The discarded prefix is `< target`; the discarded suffix is `>= target`. When the interval is empty, `left` is the first index in the suffix, possibly `n`.

For upper bound, change exactly one comparison: discard `<= target`. This is an explicitly derived variation of #35, not a separately observed upper-bound submission.

```text
nums = [1, 2, 2, 2, 5], target = 2
           ^        ^
       lower=1   upper=4

count(target) = upperBound(nums,target) - lowerBound(nums,target)
last <= target = upperBound(nums,target) - 1
last < target  = lowerBound(nums,target) - 1
```

Check `index < n` before dereferencing a bound, and `index >= 0` after subtracting one. Empty input correctly returns 0 for both bounds.

### Search an answer rather than an index

Your #875 and #1011 loops use a different invariant: the answer lies in a **closed feasible bracket**, and `right` itself is feasible.

```text
false false false | true true true
                  ^ firstTrue
if check(mid): right = mid      // mid may be the answer
else:          left = mid + 1  // mid cannot be the answer
stop when left == right
```

`firstTrue(left, right, check)` extracts that control flow. `check` must be pure and monotone from false to true. The template verifies that the bracket is nonempty and its right endpoint is feasible; it throws `std::invalid_argument` otherwise. It cannot cheaply verify monotonicity.

The index searches retain `left + (right-left)/2`. The generic signed 64-bit answer search uses C++20 `std::midpoint(left,right)` so even `[LLONG_MIN, LLONG_MAX]` is safe. Avoid `left+right` and do not assume `right-left` fits for arbitrary signed endpoints.

#### Greedy feasibility (#1011 and #410)

`minLargestGroupSum(nums, groups)` finds the smallest maximum sum for at most `groups` contiguous groups. Start with:

- `left = max(nums)`: every element must fit
- `right = sum(nums)`: one group always fits
- Scan left to right, starting another group only when the next value would overflow the candidate capacity

For nonnegative values, greedily extending each group as far as possible minimizes the number of groups for that capacity. More capacity cannot require more groups, which makes the predicate monotone.

```text
weights = [7,2,5,10,8], groups = 2
capacity 17: [7,2,5] [10] [8]   -> false
capacity 18: [7,2,5] [10,8]     -> true
```

This covers shipping within days and splitting a nonnegative array. For exactly `k` nonempty groups, equivalence requires `1 <= k <= n`: a feasible group can be split without increasing its sum. The reusable API explicitly says **at most**, permits `groups > n`, and gives empty input capacity 0. Negative inputs or nonpositive group counts throw. Negative values break the greedy proof.

Your #410 predicate named `canSplit` actually meant “too many breaks.” The adaptation uses a positive feasibility meaning throughout. Do not copy a predicate's name without checking which branch it represents.

#### Integer ceilings (#875)

`minEatingSpeed(piles, hours)` uses:

```cpp
pile / speed + (pile % speed != 0)
```

This avoids the potentially overflowing `pile + speed - 1`. Sum hours in `long long`, stop as soon as the budget is exceeded, and establish feasibility before searching. The template supports zero piles, returns 0 for all-zero/empty input, and rejects negative inputs or an impossible hour budget. Complexity: O(n log maxPile), O(1) extra space.

## 2. Rotation: recover the order or identify the sorted half

### Distinct keys (#33 / #153)

Your older correct #33 source first finds the minimum by comparing with `nums.back()`, then searches a virtual sorted array:

```text
physical: [4,5,6,7,0,1,2]  rotation = 4
virtual:  [0,1,2,4,5,6,7]
physicalIndex = (virtualIndex + rotation) % n
```

This separates the two jobs cleanly. The returned index is in the original rotated array. The empty case is handled before calling `back()` or taking a modulo.

Source choice matters: the newer accepted source #2146701709 contains `left + (right - left / 2)`, a malformed midpoint expression. The template deliberately follows #2125939691's correct parentheses. An Accepted badge is evidence of observed acceptance, not a proof that every line is a safe reusable pattern.

### Duplicates (#81)

When `nums[left] == nums[mid] == nums[right]`, neither half is identifiable as the useful sorted half. Since equality with the target was already checked, shrink both ends by one. Otherwise, identify the sorted half and retain it only if its value interval contains the target.

```text
[1,1,1,1,1,0,1]  cannot consistently discard half from equal boundaries
```

This is why duplicates can degrade the search to O(n). The distinct-key rotation trick is not a drop-in replacement.

## 3. Quickselect: Hoare partition with a global target

Your #215 sources use a middle-element pivot and inclusive `[left,right]` bounds. The target is a **global zero-based ascending index**:

```text
kth largest k = 1  -> target n-1
kth largest k = n  -> target 0
                     target = n-k
```

The partition scans inward, swaps misplaced values, and advances both indices even when the values equal the pivot:

```cpp
while (i <= j) {
    while (nums[i] < pivot) ++i;
    while (nums[j] > pivot) --j;
    if (i <= j) std::swap(nums[i++], nums[j--]);
}
```

After crossing:

```text
left ... j | possible pivot gap | i ... right
  <= pivot                        >= pivot

k <= j: keep [left,j]
k >= i: keep [i,right]
otherwise: nums[k] is already the answer
```

This is a Hoare-style split, **not** a partition that puts a chosen pivot at its final sorted index. Do not recurse around an imagined pivot index or change the target to a local rank midway through this version.

`quickselect(nums, k)` takes the zero-based ascending rank. `kthLargest(nums, k)` takes the one-based descending rank. Both reject empty/out-of-range requests with `std::out_of_range`. Both mutate the vector; neither promises the rest is sorted.

The iterative adaptation removes recursive stack growth without changing the partition logic. A deterministic middle-value pivot still has O(n²) adversarial worst cases. It does not acquire an expected-linear guarantee just because the pivot sits in the middle index. If adversarial inputs matter, randomization or an introspective selection strategy would be a new, separately justified adaptation.

## 4. Merge sorting and counting before merging (#493)

The recursive return invariant is stronger than “this half is done”:

1. Each half is sorted.
2. Its internal reverse pairs have already been counted.
3. Only cross pairs remain, and every index in the left half originally preceded every index in the right half.

```text
L = [1,3,5]          R = [1,2]
     i                    j
3 > 2*1: every L[i..end] also qualifies -> add 2, move j
5 > 2*2: every L[i..end] also qualifies -> add 1, move j
cross contribution = 3
```

The counting pointers move only forward because both halves are sorted. When `L[i] > 2LL * R[j]`, add `leftSize-i`; otherwise advance `i`. Then reset both pointers and run the ordinary merge.

Do the counting pass **before merging**: interleaving the original halves loses the simple cross-index relation. Ordinary inversions (`L[i] > R[j]`) can be counted during merge; the scaled threshold in #493 deserves its own pass.

The template uses local returned counts rather than a persistent member `result`, so repeated calls cannot retain prior answers. It returns `long long` and multiplies by `2LL` before comparison. Negative values and `INT_MIN`/`INT_MAX` are tested. `mergeSort` is the explicitly factored ordinary-sort portion of that same source, with counting disabled. It uses the observed temporary left/right arrays, not a claimed original scratch-buffer optimization.

For dynamic range counting instead of static cross-pair counting, see [Range queries](../range-queries/README.md).

## Sources and adaptation record

| Actual problem | Exact observed submission | What was retained / changed |
|---|---|---|
| [704. Binary Search](https://leetcode.com/problems/binary-search/) | [2146675354](https://leetcode.com/problems/binary-search/submissions/2146675354/) | Inclusive exact-match loop; explicit signed size conversion |
| [35. Search Insert Position](https://leetcode.com/problems/search-insert-position/) | [2146678224](https://leetcode.com/problems/search-insert-position/submissions/2146678224/) | Lower-bound loop; upper bound derived by changing `<` to `<=` |
| [875. Koko Eating Bananas](https://leetcode.com/problems/koko-eating-bananas/) | [2146691389](https://leetcode.com/problems/koko-eating-bananas/submissions/2146691389/) | Integer ceiling and first-feasible loop; widened sums, explicit feasibility/empty guards |
| [1011. Capacity To Ship Packages Within D Days](https://leetcode.com/problems/capacity-to-ship-packages-within-d-days/) | [2146696311](https://leetcode.com/problems/capacity-to-ship-packages-within-d-days/submissions/2146696311/) | Greedy contiguous packing; generalized to capacity for at most groups |
| [410. Split Array Largest Sum](https://leetcode.com/problems/split-array-largest-sum/) | [2146752727](https://leetcode.com/problems/split-array-largest-sum/submissions/2146752727/) | Same answer-search family; invert confusing infeasibility predicate |
| [33. Search in Rotated Sorted Array](https://leetcode.com/problems/search-in-rotated-sorted-array/) | [2125939691](https://leetcode.com/problems/search-in-rotated-sorted-array/submissions/2125939691/) | Pivot plus virtual search; empty guard and widened index addition |
| Same problem, reviewed caution | [2146701709](https://leetcode.com/problems/search-in-rotated-sorted-array/submissions/2146701709/) | Malformed midpoint noted; not used as template baseline |
| [153. Find Minimum in Rotated Sorted Array](https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/) | [2146698709](https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/submissions/2146698709/) | Fixed-final-value comparison supports the rotation invariant |
| [81. Search in Rotated Sorted Array II](https://leetcode.com/problems/search-in-rotated-sorted-array-ii/) | [2146739961](https://leetcode.com/problems/search-in-rotated-sorted-array-ii/submissions/2146739961/) | Equal-boundary shrink and sorted-half selection |
| [215. Kth Largest Element in an Array](https://leetcode.com/problems/kth-largest-element-in-an-array/) | [2144679787](https://leetcode.com/problems/kth-largest-element-in-an-array/submissions/2144679787/) | Middle pivot, Hoare scans, `n-k`; recursion changed to iteration and input guards added |
| [493. Reverse Pairs](https://leetcode.com/problems/reverse-pairs/) | [2150875619](https://leetcode.com/problems/reverse-pairs/submissions/2150875619/) | Separate count then merge; per-call 64-bit count and ordinary-sort wrapper |

## Run the checks

```sh
g++ -std=c++20 -O2 -Wall -Wextra -Werror test.cpp -o /tmp/search-test
/tmp/search-test
g++ -std=c++20 -O1 -g -Wall -Wextra -Werror -fsanitize=address,undefined -fno-omit-frame-pointer test.cpp -o /tmp/search-sanitized
ASAN_OPTIONS=detect_leaks=0 /tmp/search-sanitized
```

The deterministic edge cases and 600 seeded randomized cases compare bounds with the standard library, every selection rank with sorting, rotated search with linear scans, reverse pairs with O(n²) enumeration, and answer searches with brute-force candidates. Boundary tests include empty arrays, duplicates, impossible budgets, repeated calls, and full signed 64-bit answer-search endpoints.

Sanitizer note: AddressSanitizer and UndefinedBehaviorSanitizer passed with leak detection disabled. LeakSanitizer cannot run under this execution environment’s ptrace setup; this is not a leak-check result. On an ordinary local shell, omit `ASAN_OPTIONS=detect_leaks=0` to attempt leak detection too.
