# Remove Interval

## Problem

Given a sorted list of pairwise disjoint half-open intervals and another
half-open interval `toBeRemoved`, remove every point covered by
`toBeRemoved`. Return the remaining parts of the original intervals in sorted
order.

## Approach

Scan the intervals from left to right. Preserve an interval when it does not
overlap the removed range. Otherwise, preserve its left part when it starts
before the removed range and its right part when it ends after the removed
range.

- Time complexity: `O(intervals.size())`
- Additional space: `O(1)` excluding the result
