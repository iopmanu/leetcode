#pragma once

#include <algorithm>
#include <cstdint>
#include <limits>
#include <stdexcept>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

namespace patterns {

// 132: pal[l][r] uses an already-computed interior; cuts[i] starts at i.
inline int minimumPalindromeCuts(const std::string& text) {
    const int n = static_cast<int>(text.size());
    if (n == 0) { return 0; }
    std::vector<std::vector<unsigned char>> pal(n, std::vector<unsigned char>(n));
    for (int right = 0; right < n; ++right) {
        for (int left = 0; left <= right; ++left) {
            pal[left][right] = text[left] == text[right] &&
                (right - left < 2 || pal[left + 1][right - 1]);
        }
    }
    std::vector<int> cuts(n + 1, n);
    cuts[n] = -1; // One chosen final palindrome needs no following cut.
    for (int left = n - 1; left >= 0; --left) {
        for (int right = left; right < n; ++right) {
            if (pal[left][right]) { cuts[left] = std::min(cuts[left], 1 + cuts[right + 1]); }
        }
    }
    return cuts[0];
}

// 115: dp[j] counts ways to form target[0..j) from the consumed source prefix.
// Descending j prevents using the same source character twice.
inline std::uint64_t countTargetSubsequences(const std::string& source, const std::string& target) {
    std::vector<std::uint64_t> dp(target.size() + 1);
    dp[0] = 1;
    for (char ch : source) {
        for (std::size_t j = target.size(); j > 0; --j) {
            if (ch == target[j - 1]) {
                if (dp[j] > std::numeric_limits<std::uint64_t>::max() - dp[j - 1]) {
                    throw std::overflow_error("subsequence count exceeds uint64_t");
                }
                dp[j] += dp[j - 1];
            }
        }
    }
    return dp.back();
}

// 940: counts distinct nonempty byte subsequences, modulo 1,000,000,007.
inline int countDistinctSubsequences(const std::string& text) {
    constexpr long long mod = 1'000'000'007;
    std::vector<int> lastSeen(256, -1);
    std::vector<long long> dp(text.size() + 1);
    dp[0] = 1; // Include empty while applying the recurrence.
    for (int i = 1; i <= static_cast<int>(text.size()); ++i) {
        auto ch = static_cast<unsigned char>(text[i - 1]);
        dp[i] = (2 * dp[i - 1]) % mod;
        if (lastSeen[ch] != -1) { dp[i] = (dp[i] - dp[lastSeen[ch] - 1] + mod) % mod; }
        lastSeen[ch] = i;
    }
    return static_cast<int>((dp.back() + mod - 1) % mod);
}

struct WeightedInterval {
    long long left;
    long long right;
    long long weight;
};
struct IntervalSelection {
    long long score = 0;
    std::vector<int> indices; // Sorted ORIGINAL input indices.
};

// 3414: at most cap closed intervals, maximizing score, then minimizing indices
// lexicographically. Positive weights are required, as in the source problem.
inline IntervalSelection selectWeightedIntervals(const std::vector<WeightedInterval>& input, int cap = 4) {
    if (cap < 0) { throw std::invalid_argument("negative interval cap"); }
    struct Item { WeightedInterval interval; int index; };
    std::vector<Item> intervals;
    for (int i = 0; i < static_cast<int>(input.size()); ++i) {
        if (input[i].left > input[i].right || input[i].weight <= 0) {
            throw std::invalid_argument("interval needs ordered endpoints and positive weight");
        }
        intervals.push_back({input[i], i});
    }
    std::sort(intervals.begin(), intervals.end(), [](const auto& left, const auto& right) {
        if (left.interval.right != right.interval.right) { return left.interval.right < right.interval.right; }
        if (left.interval.left != right.interval.left) { return left.interval.left < right.interval.left; }
        return left.index < right.index;
    });
    int n = static_cast<int>(intervals.size());
    cap = std::min(cap, n);
    std::vector<long long> ends;
    for (const auto& item : intervals) { ends.push_back(item.interval.right); }
    std::vector<int> previousCount(n);
    for (int i = 0; i < n; ++i) {
        previousCount[i] = static_cast<int>(std::lower_bound(ends.begin(), ends.begin() + i,
                                              intervals[i].interval.left) - ends.begin());
    }
    std::vector<std::vector<IntervalSelection>> dp(cap + 1, std::vector<IntervalSelection>(n + 1));
    auto better = [](const IntervalSelection& left, const IntervalSelection& right) {
        return left.score != right.score ? left.score > right.score : left.indices < right.indices;
    };
    for (int i = 1; i <= n; ++i) {
        const auto& current = intervals[i - 1];
        for (int k = 1; k <= cap; ++k) {
            auto take = dp[k - 1][previousCount[i - 1]];
            if (take.score > std::numeric_limits<long long>::max() - current.interval.weight) {
                throw std::overflow_error("interval score exceeds long long");
            }
            take.score += current.interval.weight;
            take.indices.insert(std::lower_bound(take.indices.begin(), take.indices.end(), current.index), current.index);
            const auto& skip = dp[k][i - 1];
            dp[k][i] = better(take, skip) ? std::move(take) : skip;
        }
    }
    return dp[cap][n];
}

namespace dpDetail {
inline int gridWidth(const std::vector<std::vector<int>>& grid) {
    if (grid.empty()) { return 0; }
    auto width = grid.front().size();
    for (const auto& row : grid) {
        if (row.size() != width) { throw std::invalid_argument("ragged grid"); }
    }
    return static_cast<int>(width);
}
} // namespace dpDetail

// 329: strict increases make the implicit neighbor graph acyclic.
inline int longestIncreasingPath(const std::vector<std::vector<int>>& grid) {
    int cols = dpDetail::gridWidth(grid);
    int rows = static_cast<int>(grid.size());
    if (rows == 0 || cols == 0) { return 0; }
    std::vector<std::vector<int>> memo(rows, std::vector<int>(cols));
    const int dr[] = {-1, 1, 0, 0}; const int dc[] = {0, 0, -1, 1};
    auto dfs = [&](auto&& self, int row, int col) -> int {
        if (memo[row][col] != 0) { return memo[row][col]; }
        int best = 1;
        for (int d = 0; d < 4; ++d) {
            int nr = row + dr[d], nc = col + dc[d];
            if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && grid[nr][nc] > grid[row][col]) {
                best = std::max(best, 1 + self(self, nr, nc));
            }
        }
        return memo[row][col] = best;
    };
    int result = 0;
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) { result = std::max(result, dfs(dfs, r, c)); }
    }
    return result;
}

