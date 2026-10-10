# Strings and tries

[All topics](../../README.md) · [Source index](../../SOURCES.md) · [Coverage](../../COVERAGE.md)

## Main algorithms and structures

Start with the required state, then compose the techniques below. Links open the actual captured implementations. The complete catalog of **34 problems / 40 submissions** is last.

Here `n,m` are string lengths, `A` the tracked alphabet, `h` nesting depth, `C` total input characters, and `R` output characters. Hash-table bounds are expected. Space includes recursion and temporary storage; output is stated separately. A string passed **by value** can add its full length in entry-copy storage/time for an lvalue caller; this is included below, even when the scan itself needs only counters. Moves can avoid that copy.

| Algorithm / data structure | Recognition trigger | Time in these sources | Space in these sources | Direct implementations |
|---|---|---|---|---|
| KMP prefix function + fallback scan | A mismatch should reuse a known border | O(n+m) matching; O(n) border/period test | O(m) LPS + O(n+m) input copies; period test O(n) | [Matching](originals/28__2163524870.cpp), [period test](originals/459__2163579090.cpp) |
| Separator transform / virtual text + KMP | Palindromic prefix or matching periodic text | O(n) palindrome; O(n+m) virtual scan | O(n) transformed text/LPS/output; virtual scan O(m) LPS + O(n+m) input copies | [Palindrome transform](originals/214__2163593115.cpp), [virtual repetition](originals/686__2163561881.cpp) |
| Hash-map trie with terminal flag | Many queries share word prefixes | Expected O(L) per insert/search/prefix query | O(total inserted characters) nodes; O(L) by-value query copy | [Value-owned trie](originals/208__2167350538.cpp) |
| Composite-key trie with node aggregates | Match a prefix and a suffix, choose latest index | Build O(sum (Lᵢ+1)²); query O(P+S+1), expected | O(sum (Lᵢ+1)²) nodes; O(P+S+1) query strings | [All-suffix WordFilter](originals/745__2164622907.cpp) |
| Decimal-prefix hash sets | Common leading digits of positive integers | Expected O(Nd), N numbers of at most d digits | O(Nd) prefix entries across **two** sets | [Repeated division + intersection](originals/3043__2011710588.cpp) |
| Sorted canonical string keys | Group words modulo character permutation | Expected O(N+C + sum Lᵢ log Lᵢ), N words | O(N+C) copied keys/groups **and** returned strings | [Anagram grouping](originals/49__2127402160.cpp) |
| Frequency / two-way character maps | Multiset equality or injective renaming | Expected O(n+m) | O(A) maps + O(n+m) input copies | [Anagram counts](originals/242__2130658997.cpp), [bijection](originals/205__2125913880.cpp) |
| Deficit map + shrinking window | Shortest substring covering a multiset | Expected O(n+m) | O(A) map + O(n+m) input copies + O(R) output | [Unsatisfied count](originals/76__2149102883.cpp), [satisfied count](originals/76__2131820578.cpp) |
| Two-pointer mirror comparison | Palindrome, optionally skip one mismatch | O(n); scanning words O(C) | O(1) scan + O(n) parameter copy in 125/680; 2108 O(R) returned word only | [Normalized scan](originals/125__2147738982.cpp), [one deletion](originals/680__2147742976.cpp), [first palindrome](originals/2108__765352591.cpp) |
| Subsequence pointer + length ordering | Preserve order but allow skipped characters | O(n+m) standalone; O(N²L + N log N) for N words of max length L | Standalone O(n+m) input copies; candidate search O(NL+log N) map/sort storage | [Pointer scan](originals/392__792424958.cpp), [unique longest candidate](originals/522__2022687848.cpp) |
| Character stack / index stack | Match bracket types or measure valid suffix length | O(n) | O(n) stack and input copy | [Bracket matching](originals/20__2159229559.cpp), [sentinel index stack](originals/32__2161065445.cpp) |
| Balance, depth, directional feasibility | Types are fixed and only unmatched count matters | O(n) | O(1) counters + O(n) input copy; O(n) output for filtering/splitting | [Missing pairs](originals/921__2164607113.cpp), [paired closes](originals/1541__2167345569.cpp), [wildcards](originals/678__2161909813.cpp), [depth](originals/1614__2155954786.cpp), [strip outer pairs](originals/1021__2166675238.cpp), [depth parity](originals/1111__2158097081.cpp) |
| Stack of enclosing frames | Nested region contributes to its parent | Score O(n); decode O(n+T), T total characters copied/appended | Score O(h)+O(n) input; decode O(n+R+h) live strings/frames under positive repeat counts | [Frame scores](originals/856__2162881009.cpp), [string repetition](originals/394__2146593107.cpp) |
| Recursive-descent parser + ordered sets | Union and concatenation have different precedence | O(n + QL log(Q+1)) upper bound, Q intermediate candidate insert/merge attempts, L max candidate length | O(n+h+S), S characters/nodes in simultaneously live sets; final vector also copies output | [Brace grammar and Cartesian products](originals/1096__2153362638.cpp) |
| Output-position stack + suffix reversal | A closing delimiter reverses its built region | O(n²) worst case | O(n) output/positions/input copy | [Nested reversal](originals/1190__2154897406.cpp) |
| Nonowning views + token stack / dictionary | Tokens need inspection without substring allocation | Path O(n); substitution expected O(n+K+R), K total knowledge-key characters | Path O(n) views/copy/output; substitution O(q+n+R), q knowledge entries | [Path components](originals/71__2146563687.cpp), [bracket-key lookup](originals/1807__2154370092.cpp) |
| Bounded decimal accumulator | Parse signed integer without overflowing | O(n) | O(1) numeric state + O(n) input copy | [Sign-specific guard](originals/8__2126227733.cpp) |
| Run-length scan / alternating emit | Output is built from local runs or two streams | O(n) compression; O(n+m) merge | Compression O(n) **extra vector**; merge O(n+m) input copies and output stream | [Compression](originals/443__2126086544.cpp), [alternating merge](originals/1768__2147744998.cpp) |
| Rank map + adjacent lexicographic comparison | Alphabet order is supplied by the input | Expected O(C+A) | O(A) rank map/order copy | [Custom alphabet](originals/953__2155353571.cpp) |

