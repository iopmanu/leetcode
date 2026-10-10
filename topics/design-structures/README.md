# Design structures: make the eviction rule visible

These templates come from your observed Accepted C++ implementations of LRU/LFU caches, a chained hash map, a frequency stack, and Twitter. The recurring idea is to separate lookup from ordering: a hash map finds the object, while a list, bucket, set, or heap expresses what should happen next.

[Templates](templates.hpp) · [Executable tests](test.cpp) · Namespace: `patterns::design`

## API and contract

| Type | Public operations | Policy | Main complexity |
|---|---|---|---|
| `LRUCache(capacity)` | `get(key)`, `put(key,value)` | Evict least recently used | Expected O(1) per operation, O(C) state |
| `LFUCache(capacity)` | `get`, `put` | Lowest frequency, then least recent | Expected O(1) per operation, O(C) state |
| `LFUCacheOrdered(capacity)` | `get`, `put` | Same policy via ordered tuple | Expected O(log(C+1)) per operation, O(C) state |
| `MyHashMap` | `get`, `put`, `remove` | Fixed 32 separate chains | O(chain length), O(N) state |
| `FreqStack` | `push(value)`, `pop()` | Highest frequency, then latest push | Expected/amortized O(1) per operation |
| `Twitter` | `postTweet`, `follow`, `unfollow`, `getNewsFeed` | Newest relevant posts | Feed scans relevant historical posts |

Hash maps/sets have expected constant-time lookup, not worst-case constant time. Caches normalize nonpositive capacities to 0 and ignore puts. Cache and map `get` return `std::optional<int>` so a stored `-1` is distinguishable from a missing key:

```cpp
patterns::design::LRUCache cache(2);
cache.put(7, -1);
if (auto value = cache.get(7)) {
    // *value is -1; the key exists.
}
```

This optional-return API is an explicit generalization of the original LeetCode `-1` sentinel contract.

## 1. LRU: list order is the policy (#146)

Two synchronized structures are enough:

```text
mapping: key -----------------------> exact list node

front / most recent                           back / least recent
     [key,value] <-> [key,value] <-> [key,value]
         ^                                      ^
    access moves here                       evict here
```

Invariant: every cached key appears exactly once in the list, and its map entry points to that exact node.

- Successful `get`: splice the node to the front and return its value
- Updating `put`: replace the value and move the existing node to the front
- New `put` at capacity: erase the back key from the map, remove its node, then insert the new pair at the front
- Missing `get`: no recency change

`std::list::splice` moves a node without rebuilding it and preserves its iterator. The map iterator therefore does not need refreshing after a same-list splice. An erase is different: the erased node's iterator becomes invalid immediately.

Your source's `put` would read `values.back()` at capacity 0. The adaptation adds an early return before that branch. Overwritten keys are updated in place, not inserted as duplicate nodes.

## 2. LFU: frequency selects a bucket, recency selects a node (#460)

A successful get and an overwrite both count as an access. New keys enter at frequency 1. When frequencies tie, evict the least recently used key within that frequency.

### Bucket/list version: expected O(1)

```text
mapping[key] -> node {key,value,frequency}

frequency 1: front [MRU] ... [LRU] back  <- evict here if minFreq=1
frequency 2: front [MRU] ... [LRU] back
frequency 5: front [MRU] ... [LRU] back
```

On access, copy the node, remove it from bucket `f`, increment its frequency, and push it at the front of bucket `f+1`. Update its iterator mapping.

The subtle `minFreq` update is local:

- If promotion empties the current minimum bucket `f`, the promoted node itself proves `f+1` exists. Therefore incrementing `minFreq` by one is correct; no scan is needed.
- If a new key is inserted, reset `minFreq = 1`.
- Eviction removes the back node of `storage[minFreq]`.

```text
capacity 2
put(1,1), put(2,2)   f1: [2,1]
get(1)              f1: [2]     f2: [1]
put(3,3)            evict 2;    f1: [3], f2: [1]
get(3)              f2: [3,1]
put(4,4)            evict 1: same frequency, older access
```

Your source retains empty frequency lists in its map. The reusable version erases them, keeping stored bucket count bounded by the live cache size. Frequencies use checked 64-bit counters. These are explicit robustness changes, not claimed original details.

