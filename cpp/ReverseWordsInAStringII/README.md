# Reverse Words in a String II

## Problem

Given a character array `chars`, reverse the order of its words in-place.

A word is a sequence of non-space characters. Words are separated by a single
space, and the input contains no leading or trailing spaces.

The solution must use `O(1)` additional memory.

## Approach

First reverse the complete character array. This puts the words in the required
order, but reverses the characters inside every word as well.

Then scan the array until a space or the end of the array is reached. Each such
boundary identifies one word, which is reversed in-place to restore its
characters.

For example:

```text
the sky is blue
eulb si yks eht
blue is sky the
```

- Time complexity: `O(n)`
- Additional space: `O(1)`
