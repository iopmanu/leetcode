# Monotonic structures and heaps

[All topics](../../README.md) · [Source index](../../SOURCES.md) · [Coverage](../../COVERAGE.md)

**17 captured problems · 34 accepted submission records.** Every linked implementation below is an unchanged captured source file. These notes describe the code; they do not replace it with a common API.

## Pattern reminders

### Monotonic stack boundaries

- **Cue:** An incoming value settles an earlier next-greater/next-smaller question, or closes a contribution interval.
- **Idea and invariant:** 84 gives each popped height its maximal span. 907 gives a popped minimum a left-choice count and right-choice count; its strict comparison assigns equal-value ownership consistently. 739 holds unresolved temperatures, and 901 combines spans of popped prices.
- **Cost in these sources:** Each item enters and leaves once: O(n) total time and O(n) worst-case storage; stock span is amortized O(1) per call.
- **Read the originals:** [84. Largest Rectangle in Histogram — 2146612938](originals/84__2146612938.cpp); [907. Sum of Subarray Minimums — 2132055030](originals/907__2132055030.cpp); [739. Daily Temperatures — 2146492152](originals/739__2146492152.cpp); [901. Online Stock Span — 2146501827](originals/901__2146501827.cpp).

### Monotonic prefix candidates

- **Cue:** Negative values prevent an ordinary positive-sum sliding window.
- **Idea and invariant:** 862 uses prefix sums. Its deque orientation is source-specific: newest candidates are at the front, while feasible oldest/minimum starts are removed from the back. Dominated candidates leave from the front. The older accepted sources use a min-heap.
- **Cost in these sources:** Deque variant: O(n) time and O(n) storage. Heap variants: O(n log n) time and O(n) storage.
- **Read the originals:** [862. Shortest Subarray with Sum at Least K — 2152907567](originals/862__2152907567.cpp).

### A heap exposes the next relevant extremum

- **Cue:** Advance the smallest of several list heads, maintain a rank, or expire stale candidates.
- **Idea and invariant:** 632 keeps one head per list and the current maximum. 703 keeps only k values in a min-heap. 239 removes expired indices only when they reach the heap top, so stale entries below the top may remain.
- **Cost in these sources:** 632 is O(N log k) for N consumed elements from k lists. 703 is O(log k) per insertion. The captured lazy-expiry 239 is O(n log n) time and O(n) worst-case heap storage, not a size-k deque.
- **Read the originals:** [632. Smallest Range Covering Elements from K Lists — 2154226064](originals/632__2154226064.cpp); [703. Kth Largest Element in a Stream — 2144654284](originals/703__2144654284.cpp); [239. Sliding Window Maximum — 2149742695](originals/239__2149742695.cpp).

### Balanced halves for medians

- **Cue:** Report a middle value after additions, or after exact indexed deletions.
- **Idea and invariant:** 295 keeps a max-heap lower half and min-heap upper half. 480 instead uses two multisets of value/index pairs and maps indices to iterators. The lower half has equal size or one extra element, and every lower value precedes every upper value.
- **Cost in these sources:** 295: O(log n) insertion and O(1) median. 480: O(n log k) total time and O(k) storage for a window of k.
- **Read the originals:** [295. Find Median from Data Stream — 2150573901](originals/295__2150573901.cpp); [480. Sliding Window Median — 2150661436](originals/480__2150661436.cpp).

### Greedy subsequences and suffix comparison

- **Cue:** Choose k digits from two sequences while retaining order and maximizing the merge.
- **Idea and invariant:** 321 enumerates the split, uses a discard budget to build each maximum subsequence, then compares entire remaining suffixes when merging. Equal leading digits alone cannot decide which side to take.
- **Cost in these sources:** For s feasible splits, O(s * (m+n+k squared)) is a conservative bound because suffix comparison can rescan up to k digits per merge step. Auxiliary sequence storage is O(m+n+k).
- **Read the originals:** [321. Create Maximum Number — 2154885660](originals/321__2154885660.cpp).

## Complete problem and variant index

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

### 1046. Last Stone Weight

[Problem](https://leetcode.com/problems/last-stone-weight/) · Tags: Heaps, Simulation

Repeatedly remove two largest weights and reinsert positive difference.

**Captured variants:** One observed approach.

- [Original 2144668025](originals/1046__2144668025.cpp) · [LeetCode submission](https://leetcode.com/problems/last-stone-weight/submissions/2144668025/)
