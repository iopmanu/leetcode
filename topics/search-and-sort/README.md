# Search and sort

[All topics](../../README.md) · [Source index](../../SOURCES.md) · [Coverage](../../COVERAGE.md)

**52 captured problems · 89 accepted submission records.** Every linked implementation below is an unchanged captured source file. These notes describe the code; they do not replace it with a common API.

## Main algorithms and structures

Pick the invariant first, then open a representative original. Here `n` is input length, `u` the number of distinct values, `k` the requested rank/count, `R` the numeric search range, and `z` the number of returned tuples. Space below excludes returned output but includes recursion and temporary containers; usual library `sort` contributes O(log n) stack space. Hash-table bounds are expected, not collision-proof.

| Algorithm / structure | What it maintains | Time in these implementations | Auxiliary space / mutation | Direct implementation |
| --- | --- | --- | --- | --- |
| Binary search / lower bound | The target or insertion boundary stays inside the candidate interval | O(log n); scalar square root O(log x) | O(1) | [Boundary search](originals/35__2146678224.cpp), [exact search](originals/704__2146675354.cpp), [integer square root](originals/69__2146686635.cpp) |
| Virtual sorted indexing | Map a logical sorted index to a matrix cell or rotated physical index | O(log(rows × cols)) / O(log n) | O(1) | [Flat matrix](originals/74__2146688351.cpp), [rotation pivot + search](originals/33__2125939691.cpp) |
| Slope / sorted-half search | A neighbor comparison or ordered half identifies where an answer remains | O(log n); duplicate-heavy rotated search O(n) worst case | O(1) | [Peak](originals/162__2024553766.cpp), [mountain search](originals/1095__2147557289.cpp), [duplicate rotation](originals/81__2146739961.cpp) |
| Partition two sorted arrays | Left partitions have the required total size and both cross-boundaries are ordered | O(log(min(m,n)+1)) | O(1) | [Median partition](originals/4__2147722433.cpp) |
| Binary search on a feasible answer | A linear predicate separates feasible and infeasible thresholds | O(n log(R+1)); spacing variant also sorts in O(n log n) | O(1), or O(log n) sort stack; spacing sorts input | [Capacity](originals/1011__2146696311.cpp), [split sum](originals/410__2146752727.cpp), [speed](originals/875__2146691389.cpp), [spacing](originals/2517__2024256883.cpp), [nonadjacent picks](originals/2560__2024348959.cpp) |
| Deterministic quickselect | Only the partition containing the desired rank is pursued | O(n) average under favorable input distribution; O(n²) worst case | O(log n) average recursion, O(n) worst; rearranges input | [Middle-element pivot](originals/215__2144679787.cpp) |
| Frequency map + rank selection | Rank distinct values by their counts | Quickselect: expected counting O(n), average selection O(u), worst O(u²); bounded set: expected O(n + u log(k+1)) | O(u) map/pairs/stack, plus O(k) bounded set if used | [Count + quickselect](originals/347__2133013441.cpp), [count + bounded ordered set](originals/347__2025491048.cpp) |
| Full sorting / full heap for rank | Maintain complete order, or repeatedly expose the largest value | Sort O(n log n); repeated heap pushes + extraction O(n log n + k log n) | Sort O(log n) stack and mutates input; heap O(n) | [Sort rank](originals/215__2132966164.cpp), [full max-heap](originals/215__2132965197.cpp) |
| Sorted fixed-prefix + two pointers | After fixing one/two values, the remaining sum moves monotonically with endpoints | Triple scan O(n²); quadruple scan O(n³), including sort | O(log n) sort stack, plus O(z) output; mutates input | [Duplicate-skipping triples](originals/15__2147771319.cpp), [duplicate-skipping quadruples](originals/18__2147786844.cpp) |
| Complement binary search | For each fixed value, search the sorted suffix for its partner | O(n log n) | O(1), plus constant-size output | [Per-index complement search](originals/167__2147765072.cpp) |
| Merge sort + cross-half count | Sorted halves make a pair predicate monotone before merging | O(n log n) | O(n) merge arrays + O(log n) recursion; sorts input | [Widened reverse-pair count](originals/493__2150875619.cpp) |
| Value-to-index sign marking | The sign at value−1 records membership in a bounded value domain | O(n) | O(1); destroys original signs/values | [Normalize then mark](originals/41__2142829718.cpp), [duplicate marking](originals/287__2143946691.cpp) |
| Hash set + sequence starts | Expand only values whose predecessor is absent | Expected O(n), O(n²) with pathological hashing | O(u) | [Consecutive-run starts](originals/128__2025467217.cpp) |
| Read/write pointers and reversal | A processed prefix is compacted, merged, or reversed without a second array | O(n), or O(m+n) for merge | O(1); mutates input | [Deduplicate](originals/26__2147762984.cpp), [stable compaction](originals/283__2126091678.cpp), [backward merge](originals/88__2147757984.cpp), [three reversals](originals/189__2147800911.cpp) |
| Sorted endpoint elimination | Discard the farther endpoint until exactly k candidates remain | O(n−k) elimination + O(k) output = O(n) | O(1) apart from returned O(k) values | [Closest contiguous block](originals/658__2127298849.cpp) |
| Lexicographic frequency comparator | Compare team counts place by place, then use the character tie-break | For v votes and t teams: expected O(vt + t² log t) | O(t²) count maps + O(log t) sort stack | [Rank vectors of vote counts](originals/1366__2119622834.cpp) |
| Fixed largest side + bulk pair count | Every left index in a sorted interval satisfies the same strict inequality | O(n²), including sort | O(log n) sort stack; mutates input | [Triangle count](originals/611__2169562141.cpp) · [exact excerpt](snippets/triangle-two-pointer-count.cpp) |
| Sorted triple + closest objective | Record absolute error before moving the pair frontier | O(n²), including sort | O(log n) sort stack; mutates input | [Closest triple](originals/16__2169549656.cpp) |
| Two-pass value partition | Completed zero prefix, then completed one prefix | O(n) | O(1); mutates input | [Zero-then-one compaction](originals/75__2169541356.cpp) |
| Output-prefix multiplicity cap | Compare the incoming value with the item two output positions back | O(n) | O(1); mutates input | [Keep at most two](originals/80__2169317874.cpp) |
| Search over independent arithmetic contributions | Sum split counts, completed trips, or rounded quotients for one threshold | O(n log U); U=1e9 for bag cap, fastestTime*totalTrips for trip time, 5e7 for divisor | O(1) | [Split counts](originals/1760__2170557741.cpp), [trip counts](originals/2187__2170532508.cpp), [rounded sum](originals/1283__2170517396.cpp) |
| Threshold activation + disjoint run packing | Consecutive eligible positions form non-overlapping fixed-size groups | O(n log U), U=1e9 | O(1) | [Bloom threshold and resettable streak](originals/1482__2170542125.cpp) |
| Sorted suffix counting for repeated queries | First successful product determines all successful partners | O(p log p+s log p) for p potions and s spells | O(log p) sort stack + O(s) output; sorts potions | [Product boundary to suffix count](originals/2300__2170496273.cpp) |
| Index decoration + lower bound + output scatter | Sorted lookup keys retain original identities | O(n log n) | O(n) appended fields and output; mutates nested input | [Right-interval index lookup](originals/436__2170376810.cpp) |
| Pair-parity boundary search | Before the singleton, even/odd adjacent slots form equal pairs | O(log n) | O(1) | [Neighbor index mid XOR 1](originals/540__2170364195.cpp) |
| Count predicate for h-index | At least h papers have citations >= h | O(n log(n+1)); the source rescans all citations per predicate | O(1), no input mutation | [Captured full-scan predicate](originals/275__2170348113.cpp) |
| Descending rank crossing | First rank no longer supported by its citation count | O(n log n), including sort | O(log n) sort stack; mutates input | [Sorted h-index crossing](originals/274__2170335393.cpp) |
| Lexicographic successor via suffix reversal | Preserve the longest possible prefix, minimally increase its pivot, then minimize the tail | O(n) | O(1); mutates input | [Pivot, rightmost successor, suffix reversal](originals/31__2171277650.cpp) |
| Composite-rank quickselect + output-only sort | Select by frequency and lexical tie-break, then order winners | Expected hashing O(T); average selection O(uL), worst O(u²L); output sort O(kL log(k+1)) | O(uL+u) counts/pairs/worst recursion, plus O(kL) output | [Word-rank selection](originals/692__2170605459.cpp) |

