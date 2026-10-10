#include "templates.hpp"
#include <algorithm>
#include <climits>
#include <cstdint>
#include <iostream>
#include <numeric>
#include <random>
#include <set>
#include <stdexcept>
#include <string>
#include <vector>

namespace {
int failures = 0;
void check(bool condition, const char* name) {
    if (!condition) { std::cerr << "FAIL: " << name << '\n'; ++failures; }
}
bool palindrome(const std::string& s, int l, int r) {
    while (l < r) { if (s[l++] != s[r--]) { return false; } }
    return true;
}
int bruteCuts(const std::string& s, int i = 0) {
    if (i == static_cast<int>(s.size())) { return -1; }
    int best = static_cast<int>(s.size());
    for (int r = i; r < static_cast<int>(s.size()); ++r) {
        if (palindrome(s, i, r)) { best = std::min(best, 1 + bruteCuts(s, r + 1)); }
    }
    return best;
}
std::vector<std::string> subsequences(const std::string& s) {
    std::vector<std::string> result;
    for (unsigned mask = 0; mask < (1U << s.size()); ++mask) {
        std::string current;
        for (std::size_t i = 0; i < s.size(); ++i) { if (mask & (1U << i)) { current += s[i]; } }
        result.push_back(current);
    }
    return result;
}
patterns::IntervalSelection bruteIntervals(const std::vector<patterns::WeightedInterval>& intervals, int cap) {
    patterns::IntervalSelection best;
    for (unsigned mask = 0; mask < (1U << intervals.size()); ++mask) {
        patterns::IntervalSelection candidate; bool valid = true;
        for (int i = 0; i < static_cast<int>(intervals.size()); ++i) {
            if (!(mask & (1U << i))) { continue; }
            candidate.indices.push_back(i); candidate.score += intervals[i].weight;
            for (int j = 0; j < i; ++j) {
                if ((mask & (1U << j)) && !(intervals[j].right < intervals[i].left ||
                    intervals[i].right < intervals[j].left)) { valid = false; }
            }
        }
        if (valid && static_cast<int>(candidate.indices.size()) <= cap &&
            (candidate.score > best.score || (candidate.score == best.score && candidate.indices < best.indices))) {
            best = candidate;
        }
    }
    return best;
}
int bruteIncreasing(const std::vector<std::vector<int>>& grid, int r, int c) {
    int best = 1;
    const int dr[] = {1, -1, 0, 0}, dc[] = {0, 0, 1, -1};
    for (int d = 0; d < 4; ++d) {
        int nr = r + dr[d], nc = c + dc[d];
        if (nr >= 0 && nc >= 0 && nr < static_cast<int>(grid.size()) && nc < static_cast<int>(grid[0].size()) &&
            grid[nr][nc] > grid[r][c]) { best = std::max(best, 1 + bruteIncreasing(grid, nr, nc)); }
    }
    return best;
}
long long bruteGrid(const std::vector<std::vector<int>>& grid, int r, int c) {
    if (r + 1 == static_cast<int>(grid.size()) && c + 1 == static_cast<int>(grid[0].size())) { return grid[r][c]; }
    long long best = LLONG_MAX;
    if (r + 1 < static_cast<int>(grid.size())) { best = std::min(best, bruteGrid(grid, r + 1, c)); }
    if (c + 1 < static_cast<int>(grid[0].size())) { best = std::min(best, bruteGrid(grid, r, c + 1)); }
    return grid[r][c] + best;
}
std::vector<std::string> bruteParentheses(const std::string& s) {
    std::set<std::string> best; std::size_t longest = 0;
    for (const auto& candidate : subsequences(s)) {
        std::string originalLetters, keptLetters;
        for (char ch : s) { if (ch != '(' && ch != ')') { originalLetters += ch; } }
        for (char ch : candidate) { if (ch != '(' && ch != ')') { keptLetters += ch; } }
        if (originalLetters != keptLetters) { continue; }
        int balance = 0; bool valid = true;
        for (char ch : candidate) {
            balance += (ch == '(') - (ch == ')'); if (balance < 0) { valid = false; }
        }
        if (!valid || balance != 0 || candidate.size() < longest) { continue; }
        if (candidate.size() > longest) { longest = candidate.size(); best.clear(); }
        best.insert(candidate);
    }
    return {best.begin(), best.end()};
}
}

