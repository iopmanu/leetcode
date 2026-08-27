# Group Shifted Strings

## Problem

Two lowercase strings belong to the same shifting sequence when every letter
of one string can be shifted by the same number of alphabet positions to
produce the other string, wrapping from `z` back to `a`.

Given an array of strings, group all strings that belong to the same shifting
sequence. The groups may be returned in any order.

## Approach

For every string, build a key from the cyclic differences between adjacent
characters. Normalize every difference with modulo 26 and separate the values
with spaces to make the key unambiguous. Strings with the same sequence of
differences belong to the same group.

- Time complexity: `O(total_characters)`
- Additional space: `O(total_characters)`
