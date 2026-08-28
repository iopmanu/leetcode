# Valid Word Square

## Problem

Given a sequence of words, return whether it forms a valid word square. For
every existing position `(row, column)`, the character must equal the character
at `(column, row)`. The words do not have to have equal lengths.

## Approach

Visit every character in every word. Before comparing it with its mirrored
position, verify that both the mirrored row and character exist. Return `false`
for a missing mirror or a character mismatch.

- Time complexity: `O(S)`, where `S` is the total number of characters
- Additional space: `O(1)`
