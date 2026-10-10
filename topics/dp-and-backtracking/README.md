# DP and backtracking

[All topics](../../README.md) · [Source index](../../SOURCES.md) · [Coverage](../../COVERAGE.md)

**23 captured problems · 31 accepted submission records.** Every linked implementation below is an unchanged captured source file. These notes describe the code; they do not replace it with a common API.

## Pattern reminders

### Define a suffix or prefix state before branching

- **Cue:** The same remaining string subproblem is reached from many choices.
- **Idea and invariant:** 132 first precomputes which substrings are palindromes, then minimizes cuts from each suffix. 115 counts ways to match a target prefix from a source prefix by skipping or consuming a matching character.
- **Cost in these sources:** 132: O(n squared) time and space. 115: O(mn) state time and space, with recursion depth bounded by the source length.
- **Read the originals:** [132. Palindrome Partitioning II — 2165701086](originals/132__2165701086.cpp); [115. Distinct Subsequences — 2133267031](originals/115__2133267031.cpp).

### Memoization over acyclic movement or phases

- **Cue:** A movement rule prevents cycles, or a phase flag distinguishes legal transitions.
- **Idea and invariant:** 329 only follows strictly increasing neighbors, so cached path lengths are acyclic. 1621 uses point index, remaining segments, and an open-segment flag; closing at the same point permits a shared endpoint.
- **Cost in these sources:** 329: O(rc) time and storage. 1621 has O(nk) reachable state work, but the captured source allocates a fixed 1005 by 1005 by 2 table and initializes all of it.
- **Read the originals:** [329. Longest Increasing Path in a Matrix — 2139455187](originals/329__2139455187.cpp); [1621. Number of Sets of K Non-Overlapping Line Segments — 2144058402](originals/1621__2144058402.cpp).

### Place, recurse, undo

- **Cue:** Enumerate valid arrangements under constraints that change locally.
- **Idea and invariant:** 37 inserts a digit into row/column/box constraint sets and removes it on failure. 51 places one queen per row, checks upward attacks, and clears the square after recursion. The board and constraint structures represent exactly the current partial assignment.
- **Cost in these sources:** Worst-case search is exponential. Sudoku has a crude O(9^e) branching bound for e empty cells; N-Queens checks candidate positions with upward scans, so it is not a constant-time attack-test implementation. Output storage must be counted separately.
- **Read the originals:** [37. Sudoku Solver — 2164710608](originals/37__2164710608.cpp); [51. N-Queens — 2164697200](originals/51__2164697200.cpp).

### Count endings or distinct choices

- **Cue:** Many subarrays share the same remainder, or duplicate characters create repeated subsequences.
- **Idea and invariant:** 3524 rolls counts of product remainders for all subarrays ending at the current position. 940 doubles the previous subsequence count, then subtracts the contribution before the previous occurrence of the same character.
- **Cost in these sources:** 3524: O(nk) time and O(k) rolling state. 940: O(n) time and O(n) DP storage in the captured implementation.
- **Read the originals:** [3524. Find X Value of Array I — 2148463117](originals/3524__2148463117.cpp); [940. Distinct Subsequences II — 2133936040](originals/940__2133936040.cpp).

### Keep the best local continuation

- **Cue:** Each position combines a small, already computed set of predecessor values.
- **Idea and invariant:** 64 extends the cheaper top/left path. 4058 separates the original alternating sum from the best nonnegative gain in each adjacent-pair parity, resetting a losing running gain to zero.
- **Cost in these sources:** 64: O(rc) time and O(rc) DP storage. 4058: O(n) time and O(1) auxiliary state.
- **Read the originals:** [64. Minimum Path Sum — 2126173167](originals/64__2126173167.cpp); [4058. Maximum Pulse Value After One Subarray Rotation — 2147436566](originals/4058__2147436566.cpp).

### Enumerating strings is more than counting states

- **Cue:** Return all maximum-length valid strings after removals.
- **Idea and invariant:** 301 memoizes sets of suffix strings by index and open balance, then retains the longest complete candidates. An empty set is also its uncached marker, so impossible states may be recomputed.
- **Cost in these sources:** Time and space are output-sensitive and can be exponential; an O(n squared) count of index/balance coordinates is not a polynomial bound on the stored strings or copying work.
- **Read the originals:** [301. Remove Invalid Parentheses — 2165615628](originals/301__2165615628.cpp).

## Complete problem and variant index

All captured submissions are retained, including equivalent resubmissions and exact duplicates. Submission IDs distinguish files; they are not rankings of quality. The source itself is authoritative when a note is too brief.

### 22. Generate Parentheses

