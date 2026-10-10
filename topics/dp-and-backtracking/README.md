# DP and backtracking

[All topics](../../README.md) · [Source index](../../SOURCES.md) · [Coverage](../../COVERAGE.md)

**11 captured problems · 12 accepted submission records.** Every linked implementation below is an unchanged captured source file. These notes describe the code; they do not replace it with a common API.

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

### 64. Minimum Path Sum

[Problem](https://leetcode.com/problems/minimum-path-sum/) · Tags: Dynamic programming, Grid paths

Initialize first row/column; each cell cost plus min(top,left).

**Captured variants:** One observed approach.

- [Original 2126173167](originals/64__2126173167.cpp) · [LeetCode submission](https://leetcode.com/problems/minimum-path-sum/submissions/2126173167/)
- [Original 2126172428](originals/64__2126172428.cpp) · [LeetCode submission](https://leetcode.com/problems/minimum-path-sum/submissions/2126172428)

### 115. Distinct Subsequences

[Problem](https://leetcode.com/problems/distinct-subsequences/) · Tags: Dynamic programming, Subsequences, Coordinate packing

Memoize matching target prefix inside source prefix; choose skip or consume matching character.

**Captured variants:** One observed approach.

- [Original 2133267031](originals/115__2133267031.cpp) · [LeetCode submission](https://leetcode.com/problems/distinct-subsequences/submissions/2133267031/)

### 132. Palindrome Partitioning II

[Problem](https://leetcode.com/problems/palindrome-partitioning-ii/) · Tags: Dynamic programming, Palindromes

Build palindrome table, then memoize minimum cuts from each suffix with terminal -1 to cancel last separator.

**Captured variants:** One observed approach.

- [Original 2165701086](originals/132__2165701086.cpp) · [LeetCode submission](https://leetcode.com/problems/palindrome-partitioning-ii/submissions/2165701086/)

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

### 940. Distinct Subsequences II

[Problem](https://leetcode.com/problems/distinct-subsequences-ii/) · Tags: Dynamic programming, Subsequences, Duplicate correction

Count subsequences including empty by doubling previous count, subtracting count before previous occurrence; subtract empty at end.

**Captured variants:** One observed approach.

- [Original 2133936040](originals/940__2133936040.cpp) · [LeetCode submission](https://leetcode.com/problems/distinct-subsequences-ii/submissions/2133936040/)

### 1621. Number of Sets of K Non-Overlapping Line Segments

[Problem](https://leetcode.com/problems/number-of-sets-of-k-non-overlapping-line-segments/) · Tags: Dynamic programming, State machines

Memoize point index, remaining segment count, and whether a segment is open; close at same point to permit shared endpoints.

**Captured variants:** One observed approach.

- [Original 2144058402](originals/1621__2144058402.cpp) · [LeetCode submission](https://leetcode.com/problems/number-of-sets-of-k-non-overlapping-line-segments/submissions/2144058402/)

### 3524. Find X Value of Array I

[Problem](https://leetcode.com/problems/find-x-value-of-array-i/) · Tags: Dynamic programming, Modular products

Rolling remainder counts for all subarrays ending at current position; add singleton then extend prior endings and accumulate totals.

**Captured variants:** One source, useful companion to 3525 ordered aggregate tree.

- [Original 2148463117](originals/3524__2148463117.cpp) · [LeetCode submission](https://leetcode.com/problems/find-x-value-of-array-i/submissions/2148463117/)

### 4058. Maximum Pulse Value After One Subarray Rotation

[Problem](https://leetcode.com/problems/maximum-pulse-value-after-one-subarray-rotation/) · Tags: Greedy, Dynamic programming, Kadane

Alternating base sum plus best nonnegative segment gain over each adjacent-pair parity.

**Captured variants:** One observed approach.

- [Original 2147436566](originals/4058__2147436566.cpp) · [LeetCode submission](https://leetcode.com/problems/maximum-pulse-value-after-one-subarray-rotation/submissions/2147436566/)
