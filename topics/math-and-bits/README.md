# Math and bits

[All topics](../../README.md) · [Source index](../../SOURCES.md) · [Coverage](../../COVERAGE.md)

**13 captured problems · 17 accepted submission records.** Every linked implementation below is an unchanged captured source file. These notes describe the code; they do not replace it with a common API.

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