## Combinations and tricks

### Search a threshold, prove the greedy predicate

- **Recognize:** Minimize a capacity/speed/capability, or maximize a minimum distance; checking one guess is easier than optimizing directly.
- **Compose:** Binary search + a greedy linear scan. [Shipping](originals/1011__2146696311.cpp) fills each day; [nonadjacent picks](originals/2560__2024348959.cpp) takes the earliest affordable house and skips its neighbor; [spacing](originals/2517__2024256883.cpp) first sorts and takes the earliest sufficiently distant price.
- **Invariant:** More capacity cannot reduce feasibility; more required spacing cannot improve feasibility. The scan must maximize what remains possible after each choice.
- **Tradeoff / trap:** Include sorting and predicate cost. [Split-sum](originals/410__2146752727.cpp) names its predicate `canSplit`, but `true` means the guess is too small; copying its branch direction by name would invert the search. The spacing source double-counts its first price at distance zero; preserve that source quirk rather than treating it as a generic predicate template.

### Expose an ordered coordinate system before searching

- **Recognize:** Data is not globally increasing in physical order but has a rotation, row-major order, or two monotone slopes.
- **Compose:** Pivot/peak discovery + ordinary binary search; a coordinate mapping avoids allocating a reordered array.
- **Invariant:** [Rotation](originals/33__2125939691.cpp) searches virtual index `mid` and reads `(mid+rotation)%n`; [mountain search](originals/1095__2147557289.cpp) searches the ascending side first to obtain the lowest matching index.
- **Tradeoff / trap:** Equal rotated endpoints can conceal the ordered half, forcing linear shrink in [the duplicate variant](originals/81__2146739961.cpp). The newer [captured rotation record](originals/33__2146701709.cpp) has a differently parenthesized midpoint: with left initially zero it checks the right endpoint repeatedly and degrades to O(n). Use the correctly parenthesized original above for logarithmic search.

### Replace full ordering with count compression and rank selection

- **Recognize:** Only the k most frequent values matter, and many input entries are duplicates.
- **Compose:** Hash counts compress n entries to u `(value,count)` pairs; then [quickselect](originals/347__2133013441.cpp), a [bounded ordered set](originals/347__2025491048.cpp), or a [full heap](originals/347__2127429766.cpp) selects the winners.
- **Invariant:** Quickselect leaves the target suffix on the high-frequency side; the bounded set removes its smallest `(frequency,value)` whenever its size exceeds k.
- **Tradeoff / trap:** The map still costs O(u) even when the selector keeps only k entries. The full heap uses repeated pushes, so its bound is expected O(n + u log u + k log u), not linear heap construction. Deterministic pivots offer no worst-case linear guarantee; output need not be sorted.

### Fix a prefix, then eliminate pairs monotonically

- **Recognize:** Need unique triples/quadruples satisfying a sum, with no requirement to preserve input order.
- **Compose:** Sort + one/two fixed positions + inward two-pointer scan + duplicate skipping in [triples](originals/15__2147771319.cpp) and [quadruples](originals/18__2147786844.cpp).
- **Invariant:** If a sorted pair is too small, its left endpoint cannot work with any smaller right endpoint; if too large, its right endpoint cannot work with any larger left endpoint.
- **Tradeoff / trap:** Sorting mutates input. The [older triple](originals/15__2131829341.cpp) and [quadruple](originals/18__2127374675.cpp) variants deduplicate in an ordered set, adding O(log(z+1)) per insertion attempt and O(z) temporary storage before copying output. These are different costs from duplicate skipping. The retained sorted two-sum source uses repeated binary search, not this pair scan.

### Count with one order, merge with another

- **Recognize:** Cross-half pairs satisfy a monotone inequality that is not the ordinary merge comparison.
- **Compose:** Merge-sort recursion + a dedicated two-pointer count + ordinary merge in [the reverse-pair original](originals/493__2150875619.cpp).
- **Invariant:** If `L[i] > 2*R[j]`, all remaining values in sorted L also qualify, so add their count once. Reset pointers before merging.
- **Tradeoff / trap:** The source uses `2LL*R[j]` to widen the comparison and allocates both half-arrays. Its answer is a member initialized at construction; reusing the same solution object would retain the previous count.

### Trade an untouched input for constant auxiliary state

- **Recognize:** Values identify slots in a bounded range, or the destination already has spare capacity.
- **Compose:** [Normalize + sign marking](originals/41__2142829718.cpp), or [backward merge](originals/88__2147757984.cpp) into the destination tail.
- **Invariant:** A negative slot means its corresponding positive value occurred; merging from the end writes only beyond the unread destination prefix.
- **Tradeoff / trap:** This is an ownership decision: both mutate their input. Copying first changes end-to-end auxiliary space to O(n). [Hash membership](originals/41__2142586270.cpp) is a retained alternative when values must remain intact.

### Remove only a provably unnecessary endpoint

- **Recognize:** In a sorted array the k closest values form a contiguous block.
- **Compose:** Two boundary pointers + distance comparison + a final output copy in [the retained closest-elements source](originals/658__2127298849.cpp).
- **Invariant:** A farther extreme cannot beat all remaining values; equal distances discard the right endpoint, preserving the smaller-value tie-break.
- **Tradeoff / trap:** This code is O(n), not a binary search over block starts. It does not sort the input and relies on the input already being sorted.

### Replace one successful pair with an entire interval of successful choices