## Combinations and tricks

### Border state + a carefully chosen text representation

- **Recognize:** Matching, periodicity, and palindromic prefixes all ask whether a prefix reappears at a boundary.
- **Compose:** Build LPS once; on mismatch follow `lps[j-1]` without moving the text pointer backward. For a palindrome, apply it to `s + "#" + reverse(s)`; for repetition, scan `a[i % n]` without materializing copies.
- **Invariant:** LPS records the longest proper prefix that is a suffix of the matched region. A final border `b` gives candidate period `n-b`; require `b>0` and divisibility. The separator prevents a match crossing the original/reversed boundary.
- **Tradeoff / trap:** The virtual scan still runs up to `2*|a|+|b|` characters; the palindrome version allocates transformed strings and LPS. `#` must be outside the alphabet. The plain matching and period sources rely on nonempty patterns/strings.
- **Originals:** [Fallback matcher](originals/28__2163524870.cpp), [period condition](originals/459__2163579090.cpp), [palindrome reduction](originals/214__2163593115.cpp), [virtual scan](originals/686__2163561881.cpp).

### Encode two constraints into one trie path, then cache the answer on that path

- **Recognize:** Many static words, repeated `(prefix,suffix)` queries, and a maximum-index tie-break.
- **Compose:** Insert **every suffix, including empty**, followed by `{` and the full word. Query `suffix + "{" + prefix`; overwrite each visited node's index while inserting words in increasing index order.
- **Invariant:** Reaching the query path proves both constraints, and the last stored index is the largest matching input index. This is a prefix query on an encoded path, so it does not need a terminal-word check.
- **Tradeoff / trap:** O(L²) construction per word buys O(P+S) queries. Concatenated keys themselves allocate. The ordinary trie has value-owned children and a leaf flag; WordFilter uses `unique_ptr` children and per-node aggregates. These are distinct ownership and query contracts.
- **Originals:** [Composite trie](originals/745__2164622907.cpp), [ordinary terminal-aware trie](originals/208__2167350538.cpp). For numeric prefixes, [two hash sets](originals/3043__2011710588.cpp) are the captured alternative; there is no numeric trie here.

### Canonicalize equivalence; count deficits for coverage

