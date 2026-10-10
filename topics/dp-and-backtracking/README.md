# DP and backtracking

[All topics](../../README.md) · [Source index](../../SOURCES.md) · [Coverage](../../COVERAGE.md)

## Main algorithms and structures

Identify the smallest state that determines every legal continuation, then choose whether to count, optimize, or enumerate it. The complete catalog of **23 problems / 31 submissions** is last; links below point directly to unchanged originals.

Here `n,m` are sequence lengths, `r,c` grid dimensions, `k` a budget/remainder/segment parameter, and `L` a searched word's length. Hash-table bounds are expected. Space includes recursion, containers, and by-value string copies for lvalue calls; output storage is listed separately. Exponential search bounds below are upper bounds, not claims that every input attains them.

| Algorithm / data structure | Recognition trigger | Time in these sources | Space in these sources | Direct implementations |
|---|---|---|---|---|
| Kadane / maximum nonnegative gain | Best contiguous contribution after a baseline or weighting transform | O(n); weighted string O(n+A), A overrides | O(1) scan; weighted string O(A) map + O(n+A) input copies | [Maximum sum](originals/53__2000625681.cpp), [character weights](originals/2606__2000622350.cpp), [two parity gain scans](originals/4058__2147436566.cpp) |
| Maximum/minimum product states | Negative multiplier can swap best and worst | O(n) | O(1) | [Product DP](originals/152__2000724011.cpp) |
| Two-phase subsequence DP | Last selected difference must change sign | O(n) | O(n) up/down vectors or O(1) scalars | [Array states](originals/376__1780534196.cpp), [compressed states](originals/376__1778334407.cpp) |
| Previous-comparison state | Adjacent signs must alternate in a contiguous run | O(n) | O(1) | [Turbulent run](originals/978__2000663939.cpp) |
| Prefix best with skip/take choice | Taking an item forbids its neighbor | O(n) | O(n) DP vector, not compressed | [Nonadjacent maximum](originals/198__2024438590.cpp) |
| Direct recurrence vs bottom-up table | Repeated recursive subproblems can be tabulated | Recursive O(phiⁿ), phi≈1.618; table O(n) | Recursive O(n) stack; table O(n) vector | [Direct Fibonacci recursion](originals/509__791453355.cpp), [iterative table](originals/509__791461494.cpp) |
| Row-by-row constructive DP | Each output row depends only on its predecessor | O(r²) for r rows | Iterative O(r) temporary + O(r²) output; recursive O(r²) live copied vectors + O(r) stack + O(r²) output | [Iterative Pascal](originals/118__2116229650.cpp), [recursive copies](originals/118__791480396.cpp), [redundant-row variant](originals/118__791476688.cpp) |
| Acyclic grid-cost table | Path moves only right/down and has additive cost | O(rc) | O(rc) full table | [Top/left minimum](originals/64__2126173167.cpp) |
| Position × resource DP | Paths to the same cell have different remaining budgets | O(rc(k+1)) in both variants | O(rc(k+1)) table; recursive variant also O(r+c) stack | [Remaining-budget DFS](originals/3742__2161116179.cpp), [spent-cost forward DP](originals/3742__2161115436.cpp) |
| Position × balance memoization | A path must satisfy a prefix-balance constraint | Expected O(rc(r+c)) | O(rc(r+c)) memo + O(r+c) stack | [Parenthesis-path state](originals/2267__2157018872.cpp) |
| Memoized DFS on an implicit DAG | Strict value increase makes every move acyclic | Expected O(rc) | O(rc) memo + up to O(rc) visited entries and stack | [Increasing path](originals/329__2139455187.cpp) |
| Interval predicate + suffix optimization | Many partition choices reuse substring validity | O(n²) | O(n²) palindrome table + O(n) memo/stack/input copy | [Palindrome cuts](originals/132__2165701086.cpp) |
| Two-prefix counting memo | Count ways to match target prefix in source prefix | Expected O(nm+n+m) | O(nm) memo + O(n) stack + O(n+m) input copies | [Skip/consume subsequences](originals/115__2133267031.cpp) |
| Last-occurrence correction + prefix count | Repeated symbols double-count identical subsequences | O(n) | O(n) DP/previous arrays, recursive stack, and input copy | [Distinct subsequence counts](originals/940__2133936040.cpp) |
| Rolling histogram of endings | Aggregate all subarrays ending at the new item | O(nk) | O(k) current/next vectors + O(k) output | [Product-remainder counts](originals/3524__2148463117.cpp) |
| Position × count × phase memo | Legal choices depend on whether a segment is open | O(B+nk), B=2·1005² entries initialized every call | O(B+n+k), including recursive frames; table is 16,160,400 bytes | [Open/closed segment states](originals/1621__2144058402.cpp) |
| Balance-pruned enumeration | Generate every valid parenthesis string | O(n Cₙ), Cₙ the nth Catalan number | O(n) buffer/stack + O(n Cₙ) copied output | [Push/recurse/pop](originals/22__2160263536.cpp) |
| Constraint sets + undo | A placement must satisfy row/column/box constraints | O(9ᵉ) crude bound for e empty cells on the fixed 9×9 board | O(81) constraint data and at most 81-cell recursion, excluding input board | [Sudoku search](originals/37__2164710608.cpp) |
| Row placement + directional attack scans | Place one queen per row and enumerate boards | O(n² n! + Qn²) upper bound, Q returned boards | O(n²) board + O(n) stack + O(Qn²) copied output | [N-Queens with scans](originals/51__2164697200.cpp) |
| In-place mark/restore DFS | Match a word without reusing a cell on one path | O(rc·3ᴸ + L) upper bound | O(min(L,rc)) search stack + O(L) word copy | [Word Search](originals/79__2168591618.cpp) |
| Memoized sets of generated strings | Return all valid strings with minimum deletions | Conservative expected O(n²·2ⁿ); includes set/string copies and uncached failures | O(n²+n·2ⁿ) upper bound for memo objects/live strings; output also may be exponential | [Set-valued recursion](originals/301__2165615628.cpp) |

