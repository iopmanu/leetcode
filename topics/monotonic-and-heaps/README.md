# Monotonic structures and heaps

[All topics](../../README.md) · [Source index](../../SOURCES.md) · [Coverage](../../COVERAGE.md)

**22 captured problems · 42 accepted submission records.** Every linked implementation below is an unchanged captured source file. These notes describe the code; they do not replace it with a common API.

## Main algorithms and structures

Use a monotonic structure when a new item permanently dominates or resolves old candidates; use a heap when only the next extremum must be exposed. `n` is input length, `k` a retained/window size, `a` the number of task types, and `N` the total number of elements across lists. Space excludes returned output; persistent structures include their retained contents. Hash-map operations below are expected-time.

| Algorithm / structure | What it maintains | Time in these implementations | Auxiliary space | Direct implementation |
| --- | --- | --- | --- | --- |
| Monotonic index stack | Unresolved next-greater indices or nondecreasing candidate heights | O(n) total; each index pushes/pops once | O(n) | [Next warmer value](originals/739__2146492152.cpp), [histogram spans](originals/84__2146612938.cpp) |
| Stack contribution counting | A popped minimum owns a left-choice × right-choice rectangle of subarrays | O(n) | O(n) | [Sum of minima](originals/907__2132055030.cpp) |
| Compressed monotonic stack | Each price stores the consecutive span it represents | Amortized O(1) per call, O(n) for one worst-case call; O(n) over n calls | O(n) persistent | [Online stock span](originals/901__2146501827.cpp) |
| Prefix sums + monotonic deque | Later, no-larger prefixes dominate earlier starts | O(n) | O(n) explicit prefix array + deque | [Shortest qualifying subarray](originals/862__2152907567.cpp) |
| Prefix sums + min-heap | Repeatedly expose the smallest previous prefix that now qualifies | O(n log n) | O(n) | [Heap alternative](originals/862__2152891991.cpp) |
| Bounded heap for top k | The root is the worst of the retained k candidates | O(n log(k+1)) batch; O(log(k+1)) stream insertion | O(k) | [Streaming kth largest](originals/703__2144654284.cpp), [closest points](originals/973__2157563441.cpp), [matrix rank](originals/378__2126186308.cpp) |
| Heap with lazy expiry | The root is the best currently unexpired indexed value | O(n log n) worst case | O(n), because stale non-root entries remain | [Window maximum](originals/239__2149742695.cpp) |
| Two heaps for a running median | Lower max-heap and upper min-heap have ordered contents and balanced sizes | O(log n) insertion, O(1) median | O(n) persistent | [Insertion-only median](originals/295__2150573901.cpp) |
| Two ordered multisets + iterator maps | Same ordered halves, with exact indexed deletion | Expected O(n log(k+1)) total, O(1) median; pathological hash maps can add O(nk) | O(k) trees + maps, plus O(n−k+1) output | [Sliding median](originals/480__2150661436.cpp) |
| One min-heap head per sorted list | Current minimum head and separately tracked maximum cover every list | O(N log(k+1)) worst case for k lists | O(k) | [Smallest covering range](originals/632__2154226064.cpp) |
| Extremum-driven simulation | Repeatedly consume the largest remaining quantities | Stone merging O(n log n); scheduling O(n log(a+1)) with fixed alphabet a≤26 | O(n) stones; O(a) task counts, heap, and batch | [Stone collisions](originals/1046__2144668025.cpp), [cooldown batches](originals/621__2144706913.cpp) |
| Stack of surviving interactions | Only the newest surviving right-moving asteroid can meet the incoming left-moving one | O(n) | O(n), plus O(n) copied output | [Collision stack](originals/735__2146489128.cpp) |
| Sorted positions + monotonic arrival times | Dominated arrival times collapse into the fleet ahead | O(n log n), including sort | O(n) pair copy + stack | [Fleet aggregation](originals/853__2146549976.cpp) |
| Two boundary maxima / basin stack | Settle water at a limiting boundary, or close a bounded basin | O(n) in either variant | O(1) two pointers; O(n) stack | [Boundary maxima](originals/42__2147811654.cpp), [basin stack](originals/42__2131872743.cpp) |
| Greedy subsequence + suffix merge | Spend a discard budget, then merge by entire remaining suffix order | For s splits and input lengths m,n: O(s(m+n+k²)) worst case | O(m+n+k) temporary sequences | [Maximum-number composition](originals/321__2154885660.cpp) |
| Budgeted monotone digit deletion | Earlier smaller digits dominate larger suffix digits | O(n), each digit enters and leaves the deque at most once | O(n) deque, plus returned string | [Original digit deque](originals/402__2170593075.cpp) |
| Circular next-greater scan | A non-increasing stack contains unresolved original indexes | O(n), two scans and at most n pushes/pops | O(n) pending indexes and O(n) output | [Two-pass circular resolution](originals/503__2170588083.cpp) |
| Run-length reduction stack | Adjacent surviving equal characters occupy one counted run | O(n), including reconstruction | O(n) runs and output | [Character/count cancellation](originals/1209__2170583612.cpp) |
| Greedy stack-sequence simulation | Consume every currently forced matching pop | O(n), at most n pushes/pops | O(n) stack | [Push then drain matching pops](originals/946__2170572277.cpp) |

