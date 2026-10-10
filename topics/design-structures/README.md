# Design structures

[All topics](../../README.md) · [Source index](../../SOURCES.md) · [Coverage](../../COVERAGE.md)

## Main algorithms and structures

Start with the operation that must stay cheap and the ordering or lookup invariant it requires. Links point to actual captured code, including its retained storage. Hash costs below are expected, vector append costs are amortized; neither implies worst-case O(1). Let c be cache capacity, d live distinct values, n current entries, H a container's peak size, P total pushes/posts, and B frequency buckets ever created. Space excludes returned results and includes retained capacity where material.

| Structure / recognition trigger | Time in the captured implementation | Stored / auxiliary space | Direct implementation |
|---|---|---|---|
| Hash map + doubly linked list: evict least recently used | Expected O(1) get/put | O(c) | [LRU excerpt](snippets/lru-cache.cpp) · [Full source](originals/146__2143986850.cpp) |
| Key→iterator + frequency→list buckets: LFU with recency ties | Expected O(1) get/put | O(c+B); empty frequency lists remain allocated | [Bucket LFU](snippets/lfu-cache.cpp) · [Full source](originals/460__2144968388.cpp) |
| Ordered set of (frequency,time,key,value): explicit eviction order | O(log(c+1)) get/put, with expected key-map access | O(c) | [Ordered-set LFU](originals/460__2144919830.cpp) |
| Frequency→stack plus value→frequency: most frequent, latest push wins | Expected amortized O(1) push/pop | O(P) retained upper bound; zero-frequency keys, empty buckets and vector capacities remain | [Frequency-stack excerpt](snippets/frequency-stack.cpp) · [Full source](originals/895__2146639743.cpp) |
| Ordered set + per-value timestamp stacks: explicit frequency/recency priority | Expected amortized O(log(d+1)) push/pop | O(P) retained upper bound; O(d) ordered records plus timestamp-vector capacities | [Ordered-set frequency stack](originals/895__2146625292.cpp) |
| Dense vector + value→index map: random access and unordered deletion | Expected amortized O(1) insert/remove; O(1) getRandom | O(H), retaining vector capacity after removals | [Swap-tail excerpt](snippets/randomized-set-swap-tail.cpp) · [Full source](originals/380__2125968160.cpp) |
| Key→ordered timestamp map: latest value no later than a query | O(log(m+1)) for m versions of that key, plus key hashing/string copying | O(T+K) records for T timestamps and K keys ever accessed, plus string contents | [Overwrite variant](originals/981__2146746974.cpp) · [Insert-only-at-new-timestamp variant](originals/981__2024512612.cpp) |
| Append-only histories + bounded min-heap: newest ten items across users | Feed O(F + S log 10) for F followees and S scanned posts; other operations expected amortized O(1) | Feed O(10); persistent O(P+R+U) for posts, follow relations and accessed users | [Full-history scan and bounded heap](originals/355__2144760383.cpp) |
| Value + prefix minimum at every stack depth | Vector push amortized O(1), other operations O(1); two-stack variant O(1) operations | O(H) vector capacity; O(n) logical two-stack entries | [Paired-vector version](originals/155__2146461553.cpp) · [Two-stack version](originals/155__2025573166.cpp) |
| Queue/stack adapters: reverse order once at the appropriate boundary | Stack from queues: push O(n), others O(1). Queue from stacks: amortized O(1), individual transfer O(n) | O(n) | [Queues→stack](originals/225__2146459626.cpp) · [Stacks→queue](originals/232__2146457265.cpp) |
| Stack/history evaluation: commands consume only the newest values | O(t) for t tokens with bounded token length; add parsing cost for longer strings | O(t) | [RPN](originals/150__2146465049.cpp) · [Score history](originals/682__2145817863.cpp) |
| Fixed-bucket separate chaining: map operations by scanning a chain | O(1+chain length); worst O(n), even with only 32 bucket heads | O(n+32) | [Custom-map excerpt](snippets/custom-hash-map.cpp) · [Full source](originals/706__2144621524.cpp) |

## Combinations and tricks

### Lookup + stable location + an eviction order

