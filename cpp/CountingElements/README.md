# Counting Elements

## Problem

Given an integer array, count every element `x` for which `x + 1` also exists
in the array. Duplicate occurrences of `x` are counted separately.

## Approach

Count every value in a hash map. For each distinct value, add its frequency to
the answer when the map also contains the next value.

- Time complexity: `O(arr.size())` on average
- Additional space: `O(arr.size())`