## Combinations and tricks

### Turn a pop into the final answer for that candidate

- **Recognize:** A new value supplies the first boundary that makes an old candidate stop being useful.
- **Compose:** Monotonic indices + pop-time accounting in [histogram spans](originals/84__2146612938.cpp), [warmer-day distances](originals/739__2146492152.cpp), and [subarray-minimum contributions](originals/907__2132055030.cpp).
- **Invariant:** After popping index p, the new stack top is its surviving left boundary and the current index is its first qualifying right boundary. Each index can be charged only once.
- **Tradeoff / trap:** Equality decides ownership. The minimum-sum source pops on strictly smaller values, so the previous boundary is less-or-equal and the next boundary is strictly less; equal minima must not all claim the same subarrays. The histogram explicitly drains at n; the contribution code uses a guarded virtual end position without reading `arr[n]`.

### Store aggregate work on the monotonic stack

- **Recognize:** A popped value represents a whole block, not just one earlier index.
- **Compose:** A decreasing price stack + counts in [stock span](originals/901__2146501827.cpp).
- **Invariant:** `(price,span)` summarizes consecutive days already absorbed. Popping a price no greater than today's adds its entire span; those days never need individual reconsideration.
- **Tradeoff / trap:** Constant cost is amortized across calls. One new maximum can pop the entire stack, and a decreasing stream retains O(n) entries.

### Replace positive-value windows with prefix dominance

- **Recognize:** Negative values break the rule that removing the leftmost item decreases the window sum.
- **Compose:** Prefix sums + monotonic candidate deque in [the linear shortest-subarray source](originals/862__2152907567.cpp).
- **Invariant:** If a later prefix is no larger than an earlier one, it gives at least as large a future sum with a shorter interval. Once a start qualifies, recording its current length and removing it cannot lose a better future length for that start.
- **Tradeoff / trap:** This deque is reversed from common presentations: newest entries and dominance removal are at the front; oldest/smallest qualifying starts leave at the back. The [heap variant](originals/862__2152891991.cpp) costs O(n log n). Both retained forms use `int` prefix sums; wider numeric domains require a separate widening change, not an assumed property of the originals.

### Add deletion identity to a median structure

- **Recognize:** A sliding median must remove a particular occurrence among duplicate values.
- **Compose:** Balanced lower/upper multisets of `(value,index)` + index-to-iterator hash maps in [the sliding median source](originals/480__2150661436.cpp).
- **Invariant:** Every lower value precedes every upper value, and lower size equals upper size or exceeds it by one. Whenever rebalancing moves an item, its iterator mapping moves too.
- **Tradeoff / trap:** These are ordered multisets despite the member names `leftHeap` and `rightHeap`; arbitrary removal is real, not lazy heap deletion. Maps add O(k) storage and expected-time lookup. The [stream median](originals/295__2150573901.cpp) needs only heaps because it never removes old items.