// 64: dp[c] is previous-row cost before update, current-row cost afterward.
inline long long minimumGridPathSum(const std::vector<std::vector<int>>& grid) {
    int cols = dpDetail::gridWidth(grid);
    if (grid.empty() || cols == 0) { return 0; }
    std::vector<long long> dp(cols);
    for (int r = 0; r < static_cast<int>(grid.size()); ++r) {
        for (int c = 0; c < cols; ++c) {
            if (r == 0 && c == 0) { dp[c] = grid[r][c]; }
            else if (r == 0) { dp[c] = dp[c - 1] + grid[r][c]; }
            else if (c == 0) { dp[c] += grid[r][c]; }
            else { dp[c] = std::min(dp[c], dp[c - 1]) + grid[r][c]; }
        }
    }
    return dp.back();
}

// 51: one queen per row. Save columns rather than full n-by-n boards.
inline std::vector<std::vector<int>> nQueensColumns(int n) {
    if (n < 0) { throw std::invalid_argument("negative board size"); }
    std::vector<std::vector<int>> result;
    std::vector<int> placement;
    std::vector<unsigned char> columns(n), down(2 * n + 1), up(2 * n + 1);
    auto search = [&](auto&& self, int row) -> void {
        if (row == n) { result.push_back(placement); return; }
        for (int col = 0; col < n; ++col) {
            int d = row - col + n, u = row + col;
            if (columns[col] || down[d] || up[u]) { continue; }
            columns[col] = down[d] = up[u] = 1; placement.push_back(col);
            self(self, row + 1);
            placement.pop_back(); columns[col] = down[d] = up[u] = 0;
        }
    };
    search(search, 0); return result;
}

