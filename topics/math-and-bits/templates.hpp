#pragma once
#include <algorithm>
#include <array>
#include <climits>
#include <cstdint>
#include <limits>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

namespace patterns {
// LC 906 adaptation: comparing digits avoids overflow from reversing LLONG_MAX.
inline bool decimalPalindrome(long long value) {
    if (value < 0) { return false; }
    std::string digits = std::to_string(value);
    int left = 0, right = static_cast<int>(digits.size()) - 1;
    while (left < right) { if (digits[left++] != digits[right--]) { return false; } }
    return true;
}

// LC 906: mirror a <=5-digit seed, optionally omitting its final (middle) digit.
inline long long palindromicRoot(int seed, bool oddLength) {
    if (seed < 0 || seed > 99999) { throw std::invalid_argument("seed must be in [0,99999]"); }
    long long result = seed;
    for (int tail = oddLength ? seed / 10 : seed; tail > 0; tail /= 10) { result = result * 10 + tail % 10; }
    return result;
}

// Original domain right<=10^18; zero is an explicit extension, counted once.
inline int countSuperPalindromes(long long left, long long right) {
    if (left < 0 || right < left || right > 1'000'000'000'000'000'000LL) {
        throw std::invalid_argument("require 0 <= left <= right <= 10^18");
    }
    int result = left == 0 ? 1 : 0;
    for (bool oddLength : {true, false}) {
        for (int seed = 1; seed <= 99999; ++seed) {
            long long root = palindromicRoot(seed, oddLength);
            if (root > right / root) { break; } // Before multiplying, not afterward.
            long long square = root * root;
            if (square >= left && decimalPalindrome(square)) { ++result; }
        }
    }
    return result;
}

// LC 923: group equal values, then add products/choose2/choose3.
// Retains the source n<=3000 count bound; long long handles all count products.
inline int threeSumMultiplicity(std::vector<int> nums, long long target) {
    if (nums.size() > 3000) { throw std::invalid_argument("this snippet retains the original n<=3000 bound"); }
    constexpr long long mod = 1'000'000'007;
    std::sort(nums.begin(), nums.end());
    std::vector<int> values;
    std::vector<long long> counts;
    for (int num : nums) {
        if (values.empty() || values.back() != num) { values.push_back(num); counts.push_back(1); }
        else { ++counts.back(); }
    }
    int size = static_cast<int>(values.size());
    long long result = 0;
    for (int i = 0; i < size; ++i) {
        int j = i, k = size - 1;
        while (j <= k) {
            long long sum = static_cast<long long>(values[i]) + values[j] + values[k];
            if (sum < target) { ++j; }
            else if (sum > target) { --k; }
            else {
                long long ways = 0;
                if (i == j && j == k) {
                    long long c = counts[i]; ways = c * (c - 1) * (c - 2) / 6;
                } else if (i == j) {
                    ways = counts[i] * (counts[i] - 1) / 2 * counts[k];
                } else if (j == k) {
                    ways = counts[i] * counts[j] * (counts[j] - 1) / 2;
                } else { ways = counts[i] * counts[j] * counts[k]; }
                result = (result + ways) % mod; ++j; --k;
            }
        }
    }
    return static_cast<int>(result);
}

// LC 835: preserve signed 32-bit bit patterns in two separate unsigned lanes.
inline std::uint64_t packSignedPair(std::int32_t x, std::int32_t y) {
    return (static_cast<std::uint64_t>(static_cast<std::uint32_t>(x)) << 32)
        | static_cast<std::uint32_t>(y);
}

// LC 835 kernel: unique occupied coordinates, with each translation in int32_t.
inline int maximumTranslationOverlap(const std::vector<std::array<int, 2>>& first,
                                     const std::vector<std::array<int, 2>>& second) {
    std::unordered_map<std::uint64_t, int> counts;
    int result = 0;
    for (const auto& a : first) {
        for (const auto& b : second) {
            long long dx = static_cast<long long>(b[0]) - a[0];
            long long dy = static_cast<long long>(b[1]) - a[1];
            if (dx < INT32_MIN || dx > INT32_MAX || dy < INT32_MIN || dy > INT32_MAX) {
                throw std::invalid_argument("translation exceeds a signed 32-bit lane");
            }
            auto key = packSignedPair(static_cast<std::int32_t>(dx), static_cast<std::int32_t>(dy));
            result = std::max(result, ++counts[key]);
        }
    }
    return result;
}

// LC 836: [x1,y1,x2,y2], ordered corners; positive AREA is required.
inline bool rectanglesOverlap(const std::array<int, 4>& a, const std::array<int, 4>& b) {
    return std::max(a[0], b[0]) < std::min(a[2], b[2])
        && std::max(a[1], b[1]) < std::min(a[3], b[3]);
}

// LC 1401: ordered corners, |coordinates|<=10^9, 0<=radius<=10^9.
// Tangency counts. Cast BEFORE subtraction; squared distance can reach 8*10^18.
inline bool circleRectangleOverlap(int radius, int xCenter, int yCenter, const std::array<int, 4>& rectangle) {
    if (radius < 0 || radius > 1'000'000'000) { throw std::invalid_argument("radius outside supported bounds"); }
    long long dx = static_cast<long long>(xCenter) - std::clamp(xCenter, rectangle[0], rectangle[2]);
    long long dy = static_cast<long long>(yCenter) - std::clamp(yCenter, rectangle[1], rectangle[3]);
    return dx * dx + dy * dy <= 1LL * radius * radius;
}
} // namespace patterns
