# One Edit Distance

## Problem

Given two strings `first` and `second`, return `true` if they are exactly one
edit distance apart. Otherwise, return `false`.

An edit is exactly one of the following operations:

- insert one character;
- delete one character;
- replace one character with another character.

Equal strings are zero edits apart and therefore must return `false`.

## Approach

First ensure that `first` is not longer than `second`; swap the arguments
through a recursive call when necessary. If the length difference is greater
than one, no single edit can make the strings equal.

Scan the common prefix until the first mismatch:

- if the lengths are equal, treat the mismatch as a replacement and compare
  both suffixes after it;
- if `second` is longer, treat its mismatching character as an insertion and
  compare `first` from the mismatch with `second` after the mismatch.

If the common prefix contains no mismatch, the strings are one edit apart only
when `second` has exactly one trailing character.

- Time complexity: `O(min(n, m))`
- Additional space: `O(1)`
