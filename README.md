# LeetCode patterns, in my C++ style

A revision handbook distilled from **VanyushaDoronin's actual accepted C++ submissions**. The goal is to recognize a pattern, remember its invariant, and reproduce a small implementation without memorizing an entire problem solution.

## Start here

- [Quick review](QUICK_REVIEW.md): recognition cues, invariants, and traps.
- [Source index](SOURCES.md): the inspected problems and their actual submission links.
- [Coverage and limitations](COVERAGE.md): what was read, what remains unavailable, and how templates differ from original submissions.
- [C++ conventions](STYLE.md): naming, index ranges, numeric types, and ownership.
- [Validation](VALIDATION.md): compiler, test scope, sanitizer results, and limits.

## Topics

| Topic | What to repeat |
| --- | --- |
| [Range queries](topics/range-queries/README.md) | Fenwick, lazy segment tree, order statistics, merge-sort tree, ordered aggregates |
| [DSU and graphs](topics/dsu-and-graphs/README.md) | Compression, union by size, reverse time, virtual nodes, Kruskal, BFS/DFS, topological order |
| [Search and sort](topics/search-and-sort/README.md) | Binary-search boundaries, answer search, Hoare quickselect, merge counting |
| [Monotonic structures and heaps](topics/monotonic-and-heaps/README.md) | Stack ownership, contribution counting, deque dominance, expiry, medians |
| [Design structures](topics/design-structures/README.md) | LRU/LFU, hash buckets, frequency stacks, iterator bookkeeping |
| [Strings and tries](topics/strings-and-tries/README.md) | KMP/LPS, trie transitions, prefix/suffix encoding, parentheses state |
| [Trees and lists](topics/trees-and-lists/README.md) | Pointer rewiring, sentinels, traversal state, subtree summaries, reconstruction |
| [DP and backtracking](topics/dp-and-backtracking/README.md) | State definitions, memoization, subsequences, interval choices, place/recurse/undo |
| [Windows and prefixes](topics/windows-and-prefixes/README.md) | Frequency windows, last positions, prefix cancellation, fixed bounds |
| [Greedy and intervals](topics/greedy-and-intervals/README.md) | Earliest finish, overlap boundaries, bucket leveling, shortest feasible choices |
| [Math and bits](topics/math-and-bits/README.md) | XOR parity, counting multiplicities, palindrome generation, geometry reductions |

Each folder contains an explanation, a self-contained `templates.hpp`, and a runnable `test.cpp`. The code uses C++20 and the standard library only. Source-specific tricks that do not justify another reusable class remain in the explanations.

## Run the checks

```bash
python3 tools/test.py
python3 tools/test.py --sanitizers
```

Use `CXX=clang++` to select another compatible compiler. Sanitizer runs require AddressSanitizer and UndefinedBehaviorSanitizer support. The runner checks each topic independently and also compiles every header together.

## How to use this for revision

1. Read the recognition cue and state the invariant aloud.
2. Hide the implementation and write its skeleton from memory.
3. Check boundary conventions, duplicate handling, and the neutral element.
4. Run the tests, then adapt the template to a source problem.
5. Compare approaches only after identifying the operation that dominates their complexity.

Original accepted code is evidence of the approach, not a guarantee that every implementation is safe for inputs outside LeetCode's constraints. Generalizations and cleanups are labeled in the topic notes. Submission links may require signing into the source LeetCode account; problem links are the public entry points.
