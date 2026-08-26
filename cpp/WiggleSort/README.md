# Wiggle Sort

## Problem

Rearrange an integer array in-place so that it satisfies:

```text
nums[0] <= nums[1] >= nums[2] <= nums[3] >= ...
```

Any arrangement satisfying the inequalities is a valid answer.

## Approach

Scan the array from left to right. At every position, check only the new
inequality introduced by the current element:

- at an odd index, the current element must be greater than or equal to the
  previous one;
- at an even index, the current element must be less than or equal to the
  previous one.

If the inequality is violated, swap the two adjacent elements.

## Why the swap preserves the processed prefix

Assume the prefix ending at `i - 1` already has wiggle order.

- If `i` is odd and `nums[i - 1] > nums[i]`, swapping makes the element at
  `i - 1` smaller. The preceding inequality expects that position to be no
  greater than its left neighbour, so it remains valid.
- If `i` is even and `nums[i - 1] < nums[i]`, swapping makes the element at
  `i - 1` larger. The preceding inequality expects that position to be no
  smaller than its left neighbour, so it also remains valid.

Therefore each step repairs the new inequality without breaking the previous
one, and the whole array is valid after one pass.

## Why this is linear while sorting is not

Wiggle order is only a partial requirement: it specifies local relationships
between adjacent positions but does not determine the relative order of every
pair of elements. There are usually many valid outputs, and the algorithm only
needs to find one of them. Each new local constraint can be repaired immediately
without learning the global ranks of the elements.

Comparison sorting must recover a total order. For `n` distinct elements it has
to distinguish among `n!` possible relative orders, which requires
`log2(n!) = Omega(n log n)` comparisons in the comparison model.

The non-uniqueness of the wiggle result is a useful intuition, but it is not by
itself the full reason: some problems with a unique answer, such as finding the
maximum, are also linear. The key distinction is how much ordering information
the required output reveals. Wiggle sort needs only local alternating
inequalities; sorting reveals the complete order.

- Time complexity: `O(n)`
- Additional space: `O(1)`
