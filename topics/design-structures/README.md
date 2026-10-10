# Design structures

[All topics](../../README.md) · [Source index](../../SOURCES.md) · [Coverage](../../COVERAGE.md)

**12 captured problems · 18 accepted submission records.** Every linked implementation below is an unchanged captured source file. These notes describe the code; they do not replace it with a common API.

## Pattern reminders

### Recency and frequency are explicit order

- **Cue:** Eviction depends on recent access or on frequency with recency as a tie-break.
- **Idea and invariant:** 146 keeps MRU at the list front and stores key-to-iterator entries. The newer 460 uses one list per frequency plus minFreq; the older 460 uses an ordered set keyed by frequency/time. Moving an item must update its stored location.
- **Cost in these sources:** 146 has expected O(1) operations and O(capacity) storage. The bucket/list 460 has expected O(1) operations and O(capacity) live entries, but retains empty frequency buckets, so total storage also includes frequency buckets accumulated over time. The ordered-set LFU variant uses O(log capacity) operations and O(capacity) storage.
- **Read the originals:** [146. LRU Cache — 2143986850](originals/146__2143986850.cpp); [460. LFU Cache — 2144968388](originals/460__2144968388.cpp).

### Frequency with last-in tie-breaking

- **Cue:** Remove a value of maximum frequency, choosing its latest qualifying push.
- **Idea and invariant:** The newer 895 records a stack of values for each frequency and pops from the current maximum frequency. Its older source explicitly orders frequency and timestamps in a set.
- **Cost in these sources:** Frequency-stack variant: expected O(1) push/pop; ordered-set variant: logarithmic ordered operations. The frequency-stack source retains zero-frequency value entries, empty frequency vectors, and allocated vector capacity; total storage is not bounded solely by currently unpopped pushes.
- **Read the originals:** [895. Maximum Frequency Stack — 2146639743](originals/895__2146639743.cpp).

### Ordered history and bounded feeds

- **Cue:** Find the latest value no later than a timestamp, or keep only a small result while scanning history.
- **Idea and invariant:** 981 uses upper_bound and its predecessor in a timestamp map. 355 scans stored posts from the user and followed users into a size-10 heap. Its feed generation does not merge only the newest post from each user.
- **Cost in these sources:** 981 has O(log m) timestamp operations for m versions of a key. 355 feed generation is O(P log 10) for P scanned posts, plus followed-user traversal, with O(10) heap storage.
- **Read the originals:** [981. Time Based Key-Value Store — 2146746974](originals/981__2146746974.cpp); [355. Design Twitter — 2144760383](originals/355__2144760383.cpp).

### Adapters preserve an operation invariant

- **Cue:** Build one discipline from another container or retain an extra aggregate per entry.
- **Idea and invariant:** 225 moves the old queue behind the new element. 232 transfers the input stack only when the output stack is empty. 155 stores the minimum belonging to each stack depth. 150 pops the right operand before the left operand.
- **Cost in these sources:** 225 has O(n) push and O(1) top/pop. 232 has amortized O(1) operations. 155 uses O(1) operations and O(n) storage. RPN evaluation is O(n) time and O(n) stack storage.
- **Read the originals:** [225. Implement Stack using Queues — 2146459626](originals/225__2146459626.cpp); [232. Implement Queue using Stacks — 2146457265](originals/232__2146457265.cpp); [155. Min Stack — 2146461553](originals/155__2146461553.cpp); [150. Evaluate Reverse Polish Notation — 2146465049](originals/150__2146465049.cpp).

### Separate chaining with a fixed bucket count

- **Cue:** Implement map operations by hashing to a list and scanning for a key.
- **Idea and invariant:** 706 has exactly 32 buckets. Each bucket contains key/value pairs; updates and removals search the chain. The bucket count does not grow with the number of keys.
- **Cost in these sources:** O(chain length) per operation and O(n) storage. With a fixed 32 buckets, a general worst-case operation is O(n).
- **Read the originals:** [706. Design HashMap — 2144621524](originals/706__2144621524.cpp).

## Complete problem and variant index

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
