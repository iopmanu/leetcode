# Single-Row Keyboard

## Problem

Given a permutation of the 26 lowercase English letters representing a
single-row keyboard and a word, return the total distance needed to type the
word. The finger starts at index zero, and moving between indices `i` and `j`
costs `abs(i - j)`.

## Approach

Build a map from every character to its keyboard position. Starting at index
zero, visit each character in the word, add the distance from the current
position, and move the finger to the character's position.

- Time complexity: `O(keyboard.size() + word.size())`
- Additional space: `O(alphabet_size)`