int main() {
    using namespace patterns;
    check(minimumPalindromeCuts("aab") == 1 && minimumPalindromeCuts("") == 0, "palindrome cuts and empty");
    check(countTargetSubsequences("rabbbit", "rabbit") == 3, "subsequence multiplicity");
    check(countTargetSubsequences("", "") == 1 && countTargetSubsequences("", "a") == 0, "empty target base");
    check(countDistinctSubsequences("aba") == 6 && countDistinctSubsequences("aaa") == 3, "duplicate subtraction");
    check(countDistinctSubsequences("") == 0, "exclude empty subsequence");
    bool rejected = false;
    try { static_cast<void>(countTargetSubsequences(std::string(100, 'a'), std::string(50, 'a'))); }
    catch (const std::overflow_error&) { rejected = true; }
    check(rejected, "target count overflow is explicit");
    auto selected = selectWeightedIntervals({{1, 2, 3}, {3, 4, 3}, {1, 4, 6}});
    check(selected.score == 6 && selected.indices == std::vector<int>({0, 1}), "lexicographic tie by original index");
    selected = selectWeightedIntervals({{1, 2, 4}, {2, 3, 5}});
    check(selected.score == 5 && selected.indices == std::vector<int>({1}), "touching closed intervals overlap");
    rejected = false;
    try { static_cast<void>(selectWeightedIntervals({{1, 2, 0}})); }
    catch (const std::invalid_argument&) { rejected = true; }
    check(rejected, "positive interval weight contract");
    rejected = false;
    try { static_cast<void>(selectWeightedIntervals({{1, 1, LLONG_MAX}, {2, 2, 1}})); }
    catch (const std::overflow_error&) { rejected = true; }
    check(rejected, "interval score overflow is explicit");
    check(longestIncreasingPath({{-3, -2}, {-4, -1}}) == 4, "negative grid DAG");
    check(minimumGridPathSum({{1, 3, 1}, {1, 5, 1}, {4, 2, 1}}) == 7, "grid cost recurrence");
    check(minimumGridPathSum({{INT_MAX, INT_MAX}}) == 2LL * INT_MAX, "wide grid sum");
    check(longestIncreasingPath({}) == 0 && minimumGridPathSum({}) == 0, "empty grids");
    for (const auto& malformed : {std::vector<std::vector<int>>{{1}, {}}, std::vector<std::vector<int>>{{}, {1}}}) {
        rejected = false; try { static_cast<void>(longestIncreasingPath(malformed)); }
        catch (const std::invalid_argument&) { rejected = true; }
        check(rejected, "ragged DAG input");
    }
    const int queenCounts[] = {1, 1, 0, 0, 2, 10, 4, 40, 92};
    for (int n = 0; n <= 8; ++n) {
        auto placements = nQueensColumns(n);
        check(static_cast<int>(placements.size()) == queenCounts[n], "N-Queens known counts");
        std::set<std::vector<int>> unique(placements.begin(), placements.end());
        check(unique.size() == placements.size(), "N-Queens no duplicates");
        for (const auto& columns : placements) {
            bool valid = static_cast<int>(columns.size()) == n;
            for (int r = 0; r < n; ++r) {
                valid = valid && columns[r] >= 0 && columns[r] < n;
                for (int p = 0; p < r; ++p) { valid = valid && columns[p] != columns[r] && std::abs(columns[p] - columns[r]) != r - p; }
            }
            check(valid, "N-Queens placement validity");
        }
    }
    std::vector<std::string> puzzle = {"53..7....", "6..195...", ".98....6.", "8...6...3", "4..8.3..1", "7...2...6", ".6....28.", "...419..5", "....8..79"};
    auto original = puzzle;
    check(solveSudoku(puzzle), "Sudoku solves");
    const std::vector<std::string> solved = {"534678912", "672195348", "198342567", "859761423", "426853791", "713924856", "961537284", "287419635", "345286179"};
    check(puzzle == solved, "Sudoku exact solution");
    auto invalid = original; invalid[0][1] = '5'; auto unchanged = invalid;
    check(!solveSudoku(invalid) && invalid == unchanged, "invalid Sudoku stays unchanged");
    auto unsatisfiable = original; unsatisfiable[0][2] = '1'; unchanged = unsatisfiable;
    check(!solveSudoku(unsatisfiable) && unsatisfiable == unchanged, "unsatisfiable Sudoku fully rolls back");
    check(removeInvalidParentheses("()())()") == std::vector<std::string>({"(())()", "()()()"}), "set-valued memo deduplication");
    check(removeInvalidParentheses("abc") == std::vector<std::string>({"abc"}), "mandatory letters");

    std::mt19937 rng(0xd01234U);
    for (int trial = 0; trial < 250; ++trial) {
        std::string s, target, parens;
        for (unsigned i = 0, n = rng() % 10; i < n; ++i) { s += "abc"[rng() % 3]; parens += "()a"[rng() % 3]; }
        for (unsigned i = 0, n = rng() % 5; i < n; ++i) { target += "abc"[rng() % 3]; }
        auto all = subsequences(s); std::set<std::string> unique(all.begin(), all.end());
        check(minimumPalindromeCuts(s) == (s.empty() ? 0 : bruteCuts(s)), "seeded cuts versus partitions");
        check(countTargetSubsequences(s, target) == static_cast<std::uint64_t>(std::count(all.begin(), all.end(), target)), "seeded target counts versus masks");
        check(countDistinctSubsequences(s) == static_cast<int>(unique.size()) - 1, "seeded unique counts versus sets");
        check(removeInvalidParentheses(parens) == bruteParentheses(parens), "seeded parentheses versus masks");
    }
    for (int trial = 0; trial < 250; ++trial) {
        std::vector<WeightedInterval> intervals;
        for (unsigned i = 0, n = rng() % 10; i < n; ++i) {
            int l = static_cast<int>(rng() % 12); int r = l + static_cast<int>(rng() % 5);
            intervals.push_back({l, r, 1 + static_cast<int>(rng() % 12)});
        }
        int cap = static_cast<int>(rng() % 5);
        auto actual = selectWeightedIntervals(intervals, cap); auto expected = bruteIntervals(intervals, cap);
        check(actual.score == expected.score && actual.indices == expected.indices, "seeded weighted selection versus subsets");
    }
    for (int trial = 0; trial < 200; ++trial) {
        int rows = 1 + static_cast<int>(rng() % 3), cols = 1 + static_cast<int>(rng() % 3);
        std::vector<std::vector<int>> grid(rows, std::vector<int>(cols));
        for (auto& row : grid) { for (auto& value : row) { value = static_cast<int>(rng() % 11) - 5; } }
        int best = 0;
        for (int r = 0; r < rows; ++r) { for (int c = 0; c < cols; ++c) { best = std::max(best, bruteIncreasing(grid, r, c)); } }
        check(longestIncreasingPath(grid) == best, "seeded DAG memo versus path enumeration");
        check(minimumGridPathSum(grid) == bruteGrid(grid, 0, 0), "seeded grid DP versus path enumeration");
    }
    if (failures) { std::cerr << failures << " failures\n"; return 1; }
    std::cout << "dp-and-backtracking: deterministic + 250 string + 250 interval + 200 grid trials passed\n";
}