- **Recognize:** “Same letters” can mean an equivalence class or a covering constraint. They need different state.
- **Compose:** Sort a copy to key anagram groups; use counts for multiset equality; use two maps when a character renaming must be injective. For a covering window, subtract on entry and add on exit while tracking requirement zero-crossings.
- **Invariant:** A zero unmet-requirement count certifies window validity. Shrink only while valid, recording boundaries before removing the left character; extra copies of a needed character make its deficit negative rather than creating new requirements.
- **Tradeoff / trap:** Both window versions are linear because each boundary moves only forward, but their `matches` variables mean opposite things. Grouping copies `v` into the result (`emplace_back(v)`), so stored groups and returned strings coexist. Empty target handling is outside the window sources' contract.
- **Originals:** [Grouping](originals/49__2127402160.cpp), [bijection](originals/205__2125913880.cpp), [remaining deficits](originals/76__2149102883.cpp), [satisfied requirements](originals/76__2131820578.cpp).

### A stack stores exactly the information a counter would lose

- **Recognize:** Use a counter for depth, a character stack for bracket type, and an index stack when the answer is a length.
- **Compose:** In the longest-valid scan, initialize the index stack with `-1`, pop on a close, replace an emptied stack with the current invalid index, otherwise measure `i-stack.back()`.
- **Invariant:** The bottom sentinel is the boundary immediately before a potentially valid suffix; remaining open indexes are unmatched barriers. For score evaluation, each stack frame instead stores the sum of completed children, and a close contributes `max(1,2*inside)` to its parent.
- **Tradeoff / trap:** Fixed-type balance cannot validate mixed brackets. The bracket matcher scans only three fixed mappings, so that inner loop is constant work. Score input is assumed valid; unmatched closes are not checked.
- **Originals:** [Typed matching](originals/20__2159229559.cpp), [index sentinel](originals/32__2161065445.cpp), [score frames](originals/856__2162881009.cpp), [depth counter](originals/1614__2155954786.cpp).

### Control the moment when depth changes

- **Recognize:** Drop primitive outer pairs, split nesting evenly, or repair a modified closing rule.
- **Compose:** Strip an outer pair by decrementing **before** emitting a close and incrementing **after** emitting an open. For depth-parity splitting, increment **before** assigning an open and decrement **after** assigning its close. For double-close grammar, consume `))` as one unit and insert missing partners.
- **Invariant:** Both ends of a matched pair see the same parity; outer parentheses see zero interior depth. The repair counter represents unmatched opens after consuming complete closing units.
- **Tradeoff / trap:** Wildcard validity uses two feasibility scans, treating `*` optimistically from opposite ends. Neither scan alone supplies a concrete assignment, and one direction alone misses excess opens or closes.
- **Originals:** [Strip outer pairs](originals/1021__2166675238.cpp), [depth parity](originals/1111__2158097081.cpp), [double closes](originals/1541__2167345569.cpp), [ordinary repair](originals/921__2164607113.cpp), [two-direction wildcard test](originals/678__2161909813.cpp).

### Parse the grammar before accounting for expansion work

- **Recognize:** Nested expressions mix repetition, union, or adjacent concatenation.
- **Compose:** The decoder saves outer text and multiplier on `[`, then repeats the inner text on `]`. Brace expansion separates `item` (letter/group), `term` (Cartesian concatenation), and `eval` (comma union); ordered sets deduplicate and order the results.
- **Invariant:** Each frame owns the result of its completed inner region. The shared brace-parser index always points at the next unconsumed grammar symbol, so concatenation binds before union.
- **Tradeoff / trap:** A linear number of input tokens does not imply linear time. Decode copies `current` into saved/temporary strings; even nested repeat-count-one wrappers can recopy a large result. Brace expansion forms intermediate strings, including duplicates later discarded by sets, so count intermediate work and string-comparison length, not just final output size.
- **Originals:** [Stack decoder](originals/394__2146593107.cpp), [recursive grammar](originals/1096__2153362638.cpp). [Suffix-reversal parsing](originals/1190__2154897406.cpp) similarly repeats work on already-built text and can be quadratic.

### Views reduce copying only while their owners remain alive