## Combinations and tricks

### Turn an operation into a gain sequence, then keep the best ending here

- **Recognize:** The original objective has a fixed baseline plus a contiguous change, or characters have custom weights.
- **Compose:** Compute the pulse baseline, derive the adjacent-pair gains separately for each starting parity, and run a reset-at-zero scan on each. For weighted strings, map overrides first and feed the resulting scores into the same recurrence.
- **Invariant:** The running value is the best useful continuation ending at the current position; a negative prefix cannot improve any later sum. Pulse scans start with zero gain, preserving the option of no improvement.
- **Tradeoff / trap:** Maximum Subarray updates its best **before** resetting and initializes best to `INT_MIN`, preserving all-negative nonempty answers. The weighted-string source initializes best to zero because the empty substring is allowed. Reusing the recurrence without its empty/nonempty convention changes the answer.
- **Originals:** [Nonempty Kadane](originals/53__2000625681.cpp), [character-cost transform](originals/2606__2000622350.cpp), [baseline + parity gains](originals/4058__2147436566.cpp).

### Keep only predecessor information that can still affect the future

- **Recognize:** Every update depends on a fixed number of earlier summaries, but “best” alone may be insufficient.
- **Compose:** Maximum product stores both maximum and minimum, saving both old states before updating. Wiggle stores up/down ending types, either in full vectors or two scalars. Turbulence keeps a run length and previous comparison sign, resetting on equality.
- **Invariant:** A negative multiplier can promote the previous minimum to the new maximum. Wiggle may skip intervening elements, while turbulence must restart when adjacency breaks; their similar sign states encode different legal continuations.
- **Tradeoff / trap:** Compression is valid only when overwritten states are no longer needed. The captured House Robber still keeps its O(n) vector and has an unused cache member; the Fibonacci recursion is genuinely exponential, while its iterative counterpart keeps a full O(n) table. The compressed wiggle loop assumes nonempty input and names directions using a reverse comparison orientation.
- **Originals:** [Two product extrema](originals/152__2000724011.cpp), [wiggle vectors](originals/376__1780534196.cpp), [wiggle scalars](originals/376__1778334407.cpp), [turbulence](originals/978__2000663939.cpp), [House Robber table](originals/198__2024438590.cpp), [recursive](originals/509__791453355.cpp) / [iterative Fibonacci](originals/509__791461494.cpp).

### Precompute the expensive predicate, then optimize over valid transitions

