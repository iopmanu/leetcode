# Monotonic structures and heaps: keep only useful candidates

These are adaptations of your observed Accepted C++ code. In particular, your #239 solution is a heap, your #862 solution uses a reversed deque orientation, and your #480 solution uses indexed multisets. The handbook preserves those choices rather than attributing textbook alternatives to you.

[Templates](templates.hpp) · [Executable tests](test.cpp) · Namespace: `patterns::monotonic`

## Choose by what makes a candidate obsolete

| Situation | Tool | Why a candidate can leave | Complexity |
|---|---|---|---|
| Next strictly greater value | `nextGreaterDistances` | Current value resolves its answer | O(n) time, O(n) space |
| Largest histogram rectangle | `largestRectangle` | A lower bar closes its right boundary | O(n) time, O(n) space |
| Online stock span | `StockSpanner` | Current price absorbs its entire span | O(1) amortized per call, O(n) space |
| Sum of subarray minima | `sumSubarrayMinimums` | A lower value fixes contribution boundaries | O(n) time, O(n) space |
| Sliding window maximum | `slidingWindowMaximum` | Expired top of a max-heap | O(n log n) time, O(n) space worst case |
| Shortest subarray reaching a sum | `shortestSubarrayAtLeast` | Candidate is either already used or dominated | O(n) time, O(n) space |
| Median with insertion only | `StreamMedian` | Rebalance two heaps | O(log n) insertion, O(1) query, O(n) space |
| Median with deletion by ID | `IndexedMedian` | Remove exact iterator, then rebalance | O(log n) expected update, O(1) query, O(n) space |

The two indexed-median maps use expected O(1) hashing; pathological hash collisions can worsen update time. Every vector-index API assumes the size fits in `int`. Invalid windows throw; empty sequence behavior is documented per function.

## 1. The comparison is part of the proof

A monotonic stack is a collection of still-useful candidates. Each element is pushed once and popped at most once, giving O(n) total work even with a nested `while` loop.

| Pattern | Pop while incoming… | Stack after processing | What equality means |
|---|---|---|---|
| #739 next greater | `incoming > top` | Nonincreasing values | Equal is not warmer, so keep it |
| #84 histogram | `incoming < top` | Nondecreasing heights | Equal heights may coexist |
| #901 stock span | `incoming >= top` | Strictly decreasing prices | Equal prices belong to today's span |
| #907 minimum contribution | `incoming < top` | Nondecreasing values | Equal minima need one consistent owner |

Changing `<` to `<=` is a semantic change, not cosmetic cleanup.

### Next greater distance (#739)

Store indices, not just values: the answer needs `currentIndex - waitingIndex`. The stack contains unresolved values in nonincreasing order.

```text
values:  [73,74,75,71,69,72,...]
waiting before 72: indices [2,3,4] -> values [75,71,69]
72 resolves 69 at distance 1, then 71 at distance 2
75 remains unresolved
```

`nextGreaterDistances` returns 0 where no strictly greater value appears later. The generic name is an adaptation of your temperature-specific API.

### Histogram boundaries (#84)

When a shorter bar arrives at `i`, pop `pivot`. After popping, the new stack top is `left`, or `-1` if none:

```text
left | left+1 .... pivot .... i-1 | i
           valid width = i-left-1
             area = height[pivot] * width
```

All intervening bars are at least the popped height. With strict `>` popping, `left` can be an equal-height bar, so this pop need not produce the widest rectangle at that height. The earlier equal bar will eventually capture the wider span. Do not describe `left` as “strictly smaller” for this tie policy.

The final iteration `i == n` drains the stack without inserting a sentinel into the input. The short-circuit condition checks `i == n` before reading `heights[i]`. The result and multiplication are 64-bit. Negative heights throw; empty input returns 0.

### Compressed spans (#901)

Store `(price, span)` rather than individual days. Every popped node represents a whole consecutive block that can be absorbed:

```text
before price 75: [(100,1), (80,1), (70,2), (60,1)]
span = 1 + 1 + 2 = 4
 after price 75: [(100,1), (80,1), (75,4)]
```

This is a general trick: when popped items form a contiguous region, preserve their aggregate weight. The template keeps your algorithm but removes the unnecessary empty-stack special case and widens span counts to `long long`.