### Distinguish bounded retention from lazy expiry

- **Recognize:** Both problems mention a window or k, but they discard items for different reasons.
- **Compose:** [Top-k retention](originals/703__2144654284.cpp) pops the worst item immediately; [window maximum](originals/239__2149742695.cpp) attaches indices and pops expired values only at the root.
- **Invariant:** A bounded heap contains only candidates for the global top k. A lazy-expiry heap guarantees only that its exposed root belongs to the current window.
- **Tradeoff / trap:** An increasing window stream can leave almost every old, smaller value buried in the heap. The retained window-maximum code therefore has O(n) heap storage and O(n log n) time; an O(k) monotonic window deque would be a different, uncaptured implementation.

### Sweep several sorted lists with one live representative each

- **Recognize:** Need a range covering every list, rather than merely the globally smallest values.
- **Compose:** A min-heap of `(value,row,column)` + current maximum in [the covering-range source](originals/632__2154226064.cpp).
- **Invariant:** The heap has one current representative from each list. Only advancing a list that supplies the current minimum can improve the lower endpoint; sortedness makes the tracked maximum monotone.
- **Tradeoff / trap:** Stop as soon as a list is exhausted. The [matrix-rank source](originals/378__2126186308.cpp) instead visits every matrix cell with a bounded max-heap; it does not implement a sorted-row merge or value-domain binary search.

### Build maximal subsequences before lexicographic merging

- **Recognize:** Choose an ordered subsequence from each of two inputs, but the number taken from each is unknown.
- **Compose:** Enumerate feasible splits + a monotonic discard-budget selection + suffix comparison in [the maximum-number source](originals/321__2154885660.cpp).
- **Invariant:** A larger arriving digit can remove smaller earlier digits only while the deletion budget permits. During merge, equal front digits require comparing the complete remaining suffixes.
- **Tradeoff / trap:** `span` avoids copying those suffixes, but comparing them still takes time: repeated ties can make one merge O(k²). Selection temporarily stores the whole scanned sequence before resizing; claiming O(k) total auxiliary memory would miss those allocations.

### Process independent choices in cooldown-sized batches

- **Recognize:** Several task types compete for execution, and the same type cannot recur within the next cooldown positions.
- **Compose:** Frequency map + max-heap + a temporary batch in [the scheduler source](originals/621__2144706913.cpp).
- **Invariant:** Pop each chosen type at most once per batch and reinsert its decremented count only after the batch. A nonfinal batch accounts for the entire cooldown length; the last contributes only its actual task count.
- **Tradeoff / trap:** The source does not iterate once per idle slot, so large cooldown values do not add that many heap operations. Its O(n log(a+1)) work becomes O(n) for the fixed 26-letter task alphabet.

### Combine a monotone frontier with a deletion budget

- **Recognize:** Minimize a fixed-length subsequence under lexicographic order while preserving original order.
- **Compose:** [The original digit deque](originals/402__2170593075.cpp) removes a larger back digit only while deletion budget remains. Once the input ends, unused deletions remove the largest-position suffix; leading-zero removal is a separate representation step.
- **Invariant:** With budget available, the next smaller digit improves the earliest differing position. Once the budget is exhausted, surviving digits are appended unchanged; the entire final deque need not remain monotone.
- **Tradeoff / trap:** The source uses a deque so suffix deletions and leading-zero cleanup are both constant-time per removal. Numeric formatting is specific to this problem: leading-zero removal must not be copied into a general fixed-length subsequence template.

### Replay candidates without registering them twice

- **Recognize:** A next-greater relation wraps at the end of an array.
- **Compose:** [The two-pass source](originals/503__2170588083.cpp) combines a non-increasing stack of original indexes with a second pass over values. Register indexes only during the first pass.
- **Invariant:** Each pending index is assigned at its first strictly larger candidate in circular order; it leaves the stack once. No duplicate index bookkeeping is needed during replay.
- **Tradeoff / trap:** Equal values do not satisfy the strict relation. Unresolved entries retain -1. The newest variant always makes the second scan; the older captured variant has an additional early-break condition.