// 37: exact 9x9 board, '.' or digits. Invalid/unsatisfiable input returns false
// without changing the board; success leaves one solution in place.
inline bool solveSudoku(std::vector<std::string>& board) {
    if (board.size() != 9) { return false; }
    std::vector<int> rows(9), cols(9), boxes(9);
    std::vector<std::pair<int, int>> empty;
    for (int r = 0; r < 9; ++r) {
        if (board[r].size() != 9) { return false; }
        for (int c = 0; c < 9; ++c) {
            char ch = board[r][c];
            if (ch == '.') { empty.emplace_back(r, c); continue; }
            if (ch < '1' || ch > '9') { return false; }
            int bit = 1 << (ch - '1'), box = (r / 3) * 3 + c / 3;
            if ((rows[r] | cols[c] | boxes[box]) & bit) { return false; }
            rows[r] |= bit; cols[c] |= bit; boxes[box] |= bit;
        }
    }
    auto search = [&](auto&& self, std::size_t i) -> bool {
        if (i == empty.size()) { return true; }
        auto [r, c] = empty[i]; int box = (r / 3) * 3 + c / 3;
        for (int digit = 0; digit < 9; ++digit) {
            int bit = 1 << digit;
            if ((rows[r] | cols[c] | boxes[box]) & bit) { continue; }
            rows[r] |= bit; cols[c] |= bit; boxes[box] |= bit;
            board[r][c] = static_cast<char>('1' + digit);
            if (self(self, i + 1)) { return true; }
            board[r][c] = '.';
            rows[r] &= ~bit; cols[c] &= ~bit; boxes[box] &= ~bit;
        }
        return false;
    };
    return search(search, 0);
}

// 301: memo values are SETS of suffix strings, not scalar scores. This faithful
// pattern is deliberately output-heavy; use it for short strings only.
inline std::vector<std::string> removeInvalidParentheses(const std::string& text) {
    using StringSet = std::unordered_set<std::string>;
    int n = static_cast<int>(text.size());
    std::vector<std::vector<StringSet>> memo(n + 1, std::vector<StringSet>(n + 1));
    std::vector<std::vector<unsigned char>> seen(n + 1, std::vector<unsigned char>(n + 1));
    const StringSet impossible;
    auto search = [&](auto&& self, int i, int open) -> const StringSet& {
        if (open < 0 || open > n - i) { return impossible; }
        auto& result = memo[i][open];
        if (seen[i][open]) { return result; }
        seen[i][open] = 1;
        if (i == n) { result.insert(""); return result; }
        char ch = text[i];
        if (ch == '(' || ch == ')') {
            const auto& skip = self(self, i + 1, open);
            result.insert(skip.begin(), skip.end());
        }
        int nextOpen = open + (ch == '(') - (ch == ')');
        const auto& keep = self(self, i + 1, nextOpen);
        for (const auto& suffix : keep) { result.insert(ch + suffix); }
        return result;
    };
    const auto& candidates = search(search, 0, 0);
    std::size_t longest = 0;
    for (const auto& candidate : candidates) { longest = std::max(longest, candidate.size()); }
    std::vector<std::string> result;
    for (const auto& candidate : candidates) { if (candidate.size() == longest) { result.push_back(candidate); } }
    std::sort(result.begin(), result.end());
    return result;
}

} // namespace patterns
