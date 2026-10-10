# Dynamic programming and backtracking

Start with a precise state: what part of the input has already been decided,
what information the future still needs, and whether a transition counts paths,
optimizes a score, or constructs outputs. These are different operations even
when all three are called “DP.” [templates.hpp](templates.hpp) contains reusable
adaptations of the collected accepted code, with local state and C++20 helpers.

## Choose the state

| Pattern | State / transition | Time | Extra space |
|---|---|---:|---:|
| Palindrome cuts, **132** | palindrome interval + best cuts in suffix | O(n²) | O(n²) |
| Match a target subsequence, **115** | source/target prefixes; skip or consume | O(nm) | O(m) |
| Count distinct subsequence strings, **940** | double, subtract prior duplicate contribution | O(n) | O(n + alphabet) |
| Weighted interval choice, **3414** | sorted prefix + allowed count | O(n log n + nK²) | O(nK²) |
| Increasing grid path, **329** | longest path starting at a cell | O(RC) | O(RC), including stack |
| Right/down minimum grid cost, **64** | best cost to a cell | O(RC) | O(C) |
| N-Queens, **51** | next row + occupied columns/diagonals | O(n · n! + nQ) bound | O(n), plus O(nQ) output |
| Sudoku, **37** | next empty cell + row/column/box occupancy | O(9^E) bound | O(E + 81) |
| Remove invalid parentheses, **301** | `(position, unmatched opens)` → set of valid suffixes | Output-heavy, exponential | Output-heavy, exponential |

`n,m` are string lengths; `K` is the interval cap; `Q` is the number of queen
placements; `E` is the number of blank Sudoku cells. The original interval cap is
four, making its time O(n log n) and storage O(n). Copying a growing path is not a
constant-time operation when generalizing `K`.

## 1. Palindrome table + suffix optimization

The actual **132** code first fills a palindrome table, then memoizes minimum
cuts from each suffix. The helper keeps both states and tabulates cuts backward.

```text
pal[l][r] = s[l] == s[r] AND (length <= 2 OR pal[l+1][r-1])
                                  ↑ shorter interior is already known
cuts[i] = min(1 + cuts[r+1]) over r where pal[i][r]
cuts[n] = -1
```

Why `-1`? Choosing one final palindrome adds `1`, but there is no separator after
it. `1 + (-1) = 0` cancels that extra cut. The public helper defines the empty
string's answer as `0`; blindly returning the terminal sentinel would return `-1`.

For `aab`:

```text
suffix:    ""   "b"   "ab"   "aab"
cuts:      -1    0      1       1
choice:         b      a|b     aa|b
```

Fill the table by increasing right endpoint; `(l+1,r-1)` belongs to an earlier
right endpoint. Do not recurse into palindromicity afresh for every partition.

## 2. Two different meanings of “distinct subsequences”

### 115: count index choices that equal one target

The collected source memoizes two prefix-end indices. Its recurrence is:

```text
ways(i,j) = ways(i-1,j)                              // skip source[i]
          + ways(i-1,j-1), if source[i] == target[j]  // consume it
ways(i,-1) = 1       // exactly one way to form the empty target
ways(-1,j) = 0       // no source remains for a nonempty target
```

The helper uses equivalent prefix lengths and one row:

```cpp
dp[0] = 1;
for (char ch : source) {
    for (std::size_t j = target.size(); j > 0; --j) {
        if (ch == target[j - 1]) { dp[j] += dp[j - 1]; }
    }
}
```

Iterate **backward**. Forward updates could reuse the same source character more
than once. For source `aaa` and target `aa`, three different index pairs count,
even though every resulting string is the same.

The source's member memo only keys indices, so reusing the same `Solution` object
for different strings without clearing it is unsafe. Local state avoids that.
The helper uses `uint64_t` and throws on any intermediate count overflow; it does
not promise arbitrary-precision results. Even an eventual small answer does not
guarantee every tracked prefix count is small.

### 940: count unique resulting strings

