# Longest Substring with At Most Two Distinct Characters

## Problem

Given a string `s`, return the length of the longest contiguous substring that
contains at most two distinct characters.

## Approach

Maintain a sliding window and a frequency map for the characters inside it.
Expand the right boundary one character at a time. Whenever the window contains
more than two distinct characters, move the left boundary forward, decrementing
frequencies and removing characters whose frequency becomes zero.

After the window is valid again, update the maximum length.

- Time complexity: `O(n)`
- Additional space: `O(1)` for a fixed character alphabet
