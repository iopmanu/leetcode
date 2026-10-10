# Math, bits, counting, and geometry

These are the source-backed small ideas that are easy to forget and useful to recognize. The reusable work stays in short functions; task-specific parity facts stay as notes rather than gaining unnecessary classes.

## Pattern map

| Template / source | Invariant | Useful when | Time / extra space |
|---|---|---|---|
| XOR + parity / 810 (note) | Zero XOR or even item count is winning under these rules | This normal-play removal game | O(n) / O(1) |
| `palindromicRoot`, `countSuperPalindromes` / 906 | Generate roots already satisfying the rare structural condition | Palindromic squares with palindromic roots | O(S log R) / O(log R) |
| `threeSumMultiplicity` / 923 | Each sorted value triple appears once; multiply index choices | Duplicate-heavy 3-sum counts | O(n log n+d²) / O(n+d) including copy |
| `packSignedPair`, `maximumTranslationOverlap` / 835 | Equal displacement pairs align under one translation | Sparse binary image alignment | Expected O(ab) / O(ab) worst case |
| `rectanglesOverlap` / 836 | Both axis intersections have positive length | Axis-aligned rectangle area overlap | O(1) / O(1) |
| `circleRectangleOverlap` / 1401 | Coordinate-wise clamping gives the nearest point | Circle versus closed axis-aligned rectangle | O(1) / O(1) |

S is the seeds examined (at most 199,998 here), R the numeric bound, d the number of distinct values, and a/b the occupied-point counts. The translation helper takes occupied coordinates; scanning image grids to build those lists is an additional O(number of grid cells). Hash complexity is expected. All helpers avoid mutating caller inputs; 923 sorts a copy.

## 1. XOR cancellation is useful; the game theorem has rules

The inspected LC 810 submission is exactly the compact observation:

```cpp
int x = 0;
for (int value : nums) { x ^= value; }
return x == 0 || nums.size() % 2 == 0;
```

Under this task's rules, zero XOR at the start of your turn wins; making it zero by your own erase loses. If a nonzero-XOR position has even size, there is a safe removal: otherwise every element would equal the total XOR, but an even number of identical values has XOR zero. A safe move leaves an odd, nonzero-XOR position. From an odd, nonzero position, every safe move leaves an even, nonzero position for the opponent. This proves the parity criterion inductively.

**Reusable bit facts:** `a^a=0`, `a^0=a`, and XOR is associative/commutative. **Pitfall:** the winning formula is not a rule for arbitrary XOR games or different erase/win conditions. No unrelated bit-count/lowbit template is attributed to this submission.

## 2. Generate palindromic roots, then test their squares

LC 906 avoids scanning every integer or every square. Mirror a short seed in two ways:

```text
seed = 123
odd:   123 + reverse(12)  = 12321
even:  123 + reverse(123) = 123321
```

Every positive decimal palindrome is generated exactly once by one parity and its leading half. With right≤10^18, roots are at most 10^9, so five-digit seeds cover the required roots. Each parity's roots increase with the seed, enabling an early break.

**Explicit overflow-safe boundary:** the template checks `root > right/root` **before** multiplying. This makes the bound obvious and is a useful generalization habit. It is not a demonstrated overflow bug in the original supported domain: with right≤10^18, the even-length loop breaks at root 1,000,000,001 at the latest, whose square still fits `long long`; the odd-length seeds stop at root 999,999,999. If widening the domain or seed generation, re-check those limits rather than relying on the original early break. In this template, every actual square is ≤right≤10^18.

The reusable domain is explicitly `0 <= left <= right <= 10^18`. Zero is counted once separately; the positive-task source starts both parity loops at zero, which would double-count it if the domain were extended casually. `palindromicRoot` accepts seeds 0–99,999 and mirrors numerically rather than allocating a reversed string. `decimalPalindrome` compares decimal digits, handling any `long long` without the numeric-reversal overflow that broader inputs could create.