- **Recognize:** You need token boundaries, not independently owned strings.
- **Compose:** Keep path components as views in a deque, pop on `..`, then emit once. Map knowledge keys and values as `string_view`; scan a bracketed key span and substitute its value.
- **Invariant:** Views point into the still-live `path`, `s`, or `knowledge` strings; the deque represents the surviving canonical path prefix. No view escapes either function.
- **Tradeoff / trap:** View construction is constant-time, but hashing a string view reads its characters, and streaming the answer costs its full length. The functions still copy their by-value input strings. Returning these views, or mutating/reallocating their owners while using them, would change the lifetime contract.
- **Originals:** [View stack](originals/71__2146563687.cpp), [view-key dictionary](originals/1807__2154370092.cpp).

### Branch only at the first broken invariant

- **Recognize:** A palindrome can spend one deletion; a subsequence can advance only when the next needed character matches.
- **Compose:** Compare palindrome ends until the first mismatch, then test deleting either end with a no-more-deletions helper. To find the longest uncommon subsequence, reject duplicate words, sort longest-first, and test a unique candidate against the other distinct strings.
- **Invariant:** Earlier matched palindrome pairs need no reconsideration. The subsequence pointer is the length of the candidate prefix already matched; longest-first order makes the first feasible candidate optimal.
- **Tradeoff / trap:** The palindrome source uses bitwise `|`, so both helpers execute, though the total remains O(n). The standalone subsequence scan continues reading `s[s.size()]` after all characters match; the null terminator and lowercase-input contract keep it from advancing again. The longer candidate-search helper has an explicit bound.
- **Originals:** [One-deletion check](originals/680__2147742976.cpp), [candidate ordering](originals/522__2022687848.cpp), [standalone subsequence scan](originals/392__792424958.cpp).

### Preserve the representation contract at conversion boundaries

- **Recognize:** Text is converted into arithmetic state, compressed runs, or an external alphabet order.
- **Compose:** Check `result > (limit-digit)/10` **before** decimal multiplication, with a sign-specific limit. Flush a run when its character changes and again at the end. Compare adjacent words by the first differing rank, with the shorter-prefix rule as a separate case.
- **Invariant:** The accumulator never exceeds its permitted magnitude; the run counter belongs to exactly one source character; lexicographic comparison never examines later characters after a decisive difference.
- **Tradeoff / trap:** Compression builds a separate result vector and moves it back; it is O(n) extra storage, not an in-place write-pointer solution. The palindrome normalization helper is ASCII-specific, and numeric-prefix collection omits zero under the original positive-number contract.
- **Originals:** [Overflow guard](originals/8__2126227733.cpp), [run flush](originals/443__2126086544.cpp), [rank comparison](originals/953__2155353571.cpp), [ASCII scan](originals/125__2147738982.cpp), [decimal prefixes](originals/3043__2011710588.cpp).

## Problem and source appendix


All captured submissions are retained, including equivalent resubmissions and exact duplicates. Submission IDs distinguish files; they are not rankings of quality. The source itself is authoritative when a note is too brief.

### 8. String to Integer (atoi)

