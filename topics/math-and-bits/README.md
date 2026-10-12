# Math and bits

## Main algorithms and structures

[All ideas](../../README.md) · [Quick review](../../QUICK_REVIEW.md) · [Exact snippets](../../SNIPPETS.md)

`n` is input length, `d` distinct values, `D` distinct pair masks, `b` digit count, and `S` generated palindrome seeds. Hash-table costs are expected; collision worst cases can be worse. Space includes materialized tables and explicitly identified output. Arithmetic assumes the original bounded integer contracts.

| Algorithm / structure | Time in the linked source | Extra space | Direct implementation |
| --- | --- | --- | --- |
| Bit-count DP using the smaller half | O(n); independent per-number division variant O(n log n) | O(n) returned array | [DP](originals/338__791450580.cpp), [division variant](originals/338__791441445.cpp) |
| Meet-in-the-middle pair-sum frequencies | Expected O(n²) for four length-n arrays | O(n²), including zero-valued complement keys inserted by lookup | [Exact excerpt](snippets/four-sum-pair-frequency.cpp) · [full source](originals/454__2025540323.cpp) |
| Ordered-pair bitwise-AND frequencies | Expected O(n² + nD), D ≤ min(n², 2^B) for B-bit values | O(D) | [Exact excerpt](snippets/bitwise-and-pair-frequency.cpp) · [full source](originals/982__2168564891.cpp) |
| Sorted value triples + multiplicity formulas | Expected O(n log n + d²) | O(d + log n), including sort stack | [Exact excerpt](snippets/three-sum-multiplicity-cases.cpp) · [full source](originals/923__2140530076.cpp) |
| Two pointers + powers of two for bounded subsequences | O(n log n), including sort | O(n) power table | [Implementation](originals/1498__2140461426.cpp) |
| Frequency map + ordered deduplication set | Expected O(n + d log d) | O(d) | [K-difference pair implementation](originals/532__2022700280.cpp) |
| Count frequencies, then aggregate the maximum group | Expected O(n) | O(d) | [Implementation](originals/3005__1197606254.cpp) |
| Bounded digit enumeration with decrement/restore | O(n + 9·10·5) | O(10) | [Implementation](originals/3483__2138479064.cpp) |
| Translation-vector frequency map | Expected O(N² + ac) for N×N images with a and c nonzero pixels | O(a + c + T), T distinct displacements ≤ ac | [Implementation](originals/835__2140447101.cpp) |
| Axis overlap / clamped nearest point | O(1) | O(1) | [Rectangle overlap](originals/836__2141366410.cpp), [circle–rectangle](originals/1401__2146448826.cpp) |
| Palindromic-root generation + square validation | O(Sb), at most two loops of 100,000 seeds each | O(b) temporary strings | [Implementation](originals/906__2163458920.cpp) |
| Arithmetic digit reversal / digit scan | O(b) per value; O(nb) for an array | O(1) | [Palindrome check](originals/9__2126054933.cpp), [destructive digit sum](originals/3550__2152359464.cpp) |
| XOR/parity summary | O(n) for total XOR; O(1) for direct parity | O(1) | [XOR game](originals/810__2166697803.cpp), [divisor parity](originals/1025__792418394.cpp) |
| Threshold contributions instead of range enumeration | O(1), five explicit thresholds | O(1) | [Implementation](originals/3871__2136687887.cpp) |
| Position-divisibility filter + square accumulation | O(n), scanning all positions | O(1) | [Exact excerpt](snippets/divisor-position-square-sum.cpp) · [full source](originals/2778__2169299910.cpp) |
| Conserved bit counts + convex concentration: AND/OR redistribution preserves each bit multiplicity | O(B(n+k)), B=30 | O(B), B=30 | [Greedy bit-layer construction](originals/2897__2170231461.cpp) |
| Equal-remainder runs + gcd progression: Valid lengths satisfy (length-1)*r divisible by k | Gcd version O(n log(k+1)); retained backward-trial version O(n²) worst case | O(1) | [Gcd length rounding](originals/4076__2168355505.cpp), [backward trials](originals/4075__2168348655.cpp) |
| Complement lookup + candidate objective: Prior occurrences provide distinct indexes; retain valid pairs then rank by product | Expected O(n) | O(n) map and candidate pairs | [Unequal-value product pairs](originals/4074__2168271160.cpp) |

