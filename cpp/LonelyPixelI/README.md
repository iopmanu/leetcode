# Lonely Pixel I

## Problem

Given a rectangular picture containing black (`'B'`) and white (`'W'`)
pixels, return the number of black pixels that are the only black pixel in
both their row and their column.

## Approach

Count black pixels in every row and column. During a second pass, count each
black pixel whose row count and column count are both equal to one.

- Time complexity: `O(rows * columns)`
- Additional space: `O(rows + columns)`
