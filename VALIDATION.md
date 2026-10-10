# Validation

Verified on 10 October 2026 using GCC 14.2.0.

## Aggregate checks

```bash
python3 tools/test.py
ASAN_OPTIONS=detect_leaks=0 python3 tools/test.py --sanitizers
```

Both commands passed **all 11 topic suites** and the translation unit including **all 11 headers together**.

- Language and warnings: `-std=c++20 -Wall -Wextra -Werror -pedantic`.
- Optimized build: `-O2`.
- Sanitizer build: `-O1 -g -fsanitize=address,undefined -fno-omit-frame-pointer`.
- Tests include deterministic boundaries, seeded differential comparisons to simple reference implementations, and randomized cache/collection operations. Read each `test.cpp` for its exact domain and seed.
- Independent additional checks covered 88,573 small ternary arrays/strings for closed-substring greedy behavior and signed shortest-subarray behavior, plus all quickselect ranks through length eight.

**Leak checking was not verified.** LeakSanitizer cannot operate under the validation environment's ptrace setup. AddressSanitizer and UndefinedBehaviorSanitizer passed with only leak detection disabled. On an ordinary local machine, first try `python3 tools/test.py --sanitizers` without changing `ASAN_OPTIONS`.

## Documentation and provenance

- Every local Markdown destination exists.
- The source index accounts for 167 problems and 252 accepted submission references.
- Exact submission URLs match the captured source records; no solution is inferred solely from a problem tag.
- Captured source hashes were checked for consistency. These checks establish provenance, not that every original program is correct outside its task constraints.
- Generalized code, ownership decisions, supported input domains, and changes from submitted snippets are documented in each chapter.

These checks are strong regression evidence, not a proof over unrestricted inputs. Numeric limits and other preconditions in each API still apply. The collection gaps in [COVERAGE.md](COVERAGE.md) remain open.