- **Recognize:** A partition recurrence repeatedly asks whether the same interval is valid.
- **Compose:** Fill palindrome truth values by increasing right endpoint, using matching ends and the inner interval. Then memoize the minimum cuts starting at each suffix index, trying only palindromic next pieces.
- **Invariant:** The inner interval is already known when evaluating `[l,r]`. The suffix answer is independent of how that suffix was reached. Returning `-1` at the end cancels the extra separator added after the final piece.
- **Tradeoff / trap:** O(n²) predicate preprocessing avoids rescanning every candidate substring, but the source still stores the full table and recurses up to n frames. Distinguish a terminal sentinel from a cached valid answer: here `-1` marks uncached nonterminal states, whose true cut counts are nonnegative.
- **Originals:** [Palindrome predicate + suffix DP](originals/132__2165701086.cpp); compare [two-prefix skip/consume counting](originals/115__2133267031.cpp), where both source and target positions are required to determine a subproblem.

### Add a resource coordinate when equal positions are not equivalent

- **Recognize:** Two paths reach the same cell but leave different future choices because of budget or open-parenthesis balance.
- **Compose:** Extend `(row,column)` with remaining budget or balance. The score DFS pays the current cell **before** indexing its memo; the forward variant indexes total spent cost. The parentheses path also keys the balance after consuming the current cell.
- **Invariant:** A memo key must refer to one consistent moment in the transition. Negative budget/prefix balance is infeasible; a destination parenthesis path is valid only at balance zero. Packed coordinates must occupy disjoint bit fields.
- **Tradeoff / trap:** The parenthesis source has no parity or remaining-length pruning and uses bitwise `|`, evaluating both directions. Its balance can grow with path length, yielding O(rc(r+c)) rather than O(rc) state space. Score DFS distinguishes uncached `-2` from impossible `INT_MIN` and checks impossibility **before** addition to avoid overflowing the sentinel.
- **Originals:** [Post-payment memo](originals/3742__2161116179.cpp), [forward spent-cost table](originals/3742__2161115436.cpp), [packed post-cell balance](originals/2267__2157018872.cpp), [plain position-only grid DP](originals/64__2126173167.cpp).

### Prove acyclicity before discarding path history

- **Recognize:** A grid looks cyclic, but a strict movement rule may make the dependency graph a DAG.
- **Compose:** Increasing-path DFS accepts only a strictly larger next value, caches the best continuation per cell, and tries all four directions. Word Search instead marks each visited cell `#`, explores, and restores it; its legal continuations depend on the current path's used cells.
- **Invariant:** Strict increase makes return to an earlier cell impossible, so the longest increasing continuation is determined by the cell alone. Word Search's board markings represent exactly the active prefix path; restoring a cell restores sibling-branch state.
- **Tradeoff / trap:** Increasing-path code still maintains a redundant visited set and can recurse through rc cells. Its initial `prev=-1` relies on nonnegative values. Word Search is **not memoized**: its computed key is unused, and position/word index alone would omit path history. Its bitwise `|` evaluates every direction after a match, even when one succeeds; restoration still happens before return.
- **Originals:** [Strict-increase memo](originals/329__2139455187.cpp), [mark/explore/restore](originals/79__2168591618.cpp). Word Search assumes a nonempty board and an alphabet excluding `#`.

### Aggregate equivalent endings, then correct duplicate counting

- **Recognize:** Many histories lead to the same remainder, or appending a repeated symbol recreates already-counted strings.
- **Compose:** For product remainders, start the singleton at each position, extend every previous remainder into a fresh histogram, then add that histogram into global totals. For distinct subsequences, double the prior prefix count and subtract the count before the same character's previous occurrence.
- **Invariant:** Remainder `dp` counts only subarrays ending at the previous position; `ndp` counts only endings at the current position. Subsequence counts include the empty sequence internally, with one final subtraction; previous-occurrence correction removes exactly the repeated family.
- **Tradeoff / trap:** Updating the remainder histogram in place would mix old and new endings and reuse the current element. The distinct-subsequence source uses O(n) arrays **and** O(n) recursion, despite a possible smaller-state formulation. Counting subsequences in [115](originals/115__2133267031.cpp) counts positional matches of a fixed target, which is a different notion of duplication.
- **Originals:** [Rolling endings](originals/3524__2148463117.cpp), [last-occurrence subtraction](originals/940__2133936040.cpp).

### Phase flags encode which transitions are legal