### Ordered-set version: O(log C), simpler global ordering

Your older #460 source stores entries ordered lexicographically by:

```text
(frequency, lastAccessTime, key, value)
   primary     tie-break       payload
```

The smallest set element is the eviction victim. The hash map stores `key -> set iterator`. On access, erase the old entry and insert the same key with incremented frequency and a fresh timestamp. This directly encodes the policy and avoids `minFreq` bookkeeping, at the cost of logarithmic ordered-set operations.

The source uses `std::vector<int>` as an ordered record. `LFUCacheOrdered` adapts it to a fixed-field tuple, checked 64-bit frequency/timestamp counters, and optional results. The ordering and update rule are preserved.

Use the bucket version when constant expected update cost matters; use the ordered version when an explicit sortable policy is easier to audit or change. Do not mix the list version's `minFreq` reasoning with the set version's global ranking.

## 3. Iterator ownership is a class invariant

LRU, LFU, and ordered LFU all store iterators into another member container. An automatically copied iterator map would still point into the original object's list or set.

The handbook disables copy and move operations for these classes. This is a conservative ownership contract. A future copy implementation must rebuild every mapping; a move implementation must deliberately establish and test its container/iterator guarantees.

Other iterator rules that matter here:

- `list::splice` within the LRU list preserves the moved node's iterator
- Erasing a list/set node invalidates that node's iterator only
- After an LFU promotion implemented as erase/reinsert, always replace the cached iterator
- Rehashing an `unordered_map` invalidates its own iterators; do not retain one across insertions that could rehash that same map
- Updating an existing mapped value does not insert a new key

The templates are single-threaded algorithm building blocks, not production concurrent caches. They do not promise transactional recovery from allocation failure. Counter exhaustion throws rather than silently wrapping and corrupting policy order.

## 4. Fixed-chain hash map: understand the load factor (#706)

Your implementation has 32 buckets, each a list of `(key,value)` pairs:

```text
bucket 0:  (0,a) -> (32,b) -> (64,c)
bucket 1:  (1,d) -> (33,e)
...
bucket31:  (-1,f) -> (31,g)
```

`put` scans for an existing key before appending; `remove` erases one matching node and returns immediately. Overwrites must not grow a second node with the same key.

The number of buckets is fixed. Even under a uniform key distribution, average chain length is about N/32 and grows with N. Under collisions, one chain can contain every key. Do not advertise this implementation as expected O(1) as the map grows. Resizing and rehashing would be a new algorithmic feature, deliberately not added here.

The template uses a fixed `std::array` of lists and normalizes the signed remainder:

```cpp
int index = key % 32;
if (index < 0) index += 32;
```

This handles negative keys including `INT_MIN`, without `abs(INT_MIN)` overflow. It also avoids relying on implicit signed-to-unsigned conversion from `storage.size()`. Missing values use `std::nullopt`, preserving every `int` value as usable data.

## 5. Frequency stack: recency is already encoded in the buckets (#895)

Keep:

- `route[value]`: its current frequency
- `freqs[f]`: a stack of values that reached frequency `f`, in push order
- `maxFreq`: the highest current frequency

```text
push sequence: 5,7,5,7,4,5
frequency 1: [5,7,4]
frequency 2: [5,7]
frequency 3: [5]       <- pop 5
then f2 top is 7       <- pop 7
then f2 top is 5       <- pop 5
then f1 top is 4       <- pop 4
```

A pop removes the last value in the highest-frequency bucket and decrements that value's frequency. If the bucket empties, decrement `maxFreq` once.

The entries in lower-frequency buckets are not stale junk: they preserve the previous recency order that becomes relevant after later pops. Removing them when a value moves up would destroy the policy.

The template starts `maxFreq` at 0, throws on empty pop, and cleans up zero-frequency map entries and empty buckets. Logical entries are O(number of live pushes). Vector capacity can retain past high-water allocations, so allocated memory is bounded by push history rather than necessarily the current logical size.

Your older source uses an ordered set of `(-frequency,-latestTimestamp,value)` and per-value timestamp stacks. That is a valid O(log distinctValues) alternative; the bucket version already exploits the policy enough to avoid the ordered set, so only the preferred bucket API is implemented here.

## 6. Twitter: bounded top-k, not k-way merge (#355)

