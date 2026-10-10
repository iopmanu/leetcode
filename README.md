# My original LeetCode solutions: contest and interview handbook

A source-first handbook of **VanyushaDoronin's captured accepted C++ solutions**: **252 submission records for 167 problems**, grouped into 11 topics.

The C++ files in each `originals/` folder are unchanged. Their UTF-8 bytes match the captured code strings, including wrappers, includes, comments, names, indentation, trailing whitespace, debug output, and missing final newlines. Equivalent submissions and exact duplicate code texts remain separate records.

## Start here

- [Key code snippets](SNIPPETS.md): literal excerpts from these originals for contest and interview recall.
- [Source index](SOURCES.md): every captured problem and every original implementation.
- [Coverage and limitations](COVERAGE.md): the inspected inventory and the known collection gaps.
- [Validation](VALIDATION.md): source-fidelity checks and what they establish.
- [Source manifest](sources.json): submission ID, problem, source URL, SHA-256, and local path for all 252 records.
- [Tab-separated source index](source-index.tsv): the same source records in a compact searchable format.

## Topics

| Topic | Problems | Submissions |
| --- | ---: | ---: |
| [Range queries](topics/range-queries/README.md) | 6 | 7 |
| [DSU and graphs](topics/dsu-and-graphs/README.md) | 14 | 22 |
| [Search and sort](topics/search-and-sort/README.md) | 21 | 51 |
| [Monotonic structures and heaps](topics/monotonic-and-heaps/README.md) | 17 | 34 |
| [Design structures](topics/design-structures/README.md) | 11 | 16 |
| [Strings and tries](topics/strings-and-tries/README.md) | 22 | 23 |
| [Trees and lists](topics/trees-and-lists/README.md) | 26 | 34 |
| [DP and backtracking](topics/dp-and-backtracking/README.md) | 11 | 12 |
| [Windows and prefixes](topics/windows-and-prefixes/README.md) | 13 | 17 |
| [Greedy and intervals](topics/greedy-and-intervals/README.md) | 13 | 19 |
| [Math and bits](topics/math-and-bits/README.md) | 13 | 17 |

## How to use it

1. Read a topic cue, then state the invariant in your own words.
2. Open the linked original implementation and use that solution as the starting point for recall or contest adaptation.
3. Compare the captured variants when their approaches differ.
4. Check the original problem constraints and harness before copying code into another environment.

## Original code, original context

This repository adds navigation and explanation around the original code. It introduces no shared algorithm framework, rewritten templates, extra guards, new namespaces, or standardized interfaces. There is no combined build: many files deliberately define their own `Solution`, `Node`, or other problem-specific types.

The sources were captured from LeetCode and may rely on its standard-library setup, provided node types, problem APIs, compiler mode, and problem constraints. Some sources use C++20 features. They are not all standalone translation units. Original comments keep their original language; explanatory prose is English.

Acceptance on the original problem is not proof of correctness for unrestricted inputs, repeated object reuse, or a different harness. Imperfections remain unchanged. Submission links may require access to the original LeetCode account; the local copies do not.

## Verify source fidelity

Run from this folder:

```bash
python3 tools/check_originals.py
python3 tools/verify_snippets.py
```

For an additional byte-for-byte comparison with the separately retained normalized capture:

```bash
python3 tools/check_originals.py --capture-json /path/to/normalized-records.json
```

The original-source checker verifies recorded hashes, source IDs, local paths, source coverage, and that every original is linked from its topic index. The snippet checker verifies that all 50 excerpts are literal source slices. Neither checker compiles the solutions or asserts that every algorithm works outside its original LeetCode context.
