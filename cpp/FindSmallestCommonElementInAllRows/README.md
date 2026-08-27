# Find Smallest Common Element in All Rows

## Problem

Given a matrix whose rows are sorted in increasing order, return the smallest
element present in every row. Return `-1` when no common element exists.

## Approach

Store the first row in a hash set. For every row, remove values from the set
that are absent from that row. Return the smallest value remaining after all
rows have been processed.

- Time complexity: `O(rows * columns)` on average
- Additional space: `O(columns)`