## Combinations and tricks

Every composition below is present in a linked original. The reusable part is the reduction and invariant; integer widths, modulo arithmetic, and domain restrictions still belong to the source problem.

### Split a tuple into a summary and a compatibility test

- **Recognize:** A count over triples or quadruples repeats the same intermediate result many times.
- **Compose:** Pair enumeration + frequency map + a lookup or compatibility scan. [Pair sums](originals/454__2025540323.cpp) query the negative complementary sum. [Pair AND masks](originals/982__2168564891.cpp) scan masks compatible with each third value.
- **Invariant:** A map frequency counts index choices, not distinct values. Each frequency must contribute in full when its summary satisfies the remaining condition.
- **Tradeoff:** Sum equality permits one lookup; `(mask & x) == 0` is a relation over many masks and this source scans all D masks. It is not a subset transform. Ordered pairs include equal indexes where the original problem permits them.

### Separate value-level search from index-level multiplicity

- **Recognize:** Many equal values create the same sum, but their index choices all count.
- **Compose:** Sorting + frequency map + opposing pointers + choose-two/choose-three arithmetic in [the multiplicity implementation](originals/923__2140530076.cpp).
- **Invariant:** Visit each ordered-by-value triple once; weight it by `a·b·c`, `a(a−1)b/2`, or `a(a−1)(a−2)/6` according to its equality pattern.
- **Tradeoff:** Duplicate jumps reduce the search to distinct values, but sorting mutates input. The source promotes products with `1LL` before its final modulo; copying only the formula without that promotion changes overflow behavior.

### Turn a feasible interval into exponentially many choices

- **Recognize:** Once its minimum is fixed, any subset between that minimum and a feasible maximum satisfies the same bound.
- **Compose:** Sorted two-pointer frontier + precomputed powers of two in [the bounded-subsequence implementation](originals/1498__2140461426.cpp).
- **Invariant:** If `nums[left] + nums[right] <= target`, all `2^(right-left)` subsets of the remaining interval are valid with this fixed minimum. Incrementing left assigns every counted subsequence exactly one minimum position.
- **Tradeoff:** This counts subsequences without generating them, using O(n) precomputation. Sorting preserves value-based feasibility, not original order-sensitive constraints.

### Encode geometry as a hashable equality

- **Recognize:** One translation must align many pairs of points.
- **Compose:** Sparse coordinate lists + all cross-image point pairs + displacement histogram in [image overlap](originals/835__2140447101.cpp).
- **Invariant:** Equal displacement vectors describe the same translation; their frequency is its overlap count.
- **Tradeoff:** Work is quadratic in nonzero counts, not merely image width. The original packs signed differences through two `uint32_t` halves into a `uint64_t`; preserve those casts when reading the key. For a single shape intersection, [axis overlap](originals/836__2141366410.cpp) or [clamping](originals/1401__2146448826.cpp) avoids enumeration entirely.

### Generate constrained objects before testing the remaining property

- **Recognize:** Valid answers have a cheap constructive symmetry or a tiny alphabet.
- **Compose:** Mirror a seed + square it + numeric palindrome check in [palindromic roots](originals/906__2163458920.cpp); digit frequencies + choose/decrement/restore in [three-digit enumeration](originals/3483__2138479064.cpp).
- **Invariant:** Mirroring guarantees the root property, leaving only range and square tests. In digit enumeration, remaining counts represent unused copies; candidate digits, rather than source indexes, avoid duplicate numbers.
- **Tradeoff:** The palindrome source hardcodes seed limits and depends on its positive bounded range; zero would be generated by both loops. Digit counts cap at three because no candidate uses more than three copies. Neither source is a general digit-DP framework.

### Count threshold crossings, not formatted objects

- **Recognize:** Each object contributes one extra unit after each fixed threshold.
- **Compose:** Five arithmetic tail counts in [comma counting](originals/3871__2136687887.cpp): each reached threshold t contributes `n-t+1`.
- **Invariant:** A number above several thresholds contributes once for each of them, matching its comma count.
- **Tradeoff:** The hardcoded thresholds cover the source domain only. [Waviness](originals/3751__2022675769.cpp) actually enumerates every integer and converts it to a string; it has no analogous counting DP in this corpus.