Your feed algorithm stores append-only posts per author and scans every relevant historical post into a size-10 min-heap. The smallest timestamp is the oldest retained post:

```text
scan post -> push (time,tweetId)
if size > K -> pop oldest retained post

heap now holds the K newest seen posts
pop all -> oldest first; reverse -> newest first
```

`getNewsFeed(userId, limit=10)` retains this source algorithm and makes the bound configurable. Let P be the number of posts belonging to the user and followed authors, F the number of followed authors, and K the limit. Time is O(F + P log(K+1)), auxiliary heap/output space O(min(P,K)). With the default K=10, feed work is linear in relevant history. It is not a claim of logarithmic access to each user's newest post.

Robustness adaptations:

- `follow(user,user)` is ignored because the feed already scans the user's own posts
- Repeated follow is idempotent; unfollow of a missing relation is harmless
- Limit 0 returns an empty feed
- Queries use `find` so reading an unknown user does not create empty history entries
- Timestamps are checked 64-bit counters
- Typed `(timestamp,tweetId)` pairs replace two-element vectors

Post storage is still unbounded append-only history. Retention limits, pagination, persistence, concurrent posting, and k-way merge would be new requirements; they are not silently represented as features of your original code.

## Sources and adaptation record

| Actual problem | Exact observed submission | Pattern used |
|---|---|---|
| [146. LRU Cache](https://leetcode.com/problems/lru-cache/) | [2143986850](https://leetcode.com/problems/lru-cache/submissions/2143986850/) | Hash map of list iterators; MRU-front splice, LRU-back eviction |
| [460. LFU Cache](https://leetcode.com/problems/lfu-cache/) | [2144968388](https://leetcode.com/problems/lfu-cache/submissions/2144968388/) | Frequency-to-list buckets, iterator mapping, minimum frequency |
| Same problem, older distinct strategy | [2144919830](https://leetcode.com/problems/lfu-cache/submissions/2144919830/) | Ordered `(frequency,time,key,value)` records and key-to-iterator map |
| [706. Design HashMap](https://leetcode.com/problems/design-hashmap/) | [2144621524](https://leetcode.com/problems/design-hashmap/submissions/2144621524/) | Exactly 32 separate list chains, overwrite before append |
| [895. Maximum Frequency Stack](https://leetcode.com/problems/maximum-frequency-stack/) | [2146639743](https://leetcode.com/problems/maximum-frequency-stack/submissions/2146639743/) | Stack per frequency plus per-value counts |
| Same problem, documented alternative | [2146625292](https://leetcode.com/problems/maximum-frequency-stack/submissions/2146625292/) | Ordered set plus timestamp stacks; comparison only, not a second template |
| [355. Design Twitter](https://leetcode.com/problems/design-twitter/) | [2144760383](https://leetcode.com/problems/design-twitter/submissions/2144760383/) | Scan history into bounded min-heap, reverse extracted output |

All headers add standalone standard-library includes. Optional lookups, input guards, explicit copy/move restrictions, 64-bit counter handling, negative-key normalization, empty-bucket cleanup, and configurable feed limit are handbook adaptations described above.

## Run the checks

```sh
g++ -std=c++20 -O2 -Wall -Wextra -Werror test.cpp -o /tmp/design-test
/tmp/design-test
g++ -std=c++20 -O1 -g -Wall -Wextra -Werror -fsanitize=address,undefined -fno-omit-frame-pointer test.cpp -o /tmp/design-sanitized
ASAN_OPTIONS=detect_leaks=0 /tmp/design-sanitized
```

Tests include 90,000 seeded cache operations against a slow timestamp model across negative, zero, and positive capacities, plus 23,000 seeded hash-map/frequency-stack/feed operations. They cover LFU recency ties, overwrites, stored `-1`, all keys colliding, negative/extreme keys, arbitrary frequency-stack histories, self-follow, repeated relations, empty feeds, and varying feed limits. Compile-time assertions protect the iterator-owning classes from accidental copy enablement.

Sanitizer note: AddressSanitizer and UndefinedBehaviorSanitizer passed with leak detection disabled. LeakSanitizer cannot run under this execution environment’s ptrace setup; this is not a leak-check result. On an ordinary local shell, omit `ASAN_OPTIONS=detect_leaks=0` to attempt leak detection too.
