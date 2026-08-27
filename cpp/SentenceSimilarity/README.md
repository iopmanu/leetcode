# Sentence Similarity

## Problem

Given two sentences represented as arrays of words and a list of directly
similar word pairs, return whether the sentences are similar. The sentences
must have the same length, and corresponding words must either be equal or
form one of the supplied pairs.

Similarity is symmetric but not transitive.

## Approach

Build a bidirectional map from every word to the set of words directly similar
to it. Then compare corresponding words in the two sentences. Accept equal
words or a direct relation in the map; reject the first unmatched position.

- Time complexity: `O((p + n) * l)` on average, where `l` is the word length
- Additional space: `O(p * l)`
