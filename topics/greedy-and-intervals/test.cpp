#include "templates.hpp"
#include <algorithm>
#include <array>
#include <climits>
#include <functional>
#include <iostream>
#include <numeric>
#include <queue>
#include <random>

namespace {
int failures = 0;
void check(bool condition, const char* name) {
    if (!condition) { if (failures < 20) { std::cerr << "FAIL: " << name << '\n'; } ++failures; }
}
using Interval = std::array<int, 2>;
std::vector<Interval> bruteMerge(const std::vector<Interval>& intervals) {
    int n = static_cast<int>(intervals.size());
    std::vector<bool> seen(n);
    std::vector<Interval> result;
    for (int i = 0; i < n; ++i) {
        if (seen[i]) { continue; }
        Interval component = intervals[i]; seen[i] = true;
        bool changed = true;
        while (changed) {
            changed = false;
            for (int j = 0; j < n; ++j) {
                if (!seen[j] && component[0] <= intervals[j][1] && intervals[j][0] <= component[1]) {
                    component[0] = std::min(component[0], intervals[j][0]);
                    component[1] = std::max(component[1], intervals[j][1]);
                    seen[j] = true; changed = true;
                }
            }
        }
        result.push_back(component);
    }
    std::sort(result.begin(), result.end()); return result;
}
int bruteErased(const std::vector<Interval>& a) {
    int n = static_cast<int>(a.size()), best = 0;
    for (unsigned mask = 0; mask < (1U << n); ++mask) {
        bool valid = true; int count = 0;
        for (int i = 0; i < n; ++i) {
            if (!(mask & (1U << i))) { continue; }
            ++count;
            for (int j = 0; j < i; ++j) {
                if ((mask & (1U << j)) && std::max(a[i][0], a[j][0]) < std::min(a[i][1], a[j][1])) { valid = false; }
            }
        }
        if (valid) { best = std::max(best, count); }
    }
    return n - best;
}
bool palindrome(const std::string& s, int l, int r) {
    while (l < r) { if (s[l++] != s[r--]) { return false; } }
    return true;
}
int brutePalindromes(const std::string& s, int k) {
    int n = static_cast<int>(s.size()); std::vector<int> best(n + 1);
    for (int l = n - 1; l >= 0; --l) {
        best[l] = best[l + 1];
        for (int r = l + k - 1; r < n; ++r) {
            if (palindrome(s, l, r)) { best[l] = std::max(best[l], 1 + best[r + 1]); }
        }
    }
    return best[0];
}
std::pair<int, int> bruteClosed(const std::string& s) {
    int n = static_cast<int>(s.size());
    std::array<int, 26> total{};
    for (char ch : s) { ++total[ch - 'a']; }
    std::vector<std::pair<int, int>> best(n + 1);
    for (int l = n - 1; l >= 0; --l) {
        best[l] = best[l + 1]; std::array<int, 26> count{};
        for (int r = l; r < n; ++r) {
            ++count[s[r] - 'a']; bool valid = true;
            for (int ch = 0; ch < 26; ++ch) { if (count[ch] && count[ch] != total[ch]) { valid = false; } }
            if (valid) { best[l] = std::max(best[l], std::pair{best[r + 1].first + 1, best[r + 1].second - (r - l + 1)}); }
        }
    }
    return best[0]; // maximize count, then maximize negative total length
}
long long bruteCandy(const std::vector<int>& ratings) {
    int n = static_cast<int>(ratings.size());
    if (n == 0) { return 0; }
    std::vector<int> candies(n, 1); int best = n * n;
    std::function<void(int, int)> visit = [&](int i, int sum) {
        if (sum >= best) { return; }
        if (i == n) { best = sum; return; }
        for (int c = 1; c <= n; ++c) {
            if (i > 0 && ((ratings[i] > ratings[i - 1] && c <= candies[i - 1]) ||
                         (ratings[i] < ratings[i - 1] && c >= candies[i - 1]))) { continue; }
            candies[i] = c; visit(i + 1, sum + c);
        }
    };
    visit(0, 0); return best;
}
}
int main() {
    using namespace patterns;
    check(minSquaredDifference({1, 4, 3}, 3) == 9, "largest bucket first");
    check(minSquaredDifference({2, 1}, 99) == 0, "excess operations");
    check(eraseOverlapIntervals({{1, 2}, {2, 3}, {1, 3}}) == 1, "touching is compatible");
    check(mergeIntervals({{1, 2}, {2, 3}}) == std::vector<Interval>({{1, 3}}), "touching merges");
    check(insertInterval({{1, 2}, {5, 7}}, {2, 5}) == std::vector<Interval>({{1, 7}}), "binary bound overlap block");
    check(minimumCandy({1, 0, 2}) == 5, "two directional constraints");
    check(leastScheduleLength({'A', 'A', 'A', 'B', 'B', 'B'}, 2) == 8, "cooldown rounds");
    check(maxClosedSubstrings("adefaddaccc") == std::vector<std::string>({"e", "f", "ccc"}), "character span suffixes");
    check(maxNonOverlappingPalindromes("abaccdbbd", 3) == 2, "shortest parity lengths");
    check(countBoundedSubsequences({3, 5, 6, 7}, 9) == 4, "interior subsets");
    std::mt19937 rng(2333435);
    for (int trial = 0; trial < 500; ++trial) {
        int n = static_cast<int>(rng() % 9);
        std::vector<int> differences, nums;
        std::vector<Interval> intervals;
        std::string s;
        std::vector<char> tasks;
        for (int i = 0; i < n; ++i) {
            differences.push_back(static_cast<int>(rng() % 9));
            nums.push_back(static_cast<int>(rng() % 13) - 6);
            int left = static_cast<int>(rng() % 12) - 6;
            intervals.push_back({left, left + 1 + static_cast<int>(rng() % 5)});
            s += static_cast<char>('a' + rng() % 3); tasks.push_back(static_cast<char>('A' + rng() % 4));
        }
        int operations = static_cast<int>(rng() % 30);
        std::priority_queue<int> pq(differences.begin(), differences.end());
        for (int i = 0; i < operations && !pq.empty() && pq.top() > 0; ++i) { int value = pq.top(); pq.pop(); pq.push(value - 1); }
        long long squared = 0;
        while (!pq.empty()) { squared += 1LL * pq.top() * pq.top(); pq.pop(); }
        check(minSquaredDifference(differences, operations) == squared, "random bucket vs one move");
        check(eraseOverlapIntervals(intervals) == bruteErased(intervals), "random interval selection");
        auto merged = bruteMerge(intervals);
        check(mergeIntervals(intervals) == merged, "random components merge");
        Interval addition{static_cast<int>(rng() % 12) - 6, 0}; addition[1] = addition[0] + static_cast<int>(rng() % 6);
        auto withAddition = merged; withAddition.push_back(addition);
        check(insertInterval(merged, addition) == bruteMerge(withAddition), "random insert vs components");
        int cooldown = static_cast<int>(rng() % 6), most = 0, ties = 0;
        std::array<int, 256> frequencies{};
        for (unsigned char ch : tasks) { most = std::max(most, ++frequencies[ch]); }
        for (int f : frequencies) { ties += f == most && f > 0; }
        long long expectedSchedule = tasks.empty() ? 0 : std::max<long long>(tasks.size(), 1LL * (most - 1) * (cooldown + 1) + ties);
        check(leastScheduleLength(tasks, cooldown) == expectedSchedule, "random scheduler vs counting bound");
        int k = 1 + static_cast<int>(rng() % 6);
        check(maxNonOverlappingPalindromes(s, k) == brutePalindromes(s, k), "random palindrome DP");
        auto selected = maxClosedSubstrings(s); int length = 0; std::size_t from = 0;
        bool valid = true;
        for (const auto& part : selected) {
            std::size_t start = s.find(part, from);
            if (part.empty() || start == std::string::npos) { valid = false; break; }
            from = start + part.size(); length += static_cast<int>(part.size());
            for (char ch : part) {
                if (s.find(ch) < start || s.rfind(ch) >= from) { valid = false; }
            }
        }
        check(valid, "closed substring output validity");
        check(std::pair{static_cast<int>(selected.size()), -length} == bruteClosed(s), "random closed substring optimum");
        long long target = static_cast<int>(rng() % 17) - 8; int count = 0;
        for (unsigned mask = 1; mask < (1U << n); ++mask) {
            int low = INT_MAX, high = INT_MIN;
            for (int i = 0; i < n; ++i) { if (mask & (1U << i)) { low = std::min(low, nums[i]); high = std::max(high, nums[i]); } }
            count += static_cast<long long>(low) + high <= target;
        }
        check(countBoundedSubsequences(nums, target) == count, "random subsequence masks");
        if (trial < 100) {
            nums.resize(std::min(5, n));
            check(minimumCandy(nums) == bruteCandy(nums), "random candy assignments");
        }
    }
    check(eraseOverlapIntervals({}) == 0 && mergeIntervals({}).empty(), "empty intervals");
    check(maxNonOverlappingPalindromes("", 1) == 0 && minimumCandy({}) == 0, "empty scans");
    check(countBoundedSubsequences({INT_MAX, INT_MAX}, 2LL * INT_MAX) == 3, "wide endpoint sum");
    if (failures != 0) { std::cerr << failures << " checks failed\n"; return 1; }
    std::cout << "greedy-and-intervals: deterministic + 500 seeded differential cases passed\n";
}