- **Recognize:** Sortedness makes a pair predicate true for every larger left candidate while one right candidate stays fixed.
- **Compose:** Fix the largest side, then use opposing pointers in [triangle counting](originals/611__2169562141.cpp). When the smallest current pair already exceeds that side, add `right-left` and move the right pointer; otherwise move the left pointer.
- **Invariant:** Every counted left index has a value at least as large as the tested left value. Fixing the largest index and then the right index gives each index triple one owner, including repeated values.
- **Tradeoff / trap:** The inequality is strict. Bulk counting differs from emitting unique value triples in 3Sum. For [3Sum Closest](originals/16__2169549656.cpp), the same sorted pair movement instead updates an absolute-error objective before discarding a frontier; equal error keeps the earlier answer. Its `INT_MAX - 100000` sentinel and `int` differences are safe only within the original bounded contract.
- **Exact code:** [Bulk triangle count](snippets/triangle-two-pointer-count.cpp), [closest-sum frontier](snippets/three-sum-closest-frontier.cpp).

### State precisely what the write frontier has already accepted

- **Recognize:** A scan writes a valid prefix in place, but acceptance can depend on a category or a multiplicity limit.
- **Compose:** [Sort Colors](originals/75__2169541356.cpp) first swaps zeros into the prefix, then scans only the remaining suffix for ones. [Keep-at-most-two compaction](originals/80__2169317874.cpp) compares each input with the value two places behind the output frontier.
- **Invariant:** At each pass boundary, all earlier category positions are settled. In the sorted duplicate filter, the accepted prefix remains sorted, so equality with `nums[k-2]` means two copies are already present. The write frontier never overtakes the read position.
- **Tradeoff / trap:** The color source is two passes, not a single-pass three-way partition. Multiplicity filtering relies on sorted input and defines only the returned prefix; the tail is unspecified. The added [ordinary deduplication submission](originals/26__2169320670.cpp) repeats the existing one-copy idea and adds provenance without another theory section.
- **Exact code:** [Two-pass color partition](snippets/two-pass-color-compaction.cpp), [output-prefix multiplicity cap](snippets/at-most-two-compaction.cpp).

### Turn a threshold into independent arithmetic contributions

- **Recognize:** Given a candidate cap/time/divisor, each item contributes an exact local count and the contributions add.
- **Compose:** Binary search plus sum of ceiling/floor formulas: [bag splits](originals/1760__2170557741.cpp) uses ceil(size/cap)-1; [completed trips](originals/2187__2170532508.cpp) uses floor(time/busTime); [divisor budget](originals/1283__2170517396.cpp) uses ceil(value/divisor).
- **Invariant:** Split counts and rounded sums decrease with the candidate; completed trips increase. Branch direction follows that predicate, rather than the shared binary-search syntax.
- **Tradeoff / trap:** The trip upper bound is a constructive feasible schedule: the fastest bus performs every trip. The other sources use fixed source-contract bounds. None short-circuits its scan. Numeric promotions differ: the bag numerator is still int before adding 0LL, while trip bounds promote before multiplication.

### Activate positions, then pack disjoint runs greedily

- **Recognize:** A global threshold makes individual positions eligible, but only consecutive groups count.
- **Compose:** [The bouquet source](originals/1482__2170542125.cpp) binary-searches activation time and scans eligible runs. A gap resets the streak; forming a size-k group resets it again to prevent reuse.
- **Invariant:** A run of length L can supply exactly floor(L/k) disjoint groups. Taking its earliest complete group leaves maximum room for later groups.
- **Tradeoff / trap:** The predicate counts every group without early exit. Infeasibility is encoded by the final search boundary exceeding 1e9, not a separate m*k guard. Bounds are specific to the source problem.

### Preserve identity while turning a boundary into an answer

- **Recognize:** Many independent queries target the same sorted key set, and the result needs either a count or an original index.
- **Compose:** [Product-pair queries](originals/2300__2170496273.cpp) sort partners once, find the first successful product, and count the suffix. [Right-interval lookup](originals/436__2170376810.cpp) attaches original indexes, sorts by start, then lower-bounds each end.
- **Invariant:** Positive factors preserve product order; an increasing start-key array preserves the earliest feasible interval boundary. Attached indexes translate sorted positions back to output identities.
- **Tradeoff / trap:** Both sources mutate input. The interval code appends a third field to every inner vector, costing O(n) additional storage beyond sorting, and is not designed for repeated calls on already augmented input. The product source widens multiplication using 1LL.

### Encode a structural boundary in index parity

- **Recognize:** Sorted duplicates occur exactly twice except for one singleton.
- **Compose:** [The original search](originals/540__2170364195.cpp) compares nums[mid] with nums[mid ^ 1]. XOR toggles the least-significant bit, selecting the other slot of an even/odd pair.
- **Invariant:** Before the singleton, pairs align at even starts; after it, alignment shifts. A matching tested pair places the singleton to the right.
- **Tradeoff / trap:** This is a structural assumption, not a generic duplicate search. The odd-length, exactly-one-singleton contract and left < right guard keep the paired lookup in range.

### Increase the latest possible position, then minimize everything after it

- **Recognize:** Need the immediately next lexicographic arrangement of the same multiset, including duplicate values, without enumerating permutations.
- **Compose:** [The captured source](originals/31__2171277650.cpp) locates the maximal non-increasing suffix beginning at left. Its preceding value is the pivot. Scanning from the right finds the smallest suffix value strictly greater than that pivot; swap them, then reverse the suffix.
- **Invariant:** The suffix is already the largest arrangement of its values, so a larger permutation must change an earlier position. Changing the rightmost possible pivot preserves the longest prefix. Because the suffix is non-increasing, its rightmost qualifying value is the smallest strict increase; after the swap the suffix remains non-increasing, so reversal gives the smallest possible tail.
- **Boundary / source quirks:** With no pivot, the complete array is non-increasing and reversing it implements the required wraparound. The strict comparisons handle equal values. The source assumes at least one element: nums.size()-1 is not an empty-input guard. It returns no boolean indicating whether wraparound occurred.
- **Cost:** At most two scans and one reversal: O(n) time, O(1) auxiliary space, with in-place mutation.

### Use one total order for selection and presentation

- **Recognize:** Only k winners are needed, but ties have a semantic secondary order and the final answer must be sorted.
- **Compose:** [The word-ranking source](originals/692__2170605459.cpp) extends count-plus-quickselect: its less helper orders lower frequency first and lexically larger words first, making the retained suffix the winners. A final sort reverses this into descending frequency and ascending lexical order.
- **Invariant:** Selection and presentation encode the same winner order; reversing only the frequency comparison would select the wrong tied words.
- **Tradeoff / trap:** For total input characters T, u distinct words and maximum word length L, hashing is expected O(T), average selection O(uL), worst selection O(u²L), and output sorting O(kL log(k+1)). Midpoint pivots are deterministic, so average behavior is not a randomized guarantee. Adversarial hash collisions can add cost. The original expression pairs.size()-k-1 underflows in unsigned arithmetic when k equals u before conversion to int; it is retained, not presented as a portable rank-boundary idiom.

## Problem and source appendix


All captured submissions are retained, including equivalent resubmissions and exact duplicates. Submission IDs distinguish files; they are not rankings of quality. The source itself is authoritative when a note is too brief.

### 4. Median of Two Sorted Arrays

