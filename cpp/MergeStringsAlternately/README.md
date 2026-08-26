# Merge Strings Alternately

## Problem

Given two strings `first` and `second`, merge them by adding characters in
alternating order, starting with `first`.

If one string is longer, append its remaining characters to the end of the
result.

## Approach

Normalize the inputs so that the shorter string is processed first. When the
original `first` string was longer, swap the arguments and set `reversed` to
preserve the required output order.

Use one index to append a pair of characters from both strings on every
iteration. After the shorter string is exhausted, append the remaining suffix
of the longer string.

- Time complexity: `O(n + m)`
- Additional space excluding the result: `O(1)`
- Result space: `O(n + m)`
