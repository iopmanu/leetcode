# Missing Ranges

## Problem

Given an inclusive range `[lower, upper]` and a sorted array of unique
integers `nums`, return the shortest sorted list of ranges that covers every
number missing from `nums` within the inclusive range.

Each missing range is represented as `[start, end]`. A single missing number
is represented as `[value, value]`.

## Approach

Handle a possible gap before the first element, then scan every adjacent pair
of values and add the interval between them when they are not consecutive.
Finally, handle a possible gap after the last element. If `nums` is empty, the
entire inclusive range is missing.

- Time complexity: `O(nums.size())`
- Additional space: `O(1)`, excluding the result
