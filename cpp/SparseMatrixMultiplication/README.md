# Sparse Matrix Multiplication

## Problem

Given matrices `mat1` of size `n * k` and `mat2` of size `k * m`, return
their matrix product of size `n * m`. Both input matrices may be sparse.

## Approach

Group nonzero values of `mat1` by their column `k` and nonzero values of
`mat2` by their row `k`. For every shared index, calculate the outer product
of the corresponding sparse column and sparse row and add it to the result.

If `a_k` and `b_k` are their respective numbers of nonzero values:

- Time complexity: `O(nk + km + nm + sum(a_k * b_k))`
- Additional space: `O(nnz(mat1) + nnz(mat2))`