[Problem](https://leetcode.com/problems/median-of-two-sorted-arrays/) · Tags: Binary search, Order statistics

Partition smaller sorted array so left side has ceil(total/2), enforce maxLeft<=minRight across both arrays.

**Captured variants:** Three equivalent partition implementations, with names/comments/return fallback changes.

- [Original 2147722433](originals/4__2147722433.cpp) · [LeetCode submission](https://leetcode.com/problems/median-of-two-sorted-arrays/submissions/2147722433/)
- [Original 2147703761](originals/4__2147703761.cpp) · [LeetCode submission](https://leetcode.com/problems/median-of-two-sorted-arrays/submissions/2147703761/)
- [Original 1621118867](originals/4__1621118867.cpp) · [LeetCode submission](https://leetcode.com/problems/median-of-two-sorted-arrays/submissions/1621118867/)

### 15. 3Sum

[Problem](https://leetcode.com/problems/3sum/) · Tags: Sorting, Two pointers, Deduplication

Sort, fix one index, opposite-pointer scan. Older version inserts triples in a set; newer skips duplicates in place and appends to vector.

**Original-code context:** Sorting mutates nums. The newer source skips duplicates directly and uses int for the three-value sum; nums.size()-2 relies on the original n>=3 contract. The older ordered-set variant adds deduplication overhead to the quadratic scan.

**Captured variants:** 2 accepted C++ submissions captured; all original versions are retained.

- [Original 2147771319](originals/15__2147771319.cpp) · [LeetCode submission](https://leetcode.com/problems/3sum/submissions/2147771319/)
- [Original 2131829341](originals/15__2131829341.cpp) · [LeetCode submission](https://leetcode.com/problems/3sum/submissions/2131829341/)

### 16. 3Sum Closest

[Problem](https://leetcode.com/problems/3sum-closest/) · Tags: Sorting, Two pointers, Closest objective

Fix one sorted value, scan the remaining pair with opposing pointers, and keep a sum whenever its absolute error strictly improves.

**Original-code context:** O(n squared) time including sorting and O(log n) usual sort stack; mutates input. result starts at INT_MAX - 100000 rather than a real triple. Sums, subtraction, and abs use int, so the sentinel relies on the original small target/value bounds. Requires at least three elements. Equal-error candidates do not replace the current result; an exact match does not stop the outer search.

**Captured variants:** One Accepted C++ submission added on 11 October 2026.

- [Original 2169549656](originals/16__2169549656.cpp) · [LeetCode submission](https://leetcode.com/submissions/detail/2169549656/)

### 18. 4Sum

[Problem](https://leetcode.com/problems/4sum/) · Tags: Sorting, Two pointers, Deduplication

Sort, fix two positions, scan other two with opposite pointers. Two older versions deduplicate using set<vector<int>>; two newer submissions have identical code using duplicate skipping and vector output.

**Original-code context:** The newer source widens target subtraction to long long; nums[k]+nums[m] remains int and relies on the original element bounds. Its two newest submission records have identical code. The scan is O(n cubed), with additional ordered-set deduplication work in the older variants.

**Captured variants:** 4 accepted C++ submissions captured; all original versions are retained.

- [Original 2147786844](originals/18__2147786844.cpp) · [LeetCode submission](https://leetcode.com/problems/4sum/submissions/2147786844/)
- [Original 2147786330](originals/18__2147786330.cpp) · [LeetCode submission](https://leetcode.com/problems/4sum/submissions/2147786330/)
- [Original 2127374675](originals/18__2127374675.cpp) · [LeetCode submission](https://leetcode.com/problems/4sum/submissions/2127374675/)
- [Original 2025531964](originals/18__2025531964.cpp) · [LeetCode submission](https://leetcode.com/problems/4sum/submissions/2025531964/)

### 26. Remove Duplicates from Sorted Array

[Problem](https://leetcode.com/problems/remove-duplicates-from-sorted-array/) · Tags: Sorted arrays, Read/write pointers

Read index and write frontier; copy each new distinct value.

**Original-code context:** O(n), O(1); returns 1 on an empty vector, which lies outside official nonempty constraint.

**Captured variants:** 2 accepted C++ submissions captured; both use the same read/write compaction, with naming and formatting differences.

- [Original 2147762984](originals/26__2147762984.cpp) · [LeetCode submission](https://leetcode.com/problems/remove-duplicates-from-sorted-array/submissions/2147762984/)
- [Original 2169320670](originals/26__2169320670.cpp) · [LeetCode submission](https://leetcode.com/submissions/detail/2169320670/)

### 33. Search in Rotated Sorted Array

[Problem](https://leetcode.com/problems/search-in-rotated-sorted-array/) · Tags: Binary search, Rotated arrays

Find rotation pivot, then binary-search virtual sorted indices mapped by modulo.

**Original-code context:** [2146701709](originals/33__2146701709.cpp) computes its second-loop midpoint as `left + (right - left / 2)`. Starting with left=0 makes this equal right: it scans virtual sorted positions downward until a match or until left becomes right+1. This retained form therefore takes O(n) worst-case time rather than O(log n). The main table links the correctly parenthesized older implementation.

**Captured variants:** Three pivot-plus-search submissions; two older correct midpoint implementations.

- [Original 2146701709](originals/33__2146701709.cpp) · [LeetCode submission](https://leetcode.com/problems/search-in-rotated-sorted-array/submissions/2146701709/)
- [Original 2125939691](originals/33__2125939691.cpp) · [LeetCode submission](https://leetcode.com/problems/search-in-rotated-sorted-array/submissions/2125939691/)
- [Original 2011698957](originals/33__2011698957.cpp) · [LeetCode submission](https://leetcode.com/problems/search-in-rotated-sorted-array/submissions/2011698957/)

### 35. Search Insert Position

[Problem](https://leetcode.com/problems/search-insert-position/) · Tags: Binary search, Lower bound

Inclusive search eliminates >=target to the right and returns insertion index left.

**Captured variants:** One observed approach.

- [Original 2146678224](originals/35__2146678224.cpp) · [LeetCode submission](https://leetcode.com/problems/search-insert-position/submissions/2146678224/)

### 41. First Missing Positive

[Problem](https://leetcode.com/problems/first-missing-positive/) · Tags: In-place marking, Hash maps

Normalize outside [1,n] to n+1, mark seen values by negating slot value-1, return first positive slot. Older builds membership map and scans positive candidates.

**Captured variants:** [2142829718](originals/41__2142829718.cpp) bounded sign marking; [2142586270](originals/41__2142586270.cpp)/[1214762629](originals/41__1214762629.cpp) membership map candidate scan.

- [Original 2142829718](originals/41__2142829718.cpp) · [LeetCode submission](https://leetcode.com/problems/first-missing-positive/submissions/2142829718/)
- [Original 2142586270](originals/41__2142586270.cpp) · [LeetCode submission](https://leetcode.com/problems/first-missing-positive/submissions/2142586270/)
- [Original 1214762629](originals/41__1214762629.cpp) · [LeetCode submission](https://leetcode.com/problems/first-missing-positive/submissions/1214762629/)

### 69. Sqrt(x)

[Problem](https://leetcode.com/problems/sqrtx/) · Tags: Binary search, Integer arithmetic

Inclusive binary search for floor square root; return last feasible right boundary.

**Captured variants:** One observed approach.

- [Original 2146686635](originals/69__2146686635.cpp) · [LeetCode submission](https://leetcode.com/problems/sqrtx/submissions/2146686635/)

### 74. Search a 2D Matrix

[Problem](https://leetcode.com/problems/search-a-2d-matrix/) · Tags: Binary search, Index mapping

Binary search row-major matrix as virtual flat array.

**Captured variants:** Two equivalent submissions.

- [Original 2146688351](originals/74__2146688351.cpp) · [LeetCode submission](https://leetcode.com/problems/search-a-2d-matrix/submissions/2146688351/)
- [Original 2127411724](originals/74__2127411724.cpp) · [LeetCode submission](https://leetcode.com/problems/search-a-2d-matrix/submissions/2127411724/)

### 75. Sort Colors

[Problem](https://leetcode.com/problems/sort-colors/) · Tags: Two-pass partition, Read/write frontier

Move zeros to the front by swapping with a write frontier; then scan the remaining suffix and move ones immediately after the zeros.

**Original-code context:** O(n) total time in two passes and O(1) auxiliary space. This captured implementation is zero-then-one compaction, not the single-pass Dutch-national-flag algorithm. It assumes values are 0, 1, or 2 and mutates the input.

**Captured variants:** One Accepted C++ submission added on 11 October 2026.

- [Original 2169541356](originals/75__2169541356.cpp) · [LeetCode submission](https://leetcode.com/submissions/detail/2169541356/)

### 80. Remove Duplicates from Sorted Array II

[Problem](https://leetcode.com/problems/remove-duplicates-from-sorted-array-ii/) · Tags: Sorted arrays, Read/write pointers, Multiplicity cap

Keep a value when fewer than two items have been written or it differs from the value two places behind the write frontier.

**Original-code context:** O(n) time and O(1) auxiliary space. Sortedness makes equal values consecutive; nums[k-2] belongs to the already accepted output prefix. The returned length identifies the meaningful prefix; tail values are unspecified. Empty input returns zero.

**Captured variants:** One Accepted C++ submission added on 11 October 2026.

- [Original 2169317874](originals/80__2169317874.cpp) · [LeetCode submission](https://leetcode.com/submissions/detail/2169317874/)

### 81. Search in Rotated Sorted Array II

[Problem](https://leetcode.com/problems/search-in-rotated-sorted-array-ii/) · Tags: Binary search, Rotated arrays

Shrink ambiguous equal boundaries; otherwise identify sorted half and retain matching target interval.

**Captured variants:** Two equivalent variants.

- [Original 2146739961](originals/81__2146739961.cpp) · [LeetCode submission](https://leetcode.com/problems/search-in-rotated-sorted-array-ii/submissions/2146739961/)
- [Original 2146727441](originals/81__2146727441.cpp) · [LeetCode submission](https://leetcode.com/problems/search-in-rotated-sorted-array-ii/submissions/2146727441/)

### 88. Merge Sorted Array

[Problem](https://leetcode.com/problems/merge-sorted-array/) · Tags: Sorted arrays, Backward merge

Backward merge into spare tail of nums1; copy remaining nums2 prefix.

**Original-code context:** O(m+n), O(1); no need to copy remaining nums1.

**Captured variants:** 1 accepted C++ submission captured; all original versions are retained.

- [Original 2147757984](originals/88__2147757984.cpp) · [LeetCode submission](https://leetcode.com/problems/merge-sorted-array/submissions/2147757984/)

### 128. Longest Consecutive Sequence

[Problem](https://leetcode.com/problems/longest-consecutive-sequence/) · Tags: Hash set, Sequence starts

Deduplicates nums into unordered_set, starts only at values with no predecessor, and scans successors.

**Original-code context:** The linear expected-time argument depends on starting only at sequence minima.

**Captured variants:** 1 accepted C++ submission retained; distinctions are described above.

- [Original 2025467217](originals/128__2025467217.cpp) · [LeetCode submission](https://leetcode.com/problems/longest-consecutive-sequence/submissions/2025467217/)

### 153. Find Minimum in Rotated Sorted Array

[Problem](https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/) · Tags: Binary search, Rotated arrays

Find first index on low sorted run by comparing middle with fixed final value or current right value.

**Captured variants:** [2146698709](originals/153__2146698709.cpp) compares nums.back(); [2024485741](originals/153__2024485741.cpp) compares nums[right].

- [Original 2146698709](originals/153__2146698709.cpp) · [LeetCode submission](https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/submissions/2146698709/)
- [Original 2127418311](originals/153__2127418311.cpp) · [LeetCode submission](https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/submissions/2127418311/)
- [Original 2024485741](originals/153__2024485741.cpp) · [LeetCode submission](https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/submissions/2024485741/)

### 162. Find Peak Element

[Problem](https://leetcode.com/problems/find-peak-element/) · Tags: Binary search, Slope

Handles endpoint peaks, then binary-searches the interior using comparisons with both neighbors.

**Original-code context:** Neighbor accesses are safe because the endpoint checks leave the search within [1,n-2].

**Captured variants:** 1 accepted C++ submission retained; distinctions are described above.

- [Original 2024553766](originals/162__2024553766.cpp) · [LeetCode submission](https://leetcode.com/problems/find-peak-element/submissions/2024553766/)

### 167. Two Sum II - Input Array Is Sorted

[Problem](https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/) · Tags: Binary search, Sorted arrays

Binary-search complement for each index: newer explicit search restricted to suffix, older lower_bound across whole array with distinct-index check.

**Original-code context:** These actual sources use O(n log n) binary search, not the O(n) two-pointer method suggested by common solutions.

**Captured variants:** 2 accepted C++ submissions captured; all original versions are retained.

- [Original 2147765072](originals/167__2147765072.cpp) · [LeetCode submission](https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/submissions/2147765072/)
- [Original 2130670973](originals/167__2130670973.cpp) · [LeetCode submission](https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/submissions/2130670973/)

### 189. Rotate Array

[Problem](https://leetcode.com/problems/rotate-array/) · Tags: Arrays, Reversal

k modulo n; reverse final k elements, reverse prefix, reverse entire array.

**Original-code context:** O(n) time/O(1) space; assumes nonempty input, as the problem requires.

**Captured variants:** 1 accepted C++ submission captured; all original versions are retained.

- [Original 2147800911](originals/189__2147800911.cpp) · [LeetCode submission](https://leetcode.com/problems/rotate-array/submissions/2147800911/)

### 215. Kth Largest Element in an Array

[Problem](https://leetcode.com/problems/kth-largest-element-in-an-array/) · Tags: Quickselect, Sorting, Heaps

Hoare-style partition around middle element, recurse only partition containing zero-based target n-k; alternatives sort and max heap.

**Captured variants:** Five quickselect variants differ only base cases/return style; [2132966164](originals/215__2132966164.cpp) full sort; [2132965197](originals/215__2132965197.cpp) full max heap.

- [Original 2144679787](originals/215__2144679787.cpp) · [LeetCode submission](https://leetcode.com/problems/kth-largest-element-in-an-array/submissions/2144679787/)
- [Original 2144679621](originals/215__2144679621.cpp) · [LeetCode submission](https://leetcode.com/problems/kth-largest-element-in-an-array/submissions/2144679621/)
- [Original 2144679073](originals/215__2144679073.cpp) · [LeetCode submission](https://leetcode.com/problems/kth-largest-element-in-an-array/submissions/2144679073/)
- [Original 2144678866](originals/215__2144678866.cpp) · [LeetCode submission](https://leetcode.com/problems/kth-largest-element-in-an-array/submissions/2144678866/)
- [Original 2132995910](originals/215__2132995910.cpp) · [LeetCode submission](https://leetcode.com/problems/kth-largest-element-in-an-array/submissions/2132995910/)
- [Original 2132966164](originals/215__2132966164.cpp) · [LeetCode submission](https://leetcode.com/problems/kth-largest-element-in-an-array/submissions/2132966164/)
- [Original 2132965197](originals/215__2132965197.cpp) · [LeetCode submission](https://leetcode.com/problems/kth-largest-element-in-an-array/submissions/2132965197/)

### 283. Move Zeroes

[Problem](https://leetcode.com/problems/move-zeroes/) · Tags: Arrays, Stable compaction

Scan right, swap nonzero into left frontier when needed, advance left if nonzero.

**Original-code context:** Stable nonzero order, O(n), O(1).

**Captured variants:** 1 accepted C++ submission captured; all original versions are retained.

- [Original 2126091678](originals/283__2126091678.cpp) · [LeetCode submission](https://leetcode.com/problems/move-zeroes/submissions/2126091678/)

### 287. Find the Duplicate Number

[Problem](https://leetcode.com/problems/find-the-duplicate-number/) · Tags: In-place marking, Hash sets

Latest marks sign at value-1 to detect repeated value; older uses seen set.

**Captured variants:** [2143946691](originals/287__2143946691.cpp) sign marking; three seen-set variants, two exact duplicates.

- [Original 2143946691](originals/287__2143946691.cpp) · [LeetCode submission](https://leetcode.com/problems/find-the-duplicate-number/submissions/2143946691/)
- [Original 2143814563](originals/287__2143814563.cpp) · [LeetCode submission](https://leetcode.com/problems/find-the-duplicate-number/submissions/2143814563/)
- [Original 2140565463](originals/287__2140565463.cpp) · [LeetCode submission](https://leetcode.com/problems/find-the-duplicate-number/submissions/2140565463/)
- [Original 1212846979](originals/287__1212846979.cpp) · [LeetCode submission](https://leetcode.com/problems/find-the-duplicate-number/submissions/1212846979/)

### 344. Reverse String

[Problem](https://leetcode.com/problems/reverse-string/) · Tags: Two pointers

Swap inward in place.

**Captured variants:** One approach.

- [Original 2147725168](originals/344__2147725168.cpp) · [LeetCode submission](https://leetcode.com/problems/reverse-string/submissions/2147725168/)

### 347. Top K Frequent Elements

[Problem](https://leetcode.com/problems/top-k-frequent-elements/) · Tags: Quickselect, Heaps, Ordered sets, Frequency maps

Count values then select top k by frequency; actual alternatives full max heap and bounded ordered set.

**Captured variants:** [2133013441](originals/347__2133013441.cpp) quickselect; [2127429766](originals/347__2127429766.cpp) full max heap; [2025491048](originals/347__2025491048.cpp) bounded size-k set.

- [Original 2133013441](originals/347__2133013441.cpp) · [LeetCode submission](https://leetcode.com/problems/top-k-frequent-elements/submissions/2133013441/)
- [Original 2127429766](originals/347__2127429766.cpp) · [LeetCode submission](https://leetcode.com/problems/top-k-frequent-elements/submissions/2127429766/)
- [Original 2025491048](originals/347__2025491048.cpp) · [LeetCode submission](https://leetcode.com/problems/top-k-frequent-elements/submissions/2025491048/)

### 374. Guess Number Higher or Lower

[Problem](https://leetcode.com/problems/guess-number-higher-or-lower/) · Tags: Binary search, Interactive APIs

Inclusive search steered by sign of guess(mid).

**Captured variants:** One observed approach.

- [Original 2146681577](originals/374__2146681577.cpp) · [LeetCode submission](https://leetcode.com/problems/guess-number-higher-or-lower/submissions/2146681577/)

### 410. Split Array Largest Sum

[Problem](https://leetcode.com/problems/split-array-largest-sum/) · Tags: Binary search, Greedy feasibility

First feasible maximum partition sum, using greedy breaks; predicate currently returns true when infeasible.

**Captured variants:** Three equivalent approaches, one extra unused vector.

- [Original 2146752727](originals/410__2146752727.cpp) · [LeetCode submission](https://leetcode.com/problems/split-array-largest-sum/submissions/2146752727/)
- [Original 2139584888](originals/410__2139584888.cpp) · [LeetCode submission](https://leetcode.com/problems/split-array-largest-sum/submissions/2139584888/)
- [Original 2139584401](originals/410__2139584401.cpp) · [LeetCode submission](https://leetcode.com/problems/split-array-largest-sum/submissions/2139584401/)

### 493. Reverse Pairs

[Problem](https://leetcode.com/problems/reverse-pairs/) · Tags: Merge sort, Pair counting

Sort halves recursively, count cross pairs with monotone two pointers against 2*right, then ordinary merge.

**Captured variants:** One source; separate counting pass before merge.

- [Original 2150875619](originals/493__2150875619.cpp) · [LeetCode submission](https://leetcode.com/problems/reverse-pairs/submissions/2150875619/)

### 611. Valid Triangle Number

[Problem](https://leetcode.com/problems/valid-triangle-number/) · Tags: Sorting, Two pointers, Bulk counting

Fix the largest sorted side. If the left and right candidates make a triangle, all left positions through right-1 work with that right side, so add right-left at once.

**Original-code context:** O(n squared) time including sorting, O(log n) usual sort stack, and input mutation. The strict inequality excludes degenerate triangles; index choices remain distinct even when values repeat. Sums and counts remain int under the original bounds.

**Captured variants:** One Accepted C++ submission added on 11 October 2026.

- [Original 2169562141](originals/611__2169562141.cpp) · [LeetCode submission](https://leetcode.com/submissions/detail/2169562141/)

### 658. Find K Closest Elements

[Problem](https://leetcode.com/problems/find-k-closest-elements/) · Tags: Two pointers, Heaps, Selection

Sorted array drops farther endpoint until k remain; older keeps closest k by max heap of (distance,value), then sorts.

**Captured variants:** [2127298849](originals/658__2127298849.cpp) two-pointer trimming; [2127164573](originals/658__2127164573.cpp) bounded max heap.

- [Original 2127298849](originals/658__2127298849.cpp) · [LeetCode submission](https://leetcode.com/problems/find-k-closest-elements/submissions/2127298849/)
- [Original 2127164573](originals/658__2127164573.cpp) · [LeetCode submission](https://leetcode.com/problems/find-k-closest-elements/submissions/2127164573/)

### 704. Binary Search

[Problem](https://leetcode.com/problems/binary-search/) · Tags: Binary search

Inclusive exact-match search returning -1 when absent.

**Captured variants:** One observed approach.

- [Original 2146675354](originals/704__2146675354.cpp) · [LeetCode submission](https://leetcode.com/problems/binary-search/submissions/2146675354/)

### 852. Peak Index in a Mountain Array

[Problem](https://leetcode.com/problems/peak-index-in-a-mountain-array/) · Tags: Binary search, Unimodal search

Compare midpoint with neighbors to choose mountain slope or identify peak.

**Captured variants:** Two equivalent submissions except unreachable/fallback return.

- [Original 2147513687](originals/852__2147513687.cpp) · [LeetCode submission](https://leetcode.com/problems/peak-index-in-a-mountain-array/submissions/2147513687/)
- [Original 2147512689](originals/852__2147512689.cpp) · [LeetCode submission](https://leetcode.com/problems/peak-index-in-a-mountain-array/submissions/2147512689/)

### 875. Koko Eating Bananas

[Problem](https://leetcode.com/problems/koko-eating-bananas/) · Tags: Binary search, Integer arithmetic

First feasible speed with sum of integer ceilings.

**Captured variants:** Four equivalent first-true variants; latest includes early false.

- [Original 2146691389](originals/875__2146691389.cpp) · [LeetCode submission](https://leetcode.com/problems/koko-eating-bananas/submissions/2146691389/)
- [Original 2139503155](originals/875__2139503155.cpp) · [LeetCode submission](https://leetcode.com/problems/koko-eating-bananas/submissions/2139503155/)
- [Original 2139502841](originals/875__2139502841.cpp) · [LeetCode submission](https://leetcode.com/problems/koko-eating-bananas/submissions/2139502841/)
- [Original 2024503988](originals/875__2024503988.cpp) · [LeetCode submission](https://leetcode.com/problems/koko-eating-bananas/submissions/2024503988/)

### 1011. Capacity To Ship Packages Within D Days

[Problem](https://leetcode.com/problems/capacity-to-ship-packages-within-d-days/) · Tags: Binary search, Greedy feasibility

First feasible capacity between maximum weight and total weight; simulate sequential loading.

**Captured variants:** [2146696311](originals/1011__2146696311.cpp) closed first-true while left<right; [2024526301](originals/1011__2024526301.cpp) inclusive elimination while low<=high returns low.

- [Original 2146696311](originals/1011__2146696311.cpp) · [LeetCode submission](https://leetcode.com/problems/capacity-to-ship-packages-within-d-days/submissions/2146696311/)
- [Original 2024526301](originals/1011__2024526301.cpp) · [LeetCode submission](https://leetcode.com/problems/capacity-to-ship-packages-within-d-days/submissions/2024526301/)

### 1095. Find in Mountain Array

[Problem](https://leetcode.com/problems/find-in-mountain-array/) · Tags: Binary search, Unimodal search

Find peak, binary-search ascending half first then descending half.

**Captured variants:** [2147557289](originals/1095__2147557289.cpp) binary peak; [2147556354](originals/1095__2147556354.cpp) ternary peak narrowing accepted but has fragile endpoint handling.

- [Original 2147557289](originals/1095__2147557289.cpp) · [LeetCode submission](https://leetcode.com/problems/find-in-mountain-array/submissions/2147557289/)
- [Original 2147556354](originals/1095__2147556354.cpp) · [LeetCode submission](https://leetcode.com/problems/find-in-mountain-array/submissions/2147556354/)

### 1366. Rank Teams by Votes

[Problem](https://leetcode.com/problems/rank-teams-by-votes/) · Tags: Custom sorting, Rank counts

Map counts per rank; sort teams by descending lexicographic vote-count vector, alphabetically on full tie.

**Original-code context:** Comparator uses map operator[] and may insert zero entries; O(VT+T² log T), O(T²) worst-case rank counts.

**Captured variants:** 1 accepted C++ submission captured; all original versions are retained.

- [Original 2119622834](originals/1366__2119622834.cpp) · [LeetCode submission](https://leetcode.com/problems/rank-teams-by-votes/submissions/2119622834/)

### 1752. Check if Array Is Sorted and Rotated

[Problem](https://leetcode.com/problems/check-if-array-is-sorted-and-rotated/) · Tags: Rotated order, Linear scan

Finds the first descending adjacent pair as a pivot, rejects any later descent, and requires the last value to be at most the first.

**Original-code context:** Uses INT_MIN as the no-pivot sentinel.

**Captured variants:** 1 accepted C++ submission retained; distinctions are described above.

- [Original 2011679923](originals/1752__2011679923.cpp) · [LeetCode submission](https://leetcode.com/problems/check-if-array-is-sorted-and-rotated/submissions/2011679923/)

### 2517. Maximum Tastiness of Candy Basket

[Problem](https://leetcode.com/problems/maximum-tastiness-of-candy-basket/) · Tags: Answer binary search, Greedy spacing

Sorts prices in place, checks whether k prices can be picked at minimum spacing d, and maximizes feasible d.

**Original-code context:** The two sources differ mainly in int versus size_t search/index variables. canPick starts from index 0 after already counting price[0], so d=0 counts that first price twice; zero remains feasible under the original contract. The unsigned high=mid-1 form relies on zero being feasible. Sorting mutates price.

**Captured variants:** 2 accepted C++ submissions retained; distinctions are described above.

- [Original 2024256883](originals/2517__2024256883.cpp) · [LeetCode submission](https://leetcode.com/problems/maximum-tastiness-of-candy-basket/submissions/2024256883/)
- [Original 2024256312](originals/2517__2024256312.cpp) · [LeetCode submission](https://leetcode.com/problems/maximum-tastiness-of-candy-basket/submissions/2024256312/)

### 2560. House Robber IV

[Problem](https://leetcode.com/problems/house-robber-iv/) · Tags: Answer binary search, Greedy feasibility

Searches a capability threshold. canRob greedily takes affordable houses and skips the following index; return left after low/high convergence.

**Original-code context:** The predicate tests robbed>=k and is monotone in the threshold.

**Captured variants:** 1 accepted C++ submission retained; distinctions are described above.

- [Original 2024348959](originals/2560__2024348959.cpp) · [LeetCode submission](https://leetcode.com/problems/house-robber-iv/submissions/2024348959/)

### 3759. Count Elements With at Least K Greater Values

[Problem](https://leetcode.com/problems/count-elements-with-at-least-k-greater-values/) · Tags: Sorting, Custom binary search

Sorts nums and invokes a custom upperBound for each value, then counts those with enough strictly greater elements.

**Original-code context:** The helper saturates at n-1 rather than returning n like std::upper_bound. The extra nums[upb]>nums[i] check handles the no-greater-element case. The arithmetic is written as n-upb+1>k, equivalent to n-upb>=k; preserve this source wording in originals.

**Captured variants:** 1 accepted C++ submission retained; distinctions are described above.

- [Original 2012345290](originals/3759__2012345290.cpp) · [LeetCode submission](https://leetcode.com/problems/count-elements-with-at-least-k-greater-values/submissions/2012345290/)

### 1552. Magnetic Force Between Two Balls

[Problem](https://leetcode.com/problems/magnetic-force-between-two-balls/)

Existing answer-search plus greedy-spacing idea. This variant sorts positions, counts the first ball once, and scans from index one; this avoids the older zero-distance double-count quirk. Bounds are 1 through maximum position. O(n log n + n log M) time for M=max(position), O(log n) sort stack; input is mutated.

- [Original 2170569390](originals/1552__2170569390.cpp) · [LeetCode submission](https://leetcode.com/problems/magnetic-force-between-two-balls/submissions/2170569390/)

### 1760. Minimum Limit of Balls in a Bag

[Problem](https://leetcode.com/problems/minimum-limit-of-balls-in-a-bag/)

Binary search over cap 1..1e9. A bag contributes ceil(bag/cap)-1 required splits. O(n log U) time, O(1) auxiliary space, U=1e9. The operation accumulator is long long; bag+toCheck-1 is still evaluated as int before 0LL is added. Original bounds keep that numerator within int.

- [Original 2170557741](originals/1760__2170557741.cpp) · [LeetCode submission](https://leetcode.com/problems/minimum-limit-of-balls-in-a-bag/submissions/2170557741/)

### 1482. Minimum Number of Days to Make m Bouquets

[Problem](https://leetcode.com/problems/minimum-number-of-days-to-make-m-bouquets/)

Binary search days 1..1e9 and greedily count disjoint length-k runs of flowers already bloomed. Reset streak at an unavailable flower and after forming a bouquet. O(n log U), U=1e9, and O(1) auxiliary space. No preliminary m*k check; a never-feasible search returns -1 through the upper-bound sentinel.

- [Original 2170542125](originals/1482__2170542125.cpp) · [LeetCode submission](https://leetcode.com/problems/minimum-number-of-days-to-make-m-bouquets/submissions/2170542125/)

### 2187. Minimum Time to Complete Trips

[Problem](https://leetcode.com/problems/minimum-time-to-complete-trips/)

Minimum feasible time via sum of floor(time/busTime). The upper bound totalTrips*min(time) is feasible because one fastest bus can perform all trips. O(n log U), U=totalTrips*min(time), O(1) auxiliary space. All time bounds and accumulated trip counts are long long; input times are positive.

- [Original 2170532508](originals/2187__2170532508.cpp) · [LeetCode submission](https://leetcode.com/problems/minimum-time-to-complete-trips/submissions/2170532508/)

### 1283. Find the Smallest Divisor Given a Threshold

[Problem](https://leetcode.com/problems/find-the-smallest-divisor-given-a-threshold/)

Lower-bound search on a nonincreasing sum of positive integer ceiling quotients. Fixed upper bound 5*1e7, O(n log U) time and O(1) space. Source keeps int numerator/sum and its source constraints; widening only an outer expression would not widen inner int arithmetic.

- [Original 2170517396](originals/1283__2170517396.cpp) · [LeetCode submission](https://leetcode.com/problems/find-the-smallest-divisor-given-a-threshold/submissions/2170517396/)

### 2300. Successful Pairs of Spells and Potions

[Problem](https://leetcode.com/problems/successful-pairs-of-spells-and-potions/)

Sort potions once, binary-search the first successful product for each spell, then count the suffix. O(p log p+s log p) time, O(log p) sort stack plus O(s) output. Mutates potions. Explicit 1LL multiplication prevents int product overflow.

- [Original 2170496273](originals/2300__2170496273.cpp) · [LeetCode submission](https://leetcode.com/problems/successful-pairs-of-spells-and-potions/submissions/2170496273/)

### 436. Find Right Interval

[Problem](https://leetcode.com/problems/find-right-interval/)

Append original index to each interval, sort by start, then lower-bound each end and scatter the found original index back. O(n log n) time, O(n) extra appended-index storage plus output and O(log n) sort stack. Mutates both interval order and each interval shape; source assumes exactly two fields at entry.

- [Original 2170376810](originals/436__2170376810.cpp) · [LeetCode submission](https://leetcode.com/problems/find-right-interval/submissions/2170376810/)

### 540. Single Element in a Sorted Array

[Problem](https://leetcode.com/problems/single-element-in-a-sorted-array/)

Binary search the boundary where even/odd pairing breaks. mid^1 selects the paired neighbor without a parity branch. O(log n) time and O(1) auxiliary space. Relies on sorted odd-length input with exactly one singleton and all other values appearing twice. Original comments, including incomplete comment text, are unchanged.

- [Original 2170364195](originals/540__2170364195.cpp) · [LeetCode submission](https://leetcode.com/problems/single-element-in-a-sorted-array/submissions/2170364195/)

### 275. H-Index II

[Problem](https://leetcode.com/problems/h-index-ii/)

The captured H-Index II source does NOT exploit sortedness for logarithmic total time. It binary-searches h in 0..n but scans all n citations in each predicate. Actual time O(n log(n+1)), auxiliary space O(1), and no input mutation.

- [Original 2170348113](originals/275__2170348113.cpp) · [LeetCode submission](https://leetcode.com/problems/h-index-ii/submissions/2170348113/)

### 274. H-Index

[Problem](https://leetcode.com/problems/h-index/)

Descending sort followed by the first index i with citations[i] <= i. Actual time O(n log n), O(log n) sort stack, and input mutation. Existing sorting/rank boundary concept; retained as provenance.

- [Original 2170335393](originals/274__2170335393.cpp) · [LeetCode submission](https://leetcode.com/problems/h-index/submissions/2170335393/)

### 34. Find First and Last Position of Element in Sorted Array

[Problem](https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/)

Two boundary searches: first value >= target, then first value > target minus one. Each candidate is checked for equality and missing values return -1. O(log n) time, O(1) auxiliary space and constant-size output. Original empty/singleton fast paths and trailing newline remain unchanged.

- [Original 2170313117](originals/34__2170313117.cpp) · [LeetCode submission](https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/submissions/2170313117/)

### 31. Next Permutation

[Problem](https://leetcode.com/problems/next-permutation/)

Find the maximal non-increasing suffix, increase its preceding pivot using the rightmost strictly greater suffix value, then reverse the suffix into its minimum order. If no pivot exists, reverse the whole array to wrap to the first permutation. O(n) time and O(1) auxiliary space; mutates input. Strict inequalities support duplicates. The source assumes nonempty input.

- [Original 2171277650](originals/31__2171277650.cpp) · [LeetCode submission](https://leetcode.com/problems/next-permutation/submissions/2171277650/)

### 692. Top K Frequent Words

[Problem](https://leetcode.com/problems/top-k-frequent-words/)

Count strings, quickselect the worst-to-best rank boundary using frequency and reverse lexical ties, copy the retained suffix, then sort only that output by the desired order. This is a comparator-sensitive extension of existing frequency selection, not a new quickselect implementation. String hashing, copies and comparisons are not constant-cost.

- [Original 2170605459](originals/692__2170605459.cpp) · [LeetCode submission](https://leetcode.com/problems/top-k-frequent-words/submissions/2170605459/)
