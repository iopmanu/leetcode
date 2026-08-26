# Shortest Way to Form String

## Problem

Given two strings `source` and `target`, return the minimum number of
subsequences of `source` whose concatenation equals `target`.

If `target` cannot be constructed from subsequences of `source`, return `-1`.

## Approach

Store the ordered source positions for every character. While scanning
`target`, use `upper_bound` to select the first occurrence strictly after the
position used for the previous character.

If there is no later occurrence, start another subsequence and use the first
position of the character. If the character does not occur in `source`, the
target cannot be formed.

- Time complexity: `O(n + m log n)`
- Additional space: `O(n)`

Here, `n` is the length of `source` and `m` is the length of `target`.