### Compress reversible state into run counts

- **Recognize:** Equal adjacent values cancel only when a threshold count is reached, and cancellation may expose an earlier group.
- **Compose:** [The counted-run deque](originals/1209__2170583612.cpp) stores character/count pairs. An equal input increments the top count; reaching k removes the run.
- **Invariant:** The stack is the reduced prefix; deleting its last run makes the prior reduced boundary available for future input.
- **Tradeoff / trap:** The code uses a deque as a stack and reconstructs the string afterwards. It relies on k >= 2: the newly created singleton branch continues without checking the threshold.

### Drain all currently enabled transitions

- **Recognize:** A prescribed output order must be realizable using one stack and an input stream.
- **Compose:** [The original simulation](originals/946__2170572277.cpp) pushes one value, then drains every top matching the next requested output.
- **Invariant:** Popping a matching top immediately cannot obstruct any required earlier output; delaying it adds no useful choice. At termination an empty stack certifies the target under equal-length input constraints.
- **Tradeoff / trap:** This is an ordinary simulation stack, not a monotone stack. The unguarded popped[r] access uses the original equal-length/distinct-value contract.

## Problem and source appendix


All captured submissions are retained, including equivalent resubmissions and exact duplicates. Submission IDs distinguish files; they are not rankings of quality. The source itself is authoritative when a note is too brief.

### 42. Trapping Rain Water