**When useful:** generate candidates that already satisfy the strongest structural property, then apply the cheaper remaining test. **Pitfall:** the fixed seed bound is derived from the stated range, not a universal palindrome generator.

## 3. Value triples and index multiplicities

LC 923 sorts and skips equal-value groups while running two pointers. The template compresses those groups explicitly, preserving the same value-triple enumeration.

For ordered values a≤b≤c with frequencies A/B/C:

| Equality pattern | Number of index triples |
|---|---|
| a<b<c | A×B×C |
| a=b<c | choose(A,2)×C |
| a<b=c | A×choose(B,2) |
| a=b=c | choose(A,3) |

```text
choose(q,2) = q(q−1)/2
choose(q,3) = q(q−1)(q−2)/6
```

One copy of a value cannot fill two indices: combinations encode that automatically. The template checks `n<=3000`, retaining the original counting bound, so all pre-modulo products fit `long long`. Values may be any `int`; the three-value sum is widened before addition. The result is modulo 1,000,000,007.

**Pitfalls:** do integer division before reducing modulo; `/2` or `/6` after `%mod` is not equivalent without modular inverses. Do not multiply in `int` then assign the already-overflowed result to `long long`. If lifting the n bound, redesign the multiplication/combinations or use a safe modular implementation; removing the guard alone is insufficient.

## 4. Count translations, not moved images

For each occupied pixel p in the first image and q in the second, the only translation aligning them is `q−p`:

```text
p=(1,2), q=(4,1)  =>  shift=(+3,−1)
all pairs with that same shift contribute to the same overlap count
```

Unique occupied coordinates ensure each pair corresponds to one distinct aligned pixel under its shift. Count displacement frequencies and take the maximum. This is especially useful for sparse images. Passing duplicate coordinates would count duplicate pixels, so uniqueness is part of the contract.

The observed packing trick is retained:

```cpp
(std::uint64_t(std::uint32_t(dx)) << 32) | std::uint32_t(dy)
```

Each signed value is converted to its 32-bit unsigned representation before being placed into a 64-bit lane. Negative shifts retain distinct bit patterns; shifting a negative signed value is avoided. The helper checks widened coordinate differences fit signed 32-bit lanes before casting. Do not use `dx*100+dy` unless a proven coordinate bound makes it collision-free.

## 5. Geometry: separate axes, then distinguish contact from area

Rectangle overlap (836) is two strict one-dimensional intersections:

```text
max(left edges) < min(right edges)
AND
max(bottom edges) < min(top edges)
```

Touching along an edge or corner has zero area and returns false. The source's symmetric second call is redundant; the template uses the symmetric expression once and also handles zero-width/height rectangles as zero-area. Corners must be ordered.

For circle/rectangle overlap (1401), clamp the circle center into the rectangle:

```text
        center *
               | shortest path
rectangle +----q----+
          | nearest |
          +---------+
q.x = clamp(center.x, x1, x2)
q.y = clamp(center.y, y1, y2)
```

Compare `(center.x−q.x)² + (center.y−q.y)² <= radius²`. Tangency **does** count here. If the center is inside, q equals the center and distance is zero. No square root or separate corner/edge cases are necessary. The newer source removes the older submission's redundant corner scan.

The template's explicit domain is absolute coordinates≤10^9 and radius 0–10^9. It widens **before subtraction**; squared distance is then at most 8×10^18, within signed 64-bit range. The radius bound is checked; coordinate bounds and ordered corners are caller preconditions. Wider signed-int extremes would require wider arithmetic or a different comparison, so do not silently lift these bounds.

## Additional observed parity shortcuts

- **3876:** the inspected implementation computes minimum odd and minimum even values and returns “no odd value, or minimum odd < minimum even.” This is a condition for that task's allowed positive-value operations, not a generic uniform-parity test. Its opening comments give the wrong parity table for subtraction. The correct table is: same parity → even; different parity → odd. Do not copy those comments into another solution.
- **3875:** the actual source simply returns `true`. That is recorded as a problem-specific conclusion; it supplies no reusable transformation algorithm. No missing logic is invented from the title.