[Problem](https://leetcode.com/problems/string-to-integer-atoi/) · Tags: Strings, Parsing, Overflow guards

Skip spaces, parse optional sign, accumulate digits while checking against sign-specific integer limit.

**Captured variants:** One observed approach.

- [Original 2126227733](originals/8__2126227733.cpp) · [LeetCode submission](https://leetcode.com/problems/string-to-integer-atoi/submissions/2126227733/)

### 20. Valid Parentheses

[Problem](https://leetcode.com/problems/valid-parentheses/) · Tags: Bracket matching, Stack

Deque of opening characters plus a mapping of three bracket pairs; closing symbol must match the top and final stack must be empty.

**Original-code context:** The two newest captured code texts are byte-identical. The older source uses deque.front rather than deque.back as the stack end. Each bracket check scans only the three fixed bracket mappings.

**Captured variants:** 3 accepted C++ submissions retained; distinctions are described above.

- [Original 2159229559](originals/20__2159229559.cpp) · [LeetCode submission](https://leetcode.com/problems/valid-parentheses/submissions/2159229559/)
- [Original 2145824156](originals/20__2145824156.cpp) · [LeetCode submission](https://leetcode.com/problems/valid-parentheses/submissions/2145824156/)
- [Original 2130619573](originals/20__2130619573.cpp) · [LeetCode submission](https://leetcode.com/problems/valid-parentheses/submissions/2130619573/)

### 28. Find the Index of the First Occurrence in a String

[Problem](https://leetcode.com/problems/find-the-index-of-the-first-occurrence-in-a-string/) · Tags: String matching, KMP

Inline prefix-function build then fallback-driven linear first-match scan.

**Captured variants:** One observed approach.

- [Original 2163524870](originals/28__2163524870.cpp) · [LeetCode submission](https://leetcode.com/problems/find-the-index-of-the-first-occurrence-in-a-string/submissions/2163524870/)

### 32. Longest Valid Parentheses

[Problem](https://leetcode.com/problems/longest-valid-parentheses/) · Tags: Parentheses, Index stack

Index stack with initial sentinel -1. Pop on close; if stack empties reset base to current index, otherwise use i-stack.top.

**Original-code context:** Both accepted implementations use the same algorithm, with deque/back and stack/top wrappers.

**Captured variants:** 2 accepted C++ submissions retained; distinctions are described above.

- [Original 2161065445](originals/32__2161065445.cpp) · [LeetCode submission](https://leetcode.com/problems/longest-valid-parentheses/submissions/2161065445/)
- [Original 1780529411](originals/32__1780529411.cpp) · [LeetCode submission](https://leetcode.com/problems/longest-valid-parentheses/submissions/1780529411/)

### 49. Group Anagrams

[Problem](https://leetcode.com/problems/group-anagrams/) · Tags: Hash maps, Strings, Canonical keys

Sort each string as canonical anagram key and group original strings.

**Captured variants:** One observed approach.

- [Original 2127402160](originals/49__2127402160.cpp) · [LeetCode submission](https://leetcode.com/problems/group-anagrams/submissions/2127402160/)

### 71. Simplify Path

[Problem](https://leetcode.com/problems/simplify-path/) · Tags: Stacks, Strings, Views

Split path on /, ignore empty/dot, pop for dotdot, join surviving components.

**Captured variants:** One observed approach.

- [Original 2146563687](originals/71__2146563687.cpp) · [LeetCode submission](https://leetcode.com/problems/simplify-path/submissions/2146563687/)

### 76. Minimum Window Substring

[Problem](https://leetcode.com/problems/minimum-window-substring/) · Tags: Sliding windows, Frequency deficit

Track distinct unsatisfied/satisfied requirements; shrink while all covered and save minimum boundaries.

**Captured variants:** Two equivalent variants using remaining versus satisfied count.

- [Original 2149102883](originals/76__2149102883.cpp) · [LeetCode submission](https://leetcode.com/problems/minimum-window-substring/submissions/2149102883/)
- [Original 2131820578](originals/76__2131820578.cpp) · [LeetCode submission](https://leetcode.com/problems/minimum-window-substring/submissions/2131820578/)

### 125. Valid Palindrome

[Problem](https://leetcode.com/problems/valid-palindrome/) · Tags: Two pointers, Strings

Skip nonalphanumeric symbols at both ends and compare normalized characters.

**Captured variants:** One accepted C++ source.

- [Original 2147738982](originals/125__2147738982.cpp) · [LeetCode submission](https://leetcode.com/problems/valid-palindrome/submissions/2147738982/)

### 205. Isomorphic Strings

[Problem](https://leetcode.com/problems/isomorphic-strings/) · Tags: Strings, Bijection, Hash maps

Two character maps enforce bijection in both directions.

**Original-code context:** Same method in both sources; O(n), bounded alphabet space; contains() requires C++20.

**Captured variants:** 2 accepted C++ submissions captured; all original versions are retained.

- [Original 2125913880](originals/205__2125913880.cpp) · [LeetCode submission](https://leetcode.com/problems/isomorphic-strings/submissions/2125913880/)
- [Original 2116280947](originals/205__2116280947.cpp) · [LeetCode submission](https://leetcode.com/problems/isomorphic-strings/submissions/2116280947/)

### 208. Implement Trie (Prefix Tree)

[Problem](https://leetcode.com/problems/implement-trie-prefix-tree/) · Tags: Trie, Strings

Walk value-owned hash-map children, set terminal flag only after full insertion.

**Captured variants:** One observed approach.

- [Original 2167350538](originals/208__2167350538.cpp) · [LeetCode submission](https://leetcode.com/problems/implement-trie-prefix-tree/submissions/2167350538/)

### 214. Shortest Palindrome

[Problem](https://leetcode.com/problems/shortest-palindrome/) · Tags: String matching, KMP, Palindromes

KMP prefix-function on s+separator+reverse(s) gives longest palindromic prefix; prepend reversed leftover suffix.

**Captured variants:** Same LPS family as 459/686/28.

- [Original 2163593115](originals/214__2163593115.cpp) · [LeetCode submission](https://leetcode.com/problems/shortest-palindrome/submissions/2163593115/)

### 242. Valid Anagram

[Problem](https://leetcode.com/problems/valid-anagram/) · Tags: Frequency maps, Strings

Count both strings and compare every key/count in both directions.

**Captured variants:** One observed approach.

- [Original 2130658997](originals/242__2130658997.cpp) · [LeetCode submission](https://leetcode.com/problems/valid-anagram/submissions/2130658997/)

### 392. Is Subsequence

[Problem](https://leetcode.com/problems/is-subsequence/) · Tags: Subsequence, Pointer scan

Scans t and advances j into s on equality; returns whether j reached s length.

**Original-code context:** There is no explicit j<s_length guard inside the loop. When j==s.size(), reading through string::operator[] accesses the null terminator; the original lowercase-letter contract prevents another match. This original behavior is preserved.

**Captured variants:** 1 accepted C++ submission retained; distinctions are described above.

- [Original 792424958](originals/392__792424958.cpp) · [LeetCode submission](https://leetcode.com/problems/is-subsequence/submissions/792424958/)

### 394. Decode String

[Problem](https://leetcode.com/problems/decode-string/) · Tags: Stacks, Parsing

Save outer partial string and multiplier at [, expand current substring at ].

**Captured variants:** One observed approach.

- [Original 2146593107](originals/394__2146593107.cpp) · [LeetCode submission](https://leetcode.com/problems/decode-string/submissions/2146593107/)

### 443. String Compression

[Problem](https://leetcode.com/problems/string-compression/) · Tags: Run-length encoding, Strings

Run-length accumulation with pointer to current character; append character and decimal count to separate result vector; move result into input.

**Original-code context:** Both original versions allocate O(n) auxiliary storage and replace the input with that result vector. Historical judge acceptance does not establish constant-extra-space behavior.

**Captured variants:** 2 accepted C++ submissions captured; all original versions are retained.

- [Original 2126086544](originals/443__2126086544.cpp) · [LeetCode submission](https://leetcode.com/problems/string-compression/submissions/2126086544/)
- [Original 2119558730](originals/443__2119558730.cpp) · [LeetCode submission](https://leetcode.com/problems/string-compression/submissions/2119558730/)

### 459. Repeated Substring Pattern

[Problem](https://leetcode.com/problems/repeated-substring-pattern/) · Tags: String matching, KMP

A nonzero final border length and divisibility by n-border detect repeating period.

**Captured variants:** Same LPS family as 214/686/28.

- [Original 2163579090](originals/459__2163579090.cpp) · [LeetCode submission](https://leetcode.com/problems/repeated-substring-pattern/submissions/2163579090/)

### 522. Longest Uncommon Subsequence II

[Problem](https://leetcode.com/problems/longest-uncommon-subsequence-ii/) · Tags: Subsequence scan, Length sorting

Counts duplicate strings, sorts by descending length, skips duplicates, and checks whether each unique string is a subsequence of any other string.

**Original-code context:** Returns the first valid candidate after length sorting. The helper advances the source-string pointer only on a match.

**Captured variants:** 1 accepted C++ submission retained; distinctions are described above.

- [Original 2022687848](originals/522__2022687848.cpp) · [LeetCode submission](https://leetcode.com/problems/longest-uncommon-subsequence-ii/submissions/2022687848/)

### 678. Valid Parenthesis String

[Problem](https://leetcode.com/problems/valid-parenthesis-string/) · Tags: Parentheses, Greedy, Directional balance

Simultaneous left-to-right and right-to-left balance feasibility checks, treating * as whichever opening/closing symbol the directional test needs.

**Original-code context:** Reject as soon as either directional balance is negative.

**Captured variants:** 1 accepted C++ submission retained; distinctions are described above.

- [Original 2161909813](originals/678__2161909813.cpp) · [LeetCode submission](https://leetcode.com/problems/valid-parenthesis-string/submissions/2161909813/)

### 680. Valid Palindrome II

[Problem](https://leetcode.com/problems/valid-palindrome-ii/) · Tags: Palindrome, Two pointers

Two-pointer scan; at first mismatch test either left deletion or right deletion with helper.

**Original-code context:** Bitwise boolean OR evaluates both helper calls rather than short-circuiting; unused deleted variable; still O(n).

**Captured variants:** 1 accepted C++ submission captured; all original versions are retained.

- [Original 2147742976](originals/680__2147742976.cpp) · [LeetCode submission](https://leetcode.com/problems/valid-palindrome-ii/submissions/2147742976/)

### 686. Repeated String Match

[Problem](https://leetcode.com/problems/repeated-string-match/) · Tags: String matching, KMP, Circular traversal

Run KMP against virtual repetitions via a[i%n], stopping after finite bound; convert matched end index to repeat count.

**Captured variants:** One KMP source.

- [Original 2163561881](originals/686__2163561881.cpp) · [LeetCode submission](https://leetcode.com/problems/repeated-string-match/submissions/2163561881/)

### 745. Prefix and Suffix Search

[Problem](https://leetcode.com/problems/prefix-and-suffix-search/) · Tags: Trie, Strings, Composite keys

Insert every suffix+separator+word; query suffix+separator+prefix, storing latest index on each visited node.

**Captured variants:** One source; different ownership from 208.

- [Original 2164622907](originals/745__2164622907.cpp) · [LeetCode submission](https://leetcode.com/problems/prefix-and-suffix-search/submissions/2164622907/)

### 856. Score of Parentheses

[Problem](https://leetcode.com/problems/score-of-parentheses/) · Tags: Stacks, Parsing

Stack of partial frame scores; closing frame contributes max(1,2*inside) to parent.

**Captured variants:** One observed approach.

- [Original 2162881009](originals/856__2162881009.cpp) · [LeetCode submission](https://leetcode.com/problems/score-of-parentheses/submissions/2162881009/)

### 921. Minimum Add to Make Parentheses Valid

[Problem](https://leetcode.com/problems/minimum-add-to-make-parentheses-valid/) · Tags: Greedy, Strings, Counters

Track unmatched opens and missing openings, then sum them.

**Captured variants:** One observed approach.

- [Original 2164607113](originals/921__2164607113.cpp) · [LeetCode submission](https://leetcode.com/problems/minimum-add-to-make-parentheses-valid/submissions/2164607113/)

### 953. Verifying an Alien Dictionary

[Problem](https://leetcode.com/problems/verifying-an-alien-dictionary/) · Tags: Strings, Custom order

Build character rank and compare adjacent words at first difference, rejecting a longer word preceding its prefix.

**Captured variants:** One observed approach.

- [Original 2155353571](originals/953__2155353571.cpp) · [LeetCode submission](https://leetcode.com/problems/verifying-an-alien-dictionary/submissions/2155353571/)

### 1021. Remove Outermost Parentheses

[Problem](https://leetcode.com/problems/remove-outermost-parentheses/) · Tags: Strings, Counters

Adjust depth before a close and after an open so only inner symbols are emitted.

**Captured variants:** One observed approach.

- [Original 2166675238](originals/1021__2166675238.cpp) · [LeetCode submission](https://leetcode.com/problems/remove-outermost-parentheses/submissions/2166675238/)

### 1096. Brace Expansion II

[Problem](https://leetcode.com/problems/brace-expansion-ii/) · Tags: Parsing, Recursive descent, Sets

Grammar item handles letter or brace group, term concatenates Cartesian products, eval unions comma-separated terms.

**Captured variants:** One observed approach.

- [Original 2153362638](originals/1096__2153362638.cpp) · [LeetCode submission](https://leetcode.com/problems/brace-expansion-ii/submissions/2153362638/)

### 1111. Maximum Nesting Depth of Two Valid Parentheses Strings

[Problem](https://leetcode.com/problems/maximum-nesting-depth-of-two-valid-parentheses-strings/) · Tags: Parentheses, Depth parity

Assign both ends of each pair to depth%2; increment before assigning opening and decrement after assigning closing.

**Original-code context:** Consistent before/after order is what puts matching parentheses in the same group.

**Captured variants:** 1 accepted C++ submission retained; distinctions are described above.

- [Original 2158097081](originals/1111__2158097081.cpp) · [LeetCode submission](https://leetcode.com/problems/maximum-nesting-depth-of-two-valid-parentheses-strings/submissions/2158097081/)

### 1190. Reverse Substrings Between Each Pair of Parentheses

[Problem](https://leetcode.com/problems/reverse-substrings-between-each-pair-of-parentheses/) · Tags: Strings, Stack

Keep output positions of opening parentheses; reverse output suffix at each close.

**Captured variants:** One observed approach.

- [Original 2154897406](originals/1190__2154897406.cpp) · [LeetCode submission](https://leetcode.com/problems/reverse-substrings-between-each-pair-of-parentheses/submissions/2154897406/)

### 1541. Minimum Insertions to Balance a Parentheses String

[Problem](https://leetcode.com/problems/minimum-insertions-to-balance-a-parentheses-string/) · Tags: Strings, Greedy, Counters

Consume close parentheses in pairs; insert missing close or matching opening; account for remaining opens.

**Captured variants:** One observed approach.

- [Original 2167345569](originals/1541__2167345569.cpp) · [LeetCode submission](https://leetcode.com/problems/minimum-insertions-to-balance-a-parentheses-string/submissions/2167345569/)

### 1614. Maximum Nesting Depth of the Parentheses

[Problem](https://leetcode.com/problems/maximum-nesting-depth-of-the-parentheses/) · Tags: Strings, Counters

Single depth counter and running maximum; stack contents are unnecessary.

**Captured variants:** One approach.

- [Original 2155954786](originals/1614__2155954786.cpp) · [LeetCode submission](https://leetcode.com/problems/maximum-nesting-depth-of-the-parentheses/submissions/2155954786/)

### 1768. Merge Strings Alternately

[Problem](https://leetcode.com/problems/merge-strings-alternately/) · Tags: Strings, Two indexes

Advance two indexes, stream alternating characters, then stream each remaining suffix.

**Original-code context:** Uses ostringstream and output storage.

**Captured variants:** 1 accepted C++ submission captured; all original versions are retained.

- [Original 2147744998](originals/1768__2147744998.cpp) · [LeetCode submission](https://leetcode.com/problems/merge-strings-alternately/submissions/2147744998/)

### 1807. Evaluate the Bracket Pairs of a String

[Problem](https://leetcode.com/problems/evaluate-the-bracket-pairs-of-a-string/) · Tags: Strings, Hash maps, Views

Map knowledge to nonowning string_views; scan bracket key spans and substitute value or ?.

**Captured variants:** One observed approach.

- [Original 2154370092](originals/1807__2154370092.cpp) · [LeetCode submission](https://leetcode.com/problems/evaluate-the-bracket-pairs-of-a-string/submissions/2154370092/)

### 2108. Find First Palindromic String in the Array

[Problem](https://leetcode.com/problems/find-first-palindromic-string-in-the-array/) · Tags: Palindrome, Mirror comparison

Scans words in order, checking symmetric characters up to half the string length, and returns the first palindrome.

**Original-code context:** Uses an is_found flag and returns words[i-1] after the loop.

**Captured variants:** 1 accepted C++ submission retained; distinctions are described above.

- [Original 765352591](originals/2108__765352591.cpp) · [LeetCode submission](https://leetcode.com/problems/find-first-palindromic-string-in-the-array/submissions/765352591/)

### 3043. Find the Length of the Longest Common Prefix

[Problem](https://leetcode.com/problems/find-the-length-of-the-longest-common-prefix/) · Tags: Decimal prefixes, Hash sets

Generates all positive decimal prefixes by repeated division by 10, stores sets for both arrays, intersects them, and compares digit counts.

**Original-code context:** Actual code uses unordered_set<int> and log10 digit counting, not a trie. getPrefixes omits zero; the original problem has positive numbers.

**Captured variants:** 1 accepted C++ submission retained; distinctions are described above.

- [Original 2011710588](originals/3043__2011710588.cpp) · [LeetCode submission](https://leetcode.com/problems/find-the-length-of-the-longest-common-prefix/submissions/2011710588/)
