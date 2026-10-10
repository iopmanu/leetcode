# Strings and tries

Your submissions repeatedly turn a string into a small state machine: a matched-prefix length, a trie node, an unmatched-open count, or a stack of unfinished frames. The extracted header keeps that style: `std::` types, camelCase helpers, straightforward loops, and nested structs rather than a large generic framework.

## Copy-ready pieces

Include `templates.hpp`; everything lives in `patterns`, with no cross-topic dependencies. Strings are **byte sequences**: embedded NULs work, but Unicode grapheme boundaries, normalization, and case folding are outside these contracts.

| Piece | Meaning | Time | Extra space |
|---|---|---|---|
| `Kmp::buildLps(pattern)` | Longest proper border at every position | O(m) | O(m) |
| `Kmp::searchAll(text, pattern)` | All starting positions, including overlaps | O(n + m + matches) | O(m + matches) |
| `Kmp::isRepeatedPattern(text)` | At least two copies of one nonempty block | O(n) | O(n) |
| `Kmp::shortestPalindrome(text)` | Prepend the fewest bytes to make a palindrome | O(n) | O(n) |
| `Trie::insert/search/startsWith` | Whole-word membership versus prefix membership | Expected O(L) per operation | O(total distinct-prefix nodes) overall |
| `minAddToMakeValid(text)` | Fewest inserted single parentheses | O(n) | O(1) |
| `removeOuterParentheses(text)` | Remove the outer pair of each primitive balanced group | O(n) | O(n) output |
| `scoreParentheses(text)` | `()=1`, `(A)=2A`, concatenation adds | O(n) | O(depth) |

Empty contracts are explicit: LPS is empty; an empty search pattern matches all n+1 boundaries; empty text is not a repeated nonempty block; the shortest palindrome is empty. A trie initially contains the empty prefix but not the empty word; `insert("")` adds that word. Empty parentheses need zero insertions, produce empty output, and score zero.

## 1. KMP: on mismatch, shorten the candidate without moving the text