- **Recognize:** Access is by key, but removal is determined by an order unrelated to key value.
- **Compose:** Hash keys to list iterators; maintain most-recent at the front and least-recent at the back. LFU adds one such list per frequency and a minimum-frequency marker.
- **Invariant:** Every resident key's iterator identifies its current node. A hit changes order; a frequency increase moves the node into the next bucket. Evict the back of the minimum-frequency list.
- **Tradeoff / sources:** [LRU](originals/146__2143986850.cpp) uses splice without invalidating the node iterator and assumes positive capacity. [Bucket LFU](originals/460__2144968388.cpp) handles zero capacity but never erases empty frequency buckets, so memory can grow with accesses even at fixed capacity. [Ordered-set LFU](originals/460__2144919830.cpp) pays O(log c) and keeps only resident records; its timestamp makes the tie-break explicit.

### Frequency levels + recency stacks

- **Recognize:** Pop the most frequent value, breaking ties by the most recent qualifying push.
- **Compose:** Increment a value's frequency and push it onto that frequency's stack; pop from maxFreq and decrease maxFreq when that stack becomes empty.
- **Invariant:** The top of a frequency bucket is the latest still-valid push that reached that frequency. Lower-frequency records remain useful when higher-frequency pushes are undone; they are not duplicate records to delete eagerly.
- **Tradeoff / sources:** [Bucket/stack version](originals/895__2146639743.cpp) is expected amortized O(1), but allocated bucket capacities can outlive the current stack contents. [Set/timestamp version](originals/895__2146625292.cpp) stores one ordered record per live value and all of its unpopped timestamps, removing that value's maps when its frequency becomes zero. Surviving timestamp vectors can still retain their historical capacity.

### Dense storage + a back-pointer map

- **Recognize:** Need random indexed access and deletion, but no promise to preserve item order.
- **Compose:** Store values densely in a vector; map each value to its index; fill a deleted slot with the tail and repair the tail's map entry before popping it.
- **Invariant:** For every stored value v, vector[index[v]] == v. No holes remain, so choosing a vector index chooses a current member.
- **Tradeoff / sources:** [Swap-tail source](originals/380__2125968160.cpp) and [overwrite-tail source](originals/380__2116321400.cpp) implement the same idea. Their rand()%size sampling can be biased, assumes a nonempty set, and is not a stronger randomness guarantee. Stable order would invalidate this constant-time deletion trick.

### Ordered timestamps + predecessor search

- **Recognize:** A query asks what was true at or before a time, rather than for exact timestamp equality.
- **Compose:** Hash the key, then use upper_bound(timestamp) in its ordered version map and step back once if possible.
- **Invariant:** upper_bound is the first version strictly after the query; its predecessor is therefore the latest eligible one. There is no predecessor when the iterator equals begin.
- **Tradeoff / sources:** [Assignment-based set](originals/981__2146746974.cpp) overwrites a repeated timestamp; [insert-based set](originals/981__2024512612.cpp) preserves the first value. Both get methods use outer-map operator[], so even a missing-key read creates an empty history. The ordered map accepts arbitrary insertion order, with logarithmic cost.

### Scan many histories + retain only top k

- **Recognize:** The answer is small even though the source history is large.
- **Compose:** Scan posts from each followed user and the requesting user; push each timestamp/post pair into a size-10 min-heap, discard its smallest entry when oversized, then reverse heap extraction.
- **Invariant:** After each scanned post, the heap contains the newest ten seen so far; its root is the oldest retained candidate.
- **Tradeoff / source:** [The actual feed implementation](originals/355__2144760383.cpp) scans every relevant stored post on each request. A bounded answer does not make request time independent of history length, and the source does not perform a k-way newest-post merge. Self-follow would scan the user's posts twice; the implementation has no explicit self-follow guard.

### Store just enough history to undo the latest step

- **Recognize:** Operations remove the most recent item, or future answers need an aggregate of the surviving prefix.
- **Compose:** Pair each stack value with its minimum-so-far, or maintain synchronized value/minimum stacks. For command evaluation, retain operands or scores until a command consumes them.
- **Invariant:** Popping restores the previous prefix minimum without searching. In RPN, the first popped operand is the right operand, so subtraction and division preserve order. Score cancellation removes exactly the newest score.
- **Tradeoff / sources:** [Paired minima](originals/155__2146461553.cpp), [parallel minima](originals/155__2025573166.cpp), [RPN](originals/150__2146465049.cpp), and [score history](originals/682__2145817863.cpp) trade linear history storage for local operations and rely on the original valid-operation constraints.

