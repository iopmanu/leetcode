# Find Anagram Mappings

## Problem

Given two integer arrays `nums1` and `nums2`, where `nums2` is an anagram of
`nums1`, return an array that maps every element of `nums1` to an index of the
same value in `nums2`.

If multiple valid mappings exist, any of them may be returned.

## Approach

Store all positions of every value in `nums2`. For each value in `nums1`, take
one stored position, append it to the result, and remove it from the available
positions. Matching frequencies are guaranteed because the arrays are
anagrams.

- Time complexity: `O(n)` on average
- Additional space: `O(n)`
