# Max Consecutive Ones II

## Problem

Given a binary array `nums`, return the maximum number of consecutive ones that
can be obtained by flipping at most one zero to one.

## Approach

Maintain a sliding window containing at most one zero. Expand the right boundary
one element at a time. If the window contains more than one zero, move the left
boundary forward until the window is valid again.

The length of every valid window is `right - left + 1`; keep the maximum over
all right-boundary positions.

- Time complexity: `O(n)`
- Additional space: `O(1)`
