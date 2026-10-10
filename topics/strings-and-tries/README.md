# Strings and tries

[All topics](../../README.md) · [Source index](../../SOURCES.md) · [Coverage](../../COVERAGE.md)

**34 captured problems · 40 accepted submission records.** Every linked implementation below is an unchanged captured source file. These notes describe the code; they do not replace it with a common API.

## Pattern reminders

### Borders and KMP fallback

- **Cue:** Reuse already matched prefixes rather than restarting comparisons.
- **Idea and invariant:** 28 builds the prefix function and falls back to the longest smaller border on mismatch. 214 applies the same border structure to a string/separator/reverse construction, 459 tests periodicity, and 686 scans virtual repetitions.
- **Cost in these sources:** Prefix-function construction and KMP scan are linear in the built/scanned text length; the prefix table uses linear storage.
- **Read the originals:** [28. Find the Index of the First Occurrence in a String — 2163524870](originals/28__2163524870.cpp); [214. Shortest Palindrome — 2163593115](originals/214__2163593115.cpp); [459. Repeated Substring Pattern — 2163579090](originals/459__2163579090.cpp); [686. Repeated String Match — 2163561881](originals/686__2163561881.cpp).

### Trie path state

- **Cue:** Queries share prefixes, or a compound query can be encoded as a single path.
- **Idea and invariant:** 208 owns children by value in hash maps and marks complete words. 745 inserts suffix + separator + word paths and stores the latest word index on visited nodes; it has a different allocation/ownership structure.
- **Cost in these sources:** 208 operations are expected O(L) for a word of length L. 745 inserts O(L squared) path characters per word and answers in O(prefix length + suffix length), assuming expected constant-time transitions.
- **Read the originals:** [208. Implement Trie (Prefix Tree) — 2167350538](originals/208__2167350538.cpp); [745. Prefix and Suffix Search — 2164622907](originals/745__2164622907.cpp).

### Nested syntax carries a frame or parser position

- **Cue:** Parentheses, repeated brackets, or braces change the meaning of a local region.
- **Idea and invariant:** 394 saves the outer string and repeat count while decoding a bracketed substring. 1096 separates item, concatenated term, and comma union. 856 saves frame scores; 1190 reverses the built suffix on a closing parenthesis.
- **Cost in these sources:** Materializing expansions costs at least their output size; brace concatenation additionally forms Cartesian products and inserts into ordered sets. Repeated nested reversals in 1190 can take O(n squared).
- **Read the originals:** [394. Decode String — 2146593107](originals/394__2146593107.cpp); [1096. Brace Expansion II — 2153362638](originals/1096__2153362638.cpp); [856. Score of Parentheses — 2162881009](originals/856__2162881009.cpp); [1190. Reverse Substrings Between Each Pair of Parentheses — 2154897406](originals/1190__2154897406.cpp).

### Depth and unmatched counts

- **Cue:** Only balance or nesting matters, rather than the full stack contents.
- **Idea and invariant:** 921 counts missing opens and remaining unmatched opens. 1021 emits only symbols inside each primitive outer pair. 1541 consumes closing parentheses in pairs. 1614 tracks the current and maximum depth.
- **Cost in these sources:** O(n) time and O(1) counting state, excluding any output string.
- **Read the originals:** [921. Minimum Add to Make Parentheses Valid — 2164607113](originals/921__2164607113.cpp); [1021. Remove Outermost Parentheses — 2166675238](originals/1021__2166675238.cpp); [1541. Minimum Insertions to Balance a Parentheses String — 2167345569](originals/1541__2167345569.cpp); [1614. Maximum Nesting Depth of the Parentheses — 2155954786](originals/1614__2155954786.cpp).

### Canonical keys and requirement coverage

- **Cue:** Anagrams should share a key, or a substring must cover every requested character count.
- **Idea and invariant:** 49 sorts each word as its group key. 76 tracks outstanding or satisfied distinct requirements and shrinks only while the full multiset is covered. The two captured window versions use different count conventions.
- **Cost in these sources:** 49 costs O(sum L_i log L_i) for sorting words. 76 is expected O(n+m) with hash-map counting and storage proportional to the tracked alphabet, plus output.
- **Read the originals:** [49. Group Anagrams — 2127402160](originals/49__2127402160.cpp); [76. Minimum Window Substring — 2149102883](originals/76__2149102883.cpp).

## Complete problem and variant index

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