### Replace a game tree with the preserved summary

- **Recognize:** A legal move changes a small invariant predictably enough to characterize winning positions.
- **Compose:** Total XOR + length parity in [XOR game](originals/810__2166697803.cpp); direct parity in [divisor game](originals/1025__792418394.cpp); odd/even minima in [uniform parity](originals/3876__2131978781.cpp).
- **Invariant:** The implementation decides from the summary without enumerating future states. The proof must come from the particular move rules; a compact return expression is not itself that proof.
- **Tradeoff:** The uniform-parity sources retain misleading parity comments. The separate [constant-true source](originals/3875__2128397234.cpp) stays an explicitly problem-specific result, not a reusable parity algorithm.

### Separate the position predicate from the value contribution

- **Recognize:** Eligibility is a property of an item's one-based index, while the accumulated contribution depends on its value.
- **Compose:** A linear position scan + divisibility test + square accumulation in [the special-element source](originals/2778__2169299910.cpp).
- **Invariant:** The partial result contains exactly the squares at processed positions dividing the total length. Convert zero-based `i` to `i+1` before testing; the array value itself is not the divisor.
- **Tradeoff / trap:** This implementation checks all n positions, not only divisor pairs, so it is O(n) time and O(1) space. Its multiplication and accumulator stay `int` under the original constraints.
- **Exact code:** [Literal filtered-accumulation method](snippets/divisor-position-square-sum.cpp).

### Replace operations with conserved counts, then concentrate value

- **Recognize:** Pairwise AND/OR operations can move bits between numbers, while the objective rewards large numbers more than evenly distributed values.
- **Compose:** [The original source](originals/2897__2170231461.cpp) counts each bit, then repeatedly constructs one number using every bit with remaining inventory. The resulting numbers are nested bit layers.
- **Invariant:** For each bit, AND/OR preserves the total number of set occurrences. Concentrating a transferable bit on a larger value increases the unmodded sum of squares: moving value d from b to a changes the sum by 2d(a-b)+2d² when a >= b. Repeated concentration aligns high bits with other high bits.
- **Tradeoff / trap:** Optimization is over the true sum, before modulo; modulo only limits accumulated output. The source hardcodes 30 bit positions. It counts all n inputs even though it constructs only k output values, uses long long for the constructed value and square, and retains int bit tests within the source bounds.

### Replace a backward length search with a gcd progression

- **Recognize:** Deleting any single element must leave a sum divisible by k. Subtracting two deletion conditions shows all elements have the same remainder r. A length-L segment then requires (L-1)r divisible by k.
- **Compose:** Scan maximal equal-remainder runs, then use [the gcd source](originals/4076__2168355505.cpp) to find the largest feasible length within the current run. With d=k/gcd(k,r), valid lengths are 1,1+d,1+2d,..., so round run length L down to L-(L-1)%d.
- **Invariant:** Every element inside a run has the same remainder r; a subarray's length determines its deletion-sum divisibility. Once a different remainder appears, reset the run start. For r=0, d=1 and every run length works.
- **Tradeoff / trap:** The [older original](originals/4075__2168348655.cpp) tries candidate lengths backward and is quadratic in the worst case. The gcd variant removes that inner trial loop, but still recomputes gcd at every position: O(n log(k+1)), not constant-cost-gcd-free O(n). Both use raw C++ remainder for run grouping; their positive-input contract matters if adapting to signed values. Empty input is outside the source contract (result starts at one).

## Problem and source appendix


All captured submissions are retained, including equivalent resubmissions and exact duplicates. Submission IDs distinguish files; they are not rankings of quality. The source itself is authoritative when a note is too brief.

### 9. Palindrome Number