Let `dp[i]` count distinct subsequences of prefix length `i`, **including empty**.
For a new character, either omit it or append it to every existing subsequence.
This suggests doubling. If the same character last occurred at one-based position
`p`, those formed from the prefix before `p` were already generated:

```text
dp[i] = 2 * dp[i-1] - dp[p-1]       if a previous occurrence p exists
dp[i] = 2 * dp[i-1]                 otherwise
answer = dp[n] - 1                 remove the empty subsequence
```

Example `aba`: prefix totals including empty are `1, 2, 4, 7`; at the last `a`,
subtract `dp[0]` to avoid counting `a` twice. Result: six nonempty strings.

Normalize subtraction before `% mod`, and use an integer constant for the
modulus. The source uses lowercase letters and recursive memoization; the helper
uses a 256-entry byte table and bottom-up DP. This handles bytes, not Unicode code
points or grapheme clusters.

## 3. Weighted intervals: compatibility + an explicit tie-break

Source **3414** selects at most four **closed** intervals. An interval ending at
`x` overlaps one starting at `x`. Compatibility is therefore `end < nextStart`,
not `end <= nextStart`.

1. Keep each original input index and sort a copy by right endpoint.
2. Binary-search how many earlier intervals end **strictly before** the current
   left endpoint. This prefix is `previousCount[i]`.
3. Store score **and sorted original indices** in each DP state.

```text
dp[k][i] = best among first i sorted intervals using at most k

skip = dp[k][i-1]
take = dp[k-1][previousCount[i-1]] + current interval
best = larger score, then lexicographically smaller original-index vector
```

```text
sorted by finish:       ... compatible prefix ... | overlapping ... | current
                                  ↑
                               take starts here
```

Original indices must survive sorting. Compare the sorted **answer indices**,
not end-time order, selected count, or only the last index. For intervals
`[1,2,3], [3,4,3], [1,4,6]`, both scores are six; `[0,1]` beats `[2]`.

The reusable API returns `{score, indices}`, preserves the input, permits an
explicit `cap`, inserts each chosen index in sorted order, and checks score
overflow. `cap == 0` returns an empty selection.

**Keep the positive-weight contract.** This matches the collected problem and
also supports the local lexicographic tie-break. With positive weights, equal-score
selections cannot be strict subset/prefix extensions of one another; inserting
the same new index preserves their lexicographic order. Allowing zero weights
without revisiting the tie logic is not a harmless generalization: an empty
prefix can locally beat `[0]`, but after adding index `2`, `[0,2]` beats `[2]`.
The helper rejects zero/negative weights and reversed endpoints.

For general `K`, each state may copy/insert O(K) indices. There are O(nK) states,
so O(nK²) time and stored index elements are honest bounds. The source sorts the
chosen vector each time; the helper maintains its order by insertion.

## 4. Recognize an implicit DAG

### 329: strict increases already prevent cycles

Treat each cell as a vertex and draw an edge to every strictly larger orthogonal
neighbor. Values strictly increase along an edge, so returning to a previous
vertex would require its value to be larger than itself.

```text
memo[r][c] = 1 + max(memo[nr][nc]) over larger neighbors
no larger neighbor → 1
answer = max over all starting cells
```

Each cell computes once; at most four outgoing edges are checked. A separate
current-path visited set is unnecessary. The source had both memo and such a set;
the helper removes the redundant set and compares neighbors directly.

The collected DFS starts every search with `prev = -1`, consistent with its
nonnegative input. That sentinel is invalid for a reusable negative-valued grid.
The helper handles values such as `-4 → -3 → -2 → -1` naturally. State is rebuilt
per call, avoiding the source's `resize` behavior that could retain old memo
entries across calls with the same dimensions. Worst-case recursion depth is RC.

### 64: right/down moves define the dependency order

```text
           top
            ↓
left → current
cost[r][c] = grid[r][c] + min(cost[r-1][c], cost[r][c-1])
```

The source stores the entire table and separately initializes the first row and
column. The helper rolls it into one row. Before updating column `c`, `dp[c]` is
the top value and `dp[c-1]` is the left value already computed in the current row.
First-row/first-column handling avoids “infinity + cost” arithmetic.

