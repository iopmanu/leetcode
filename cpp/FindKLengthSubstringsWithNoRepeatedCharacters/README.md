# Find K-Length Substrings With No Repeated Characters

## Problem

Given a string `s` and an integer `k`, return the number of substrings of length
exactly `k` that contain no repeated characters.

## Approach

Scan the string from left to right and maintain the left boundary of the longest
substring ending at `right` that contains no repeated characters. Store the last
position of every character. If the current character already occurred inside
the window, move `left` past that occurrence.

Whenever the unique window has length at least `k`, its suffix of length exactly
`k` is a valid substring, so increment the result.

- Time complexity: `O(n)` on average
- Additional space: `O(min(n, alphabet_size))`
