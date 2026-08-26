# Longest Substring with At Most K Distinct Characters

## Problem

Given a string `s` and an integer `k`, return the length of the longest
contiguous substring that contains at most `k` distinct characters.

## Approach

Maintain a sliding window and a frequency map for the characters inside it.
Expand the right boundary one character at a time. Whenever the window contains
more than `k` distinct characters, move the left boundary forward, decrementing
frequencies and removing characters whose frequency becomes zero.

After the window is valid again, update the maximum length. If `k` is not
positive, return zero.

- Time complexity: `O(n)`
- Additional space: `O(k)`