Negative cell costs remain valid because right/down paths cannot cycle. Path
sums must fit `long long`. Both grid helpers return zero for a rectangular empty
grid and reject ragged rows before indexing.

## 5. Backtracking is a reversible state transition

The reusable skeleton is the same in **37** and **51**:

```text
choose legal candidate
apply every state change
recurse
undo every state change          ← including constraint bookkeeping
```

Do not undo on a successful Sudoku return: the solved board is the output.
Always undo after recording an N-Queens solution because search continues.

### N-Queens

Source **51** puts one queen in each row and checks three upward attack rays.
The helper's explicit optimization uses occupancy vectors:

- Column: `col`
- Downward diagonal: `row - col + n`
- Upward diagonal: `row + col`

Two queens attack exactly when one of those identities agrees. Row uniqueness is
already enforced by recursion. Store the chosen column per row instead of copying
an n-by-n string board for every solution; convert to a board only if needed.

The source's upper-right loop uses `col <= n`, reaching the string's terminating
NUL at `col == n`, rather than a board cell. The correct board-bound check would
be `col < n`; occupancy vectors eliminate that scan entirely. This is a documented
adaptation, not an assertion that the source already used constant-time checks.
`n == 0` returns one empty placement; negative `n` is rejected.

### Sudoku

Source **37** tracks sets of used characters for each row, column, and 3-by-3 box.
The helper keeps exactly those constraints in nine-bit integer masks and walks a
row-major vector of initially blank cells. Box index is `(row / 3) * 3 + col / 3`.

Applying a digit sets the board cell and all three masks. A failed branch must
undo all four. Initial dimensions, characters, and duplicate givens are checked
before writing any cell. The result is `true` with a solution, or `false` with the
input unchanged. This fixed 9-by-9 solver deliberately makes no uniqueness claim.

## 6. Memoized sets are not polynomial numeric DP

The collected **301** implementation returns an entire set of strings from each
state `(i, open)`. Here `open` is the number of unmatched `(` in the already-kept
prefix; each returned suffix must finish that balance without becoming negative.

- Parenthesis: branch into skip and keep
- Non-parenthesis: must keep it
- Keep `(`: balance increases; keep `)`: balance decreases
- Negative balance: impossible
- End: return `{ "" }` only when the balance is zero
- Union results to remove duplicate strings

Finally, retain the longest valid strings. With non-parenthesis characters
mandatory, longest output is equivalent to fewest removals.

```text
state (i, open)
   ├─ skip parenthesis → suffixes from (i+1, open)
   └─ keep character   → character + suffixes from (i+1, nextOpen)
```

The source uses `memo[i][open].empty()` as its cached test, so a computed impossible
state is recomputed. The helper keeps a separate `seen` table. It also prunes
`open > remaining characters`, returns cached sets by reference, and sorts the
final result for stable output.

There may be only O(n²) state coordinates, but each value is a **set of many
strings**. If `p` characters are parentheses, a conservative expected bound for
this implementation is O(n³ · 2^p) time and stored character data, plus O(n²)
empty-state overhead; hash-table worst cases can be worse. Output copies and hash
costs matter. Use this faithful teaching pattern on short strings, not as a
polynomial-time template for long inputs.

## Adaptation ledger

- **132:** preserve the palindrome recurrence and terminal `-1`; iterative suffix
  table, explicit empty answer, byte-backed booleans instead of `vector<bool>`.
- **115:** two-index memo recurrence → rolling row; local state; backward updates;
  checked `uint64_t` arithmetic instead of unchecked `int` counts.
- **940:** recursive recurrence → iterative table; integer modulus; 256-byte
  alphabet instead of fixed lowercase; local prior-occurrence state.
- **3414:** input copy; `{score, indices}` return; explicit cap; predecessor prefix
  through `lower_bound`; sorted insertion; positive-weight and overflow checks.
- **329:** direct neighbor comparisons, no fake lower sentinel or path set;
  fresh memo per call; empty/ragged grid behavior defined.