[Problem](https://leetcode.com/problems/palindrome-number/) · Tags: Digits, Arithmetic reversal

Reject negatives, reverse all decimal digits arithmetically, compare with original.

**Original-code context:** Uses long accumulator; portability depends on long width (64-bit in this accepted environment); not half-reversal.

**Captured variants:** 1 accepted C++ submission captured; all original versions are retained.

- [Original 2126054933](originals/9__2126054933.cpp) · [LeetCode submission](https://leetcode.com/problems/palindrome-number/submissions/2126054933/)

### 338. Counting Bits

[Problem](https://leetcode.com/problems/counting-bits/) · Tags: Bit-count DP, Binary digits

One source uses bits[i]=bits[i/2]+i%2; the other separately divides each integer by 2 while counting odd remainders.

**Original-code context:** The DP source loops from i=0 and reads its already-zero-initialized bits[0]. Both accepted originals are preserved as separate variants.

**Captured variants:** 2 accepted C++ submissions retained; distinctions are described above.

- [Original 791450580](originals/338__791450580.cpp) · [LeetCode submission](https://leetcode.com/problems/counting-bits/submissions/791450580/)
- [Original 791441445](originals/338__791441445.cpp) · [LeetCode submission](https://leetcode.com/problems/counting-bits/submissions/791441445/)

### 454. 4Sum II

[Problem](https://leetcode.com/problems/4sum-ii/) · Tags: Pair sums, Frequency map

Counts every nums3+nums4 sum in unordered_map<int,int>, then sums frequencies at -(nums1+nums2).

**Original-code context:** operator[] inserts missing complement keys with value 0.

**Captured variants:** 1 accepted C++ submission retained; distinctions are described above.

- [Original 2025540323](originals/454__2025540323.cpp) · [LeetCode submission](https://leetcode.com/problems/4sum-ii/submissions/2025540323/)

### 532. K-diff Pairs in an Array

[Problem](https://leetcode.com/problems/k-diff-pairs-in-an-array/) · Tags: Frequency map, Pair counting

Counts nums, handles k==0 by requiring frequency>1, otherwise checks existence of num+k; stores unique pairs in set<pair<int,int>>.

**Original-code context:** Because map keys are unique and only num+k is checked for k>0, the ordered result set is extra deduplication in this implementation.

**Captured variants:** 1 accepted C++ submission retained; distinctions are described above.

- [Original 2022700280](originals/532__2022700280.cpp) · [LeetCode submission](https://leetcode.com/problems/k-diff-pairs-in-an-array/submissions/2022700280/)

### 810. Chalkboard XOR Game

[Problem](https://leetcode.com/problems/chalkboard-xor-game/) · Tags: Bitwise, Game theory

XOR all values and return zero-XOR or even parity.

**Captured variants:** One observed approach.

- [Original 2166697803](originals/810__2166697803.cpp) · [LeetCode submission](https://leetcode.com/problems/chalkboard-xor-game/submissions/2166697803/)

### 835. Image Overlap

[Problem](https://leetcode.com/problems/image-overlap/) · Tags: Geometry, Hash maps, Coordinate packing

For every pair of nonzero pixel coordinates, count translation vector; maximum frequency is best overlap.

**Captured variants:** One observed approach.

- [Original 2140447101](originals/835__2140447101.cpp) · [LeetCode submission](https://leetcode.com/problems/image-overlap/submissions/2140447101/)
- [Original 2140436041](originals/835__2140436041.cpp) · [LeetCode submission](https://leetcode.com/problems/image-overlap/submissions/2140436041)

### 836. Rectangle Overlap

[Problem](https://leetcode.com/problems/rectangle-overlap/) · Tags: Geometry, Intervals

Positive-area rectangle intersection equals strict overlap on both axes.

**Captured variants:** One observed approach.

- [Original 2141366410](originals/836__2141366410.cpp) · [LeetCode submission](https://leetcode.com/problems/rectangle-overlap/submissions/2141366410/)

### 906. Super Palindromes

[Problem](https://leetcode.com/problems/super-palindromes/) · Tags: Palindromes, Enumeration

Generate odd/even palindromic roots by mirroring half, square them, and test numeric palindrome in target range.

**Captured variants:** One observed approach.

- [Original 2163458920](originals/906__2163458920.cpp) · [LeetCode submission](https://leetcode.com/problems/super-palindromes/submissions/2163458920/)

### 923. 3Sum With Multiplicity

[Problem](https://leetcode.com/problems/3sum-with-multiplicity/) · Tags: Two pointers, Counting, Combinatorics

Sort, walk distinct value triples using frequencies, add product/choose2/choose3 multiplicities.

**Captured variants:** One observed approach.

- [Original 2140530076](originals/923__2140530076.cpp) · [LeetCode submission](https://leetcode.com/problems/3sum-with-multiplicity/submissions/2140530076/)

### 982. Triples with Bitwise AND Equal To Zero

[Problem](https://leetcode.com/problems/triples-with-bitwise-and-equal-to-zero/) · Tags: Bitwise AND, Ordered-pair frequencies

Count the bitwise-AND mask for every ordered pair of input positions, then for each third value add the frequencies of masks whose AND with that value is zero.

**Original-code context:** Pairs include equal indexes, as allowed by the original ordered-triple definition. For D distinct pair masks, expected time is O(n squared + nD) and map storage is O(D). Counts and the result remain int under the original bounds.

**Captured variants:** One captured pair-frequency implementation.

- [Original 2168564891](originals/982__2168564891.cpp) · [LeetCode submission](https://leetcode.com/submissions/detail/2168564891/)

### 1025. Divisor Game

[Problem](https://leetcode.com/problems/divisor-game/) · Tags: Parity, Game invariant

Returns n%2==0 for Divisor Game.

**Original-code context:** Actual source is the parity result, not a game-state DP implementation.

**Captured variants:** 1 accepted C++ submission retained; distinctions are described above.

- [Original 792418394](originals/1025__792418394.cpp) · [LeetCode submission](https://leetcode.com/problems/divisor-game/submissions/792418394/)

### 1401. Circle and Rectangle Overlapping

[Problem](https://leetcode.com/problems/circle-and-rectangle-overlapping/) · Tags: Geometry, Clamping

Closest rectangle point to circle center obtained by clamping both coordinates; compare squared distance.

**Captured variants:** Latest compact clamp; older redundant corner-distance precheck then identical clamp.

- [Original 2146448826](originals/1401__2146448826.cpp) · [LeetCode submission](https://leetcode.com/problems/circle-and-rectangle-overlapping/submissions/2146448826/)
- [Original 2146448651](originals/1401__2146448651.cpp) · [LeetCode submission](https://leetcode.com/problems/circle-and-rectangle-overlapping/submissions/2146448651/)

### 1498. Number of Subsequences That Satisfy the Given Sum Condition

[Problem](https://leetcode.com/problems/number-of-subsequences-that-satisfy-the-given-sum-condition/) · Tags: Two pointers, Combinatorics

Sort; when minimum+maximum fits, all subsets of interior elements yield 2^(right-left) valid subsequences with fixed minimum.

**Captured variants:** One observed approach.

- [Original 2140461426](originals/1498__2140461426.cpp) · [LeetCode submission](https://leetcode.com/problems/number-of-subsequences-that-satisfy-the-given-sum-condition/submissions/2140461426/)

### 2553. Separate the Digits in an Array

[Problem](https://leetcode.com/problems/separate-the-digits-in-an-array/) · Tags: Digit extraction

Extracts decimal digits with %10 into a deque, then pops from the back to restore their order in the result.

**Original-code context:** Zero contributes no digits in this implementation; it relies on the original positive-number constraint.

**Captured variants:** 1 accepted C++ submission retained; distinctions are described above.

- [Original 2000541813](originals/2553__2000541813.cpp) · [LeetCode submission](https://leetcode.com/problems/separate-the-digits-in-an-array/submissions/2000541813/)

### 2778. Sum of Squares of Special Elements

[Problem](https://leetcode.com/problems/sum-of-squares-of-special-elements/) · Tags: Divisibility, One-based positions, Filtered accumulation

Scan all positions and add nums[i] squared exactly when the one-based position i+1 divides the array length.

**Original-code context:** O(n) time and O(1) auxiliary space. This scans every position rather than enumerating divisor pairs. Values are selected by their positions, not by whether the values divide n. Products and the result remain int under the source bounds.

**Captured variants:** One Accepted C++ submission added on 11 October 2026.

- [Original 2169299910](originals/2778__2169299910.cpp) · [LeetCode submission](https://leetcode.com/submissions/detail/2169299910/)

### 3005. Count Elements With Maximum Frequency

[Problem](https://leetcode.com/problems/count-elements-with-maximum-frequency/) · Tags: Frequency aggregation

First pass counts each integer and tracks max_freq; second sums frequencies equal to that maximum.

**Original-code context:** The result is the number of elements at maximum-frequency values, not the number of such distinct values.

**Captured variants:** 1 accepted C++ submission retained; distinctions are described above.

- [Original 1197606254](originals/3005__1197606254.cpp) · [LeetCode submission](https://leetcode.com/problems/count-elements-with-maximum-frequency/submissions/1197606254/)

### 3483. Unique 3-Digit Even Numbers

[Problem](https://leetcode.com/problems/unique-3-digit-even-numbers/) · Tags: Enumeration, Frequency maps

Enumerate hundreds,tens,even units using decrement/restore counts, avoiding leading zero and duplicate values.

**Captured variants:** One observed approach.

- [Original 2138479064](originals/3483__2138479064.cpp) · [LeetCode submission](https://leetcode.com/problems/unique-3-digit-even-numbers/submissions/2138479064/)

### 3498. Reverse Degree of a String

[Problem](https://leetcode.com/problems/reverse-degree-of-a-string/) · Tags: Strings, Arithmetic

Map lowercase character to reverse alphabet weight and multiply by one-based index.

**Captured variants:** Two equivalent implementations, one with debug output.

- [Original 2147499756](originals/3498__2147499756.cpp) · [LeetCode submission](https://leetcode.com/problems/reverse-degree-of-a-string/submissions/2147499756/)
- [Original 2147499695](originals/3498__2147499695.cpp) · [LeetCode submission](https://leetcode.com/problems/reverse-degree-of-a-string/submissions/2147499695/)

### 3550. Smallest Index With Digit Sum Equal to Index

[Problem](https://leetcode.com/problems/smallest-index-with-digit-sum-equal-to-index/) · Tags: Digits, Linear scan

Scan indexes; repeatedly divide nums[i] by 10 to accumulate digit sum.

**Original-code context:** Mutates visited input numbers to zero; O(n log M), O(1) auxiliary space.

**Captured variants:** 1 accepted C++ submission captured; all original versions are retained.

- [Original 2152359464](originals/3550__2152359464.cpp) · [LeetCode submission](https://leetcode.com/problems/smallest-index-with-digit-sum-equal-to-index/submissions/2152359464/)

### 3718. Smallest Missing Multiple of K

[Problem](https://leetcode.com/problems/smallest-missing-multiple-of-k/) · Tags: Hash set, Multiples

Hash-set membership; repeatedly add k until absent.

**Original-code context:** Average O(n) time and O(n) space; positive k under constraints.

**Captured variants:** 1 accepted C++ submission captured; all original versions are retained.

- [Original 2119524038](originals/3718__2119524038.cpp) · [LeetCode submission](https://leetcode.com/problems/smallest-missing-multiple-of-k/submissions/2119524038/)

### 3751. Total Waviness of Numbers in Range I

[Problem](https://leetcode.com/problems/total-waviness-of-numbers-in-range-i/) · Tags: Digit enumeration, Local extrema

Enumerates every integer in [num1,num2], converts it to a string and counts strict local peaks or valleys among digit triples.

**Original-code context:** This actual source is brute-force enumeration, not digit DP.

**Captured variants:** 1 accepted C++ submission retained; distinctions are described above.

- [Original 2022675769](originals/3751__2022675769.cpp) · [LeetCode submission](https://leetcode.com/problems/total-waviness-of-numbers-in-range-i/submissions/2022675769/)

### 3870. Count Commas in Range

[Problem](https://leetcode.com/problems/count-commas-in-range/) · Tags: Counting, Digit thresholds

Counts numbers at first comma threshold under original small range.

**Captured variants:** One observed approach.

- [Original 2134960323](originals/3870__2134960323.cpp) · [LeetCode submission](https://leetcode.com/problems/count-commas-in-range/submissions/2134960323/)

### 3871. Count Commas in Range II

[Problem](https://leetcode.com/problems/count-commas-in-range-ii/) · Tags: Counting, Digit thresholds

Each decimal comma threshold contributes max(0,n-threshold+1); five hardcoded powers of 1000.

**Captured variants:** One observed approach.

- [Original 2136687887](originals/3871__2136687887.cpp) · [LeetCode submission](https://leetcode.com/problems/count-commas-in-range-ii/submissions/2136687887/)

### 3875. Construct Uniform Parity Array I

[Problem](https://leetcode.com/problems/construct-uniform-parity-array-i/) · Tags: Math, Problem-specific invariant

Actual implementation returns true for every input.

**Captured variants:** One constant-result source.

- [Original 2128397234](originals/3875__2128397234.cpp) · [LeetCode submission](https://leetcode.com/problems/construct-uniform-parity-array-i/submissions/2128397234/)

### 3876. Construct Uniform Parity Array II

[Problem](https://leetcode.com/problems/construct-uniform-parity-array-ii/) · Tags: Greedy, Parity

Scan minimum odd and even; return all-even or minimum odd below minimum even.

**Captured variants:** One observed approach.

- [Original 2131978781](originals/3876__2131978781.cpp) · [LeetCode submission](https://leetcode.com/problems/construct-uniform-parity-array-ii/submissions/2131978781/)
- [Original 2131975505](originals/3876__2131975505.cpp) · [LeetCode submission](https://leetcode.com/problems/construct-uniform-parity-array-ii/submissions/2131975505/)

### 2897. Apply Operations on Array to Maximize Sum of Squares

[Problem](https://leetcode.com/problems/apply-operations-on-array-to-maximize-sum-of-squares/)

Count occurrences of each of the 30 bit positions, then construct k numbers by taking every available bit each round. Maximizes the convex sum of squares by concentrating conserved bits. O(30(n+k)) time, O(30) auxiliary storage; does not mutate input. Hardcoded bit width and modulo are retained.

- [Original 2170231461](originals/2897__2170231461.cpp) · [LeetCode submission](https://leetcode.com/problems/apply-operations-on-array-to-maximize-sum-of-squares/submissions/2170231461/)

### 4076. Longest Resilient Subarray II

[Problem](https://leetcode.com/problems/longest-resilient-subarray-ii/)

Scan maximal equal-remainder runs. For run length L and remainder r, valid lengths are 1 modulo d=k/gcd(k,r); take L-(L-1)%d. O(n log(k+1)) standard arithmetic-operation time because gcd is recomputed at every endpoint, O(1) auxiliary space. Inputs and k are positive; r=0 yields d=1.

- [Original 2168355505](originals/4076__2168355505.cpp) · [LeetCode submission](https://leetcode.com/problems/longest-resilient-subarray-ii/submissions/2168355505/)

### 4075. Longest Resilient Subarray I

[Problem](https://leetcode.com/problems/longest-resilient-subarray-i/)

Scan equal-remainder runs and trial lengths backward until (length-1)*remainder is divisible by k or no improvement remains. O(n²) worst-case time and O(1) auxiliary space. A long run with k/gcd(k,r)>n keeps result=1 and triggers quadratic unsuccessful trials. Positive nonempty input and k>=1 are source assumptions; original normalized-remainder expression and trailing newline are retained.

- [Original 2168348655](originals/4075__2168348655.cpp) · [LeetCode submission](https://leetcode.com/problems/longest-resilient-subarray-i/submissions/2168348655/)

### 4074. Maximum Product Pair With Target Sum

[Problem](https://leetcode.com/problems/maximum-product-pair-with-target-sum/)

Complement hash lookup records prior indexes and saves every unequal-value candidate pair, larger value first. A later max_element compares products. Expected O(n) time, O(n) stored candidates and map; no input mutation. Equal values are intentionally forbidden by the problem. Any optimum is allowed, so retaining the latest prior index is sufficient. Products remain int and are safe under the original -100..100 value bounds, including negative products.

- [Original 2168271160](originals/4074__2168271160.cpp) · [LeetCode submission](https://leetcode.com/problems/maximum-product-pair-with-target-sum/submissions/2168271160/)
