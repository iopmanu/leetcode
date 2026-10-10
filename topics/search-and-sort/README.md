# Search and sort

[All topics](../../README.md) · [Source index](../../SOURCES.md) · [Coverage](../../COVERAGE.md)

**35 captured problems · 71 accepted submission records.** Every linked implementation below is an unchanged captured source file. These notes describe the code; they do not replace it with a common API.

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

**Captured variants:** 1 accepted C++ submission captured; all original versions are retained.

- [Original 2147762984](originals/26__2147762984.cpp) · [LeetCode submission](https://leetcode.com/problems/remove-duplicates-from-sorted-array/submissions/2147762984/)

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
