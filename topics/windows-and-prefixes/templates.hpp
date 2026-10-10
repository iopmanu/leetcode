#pragma once
#include <algorithm>
#include <array>
#include <climits>
#include <numeric>
#include <stdexcept>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

namespace patterns {
// Byte strings; lengths fit int. Read-only inputs. See README for numeric bounds.
static_assert(CHAR_BIT == 8, "These frequency tables assume 8-bit bytes");

// LC 76: distinct requirements cross zero exactly when their quota is met.
inline std::string minWindow(std::string_view s, std::string_view t) {
    if (t.empty()) { return {}; }
    std::array<int, 256> counts{};
    int missing = 0;
    for (unsigned char ch : t) { missing += counts[ch]++ == 0; }
    int left = 0, bestLeft = -1, bestLength = INT_MAX;
    for (int right = 0; right < static_cast<int>(s.size()); ++right) {
        missing -= --counts[static_cast<unsigned char>(s[right])] == 0;
        while (missing == 0) {
            if (right - left + 1 < bestLength) { bestLeft = left; bestLength = right - left + 1; }
            missing += ++counts[static_cast<unsigned char>(s[left++])] > 0;
        }
    }
    return bestLeft == -1 ? "" : std::string(s.substr(bestLeft, bestLength));
}

// LC 567: quotas plus a fixed window length imply an exact multiset match.
inline bool containsPermutation(std::string_view pattern, std::string_view text) {
    if (pattern.empty()) { return true; }
    std::array<int, 256> counts{};
    int required = 0, matches = 0, left = 0;
    for (unsigned char ch : pattern) { required += counts[ch]++ == 0; }
    for (int right = 0; right < static_cast<int>(text.size()); ++right) {
        matches += --counts[static_cast<unsigned char>(text[right])] == 0;
        if (right - left + 1 > static_cast<int>(pattern.size())) {
            matches -= counts[static_cast<unsigned char>(text[left++])]++ == 0;
        }
        if (matches == required) { return true; }
    }
    return false;
}

// LC 424: maxCount is deliberately historical, not the current-window maximum.
inline int longestReplacementWindow(std::string_view s, int k) {
    if (k < 0) { throw std::invalid_argument("k must be nonnegative"); }
    std::array<int, 256> counts{};
    int left = 0, maxCount = 0, result = 0;
    for (int right = 0; right < static_cast<int>(s.size()); ++right) {
        maxCount = std::max(maxCount, ++counts[static_cast<unsigned char>(s[right])]);
        if (right - left + 1 - maxCount > k) { --counts[static_cast<unsigned char>(s[left++])]; }
        result = std::max(result, right - left + 1);
    }
    return result;
}

// LC 1004: binary input. This explicit while-loop keeps the actual window valid.
inline int longestOnes(const std::vector<int>& nums, int k) {
    if (k < 0) { throw std::invalid_argument("k must be nonnegative"); }
    int left = 0, zeroes = 0, result = 0;
    for (int right = 0; right < static_cast<int>(nums.size()); ++right) {
        zeroes += nums[right] == 0;
        while (zeroes > k) { zeroes -= nums[left++] == 0; }
        result = std::max(result, right - left + 1);
    }
    return result;
}

// LC 1493: removing one element is mandatory, including an all-ones array.
inline int longestOnesAfterDeletion(const std::vector<int>& nums) {
    return std::max(0, longestOnes(nums, 1) - 1);
}

// LC 209: nums are nonnegative; target > 0. A negative value breaks monotonicity.
inline int minSubarrayLength(const std::vector<int>& nums, long long target) {
    if (target <= 0) { throw std::invalid_argument("target must be positive"); }
    int left = 0, result = INT_MAX;
    long long current = 0;
    for (int right = 0; right < static_cast<int>(nums.size()); ++right) {
        current += nums[right];
        while (current >= target) {
            result = std::min(result, right - left + 1);
            current -= nums[left++];
        }
    }
    return result == INT_MAX ? 0 : result;
}

// LC 1658: retain the longest middle of sum total-x. Nonnegative values only.
inline int minEndRemovals(const std::vector<int>& nums, long long x) {
    if (x < 0) { return -1; }
    long long total = std::accumulate(nums.begin(), nums.end(), 0LL);
    if (x > total) { return -1; }
    long long target = total - x, current = 0;
    int left = 0, longest = target == 0 ? 0 : -1;
    for (int right = 0; right < static_cast<int>(nums.size()); ++right) {
        current += nums[right];
        while (current > target) { current -= nums[left++]; }
        if (current == target) { longest = std::max(longest, right - left + 1); }
    }
    return longest == -1 ? -1 : static_cast<int>(nums.size()) - longest;
}

// LC 560: unlike a sum window, this works with negative values.
inline long long countSubarraysSum(const std::vector<int>& nums, long long target) {
    std::unordered_map<long long, long long> counts{{0, 1}};
    long long current = 0, result = 0;
    for (int num : nums) {
        current += num;
        if (auto it = counts.find(current - target); it != counts.end()) { result += it->second; }
        ++counts[current];
    }
    return result;
}

// LC 2444: starts lie in (lastBad, min(lastMin,lastMax)].
inline long long countFixedBoundSubarrays(const std::vector<int>& nums, int minValue, int maxValue) {
    if (minValue > maxValue) { return 0; }
    int lastBad = -1, lastMin = -1, lastMax = -1;
    long long result = 0;
    for (int right = 0; right < static_cast<int>(nums.size()); ++right) {
        if (nums[right] < minValue || nums[right] > maxValue) { lastBad = right; }
        if (nums[right] == minValue) { lastMin = right; }
        if (nums[right] == maxValue) { lastMax = right; }
        result += std::max(0, std::min(lastMin, lastMax) - lastBad);
    }
    return result;
}

// LC 238: explicit identity-padded prefix/suffix arrays, with no division.
inline std::vector<long long> productExceptSelf(const std::vector<int>& nums) {
    int n = static_cast<int>(nums.size());
    std::vector<long long> left(n + 1, 1), right(n + 1, 1), result(n);
    for (int i = 0; i < n; ++i) { left[i + 1] = left[i] * nums[i]; }
    for (int i = n - 1; i >= 0; --i) { right[i] = nums[i] * right[i + 1]; }
    for (int i = 0; i < n; ++i) { result[i] = left[i] * right[i + 1]; }
    return result;
}

// LC 1477: strictly positive nums, positive target. best[i] uses [0,i).
inline int minTwoTargetLengths(const std::vector<int>& nums, long long target) {
    if (target <= 0) { throw std::invalid_argument("target must be positive"); }
    int n = static_cast<int>(nums.size()), left = 0, result = n + 1;
    long long current = 0;
    std::vector<int> best(n + 1, n + 1);
    for (int right = 0; right < n; ++right) {
        current += nums[right];
        while (current > target) { current -= nums[left++]; }
        best[right + 1] = best[right];
        if (current == target) {
            int length = right - left + 1;
            if (best[left] != n + 1) { result = std::min(result, length + best[left]); }
            best[right + 1] = std::min(best[right + 1], length);
        }
    }
    return result == n + 1 ? -1 : result;
}

// LC 3903/3904: index i belongs to BOTH prefix [0,i] and suffix [i,n).
inline int firstStableIndex(const std::vector<int>& nums, long long k) {
    int n = static_cast<int>(nums.size());
    std::vector<int> suffixMin(n);
    for (int i = n - 1; i >= 0; --i) { suffixMin[i] = i + 1 == n ? nums[i] : std::min(nums[i], suffixMin[i + 1]); }
    int prefixMax = INT_MIN;
    for (int i = 0; i < n; ++i) {
        prefixMax = std::max(prefixMax, nums[i]);
        if (static_cast<long long>(prefixMax) - suffixMin[i] <= k) { return i; }
    }
    return -1;
}

// LC 30: string_views point into inputs only for this call; none escape.
inline std::vector<int> findWordConcatenations(std::string_view text, const std::vector<std::string>& words) {
    if (words.empty()) { return {}; }
    int width = static_cast<int>(words[0].size());
    if (width == 0) { throw std::invalid_argument("words must be nonempty"); }
    std::unordered_map<std::string_view, int> wanted;
    for (const auto& word : words) {
        if (word.size() != static_cast<std::size_t>(width)) { throw std::invalid_argument("word lengths must match"); }
        ++wanted[word];
    }
    std::vector<int> result;
    int n = static_cast<int>(text.size());
    for (int offset = 0; offset < width && offset + width <= n; ++offset) {
        std::unordered_map<std::string_view, int> counts;
        int left = offset, matches = 0;
        for (int right = offset; right <= n - width; right += width) {
            auto word = text.substr(right, width);
            auto it = wanted.find(word);
            if (it == wanted.end()) { counts.clear(); left = right + width; matches = 0; continue; }
            ++counts[word]; ++matches;
            while (counts[word] > it->second) { --counts[text.substr(left, width)]; left += width; --matches; }
            if (matches == static_cast<int>(words.size())) { result.push_back(left); }
        }
    }
    return result;
}
} // namespace patterns