### Put the expensive reversal where it can be amortized

- **Recognize:** Required FIFO/LIFO behavior differs from the available primitive container.
- **Compose:** [Stack from queues](originals/225__2146459626.cpp) moves the old queue behind each new item. [Queue from stacks](originals/232__2146457265.cpp) transfers all input elements only when the output stack is empty.
- **Invariant:** The queue-adapter's output top remains the oldest item; later pushes stay in the input stack. Each item crosses stacks at most once before removal.
- **Tradeoff:** Queue-adapter peek/pop can individually be O(n), despite amortized O(1). The stack-adapter instead pays O(n) on every push and makes top/pop O(1); mixing new input into nonempty output would break FIFO order.

### Audit the load factor before calling a hash map constant-time

- **Recognize:** A custom map hashes into lists but has no growth/rehash path.
- **Compose:** Compute key modulo bucket count, scan that list, then update/append/remove the matching pair.
- **Invariant:** All matching keys belong to the same chain; one stored pair per key makes put an upsert.
- **Tradeoff / source:** [The original fixed-32-bucket map](originals/706__2144621524.cpp) has average chain length n/32 under uniform distribution, so average chain work still grows linearly with n. Adversarial collisions also cost O(n). Standard unordered_map expectations cannot be transferred to this implementation.

## Problem and source appendix

All captured submissions are retained, including equivalent resubmissions and exact duplicates. Submission IDs distinguish files; they are not rankings of quality. The source itself is authoritative when a note is too brief.

### 146. LRU Cache

