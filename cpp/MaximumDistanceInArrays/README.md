# Maximum Distance in Arrays

## Problem

You are given `m` arrays, each sorted in ascending order. Choose two integers
from two different arrays and calculate the distance between them. The distance
between integers `a` and `b` is `|a - b|`.

Return the maximum possible distance.

For example, for arrays `[1, 4, 5]` and `[0, 2]`, choosing `5` from the first
array and `0` from the second gives a distance of `5`, which is the maximum.

The two integers must always come from different arrays.

## Approach

Only the minimum and maximum element of every sorted array can participate in
the answer. While iterating over the arrays, keep:

- the two largest array maxima;
- the two smallest array minima.

Each heap is trimmed to two elements immediately after insertion. If the global
maximum and global minimum belong to different arrays, they form the answer.
Otherwise, use the better of the two combinations involving the corresponding
second extreme.

- Time complexity: `O(m)`
- Additional space: `O(1)`