[Problem](https://leetcode.com/problems/trapping-rain-water/) · Tags: Two pointers, Monotonic stack

Two-pointer boundary maxima accumulate water at lower endpoint; alternate decreasing stack pops basin bottom and computes bounded layer.

**Captured variants:** Four two-pointer forms including single global limiting max; two stack forms.

- [Original 2147811654](originals/42__2147811654.cpp) · [LeetCode submission](https://leetcode.com/problems/trapping-rain-water/submissions/2147811654/)
- [Original 2143469631](originals/42__2143469631.cpp) · [LeetCode submission](https://leetcode.com/problems/trapping-rain-water/submissions/2143469631/)
- [Original 2142850361](originals/42__2142850361.cpp) · [LeetCode submission](https://leetcode.com/problems/trapping-rain-water/submissions/2142850361/)
- [Original 2131909942](originals/42__2131909942.cpp) · [LeetCode submission](https://leetcode.com/problems/trapping-rain-water/submissions/2131909942/)
- [Original 2131872743](originals/42__2131872743.cpp) · [LeetCode submission](https://leetcode.com/problems/trapping-rain-water/submissions/2131872743/)
- [Original 2131851296](originals/42__2131851296.cpp) · [LeetCode submission](https://leetcode.com/problems/trapping-rain-water/submissions/2131851296/)

### 84. Largest Rectangle in Histogram

[Problem](https://leetcode.com/problems/largest-rectangle-in-histogram/) · Tags: Monotonic stack, Range boundaries

Increasing stack of indices; on smaller height, popped bar spans after new stack top through i-1; drain at n.

**Captured variants:** Four equivalent monotonic-index sources.

- [Original 2146612938](originals/84__2146612938.cpp) · [LeetCode submission](https://leetcode.com/problems/largest-rectangle-in-histogram/submissions/2146612938/)
- [Original 2143497674](originals/84__2143497674.cpp) · [LeetCode submission](https://leetcode.com/problems/largest-rectangle-in-histogram/submissions/2143497674/)
- [Original 2132956467](originals/84__2132956467.cpp) · [LeetCode submission](https://leetcode.com/problems/largest-rectangle-in-histogram/submissions/2132956467/)
- [Original 2132944465](originals/84__2132944465.cpp) · [LeetCode submission](https://leetcode.com/problems/largest-rectangle-in-histogram/submissions/2132944465/)

### 239. Sliding Window Maximum

[Problem](https://leetcode.com/problems/sliding-window-maximum/) · Tags: Heaps, Sliding windows, Lazy removal

Max heap of (value,index), discard expired entries only when they reach top.

**Captured variants:** Two heap variants differ tie order.

- [Original 2149742695](originals/239__2149742695.cpp) · [LeetCode submission](https://leetcode.com/problems/sliding-window-maximum/submissions/2149742695/)
- [Original 2024277288](originals/239__2024277288.cpp) · [LeetCode submission](https://leetcode.com/problems/sliding-window-maximum/submissions/2024277288/)

### 295. Find Median from Data Stream

[Problem](https://leetcode.com/problems/find-median-from-data-stream/) · Tags: Heaps, Median

Max-heap lower half and min-heap upper half; rebalance size difference to left=right or left=right+1.

**Captured variants:** Three equivalent implementations; baseline sorted vector exists only as comment, not source algorithm.

- [Original 2150573901](originals/295__2150573901.cpp) · [LeetCode submission](https://leetcode.com/problems/find-median-from-data-stream/submissions/2150573901/)
- [Original 2144767620](originals/295__2144767620.cpp) · [LeetCode submission](https://leetcode.com/problems/find-median-from-data-stream/submissions/2144767620/)
- [Original 2133767286](originals/295__2133767286.cpp) · [LeetCode submission](https://leetcode.com/problems/find-median-from-data-stream/submissions/2133767286/)

### 321. Create Maximum Number

[Problem](https://leetcode.com/problems/create-maximum-number/) · Tags: Monotonic stack, Greedy, Lexicographic merge

Enumerate split of k across arrays, select max subsequence with discard budget, merge by comparing entire remaining suffixes.

**Captured variants:** One observed approach.

- [Original 2154885660](originals/321__2154885660.cpp) · [LeetCode submission](https://leetcode.com/problems/create-maximum-number/submissions/2154885660/)

### 378. Kth Smallest Element in a Sorted Matrix

[Problem](https://leetcode.com/problems/kth-smallest-element-in-a-sorted-matrix/) · Tags: Heaps, Order statistics

Scan every matrix value maintaining k smallest in max heap.

**Captured variants:** One observed approach.

- [Original 2126186308](originals/378__2126186308.cpp) · [LeetCode submission](https://leetcode.com/problems/kth-smallest-element-in-a-sorted-matrix/submissions/2126186308/)

### 480. Sliding Window Median

[Problem](https://leetcode.com/problems/sliding-window-median/) · Tags: Ordered multisets, Median, Iterator indexing

Two balanced multisets of (value,index) plus maps index->iterator support insertion, deletion, and median.

**Captured variants:** One source; no lazy-deletion heap in actual code.

- [Original 2150661436](originals/480__2150661436.cpp) · [LeetCode submission](https://leetcode.com/problems/sliding-window-median/submissions/2150661436/)

### 621. Task Scheduler

[Problem](https://leetcode.com/problems/task-scheduler/) · Tags: Heaps, Greedy scheduling

Consume up to n+1 distinct most-frequent task types per round, reinsert remaining counts, count full round unless terminal.

**Captured variants:** One observed approach.

- [Original 2144706913](originals/621__2144706913.cpp) · [LeetCode submission](https://leetcode.com/problems/task-scheduler/submissions/2144706913/)

### 632. Smallest Range Covering Elements from K Lists

[Problem](https://leetcode.com/problems/smallest-range-covering-elements-from-k-lists/) · Tags: Heaps, K-way merge

Heap holds one head per list and scalar tracks current maximum; advance current minimum list and improve range.

**Captured variants:** One observed approach.

- [Original 2154226064](originals/632__2154226064.cpp) · [LeetCode submission](https://leetcode.com/problems/smallest-range-covering-elements-from-k-lists/submissions/2154226064/)

### 703. Kth Largest Element in a Stream

[Problem](https://leetcode.com/problems/kth-largest-element-in-a-stream/) · Tags: Heaps, Streaming order statistics

Maintain size-k min heap so root is kth largest seen.

**Captured variants:** One observed approach.

- [Original 2144654284](originals/703__2144654284.cpp) · [LeetCode submission](https://leetcode.com/problems/kth-largest-element-in-a-stream/submissions/2144654284/)

### 735. Asteroid Collision

[Problem](https://leetcode.com/problems/asteroid-collision/) · Tags: Stacks, Simulation

Only right-moving stack top and incoming left-moving item can collide; pop weaker until incoming destroyed or no conflict.

**Captured variants:** Two equivalent collision algorithms with container/initialization differences.

- [Original 2146489128](originals/735__2146489128.cpp) · [LeetCode submission](https://leetcode.com/problems/asteroid-collision/submissions/2146489128/)
- [Original 2025582812](originals/735__2025582812.cpp) · [LeetCode submission](https://leetcode.com/problems/asteroid-collision/submissions/2025582812/)

### 739. Daily Temperatures

[Problem](https://leetcode.com/problems/daily-temperatures/) · Tags: Monotonic stack, Next greater

Keep unresolved decreasing temperatures by index; warmer incoming value resolves waiting distances.

**Captured variants:** Three equivalent stack implementations.

- [Original 2146492152](originals/739__2146492152.cpp) · [LeetCode submission](https://leetcode.com/problems/daily-temperatures/submissions/2146492152/)
- [Original 2131986928](originals/739__2131986928.cpp) · [LeetCode submission](https://leetcode.com/problems/daily-temperatures/submissions/2131986928/)
- [Original 2025552405](originals/739__2025552405.cpp) · [LeetCode submission](https://leetcode.com/problems/daily-temperatures/submissions/2025552405/)

### 853. Car Fleet

[Problem](https://leetcode.com/problems/car-fleet/) · Tags: Monotonic stack, Greedy

Sort cars by position ascending; arrival-time stack pops fleets behind that catch a later slower fleet.

**Captured variants:** Two equivalent variants, storing speed or precomputed time.

- [Original 2146549976](originals/853__2146549976.cpp) · [LeetCode submission](https://leetcode.com/problems/car-fleet/submissions/2146549976/)
- [Original 2146548870](originals/853__2146548870.cpp) · [LeetCode submission](https://leetcode.com/problems/car-fleet/submissions/2146548870/)

### 862. Shortest Subarray with Sum at Least K

[Problem](https://leetcode.com/problems/shortest-subarray-with-sum-at-least-k/) · Tags: Monotonic deque, Prefix sums, Heaps

Newest deque stores candidate prefixes in reverse orientation: newest at front, oldest/minimum at back; pop feasible starts from back and dominated prefixes from front. Older min-heap pops feasible prior prefixes.

**Captured variants:** [2152907567](originals/862__2152907567.cpp) O(n) monotonic deque; [2152891991](originals/862__2152891991.cpp)/[2152436083](originals/862__2152436083.cpp) O(n log n) prefix-min heap.

- [Original 2152907567](originals/862__2152907567.cpp) · [LeetCode submission](https://leetcode.com/problems/shortest-subarray-with-sum-at-least-k/submissions/2152907567/)
- [Original 2152891991](originals/862__2152891991.cpp) · [LeetCode submission](https://leetcode.com/problems/shortest-subarray-with-sum-at-least-k/submissions/2152891991/)
- [Original 2152436083](originals/862__2152436083.cpp) · [LeetCode submission](https://leetcode.com/problems/shortest-subarray-with-sum-at-least-k/submissions/2152436083/)

### 901. Online Stock Span

[Problem](https://leetcode.com/problems/online-stock-span/) · Tags: Monotonic stack, Aggregated spans

Stack holds (price,span); pop <=price and combine spans before pushing new price.

**Captured variants:** One observed approach.

- [Original 2146501827](originals/901__2146501827.cpp) · [LeetCode submission](https://leetcode.com/problems/online-stock-span/submissions/2146501827/)

### 907. Sum of Subarray Minimums

[Problem](https://leetcode.com/problems/sum-of-subarray-minimums/) · Tags: Monotonic stack, Contribution counting

Pop minimum indices and multiply value by left choices and right choices; final i=n drains stack.

**Captured variants:** One observed approach.

- [Original 2132055030](originals/907__2132055030.cpp) · [LeetCode submission](https://leetcode.com/problems/sum-of-subarray-minimums/submissions/2132055030/)

### 973. K Closest Points to Origin

[Problem](https://leetcode.com/problems/k-closest-points-to-origin/) · Tags: Bounded max-heap, Top-k

Maintain max-heap of {squared distance,x,y}, removing farthest when size exceeds k.

**Original-code context:** Default priority_queue and explicit less<> variants are equivalent. int distance is safe for this problem bounds but cast after multiplication would not prevent overflow for wider coordinates.

**Captured variants:** 3 accepted C++ submissions retained; distinctions are described above.

- [Original 2157563441](originals/973__2157563441.cpp) · [LeetCode submission](https://leetcode.com/problems/k-closest-points-to-origin/submissions/2157563441/)
- [Original 2157563214](originals/973__2157563214.cpp) · [LeetCode submission](https://leetcode.com/problems/k-closest-points-to-origin/submissions/2157563214/)
- [Original 2144675588](originals/973__2144675588.cpp) · [LeetCode submission](https://leetcode.com/problems/k-closest-points-to-origin/submissions/2144675588/)

### 1046. Last Stone Weight

[Problem](https://leetcode.com/problems/last-stone-weight/) · Tags: Heaps, Simulation

Repeatedly remove two largest weights and reinsert positive difference.

**Captured variants:** One observed approach.

- [Original 2144668025](originals/1046__2144668025.cpp) · [LeetCode submission](https://leetcode.com/problems/last-stone-weight/submissions/2144668025/)

### 402. Remove K Digits

[Problem](https://leetcode.com/problems/remove-k-digits/)

A deque stores the surviving digit sequence. Remove a larger suffix digit while deletion budget remains, then trim the remaining suffix budget and leading zeros. The original retains its early k >= num.size() guard and returns zero when no nonzero digit survives.

- [Original 2170593075](originals/402__2170593075.cpp) · [LeetCode submission](https://leetcode.com/problems/remove-k-digits/submissions/2170593075/)

### 503. Next Greater Element II

[Problem](https://leetcode.com/problems/next-greater-element-ii/)

Two passes resolve pending next-greater indexes. Only the first pass pushes indexes; the second supplies wraparound candidates. Both accepted variants are preserved; the older one additionally stops when the pending stack is empty or the scan reaches its last pending index. Strict comparison leaves equal values unresolved.

- [Original 2170588083](originals/503__2170588083.cpp) · [LeetCode submission](https://leetcode.com/problems/next-greater-element-ii/submissions/2170588083/)
- [Original 2170587971](originals/503__2170587971.cpp) · [LeetCode submission](https://leetcode.com/problems/next-greater-element-ii/submissions/2170587971/)

### 1209. Remove All Adjacent Duplicates in String II

[Problem](https://leetcode.com/problems/remove-all-adjacent-duplicates-in-string-ii/)

Run-length stack of character/count pairs. Removing a group exposes the previous group, which can combine with later input. Reconstruction appends each remaining run. The original assumes k >= 2; a newly pushed count of one is not checked for deletion.

- [Original 2170583612](originals/1209__2170583612.cpp) · [LeetCode submission](https://leetcode.com/problems/remove-all-adjacent-duplicates-in-string-ii/submissions/2170583612/)

### 946. Validate Stack Sequences

[Problem](https://leetcode.com/problems/validate-stack-sequences/)

Push each arrival, then consume the maximal prefix of requested pops that matches the current top. The deque is used as a stack. The original indexes popped[r] without a separate bounds guard and relies on the source contract: equal lengths and distinct values.

- [Original 2170572277](originals/946__2170572277.cpp) · [LeetCode submission](https://leetcode.com/problems/validate-stack-sequences/submissions/2170572277/)
