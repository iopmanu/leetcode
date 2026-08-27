# Largest Unique Number

## Problem

Given an array of non-negative integers, return the largest number that occurs
exactly once. Return `-1` when the array contains no unique number.

## Approach

Count the occurrences of every number in a hash map. Scan the frequency map
and keep the largest number whose count is one.

- Time complexity: `O(nums.size())` on average
- Additional space: `O(nums.size())`