## 2. Contribution counting: choose an owner for equal minima (#907)

Instead of enumerating all subarrays and finding their minima, ask how many subarrays belong to each minimum index.

For a popped index `m`:

- `left` is the previous index with value **less than or equal** to `nums[m]`
- `right` is the next index with value **strictly less** than `nums[m]`
- Start choices: `m-left`
- End choices: `right-m`

```text
left | possible starts ... m ... possible ends | right
                     contribution
          nums[m] * (m-left) * (right-m)
```

With `[2,2]`, the first 2 owns `[0]` and `[0,1]`; the second owns `[1]`. The strict right boundary and non-strict left boundary assign multi-equal subarrays to their leftmost minimum exactly once.

Using strict boundaries on both sides double-counts equal-minimum subarrays; using non-strict boundaries on both sides misses them. One side must break the tie.

`sumSubarrayMinimums` returns the sum modulo 1,000,000,007, including for negative values. This extends the original positive-input contract: normalize each value into `[0,mod)`, reduce between multiplications, and keep products in `long long`. Empty input returns 0.

## 3. Sliding window maximum: your actual lazy heap (#239)

Your source pushes `(value,index)` into a max-heap and removes expired entries only when they reach the top:

```cpp
heap.push(std::make_pair(nums[i], i));
while (heap.top().second <= i - k) heap.pop();
```

The current element is always valid, so the heap cannot become empty during this pruning. After pruning, the maximum remaining valid value is at the top.

The subtle complexity point is retained history. In a strictly increasing array, old smaller values can stay buried forever. Heap size can grow to n, so the bound is O(n log n) time and O(n) extra space, not guaranteed O(n log k)/O(k).

A monotonic deque could produce an O(n)/O(k) solution, but it is **not** the observed #239 implementation. The runnable template deliberately remains heap-based. It requires `1 <= k <= n`; invalid or empty-window requests throw `std::invalid_argument`.

## 4. Prefix dominance with negative numbers (#862)

For prefix sums `prefix[i]`, the query is:

```text
find smallest i-j > 0 with prefix[i]-prefix[j] >= target
```

A normal expand/shrink sum window is unreliable with negative values. The deque tracks candidate prefixes, using your source's orientation:

```text
front                                     back
newest / largest prefix -> ... -> oldest / smallest prefix
     push here                            test feasible here
```

At each endpoint `i`, two different deletions are justified:

1. **Pop from back while feasible.** If `prefix[i]-prefix[j] >= target`, record length `i-j`. A future endpoint paired with this same `j` would only be longer. Remove it and test the next candidate.
2. **Pop from front while dominated.** If the new prefix is no larger than an older prefix, the new index has a better or equal sum baseline and a shorter future distance. The older candidate will never be preferable.
3. Push `i` at the front.

```text
old j < new i, but prefix[i] <= prefix[j]
for every future r:
  prefix[r]-prefix[i] >= prefix[r]-prefix[j]
  r-i < r-j
therefore j is dominated
```

Both prefixes and differences use `long long`. The function checks prior indices before inserting the current one, so it asks for a **nonempty** subarray even when `target <= 0`. Empty input or no feasible subarray returns `-1`. Reversing the deque ends is fine only if every operation is reversed consistently.

## 5. Median is an ordering invariant plus a size invariant

Both #295 and #480 maintain:

```text
lower half                        upper half
 ... <= maxLower        <=        minUpper <= ...
 size lower = size upper, or size upper + 1
```

Then the median is either `maxLower` or the average of `maxLower` and `minUpper`. Cast **before adding** so `INT_MAX + INT_MAX` cannot overflow an integer expression.

### Insert-only: two heaps (#295)

`StreamMedian::addNum` inserts into the side selected by `maxLower`, then transfers one boundary element if sizes violate the invariant. One insertion changes the size difference by only one, so one transfer suffices. `findMedian()` throws on an empty stream.

### Deletion: identity and iterator ownership (#480)

Your source uses two ordered multisets, not removable heaps:

```text
(value, uniqueIndex) in descending lower multiset
(value, uniqueIndex) in ascending upper multiset
index -> its exact iterator in the owning multiset
```