- **64:** rolling row rather than full table; `long long` sums; no grid mutation.
- **51:** occupancy vectors replace source ray scans; column-vector outputs;
  remove unused recursive argument and questionable inclusive column bound.
- **37:** bit masks replace source sets; precomputed blank cells; validate givens;
  return success/failure and guarantee full rollback on failure.
- **301:** independent computed flag; safe remaining-length prune; const cached
  references; stable sorted result. Still enumerates valid subsequences.

## Tests

From this folder:

```sh
g++ -std=c++20 -O2 -Wall -Wextra -Werror test.cpp -o /tmp/dp-test
/tmp/dp-test
g++ -std=c++20 -O1 -g -Wall -Wextra -Werror \
  -fsanitize=address,undefined -fno-omit-frame-pointer test.cpp -o /tmp/dp-asan
ASAN_OPTIONS=detect_leaks=1 /tmp/dp-asan
```

Seed `0xd01234` drives:

- 250 short-string trials: palindrome partitions, target multiplicity, distinct
  subsequence sets, and minimal parenthesis removals, compared to enumeration
- 250 weighted-interval trials compared to every subset, including tied scores,
  original-index ordering, strict overlap, and caps 0–4
- 200 small grids compared to exhaustive increasing and right/down paths

Deterministic tests additionally cover empty inputs, a negative-valued DAG,
wide grid sums, target-count overflow, malformed grids, known N-Queens counts
0–8, a solved Sudoku, contradictory givens, and complete rollback for a valid-
looking but unsatisfiable puzzle. Test bodies were written and observed failing
against no-op API stubs before implementing the helpers.

Strict compilation and AddressSanitizer/UndefinedBehaviorSanitizer passed. The
sandbox's ptrace environment prevents LeakSanitizer from running; its successful
sanitizer pass used `ASAN_OPTIONS=detect_leaks=0`. Enable leak detection when
running in an unrestricted local process.

## Collected source links

Every algorithm above is tied to actual collected accepted code. Links may
require the submission owner's LeetCode login.

- [132. Palindrome Partitioning II](https://leetcode.com/problems/palindrome-partitioning-ii/) — [submission 2165701086](https://leetcode.com/problems/palindrome-partitioning-ii/submissions/2165701086/).

- [115. Distinct Subsequences](https://leetcode.com/problems/distinct-subsequences/) — [submission 2133267031](https://leetcode.com/problems/distinct-subsequences/submissions/2133267031/).

- [940. Distinct Subsequences II](https://leetcode.com/problems/distinct-subsequences-ii/) — [submission 2133936040](https://leetcode.com/problems/distinct-subsequences-ii/submissions/2133936040/).

- [3414. Maximum Score of Non-overlapping Intervals](https://leetcode.com/problems/maximum-score-of-non-overlapping-intervals/) — [submission 2139370298](https://leetcode.com/problems/maximum-score-of-non-overlapping-intervals/submissions/2139370298/).

- [329. Longest Increasing Path in a Matrix](https://leetcode.com/problems/longest-increasing-path-in-a-matrix/) — [submission 2139455187](https://leetcode.com/problems/longest-increasing-path-in-a-matrix/submissions/2139455187/).

- [64. Minimum Path Sum](https://leetcode.com/problems/minimum-path-sum/) — [submission 2126173167](https://leetcode.com/problems/minimum-path-sum/submissions/2126173167/), [submission 2126172428](https://leetcode.com/problems/minimum-path-sum/submissions/2126172428).

- [51. N-Queens](https://leetcode.com/problems/n-queens/) — [submission 2164697200](https://leetcode.com/problems/n-queens/submissions/2164697200/).

- [37. Sudoku Solver](https://leetcode.com/problems/sudoku-solver/) — [submission 2164710608](https://leetcode.com/problems/sudoku-solver/submissions/2164710608/).

- [301. Remove Invalid Parentheses](https://leetcode.com/problems/remove-invalid-parentheses/) — [submission 2165615628](https://leetcode.com/problems/remove-invalid-parentheses/submissions/2165615628/).
