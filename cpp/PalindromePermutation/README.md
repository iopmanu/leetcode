# Palindrome Permutation

## Problem

Given a string `s`, return whether its characters can be rearranged to form a
palindrome.

## Approach

Count the frequency of every character, then count how many frequencies are
odd. An even-length palindrome requires every frequency to be even, while an
odd-length palindrome requires exactly one odd frequency for its center.

- Time complexity: `O(n)`
- Additional space: `O(alphabet_size)`
