# Confusing Number

## Problem

A confusing number is a number that, when rotated 180 degrees, becomes a valid
number different from the original number.

Valid rotations:

```text
0 -> 0
1 -> 1
6 -> 9
8 -> 8
9 -> 6
```

Digits `2`, `3`, `4`, `5`, and `7` become invalid after rotation.

Given an integer `n`, return `true` if it is a confusing number, or `false`
otherwise.

## Approach

Process the number from right to left using `% 10`. Map each digit to its
rotated value and append it to the result. Reading from the least significant
digit naturally accounts for the reversal caused by a 180-degree rotation.

Return `false` immediately if a digit has no valid rotation. Otherwise, the
number is confusing exactly when the rotated result differs from the original.

- Time complexity: `O(log n)`, linear in the number of digits
- Additional space: `O(1)`
