# C++ conventions

## What comes from the inspected solutions

- Small `struct` helpers inside or beside a `Solution` class.
- Explicit `std::` names, camelCase functions and variables, four-space indentation.
- `std::vector` storage, direct indexed loops, braced empty containers, and early returns.
- Capture-by-reference recursive lambdas with `std::function` where a local recurrence reads more clearly than a class.
- Names such as `parent`, `size`, `find`, `uni`, `update`, `query`, `left`, `right`, `prevLps`, and `result`.
- Explicit invariants and problem-shaped implementations rather than a large generic framework.

## Deliberate changes for a reusable handbook

The templates are adaptations, not byte-for-byte copies of submissions.

1. **Self-contained C++20 headers.** Necessary includes and `std::` qualifications are present. The LeetCode harness is not required. Incidental newer-language syntax is replaced where necessary.
2. **Namespaced helpers.** Everything is under `patterns` or a topic namespace beneath it, so headers can be included together. Source `Solution` wrappers are removed.
3. **Documented intervals.** There is no silent global switch of indexing convention. Each API states whether its interval is inclusive or half-open. Preserve a source convention when it keeps the implementation recognizable.
4. **Generalization is explicit.** Empty inputs, duplicate values, zero assignments, negative values, capacity zero, and arithmetic limits need a decision. LeetCode's accepted status alone does not establish their behavior outside its constraints.
5. **Widen before arithmetic.** Converting an already-overflowed `int` expression to `long long` cannot repair it. Counts and products use wider intermediates where appropriate; numeric assumptions remain documented.
6. **Do not imitate accidental mutation.** A reference such as `auto& last = intervals[0]` stays bound to that element. Assigning to `last` overwrites the first interval; it does not rebind the reference. A scalar endpoint or copied value is often the intended reusable state.
7. **Explicit ownership.** Pointer-based examples must state who owns their nodes. Tests free allocated trees and lists. Cache classes must account for iterator validity and copy/move behavior.
8. **Correctness before cleverness.** Keep an older correct source variant when a newer accepted one has an incidental defect or worsens the intended complexity. The chapter explains the relevant change.

## Reuse checklist

- What is the state invariant before and after one operation?
- Is the input mutated? Are references or iterators invalidated?
- What does an empty query return? Is an invalid request checked or a documented precondition?
- How are equal values assigned to one side of a partition or stack boundary?
- Is the operation invertible, associative, commutative, or none of these?
- Does the complexity include sorting, copying, output size, recursion depth, and hash-table worst cases?
- What part of the implementation depends on the original problem's constraints?