The index disambiguates duplicate values. `push(index,value)` requires a unique live index; a repeated live ID throws. `remove(index)` returns false for a missing ID. An ID can be reused after removal.

When moving a boundary element between sets, erase the old iterator mapping and install the new one. Erasing a node invalidates that node's iterator; reading it afterward is not allowed. Copying containers with iterator maps would leave iterators pointing into the original object, so `IndexedMedian` explicitly disables copy and move operations rather than silently promising unsupported ownership semantics.

`slidingWindowMedian(nums,k)` composes these operations with array indices as IDs. It uses O(k) live storage and O(n log k) expected time (write O(n log(k+1)) if k=1 must be included algebraically). It validates `1 <= k <= n` and returns one median per complete window.

## Sources and adaptation record

| Actual problem | Exact observed submission | Retained pattern / explicit adaptation |
|---|---|---|
| [739. Daily Temperatures](https://leetcode.com/problems/daily-temperatures/) | [2146492152](https://leetcode.com/problems/daily-temperatures/submissions/2146492152/) | Strict next-greater indexed stack; generalized API name |
| [84. Largest Rectangle in Histogram](https://leetcode.com/problems/largest-rectangle-in-histogram/) | [2146612938](https://leetcode.com/problems/largest-rectangle-in-histogram/submissions/2146612938/) | Strict-pop indices and final drain; 64-bit area, nonnegative guard, combined drain loop |
| [901. Online Stock Span](https://leetcode.com/problems/online-stock-span/) | [2146501827](https://leetcode.com/problems/online-stock-span/submissions/2146501827/) | `(price,span)` compression; widened span and removed redundant branch |
| [907. Sum of Subarray Minimums](https://leetcode.com/problems/sum-of-subarray-minimums/) | [2132055030](https://leetcode.com/problems/sum-of-subarray-minimums/submissions/2132055030/) | Strict-right/non-strict-left ownership; signed-input modular normalization |
| [239. Sliding Window Maximum](https://leetcode.com/problems/sliding-window-maximum/) | [2149742695](https://leetcode.com/problems/sliding-window-maximum/submissions/2149742695/) | Lazy expiration max-heap; unified insertion loop and window validation |
| [862. Shortest Subarray with Sum at Least K](https://leetcode.com/problems/shortest-subarray-with-sum-at-least-k/) | [2152907567](https://leetcode.com/problems/shortest-subarray-with-sum-at-least-k/submissions/2152907567/) | Reversed deque orientation; widened prefixes/target, nonempty semantics |
| [295. Find Median from Data Stream](https://leetcode.com/problems/find-median-from-data-stream/) | [2150573901](https://leetcode.com/problems/find-median-from-data-stream/submissions/2150573901/) | Two heaps and pre-add floating conversion; empty guard |
| [480. Sliding Window Median](https://leetcode.com/problems/sliding-window-median/) | [2150661436](https://leetcode.com/problems/sliding-window-median/submissions/2150661436/) | Two multisets with iterator maps; unique-ID checks, explicit lifetime restrictions, empty guard |

## Run the checks

```sh
g++ -std=c++20 -O2 -Wall -Wextra -Werror test.cpp -o /tmp/monotonic-test
/tmp/monotonic-test
g++ -std=c++20 -O1 -g -Wall -Wextra -Werror -fsanitize=address,undefined -fno-omit-frame-pointer test.cpp -o /tmp/monotonic-sanitized
ASAN_OPTIONS=detect_leaks=0 /tmp/monotonic-sanitized
```

Deterministic edges plus 500 seeded randomized cases check stacks against direct scans, rectangles and subarray contributions against enumeration, shortest subarrays against O(n²) sums, every window size against sorted-window medians/maxima, and arbitrary indexed removals against a sorted live set. Tests include equal values, negative sums, invalid windows, empty medians, and integer extremes.

Sanitizer note: AddressSanitizer and UndefinedBehaviorSanitizer passed with leak detection disabled. LeakSanitizer cannot run under this execution environment’s ptrace setup; this is not a leak-check result. On an ordinary local shell, omit `ASAN_OPTIONS=detect_leaks=0` to attempt leak detection too.
