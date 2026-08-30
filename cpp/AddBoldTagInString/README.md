# Add Bold Tag in String

## Problem

Given a string `s` and a list of words, wrap every substring of `s` that
matches a word in `<b>` and `</b>` tags. Overlapping and consecutive matching
substrings must be combined into a single bold section.

## Approach

Store the words in a trie. For every position in `s`, find the longest word
that starts there and extend the exclusive right boundary of the current bold
section. Open or close a tag only when the current position crosses that
boundary, which merges overlapping and consecutive matches automatically.

Let `D` be the total number of characters in `words` and `L` be the length of
the longest word.

- Time complexity: `O(D + s.size() * L)`
- Additional space: `O(D)` excluding the result