- **Recognize:** A choice has an opening and closing phase, and endpoint-sharing rules matter.
- **Compose:** Segment counting uses `(point,remaining segments,open)`. Opening advances to the next point; while open, either advance or close at the same point with one fewer segment. This permits the next segment to start at the shared endpoint without allowing zero-length segments.
- **Invariant:** The phase says whether a start point is already committed. Every transition increases the point index or decreases the remaining count, so the state graph is acyclic even when closing does not move the point.
- **Tradeoff / trap:** Reachable transition work is O(nk), but the implementation always allocates and clears a fixed `1005×1005×2` long-long table, about 16.2 MB, even for tiny inputs. Recursion adds O(n+k) frames. Report setup cost rather than replacing this source with an imagined dynamically sized table.
- **Originals:** [Open/closed segment state machine](originals/1621__2144058402.cpp); [grid resource state](originals/3742__2161116179.cpp) is the same principle of retaining information that changes legal future moves.

### Apply a choice, recurse, and undo exactly that choice

- **Recognize:** You must enumerate feasible arrangements or search a mutable board.
- **Compose:** Sudoku updates the board plus row/column/box sets and undoes all four on failure. N-Queens places one queen per row, scans earlier rows for attacks, recurses, then clears the square. Parenthesis generation pushes and pops a shared string while checking nonnegative balance and whether the remaining slots can close the opens.
- **Invariant:** Mutable state describes exactly the current partial assignment when entering and leaving a failed branch. Successful Sudoku deliberately returns without undoing, preserving the solution; enumerators undo even after recording an answer so they can continue searching.
- **Tradeoff / trap:** N-Queens tests up to n candidates with O(n) attack scans per search node, not constant-time diagonal sets. Its right-diagonal bound is `col <= n`, which reads the string's terminator at `col==n`; that is outside board columns and is not a reusable indexing convention. Returned boards/strings are copied, so include Qn² or nCₙ output storage and work.
- **Originals:** [Sudoku constraint sets](originals/37__2164710608.cpp), [scanning queen attacks](originals/51__2164697200.cpp), [balance-pruned string buffer](originals/22__2160263536.cpp).

### Memoizing a set is not the same cost as memoizing a number

- **Recognize:** A state returns every valid completion rather than one count or optimum.
- **Compose:** Parenthesis removal memoizes sets of suffix strings by `(index,open balance)`, combines skip/keep branches, deduplicates, then filters complete candidates to maximum length. Equal-length longest survivors correspond to minimum removals.
- **Invariant:** A stored suffix must close exactly the incoming balance without a negative intermediate prefix. Deduplication removes repeated strings produced by deleting indistinguishable parentheses, not the need to construct and hash them first.
- **Tradeoff / trap:** There are O(n²) state coordinates, but each can hold many strings. The function returns sets **by value**, copies cached sets, prepends characters, and treats an empty set as “not computed,” so impossible states can repeat. Its output and intermediate work can be exponential; the table gives conservative character-copy-aware upper bounds rather than a misleading O(n²) claim.
- **Originals:** [Set-valued removal recursion](originals/301__2165615628.cpp); compare [scalar balance memo](originals/2267__2157018872.cpp) and [output enumeration with one mutable buffer](originals/22__2160263536.cpp).

### Account for live frames and reset state at the correct lifetime

- **Recognize:** A seemingly small recurrence retains local buffers or class members beyond one transition/call.
- **Compose:** Iterative Pascal moves a finished row into output; the recursive sources copy both the current and next rows and leave those vectors alive while deeper rows are built. Memoization must likewise be initialized for the current input before cached answers can be reused.
- **Invariant:** A cache key is valid only relative to the input that defined it. An allocation in a suspended recursive frame remains live until that frame returns, even if deeper calls no longer read it.
- **Tradeoff / trap:** Recursive Pascal can retain O(r²) auxiliary vector data in addition to O(r²) output and O(r) frames. Distinct Subsequences never clears its member memo. Increasing Path uses `resize(...,-1)`, which does not reset existing cells when dimensions stay the same, so repeated calls can reuse stale answers. Distinct Subsequences II explicitly resets its arrays each call. These notes describe single-call judge implementations, not a reusable shared-state API.
- **Originals:** [Iterative Pascal](originals/118__2116229650.cpp), [live recursive row copies](originals/118__791480396.cpp), [extra-row recursive variant](originals/118__791476688.cpp), [retained prefix memo](originals/115__2133267031.cpp), [resize-based grid memo](originals/329__2139455187.cpp), [explicit reset](originals/940__2133936040.cpp).

## Problem and source appendix


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
