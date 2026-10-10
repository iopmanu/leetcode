# Math and bits

[All topics](../../README.md) · [Source index](../../SOURCES.md) · [Coverage](../../COVERAGE.md)

**24 captured problems · 29 accepted submission records.** Every linked implementation below is an unchanged captured source file. These notes describe the code; they do not replace it with a common API.

## Pattern reminders

### Count multiplicities rather than materializing combinations

- **Cue:** Several equal values yield the same value-level choice.
- **Idea and invariant:** 923 sorts and uses occurrence counts with product, choose-two, or choose-three factors. 3483 decrements/restores digit frequencies while enumerating three-digit even numbers. 1498 fixes the minimum and counts subsets of the feasible interior with powers of two.
- **Cost in these sources:** 923 combines O(n log n) sorting with up to O(d squared) distinct-value pair work. 3483 has O(n) counting plus a bounded digit search. 1498 is O(n log n) including sort and uses O(n) powers.
- **Read the originals:** [923. 3Sum With Multiplicity — 2140530076](originals/923__2140530076.cpp); [3483. Unique 3-Digit Even Numbers — 2138479064](originals/3483__2138479064.cpp); [1498. Number of Subsequences That Satisfy the Given Sum Condition — 2140461426](originals/1498__2140461426.cpp).

### Reduce geometry to coordinates

- **Cue:** Overlap can be tested independently on axes, or identical translations can be counted.
- **Idea and invariant:** 836 requires strict positive overlap on both axes. 1401 clamps the circle center to the nearest rectangle point and compares squared distance. 835 counts displacement vectors between nonzero pixels.
- **Cost in these sources:** 836 and 1401: O(1). 835: O(n squared + ab) time for n by n images with a and b nonzero pixels, and up to O(ab) translation-count storage.
- **Read the originals:** [836. Rectangle Overlap — 2141366410](originals/836__2141366410.cpp); [1401. Circle and Rectangle Overlapping — 2146448826](originals/1401__2146448826.cpp); [835. Image Overlap — 2140447101](originals/835__2140447101.cpp).

### Generate only plausible candidates

- **Cue:** The target has symmetry or threshold structure.
- **Idea and invariant:** 906 mirrors a short seed to form odd/even palindromic roots, squares each, and tests the square. 3871 sums contributions of five fixed powers-of-1000 thresholds; 3870 uses its original smaller-range threshold.
- **Cost in these sources:** 906 examines at most 100,000 seeds in each of two loops, with work proportional to the number of generated digits per candidate. 3871 and 3870 have fixed O(1) arithmetic work under their original bounds.
- **Read the originals:** [906. Super Palindromes — 2163458920](originals/906__2163458920.cpp); [3871. Count Commas in Range II — 2136687887](originals/3871__2136687887.cpp); [3870. Count Commas in Range — 2134960323](originals/3870__2134960323.cpp).

### Parity or a minimum can determine the answer

- **Cue:** The full arrangement is irrelevant after a small summary is known.
- **Idea and invariant:** 810 reduces the position to total XOR and length parity. 3876 compares the minimum odd and even values. The captured 3875 implementation always returns true; the file is preserved as written.
- **Cost in these sources:** 810 and 3876: O(n) time and O(1) state. 3875: O(1).
- **Read the originals:** [810. Chalkboard XOR Game — 2166697803](originals/810__2166697803.cpp); [3876. Construct Uniform Parity Array II — 2131978781](originals/3876__2131978781.cpp); [3875. Construct Uniform Parity Array I — 2128397234](originals/3875__2128397234.cpp).

## Complete problem and variant index

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