The construction comes from your [28. Find the Index of the First Occurrence in a String](https://leetcode.com/problems/find-the-index-of-the-first-occurrence-in-a-string/) ([submission 2163524870](https://leetcode.com/problems/find-the-index-of-the-first-occurrence-in-a-string/submissions/2163524870/)) and the extracted `buildLps` in [214. Shortest Palindrome](https://leetcode.com/problems/shortest-palindrome/) ([submission 2163593115](https://leetcode.com/problems/shortest-palindrome/submissions/2163593115/)).

```text
index     0 1 2 3 4 5 6
pattern   a b a b a c a
lps       0 0 1 2 3 0 1

At a mismatch after matching "ababa":
matched = 5 → lps[4] = 3 → lps[2] = 1 → lps[0] = 0
Try each viable border against the SAME current text byte.
```

`lps[i]` is the length of the longest **proper** prefix of `pattern[0..i]` that is also its suffix. During search, `matched` is the length of the pattern prefix matching the suffix of the text already consumed. A mismatch discards only lengths ruled out by the border chain. Successful comparisons increase this length; fallback decreases it, which gives linear total work.

**The all-matches change:** your source returns on the first match. This header records it, then sets `matched = lps[matched - 1]`. Resetting to zero loses overlaps: `aaa` occurs at 0, 1, and 2 in `aaaaa`. Accessing `pattern[matched]` while matched equals its length is also unsafe; fallback must happen before processing the next byte.

**Changes from source:** shared `buildLps`; `std::size_t` lengths/positions instead of narrowing `int`; `std::string_view` inputs avoid copies; empty-pattern behavior is checked before indexing. The original 28 submission relies on the problem's nonempty needle constraint. The helper's all-boundaries empty result is a deliberate API choice, not a claim about the submitted return convention.

### Border length also detects a full repeated block

Your [459. Repeated Substring Pattern](https://leetcode.com/problems/repeated-substring-pattern/) ([submission 2163579090](https://leetcode.com/problems/repeated-substring-pattern/submissions/2163579090/)) uses:

```text
border = lps[n-1]
period = n - border
repetition ⇔ border > 0 and n % period == 0
```

A nonzero border alone is insufficient: `aba` has border `a`, but length 3 is not divisible by candidate period 2. The extracted function drops the unused map and zero-prefix scan, and protects the empty case before `lps.back()`.

### Palindromic prefixes without a reserved separator

Your 214 solution builds LPS for `s + "#" + reverse(s)`. The last value is the longest palindromic-prefix length because the separator cannot appear inside the problem's lowercase-only input.

The reusable helper instead builds LPS for s and runs its matcher over `reverse(s)`. At the end, a matching prefix of s equals a suffix of `reverse(s)`, which is the reverse of that same prefix. The largest such length is exactly the longest palindromic prefix. Reverse the remaining suffix and prepend it.

```text
s = a a c e c a a a
    └ palindromic ┘ │
         prefix     suffix
prepend reverse(suffix) → a a a c e c a a a
```

**Change from source:** no delimiter is reserved, so `#` and arbitrary bytes are safe. The matcher scans exactly n bytes; a full n-byte match can happen only on its final iteration. This is an adaptation of your KMP palindrome idea, not a verbatim copy.

### An observed implicit-string extension

[686. Repeated String Match](https://leetcode.com/problems/repeated-string-match/) ([submission 2163561881](https://leetcode.com/problems/repeated-string-match/submissions/2163561881/)) reads `a[i % a.size()]` rather than allocating repeated copies. Your submitted bound is `2*|a| + |b|`. With nonempty a and b, considering starting offsets `0..|a|-1` only needs `|a|+|b|-1` virtual bytes. Once a match ends at exclusive index i, the required copies are `ceil(i/|a|)`. This remains a documented recipe rather than another header function; any reusable version must define empty a/b behavior before modulo/index operations.

## 2. Trie: a path is not necessarily a word

Your [208. Implement Trie (Prefix Tree)](https://leetcode.com/problems/implement-trie-prefix-tree/) ([submission 2167350538](https://leetcode.com/problems/implement-trie-prefix-tree/submissions/2167350538/)) uses value-owned `unordered_map<char, Node>` children and a terminal `leaf` flag.

```text
insert("app"), insert("apple")
root → a → p → p* → l → e*
               ↑
               terminal word
search("ap") = false; startsWith("ap") = true
```

- Insertion creates missing children, then marks **only the final node** as a whole word.
- Queries must not create missing children. The helper uses `find` in a shared `const getLeaf` walk.
- Duplicate insertion is idempotent. Empty insertion marks the root terminal.
- The hash-map alphabet is retained; no lowercase-only array assumption is added.
- Children are owned by their maps, so no manual `delete` is needed. Extremely deep words can still make recursive value destruction/copying deep; this is a small interview-style trie, not an arena-based storage engine.

**Changes from source:** const queries, nonmutating `find`, shared walking logic, `try_emplace` for insertion, and borrowed `string_view` input. Returned internal pointers are not exposed.

Your [745. Prefix and Suffix Search](https://leetcode.com/problems/prefix-and-suffix-search/) ([submission 2164622907](https://leetcode.com/problems/prefix-and-suffix-search/submissions/2164622907/)) layers metadata on the same idea:

```text
word "apple": insert each suffix + "{" + "apple"
query prefix="ap", suffix="le": walk "le{ap"
each visited node stores the greatest inserted word index
```

That source uses `unique_ptr` children, includes the empty suffix, and writes the index at each traversed node. Inserting words in increasing index order lets later writes implement “largest index wins.” It costs O(Σ L²) preprocessing time and worst-case space, with expected O(prefix length + suffix length) query time. `{` is safe for the source's lowercase alphabet; for arbitrary bytes, encode/escape the separator. The ordinary `Trie` header intentionally does not implement WordFilter metadata.

## 3. Parentheses: counters when structure can be forgotten, frames when it cannot

### Repair a sequence with a counter

[921. Minimum Add to Make Parentheses Valid](https://leetcode.com/problems/minimum-add-to-make-parentheses-valid/) ([submission 2164607113](https://leetcode.com/problems/minimum-add-to-make-parentheses-valid/submissions/2164607113/)) tracks unmatched opens and missing opens. A close consumes an open if possible; otherwise that close permanently requires an inserted open. At the end, each remaining open needs a close. This local choice is forced, so no stack of positions is needed.

Do not blindly reuse the same counter for [1541. Minimum Insertions to Balance a Parentheses String](https://leetcode.com/problems/minimum-insertions-to-balance-a-parentheses-string/) ([submission 2167345569](https://leetcode.com/problems/minimum-insertions-to-balance-a-parentheses-string/submissions/2167345569/)): there one open requires **two consecutive closes**. Your source consumes a `))` pair together, inserts a missing close when necessary, then matches/inserts its open; leftover opens cost two each. The header implements only ordinary single-close balancing.

### Remove outer pairs by choosing when to update depth

[1021. Remove Outermost Parentheses](https://leetcode.com/problems/remove-outermost-parentheses/) ([submission 2166675238](https://leetcode.com/problems/remove-outermost-parentheses/submissions/2166675238/)) has a useful ordering trick:

```text
')' : decrement depth BEFORE deciding whether to emit
emit only if depth > 0
'(' : increment depth AFTER deciding whether to emit
```

The opening byte of a primitive sees depth zero; its closing byte returns depth to zero. Both are suppressed, while all inner bytes survive. The helper uses `std::string` append rather than `ostringstream`.

### Parse nested scores with frames

[856. Score of Parentheses](https://leetcode.com/problems/score-of-parentheses/) ([submission 2162881009](https://leetcode.com/problems/score-of-parentheses/submissions/2162881009/)) starts with a zero-valued outer frame. `(` pushes a new empty frame; `)` pops the inner score and adds `max(1, 2*inside)` to its parent.

```text
(()())
stack after "(()()": [0, 2]
final ')' pops 2, contributes 4 → [4]
```

**Invariant:** each frame is the sum of complete groups inside one still-open pair; the bottom frame accumulates top-level groups. Keeping a frame per nesting level preserves exactly the structure the counter-only algorithms can discard.

**Changes from source:** `back() += contribution` replaces pop/re-push of the parent; `std::vector` is the stack; `uint64_t` replaces `int`; multiplication and addition are checked for overflow. All three parentheses helpers reject non-parenthesis bytes. The two balanced-input helpers reject unmatched opens/closes instead of relying on problem constraints. A 65-pair fully nested input exceeds `uint64_t` score and throws `overflow_error`.

Another observed stack recipe is [1190. Reverse Substrings Between Each Pair of Parentheses](https://leetcode.com/problems/reverse-substrings-between-each-pair-of-parentheses/) ([submission 2154897406](https://leetcode.com/problems/reverse-substrings-between-each-pair-of-parentheses/submissions/2154897406/)): save output length at `(`, reverse that suffix at `)`. Its repeated reversals can take O(n²) time on nested inputs. Do not label that submitted algorithm linear just because its outer scan is linear; it is documented here without adding a duplicate parser template.

## Tests and verification

`test.cpp` checks 1,500 random LPS arrays against exhaustive borders, 2,500 KMP searches against a naive scan, 1,000 periodicity cases against direct divisors, 1,500 palindromes against prefix enumeration, and 2,000 trie operations against a set/prefix scan. Fixed seeds include embedded NUL and `#` bytes. Exhaustive parentheses strings through length 11/12 check repairs, primitive removal, and recursive-definition scores. Malformed input and both score overflow paths are tested.

```sh
g++ -std=c++20 -O2 -Wall -Wextra -Werror -pedantic test.cpp -o /tmp/string-tests
/tmp/string-tests
g++ -std=c++20 -O1 -g -Wall -Wextra -Werror -pedantic \
  -fsanitize=address,undefined -fno-omit-frame-pointer test.cpp -o /tmp/string-san
ASAN_OPTIONS=detect_leaks=0 /tmp/string-san
```

The sanitizer command checks address/undefined behavior, not leaks. LeakSanitizer cannot run under this execution environment's ptrace arrangement. Tests were written first and each feature group failed against an API stub before implementation.