[Problem](https://leetcode.com/problems/generate-parentheses/) · Tags: Backtracking, Parentheses balance

Generate with index, balance and mutable string; prune negative balance and cases where remaining slots cannot close the opens.

**Original-code context:** The mutable buffer is pushed and popped symmetrically, with the closing branch explored before the opening branch. A complete string is accepted only at length 2*n with balance 0.

**Captured variants:** 1 accepted C++ submission retained; distinctions are described above.

- [Original 2160263536](originals/22__2160263536.cpp) · [LeetCode submission](https://leetcode.com/problems/generate-parentheses/submissions/2160263536/)

### 37. Sudoku Solver

[Problem](https://leetcode.com/problems/sudoku-solver/) · Tags: Backtracking, Constraint tracking

Track used digits per row/column/box; place, recurse, erase on failure.

**Captured variants:** One observed approach.

- [Original 2164710608](originals/37__2164710608.cpp) · [LeetCode submission](https://leetcode.com/problems/sudoku-solver/submissions/2164710608/)

### 51. N-Queens

[Problem](https://leetcode.com/problems/n-queens/) · Tags: Backtracking

Place one queen per row; scan three upward attack directions; undo after recursive visit.

**Captured variants:** One observed approach.

- [Original 2164697200](originals/51__2164697200.cpp) · [LeetCode submission](https://leetcode.com/problems/n-queens/submissions/2164697200/)

### 53. Maximum Subarray

[Problem](https://leetcode.com/problems/maximum-subarray/) · Tags: Kadane, Maximum subarray

Accumulates current, updates sum initialized to INT_MIN, then resets current if negative.

**Original-code context:** Updating the best before resetting preserves the correct answer for all-negative input.

**Captured variants:** 1 accepted C++ submission retained; distinctions are described above.

- [Original 2000625681](originals/53__2000625681.cpp) · [LeetCode submission](https://leetcode.com/problems/maximum-subarray/submissions/2000625681/)

### 64. Minimum Path Sum

[Problem](https://leetcode.com/problems/minimum-path-sum/) · Tags: Dynamic programming, Grid paths

Initialize first row/column; each cell cost plus min(top,left).

**Captured variants:** One observed approach.

- [Original 2126173167](originals/64__2126173167.cpp) · [LeetCode submission](https://leetcode.com/problems/minimum-path-sum/submissions/2126173167/)
- [Original 2126172428](originals/64__2126172428.cpp) · [LeetCode submission](https://leetcode.com/problems/minimum-path-sum/submissions/2126172428)

### 79. Word Search

[Problem](https://leetcode.com/problems/word-search/) · Tags: Grid DFS, Backtracking, Mark and restore

Try every start cell. Match the next character, temporarily mark that board cell with #, recurse in all four directions, and restore the saved character before returning.

**Original-code context:** The four recursive results are joined with bitwise |, so every branch is evaluated even when an earlier one succeeds. The unused uint64_t key remains in the code. The source relies on the board alphabet excluding # and the original nonempty board contract.

**Captured variants:** One captured recursive backtracking implementation.

- [Original 2168591618](originals/79__2168591618.cpp) · [LeetCode submission](https://leetcode.com/submissions/detail/2168591618/)

### 115. Distinct Subsequences

[Problem](https://leetcode.com/problems/distinct-subsequences/) · Tags: Dynamic programming, Subsequences, Coordinate packing

Memoize matching target prefix inside source prefix; choose skip or consume matching character.

**Captured variants:** One observed approach.

- [Original 2133267031](originals/115__2133267031.cpp) · [LeetCode submission](https://leetcode.com/problems/distinct-subsequences/submissions/2133267031/)

### 118. Pascal's Triangle

[Problem](https://leetcode.com/problems/pascals-triangle/) · Tags: Row DP, Recursion

2026 iterative row DP; two 2022 recursive row-building versions.

**Original-code context:** The output occupies O(r squared) space. The recursive versions retain current_vector and next_row allocations in live call frames, so auxiliary vector storage can also total O(r squared), in addition to O(r) call frames. Source 791476688 builds a redundant second row then erases it; 791480396 has a cleaner recursive stopping condition. The iterative source handles numRows<=0.

**Captured variants:** 3 accepted C++ submissions captured; all original versions are retained.

- [Original 2116229650](originals/118__2116229650.cpp) · [LeetCode submission](https://leetcode.com/problems/pascals-triangle/submissions/2116229650/)
- [Original 791480396](originals/118__791480396.cpp) · [LeetCode submission](https://leetcode.com/problems/pascals-triangle/submissions/791480396/)
- [Original 791476688](originals/118__791476688.cpp) · [LeetCode submission](https://leetcode.com/problems/pascals-triangle/submissions/791476688/)

### 132. Palindrome Partitioning II

[Problem](https://leetcode.com/problems/palindrome-partitioning-ii/) · Tags: Dynamic programming, Palindromes

Build palindrome table, then memoize minimum cuts from each suffix with terminal -1 to cancel last separator.

**Captured variants:** One observed approach.

- [Original 2165701086](originals/132__2165701086.cpp) · [LeetCode submission](https://leetcode.com/problems/palindrome-partitioning-ii/submissions/2165701086/)

### 152. Maximum Product Subarray

[Problem](https://leetcode.com/problems/maximum-product-subarray/) · Tags: Product DP, Maximum/minimum states

Keeps current maximum and minimum products. Saves both previous states before multiplying by the next number.

**Original-code context:** The previous minimum matters because multiplication by a negative can make it the new maximum.

**Captured variants:** 1 accepted C++ submission retained; distinctions are described above.

- [Original 2000724011](originals/152__2000724011.cpp) · [LeetCode submission](https://leetcode.com/problems/maximum-product-subarray/submissions/2000724011/)

### 198. House Robber

[Problem](https://leetcode.com/problems/house-robber/) · Tags: One-dimensional DP

Builds vector dp with dp[i]=max(dp[i-1],nums[i]+dp[i-2]); reserves capacity and pushes states.

**Original-code context:** The class has an unused unordered_map cache; the actual algorithm is iterative DP, not memoized recursion. The nums.size()<=1 branch accesses nums[0], relying on the problem nonempty-input constraint.

**Captured variants:** 1 accepted C++ submission retained; distinctions are described above.

- [Original 2024438590](originals/198__2024438590.cpp) · [LeetCode submission](https://leetcode.com/problems/house-robber/submissions/2024438590/)

### 301. Remove Invalid Parentheses

[Problem](https://leetcode.com/problems/remove-invalid-parentheses/) · Tags: Dynamic programming, Backtracking, Strings

Memoized (index,open balance) generates unique valid suffixes; longest remaining strings minimize removals.

**Captured variants:** One observed approach.

- [Original 2165615628](originals/301__2165615628.cpp) · [LeetCode submission](https://leetcode.com/problems/remove-invalid-parentheses/submissions/2165615628/)

### 329. Longest Increasing Path in a Matrix

[Problem](https://leetcode.com/problems/longest-increasing-path-in-a-matrix/) · Tags: Graphs, DAG, Memoized DFS

Memoize longest increasing path from each cell; strictly increasing values provide acyclic dependency.

**Captured variants:** One observed approach.

- [Original 2139455187](originals/329__2139455187.cpp) · [LeetCode submission](https://leetcode.com/problems/longest-increasing-path-in-a-matrix/submissions/2139455187/)

### 376. Wiggle Subsequence

[Problem](https://leetcode.com/problems/wiggle-subsequence/) · Tags: Wiggle DP, State compression

One accepted source keeps up/down vectors; another compresses the recurrence to two size_t scalars.

**Original-code context:** The compressed source compares nums[i] to nums[i+1], so its up/down naming follows the reverse comparison orientation. Both versions rely on nonempty input; the compressed loop uses nums.size()-1.

**Captured variants:** 2 accepted C++ submissions retained; distinctions are described above.

- [Original 1780534196](originals/376__1780534196.cpp) · [LeetCode submission](https://leetcode.com/problems/wiggle-subsequence/submissions/1780534196/)
- [Original 1778334407](originals/376__1778334407.cpp) · [LeetCode submission](https://leetcode.com/problems/wiggle-subsequence/submissions/1778334407/)

### 509. Fibonacci Number

[Problem](https://leetcode.com/problems/fibonacci-number/) · Tags: Recurrence, Recursion, Bottom-up DP

One accepted source is direct exponential recursion; another fills vector calculations bottom-up.

**Original-code context:** Keep the two genuine variants separate. Do not describe the recursive source as memoized.

**Captured variants:** 2 accepted C++ submissions retained; distinctions are described above.

- [Original 791461494](originals/509__791461494.cpp) · [LeetCode submission](https://leetcode.com/problems/fibonacci-number/submissions/791461494/)
- [Original 791453355](originals/509__791453355.cpp) · [LeetCode submission](https://leetcode.com/problems/fibonacci-number/submissions/791453355/)

### 940. Distinct Subsequences II

[Problem](https://leetcode.com/problems/distinct-subsequences-ii/) · Tags: Dynamic programming, Subsequences, Duplicate correction

Count subsequences including empty by doubling previous count, subtracting count before previous occurrence; subtract empty at end.

**Captured variants:** One observed approach.

- [Original 2133936040](originals/940__2133936040.cpp) · [LeetCode submission](https://leetcode.com/problems/distinct-subsequences-ii/submissions/2133936040/)

### 978. Longest Turbulent Subarray

[Problem](https://leetcode.com/problems/longest-turbulent-subarray/) · Tags: Comparison-state DP

Tracks current turbulent length and a uint8_t comparison code. Equal neighbors reset the state; alternating comparison signs extend it.

**Original-code context:** Two accepted submissions have byte-identical captured code. The original names contain the spelling Comparsion; preserved unchanged.

**Captured variants:** 2 accepted C++ submissions retained; distinctions are described above.

- [Original 2000663939](originals/978__2000663939.cpp) · [LeetCode submission](https://leetcode.com/problems/longest-turbulent-subarray/submissions/2000663939/)
- [Original 2000663816](originals/978__2000663816.cpp) · [LeetCode submission](https://leetcode.com/problems/longest-turbulent-subarray/submissions/2000663816/)

### 1621. Number of Sets of K Non-Overlapping Line Segments

[Problem](https://leetcode.com/problems/number-of-sets-of-k-non-overlapping-line-segments/) · Tags: Dynamic programming, State machines

Memoize point index, remaining segment count, and whether a segment is open; close at same point to permit shared endpoints.

**Captured variants:** One observed approach.

- [Original 2144058402](originals/1621__2144058402.cpp) · [LeetCode submission](https://leetcode.com/problems/number-of-sets-of-k-non-overlapping-line-segments/submissions/2144058402/)

### 2267.  Check if There Is a Valid Parentheses String Path

[Problem](https://leetcode.com/problems/check-if-there-is-a-valid-parentheses-string-path/) · Tags: Grid DP, Parentheses balance, Memoization

Memoized DFS over position and post-cell balance, packed into uint64_t key. Explore down/right and reject negative prefixes.

**Original-code context:** Bitwise | evaluates both recursive branches. The original has no parity or remaining-length pruning and retains potentially large position/balance state. It uses C++20 contains and fixed bit fields for the packed key; the input bounds keep those fields disjoint.

**Captured variants:** 1 accepted C++ submission retained; distinctions are described above.

- [Original 2157018872](originals/2267__2157018872.cpp) · [LeetCode submission](https://leetcode.com/problems/check-if-there-is-a-valid-parentheses-string-path/submissions/2157018872/)

### 2606. Find the Substring With Maximum Cost

[Problem](https://leetcode.com/problems/find-the-substring-with-maximum-cost/) · Tags: Kadane, Character weights

Builds character score overrides in unordered_map. A helper returns optional<int>, falling back to the alphabet score; Kadane tracks a best score starting at zero.

**Original-code context:** The original helper returns size_t for the default alphabet score, while explicit overrides and optional<int>::value_or produce int scores. The named helpers and std::optional are part of the original code, not an added interface.

**Captured variants:** 1 accepted C++ submission retained; distinctions are described above.

- [Original 2000622350](originals/2606__2000622350.cpp) · [LeetCode submission](https://leetcode.com/problems/find-the-substring-with-maximum-cost/submissions/2000622350/)

### 3524. Find X Value of Array I

[Problem](https://leetcode.com/problems/find-x-value-of-array-i/) · Tags: Dynamic programming, Modular products

Rolling remainder counts for all subarrays ending at current position; add singleton then extend prior endings and accumulate totals.

**Captured variants:** One source, useful companion to 3525 ordered aggregate tree.

- [Original 2148463117](originals/3524__2148463117.cpp) · [LeetCode submission](https://leetcode.com/problems/find-x-value-of-array-i/submissions/2148463117/)

### 3742. Maximum Path Score in a Grid

[Problem](https://leetcode.com/problems/maximum-path-score-in-a-grid/) · Tags: Grid DP, Budget state, Memoization

Two distinct approaches among three sources: memoized DFS over cell and remaining budget, and forward 3D DP over cell and spent cost.

**Original-code context:** Memo index is balance after paying for current cell; INT_MIN denotes impossible and is explicitly guarded before score addition. 3D storage O(rows*cols*k). Two recursive sources differ only by trailing newline.

**Captured variants:** 3 accepted C++ submissions retained; distinctions are described above.

- [Original 2161116179](originals/3742__2161116179.cpp) · [LeetCode submission](https://leetcode.com/problems/maximum-path-score-in-a-grid/submissions/2161116179/)
- [Original 2161115436](originals/3742__2161115436.cpp) · [LeetCode submission](https://leetcode.com/problems/maximum-path-score-in-a-grid/submissions/2161115436/)
- [Original 2161089125](originals/3742__2161089125.cpp) · [LeetCode submission](https://leetcode.com/problems/maximum-path-score-in-a-grid/submissions/2161089125/)

### 4058. Maximum Pulse Value After One Subarray Rotation

[Problem](https://leetcode.com/problems/maximum-pulse-value-after-one-subarray-rotation/) · Tags: Greedy, Dynamic programming, Kadane

Alternating base sum plus best nonnegative segment gain over each adjacent-pair parity.

**Captured variants:** One observed approach.

- [Original 2147436566](originals/4058__2147436566.cpp) · [LeetCode submission](https://leetcode.com/problems/maximum-pulse-value-after-one-subarray-rotation/submissions/2147436566/)
