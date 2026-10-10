#pragma once
#include <algorithm>
#include <array>
#include <climits>
#include <deque>
#include <numeric>
#include <queue>
#include <stdexcept>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

namespace patterns {
// LC 2333: already-computed absolute differences; use only for a modest max value.
// O(n + maxDifference) time/space. The final squared sum must fit long long.
inline long long minSquaredDifference(const std::vector<int>& differences, long long operations) {
    if (operations < 0) { throw std::invalid_argument("operations must be nonnegative"); }
    int maximum = 0;
    long long total = 0;
    for (int difference : differences) {
        if (difference < 0) { throw std::invalid_argument("differences must be nonnegative"); }
        maximum = std::max(maximum, difference); total += difference;
    }
    if (total <= operations) { return 0; }
    std::vector<long long> counts(static_cast<std::size_t>(maximum) + 1);
    for (int difference : differences) { ++counts[difference]; }
    for (int value = maximum; value > 0 && operations > 0; --value) {
        long long moved = std::min(operations, counts[value]);
        counts[value] -= moved; counts[value - 1] += moved; operations -= moved;
    }
    long long result = 0;
    for (int value = 1; value <= maximum; ++value) { result += 1LL * value * value * counts[value]; }
    return result;
}

// LC 435: positive-length intervals; touching endpoints are compatible.
// Pass by value deliberately protects the caller from sorting and alias writes.
inline int eraseOverlapIntervals(std::vector<std::array<int, 2>> intervals) {
    if (intervals.empty()) { return 0; }
    std::sort(intervals.begin(), intervals.end(), [](const auto& l, const auto& r) { return l[1] < r[1]; });
    int lastEnd = intervals[0][1], removed = 0;
    for (std::size_t i = 1; i < intervals.size(); ++i) {
        if (intervals[i][0] >= lastEnd) { lastEnd = intervals[i][1]; } else { ++removed; }
    }
    return removed;
}

// LC 56: closed intervals; touching endpoints DO merge.
inline std::vector<std::array<int, 2>> mergeIntervals(std::vector<std::array<int, 2>> intervals) {
    std::sort(intervals.begin(), intervals.end());
    std::vector<std::array<int, 2>> result;
    for (const auto& interval : intervals) {
        if (!result.empty() && result.back()[1] >= interval[0]) { result.back()[1] = std::max(result.back()[1], interval[1]); }
        else { result.push_back(interval); }
    }
    return result;
}

// LC 57: intervals already sorted and strictly separated; all starts <= ends.
// Searches are logarithmic, but vector erase/insert and the copy are linear.
inline std::vector<std::array<int, 2>> insertInterval(std::vector<std::array<int, 2>> intervals, std::array<int, 2> added) {
    auto left = std::lower_bound(intervals.begin(), intervals.end(), added[0],
        [](const auto& interval, int value) { return interval[1] < value; });
    auto right = std::upper_bound(intervals.begin(), intervals.end(), added[1],
        [](int value, const auto& interval) { return value < interval[0]; });
    if (left != right) {
        added[0] = std::min(added[0], (*left)[0]);
        added[1] = std::max(added[1], (*std::prev(right))[1]);
    }
    auto position = intervals.erase(left, right);
    intervals.insert(position, added);
    return intervals;
}

// LC 135: each pass enforces one direction; max preserves the other direction.
inline long long minimumCandy(const std::vector<int>& ratings) {
    int n = static_cast<int>(ratings.size());
    std::vector<int> candies(n, 1);
    for (int i = 1; i < n; ++i) { if (ratings[i] > ratings[i - 1]) { candies[i] = candies[i - 1] + 1; } }
    for (int i = n - 2; i >= 0; --i) {
        if (ratings[i] > ratings[i + 1]) { candies[i] = std::max(candies[i], candies[i + 1] + 1); }
    }
    return std::accumulate(candies.begin(), candies.end(), 0LL);
}

// LC 621: most-frequent types first in rounds of cooldown+1 distinct types.
inline long long leastScheduleLength(const std::vector<char>& tasks, int cooldown) {
    if (cooldown < 0) { throw std::invalid_argument("cooldown must be nonnegative"); }
    std::unordered_map<char, int> counts;
    for (char task : tasks) { ++counts[task]; }
    std::priority_queue<int> queue;
    for (const auto& entry : counts) { queue.push(entry.second); }
    long long result = 0;
    while (!queue.empty()) {
        std::vector<int> remaining;
        for (long long i = 0; i <= cooldown && !queue.empty(); ++i) { remaining.push_back(queue.top()); queue.pop(); }
        for (int frequency : remaining) { if (frequency > 1) { queue.push(frequency - 1); } }
        result += queue.empty() ? static_cast<long long>(remaining.size()) : 1LL + cooldown;
    }
    return result;
}

// LC 1520: preserve the observed first-appearance/deque suffix method.
// ASCII lowercase only. All occurrences of every selected character must fit.
inline std::vector<std::string> maxClosedSubstrings(std::string_view s) {
    std::array<int, 26> count{}, first{}, last{};
    std::vector<int> order;
    for (int i = 0; i < static_cast<int>(s.size()); ++i) {
        if (s[i] < 'a' || s[i] > 'z') { throw std::invalid_argument("ASCII lowercase required"); }
        int ch = s[i] - 'a';
        if (count[ch] == 0) { first[ch] = i; order.push_back(ch); }
        ++count[ch]; last[ch] = i;
    }
    std::deque<std::array<int, 3>> queue;
    std::vector<std::string> result;
    for (int ch : order) {
        queue.push_front({first[ch], last[ch], count[ch]});
        int left = INT_MAX, right = INT_MIN, total = 0;
        for (const auto& item : queue) {
            left = std::min(left, item[0]); right = std::max(right, item[1]); total += item[2];
            if (total == right - left + 1) { break; }
        }
        if (total == right - left + 1) { result.emplace_back(s.substr(left, right - left + 1)); queue.clear(); }
    }
    return result;
}

// LC 2472: any longer palindrome has an inner one of length k or k+1.
inline int maxNonOverlappingPalindromes(std::string_view s, int k) {
    if (k <= 0) { throw std::invalid_argument("minimum length must be positive"); }
    int n = static_cast<int>(s.size()), result = 0;
    if (k > n) { return 0; }
    for (int i = 0; i <= n - k; ++i) {
        for (int length : {k, k + 1}) {
            if (length > n - i) { continue; }
            int left = i, right = i + length - 1;
            bool valid = true;
            while (left < right) { if (s[left++] != s[right--]) { valid = false; break; } }
            if (valid) { ++result; i += length - 1; break; }
        }
    }
    return result;
}

// LC 1498: each nonempty indexed subsequence belongs to its smallest index.
inline int countBoundedSubsequences(std::vector<int> nums, long long target) {
    constexpr int mod = 1'000'000'007;
    std::sort(nums.begin(), nums.end());
    int n = static_cast<int>(nums.size());
    std::vector<int> powers(n, 1);
    for (int i = 1; i < n; ++i) { powers[i] = static_cast<int>(2LL * powers[i - 1] % mod); }
    int left = 0, right = n - 1, result = 0;
    while (left <= right) {
        if (static_cast<long long>(nums[left]) + nums[right] <= target) {
            result = static_cast<int>((static_cast<long long>(result) + powers[right - left]) % mod); ++left;
        } else { --right; }
    }
    return result;
}
} // namespace patterns