[Problem](https://leetcode.com/problems/lru-cache/) · Tags: Design, LRU cache, Linked lists

List MRU-front/LRU-back with key->iterator map; splice hit to front, evict back when full.

**Captured variants:** One observed approach.

- [Original 2143986850](originals/146__2143986850.cpp) · [LeetCode submission](https://leetcode.com/problems/lru-cache/submissions/2143986850/)

### 150. Evaluate Reverse Polish Notation

[Problem](https://leetcode.com/problems/evaluate-reverse-polish-notation/) · Tags: Stacks, Parsing

Push operands, pop right then left for binary operator.

**Captured variants:** Two equivalent evaluator sources.

- [Original 2146465049](originals/150__2146465049.cpp) · [LeetCode submission](https://leetcode.com/problems/evaluate-reverse-polish-notation/submissions/2146465049/)
- [Original 2025562806](originals/150__2025562806.cpp) · [LeetCode submission](https://leetcode.com/problems/evaluate-reverse-polish-notation/submissions/2025562806/)

### 155. Min Stack

[Problem](https://leetcode.com/problems/min-stack/) · Tags: Design, Stacks, Prefix aggregates

Store minimum-so-far beside each value or in parallel stack.

**Captured variants:** [2146461553](originals/155__2146461553.cpp) vector<pair<value,min>>; [2025573166](originals/155__2025573166.cpp) two synchronized stacks.

- [Original 2146461553](originals/155__2146461553.cpp) · [LeetCode submission](https://leetcode.com/problems/min-stack/submissions/2146461553/)
- [Original 2025573166](originals/155__2025573166.cpp) · [LeetCode submission](https://leetcode.com/problems/min-stack/submissions/2025573166/)

### 225. Implement Stack using Queues

[Problem](https://leetcode.com/problems/implement-stack-using-queues/) · Tags: Design, Queues

Push into spare queue then move old queue behind it; swap so front is newest.

**Captured variants:** One observed approach.

- [Original 2146459626](originals/225__2146459626.cpp) · [LeetCode submission](https://leetcode.com/problems/implement-stack-using-queues/submissions/2146459626/)

### 232. Implement Queue using Stacks

[Problem](https://leetcode.com/problems/implement-queue-using-stacks/) · Tags: Design, Amortized analysis, Stacks

Input stack for push; transfer all to output stack only when output empty.

**Captured variants:** One observed approach.

- [Original 2146457265](originals/232__2146457265.cpp) · [LeetCode submission](https://leetcode.com/problems/implement-queue-using-stacks/submissions/2146457265/)

### 355. Design Twitter

[Problem](https://leetcode.com/problems/design-twitter/) · Tags: Design, Heaps, Bounded top-k

Store append-only posts by user; scan followed and own posts into size-10 min heap, reverse output.

**Captured variants:** One observed approach.

- [Original 2144760383](originals/355__2144760383.cpp) · [LeetCode submission](https://leetcode.com/problems/design-twitter/submissions/2144760383/)

### 380. Insert Delete GetRandom O(1)

[Problem](https://leetcode.com/problems/insert-delete-getrandom-o1/) · Tags: Hash map, Dense vector, Randomized set

Unordered value→index map plus dense vector; deletion replaces/switches with tail and updates map; random index via rand()%size.

**Original-code context:** Average O(1) map operations; modulo RNG can be biased; assumes getRandom on nonempty set under task guarantee; contains() requires C++20.

**Captured variants:** 2 accepted C++ submissions captured; all original versions are retained.

- [Original 2125968160](originals/380__2125968160.cpp) · [LeetCode submission](https://leetcode.com/problems/insert-delete-getrandom-o1/submissions/2125968160/)
- [Original 2116321400](originals/380__2116321400.cpp) · [LeetCode submission](https://leetcode.com/problems/insert-delete-getrandom-o1/submissions/2116321400/)

### 460. LFU Cache

[Problem](https://leetcode.com/problems/lfu-cache/) · Tags: Design, LFU cache, Linked lists, Ordered sets

Latest frequency->list buckets and key->iterator map use MRU-front/LRU-back within a frequency, tracking minFreq. Older ordered set sorts (frequency,time,key,value).

**Captured variants:** [2144968388](originals/460__2144968388.cpp) expected O(1) bucket/list; [2144919830](originals/460__2144919830.cpp) O(log capacity) ordered set.

- [Original 2144968388](originals/460__2144968388.cpp) · [LeetCode submission](https://leetcode.com/problems/lfu-cache/submissions/2144968388/)
- [Original 2144919830](originals/460__2144919830.cpp) · [LeetCode submission](https://leetcode.com/problems/lfu-cache/submissions/2144919830/)

### 682. Baseball Game

[Problem](https://leetcode.com/problems/baseball-game/) · Tags: Stacks, Simulation

Maintain score history with cancel/double/sum-of-last-two commands.

**Captured variants:** One observed approach.

- [Original 2145817863](originals/682__2145817863.cpp) · [LeetCode submission](https://leetcode.com/problems/baseball-game/submissions/2145817863/)

### 706. Design HashMap

[Problem](https://leetcode.com/problems/design-hashmap/) · Tags: Design, Custom hash map, Separate chaining

Fixed 32 buckets, each list of key/value pairs; scan chain for upsert/get/remove.

**Captured variants:** One observed approach.

- [Original 2144621524](originals/706__2144621524.cpp) · [LeetCode submission](https://leetcode.com/problems/design-hashmap/submissions/2144621524/)

### 895. Maximum Frequency Stack

[Problem](https://leetcode.com/problems/maximum-frequency-stack/) · Tags: Design, Frequency buckets, Ordered sets

Latest keeps stack per frequency and per-value frequency; pop last value at highest frequency. Older maintains ordered set by (-frequency,-latest_timestamp,value).

**Captured variants:** [2146639743](originals/895__2146639743.cpp) frequency stacks; [2146625292](originals/895__2146625292.cpp) ordered set plus timestamp stacks.

- [Original 2146639743](originals/895__2146639743.cpp) · [LeetCode submission](https://leetcode.com/problems/maximum-frequency-stack/submissions/2146639743/)
- [Original 2146625292](originals/895__2146625292.cpp) · [LeetCode submission](https://leetcode.com/problems/maximum-frequency-stack/submissions/2146625292/)

### 981. Time Based Key-Value Store

[Problem](https://leetcode.com/problems/time-based-key-value-store/) · Tags: Ordered maps, Predecessor queries

Key maps to ordered timestamp/value map; upper_bound then predecessor finds most recent <=timestamp.

**Captured variants:** Two same data structure variants with overwrite semantics difference.

- [Original 2146746974](originals/981__2146746974.cpp) · [LeetCode submission](https://leetcode.com/problems/time-based-key-value-store/submissions/2146746974/)
- [Original 2024512612](originals/981__2024512612.cpp) · [LeetCode submission](https://leetcode.com/problems/time-based-key-value-store/submissions/2024512612/)