## Tests and safety changes

Deterministic cases plus 500 seeded cases compare multiplicity counts with explicit index triples, translation counts with all small shifts, generated super-palindromes with integer-root enumeration, rectangle overlap with unit cells, and clamp distance with lattice-point enumeration. Dedicated cases cover the full original 10^18 bound, zero once, negative shifts, 1,681 unique packed pairs, `INT_MAX` value sums, 3,000 equal values, wide squared distances, and tangency.

The input contracts are part of the snippets. Helpers are self-contained C++20 and use only standard types; no nonstandard `__int128`, magic grid widths, floating modulus construction, or cross-topic dependency is required.

## Compile and verify

From this folder:

```sh
g++ -std=c++20 -O2 -Wall -Wextra -Werror test.cpp -o /tmp/pattern-test
/tmp/pattern-test
g++ -std=c++20 -O1 -g -Wall -Wextra -Werror -fsanitize=address,undefined -fno-omit-frame-pointer test.cpp -o /tmp/pattern-test-sanitized
/tmp/pattern-test-sanitized
```

Verification in the build environment used `ASAN_OPTIONS=detect_leaks=0` for the sanitizer run because LeakSanitizer cannot operate under ptrace there. AddressSanitizer and UndefinedBehaviorSanitizer remained enabled; leak checking was not completed. On a normal local environment, try the command above with leak detection left enabled.

The tests were written before the implementations. Neutral stubs produced failing behavioral checks; the implementations then passed the same checks. No LeetCode harness, external libraries, or other handbook topics are needed. Helpers are `inline` in namespace `patterns`; include `templates.hpp` and call only the pieces you need.

## Exact source map

These are the inspected submissions, not algorithms inferred from problem titles. Multiple links show observed variants.

- [810. Chalkboard XOR Game](https://leetcode.com/problems/chalkboard-xor-game/) · inventory row 8 · [submission 2166697803](https://leetcode.com/problems/chalkboard-xor-game/submissions/2166697803/)
- [906. Super Palindromes](https://leetcode.com/problems/super-palindromes/) · inventory row 21 · [submission 2163458920](https://leetcode.com/problems/super-palindromes/submissions/2163458920/)
- [923. 3Sum With Multiplicity](https://leetcode.com/problems/3sum-with-multiplicity/) · inventory row 172 · [submission 2140530076](https://leetcode.com/problems/3sum-with-multiplicity/submissions/2140530076/)
- [835. Image Overlap](https://leetcode.com/problems/image-overlap/) · inventory row 175 · [submission 2140447101](https://leetcode.com/problems/image-overlap/submissions/2140447101/), [submission 2140436041](https://leetcode.com/problems/image-overlap/submissions/2140436041)
- [836. Rectangle Overlap](https://leetcode.com/problems/rectangle-overlap/) · inventory row 159 · [submission 2141366410](https://leetcode.com/problems/rectangle-overlap/submissions/2141366410/)
- [1401. Circle and Rectangle Overlapping](https://leetcode.com/problems/circle-and-rectangle-overlapping/) · inventory row 133 · [submission 2146448826](https://leetcode.com/problems/circle-and-rectangle-overlapping/submissions/2146448826/), [submission 2146448651](https://leetcode.com/problems/circle-and-rectangle-overlapping/submissions/2146448651/)
- [3876. Construct Uniform Parity Array II](https://leetcode.com/problems/construct-uniform-parity-array-ii/) · inventory row 187 · [submission 2131978781](https://leetcode.com/problems/construct-uniform-parity-array-ii/submissions/2131978781/), [submission 2131975505](https://leetcode.com/problems/construct-uniform-parity-array-ii/submissions/2131975505/)
- [3875. Construct Uniform Parity Array I](https://leetcode.com/problems/construct-uniform-parity-array-i/) · inventory row 196 · [submission 2128397234](https://leetcode.com/problems/construct-uniform-parity-array-i/submissions/2128397234/)
