#include "templates.hpp"
#include <algorithm>
#include <cassert>
#include <climits>
#include <iostream>
#include <numeric>
#include <random>
#include <stdexcept>
#include <vector>

using namespace patterns::search;

template <class Exception, class Function>
void expectThrow(Function function) {
    bool threw = false;
    try { function(); } catch (const Exception&) { threw = true; }
    assert(threw);
}

int main() {
    std::vector<int> empty;
    assert(lowerBound(empty, 3) == 0);
    assert(upperBound(empty, 3) == 0);
    assert(binarySearch(empty, 3) == -1);
    assert(searchRotated(empty, 3) == -1);
    assert(!searchRotatedWithDuplicates(empty, 3));
    expectThrow<std::out_of_range>([&] { kthLargest(empty, 1); });
    expectThrow<std::out_of_range>([&] { quickselect(empty, 0); });
    expectThrow<std::invalid_argument>([] { firstTrue(2, 1, [](long long) { return true; }); });
    expectThrow<std::invalid_argument>([] { firstTrue(0, 2, [](long long) { return false; }); });
    assert(firstTrue(LLONG_MIN, LLONG_MAX, [](long long x) { return x >= 17; }) == 17);
    assert(firstTrue(LLONG_MIN, LLONG_MAX, [](long long x) { return x == LLONG_MAX; }) == LLONG_MAX);
    assert(minLargestGroupSum({INT_MAX, INT_MAX}, 1) == 2LL * INT_MAX);
    assert(minLargestGroupSum({}, 1) == 0);
    expectThrow<std::invalid_argument>([] { minLargestGroupSum({1}, 0); });
    expectThrow<std::invalid_argument>([] { minLargestGroupSum({1, -1}, 1); });
    assert(lowerBound({INT_MIN, INT_MAX}, INT_MIN) == 0);
    assert(upperBound({INT_MIN, INT_MAX}, INT_MAX) == 2);
    assert(minEatingSpeed({3, 6, 7, 11}, 8) == 4);
    assert(minEatingSpeed({}, 0) == 0);
    expectThrow<std::invalid_argument>([] { minEatingSpeed({1, 2}, 1); });
    expectThrow<std::invalid_argument>([] { minEatingSpeed({-1}, 1); });
    expectThrow<std::invalid_argument>([] { minEatingSpeed({1}, -1); });
    std::mt19937 random(215493);
    for (int run = 0; run < 600; ++run) {
        int n = static_cast<int>(random() % 40);
        std::vector<int> nums(n);
        for (auto& num : nums) num = static_cast<int>(random() % 21) - 10;
        if (run == 1) nums = {INT_MIN, INT_MAX, INT_MIN, INT_MAX};
        n = static_cast<int>(nums.size());
        auto sorted = nums;
        std::sort(sorted.begin(), sorted.end());
        for (int target = -12; target <= 12; ++target) {
            assert(lowerBound(sorted, target) == std::lower_bound(sorted.begin(), sorted.end(), target) - sorted.begin());
            assert(upperBound(sorted, target) == std::upper_bound(sorted.begin(), sorted.end(), target) - sorted.begin());
            int found = binarySearch(sorted, target);
            assert((found != -1) == std::binary_search(sorted.begin(), sorted.end(), target));
            if (found != -1) assert(sorted[found] == target);
        }
        for (int k = 0; k < n; ++k) {
            auto copy = nums;
            assert(quickselect(copy, k) == sorted[k]);
            copy = nums;
            assert(kthLargest(copy, n - k) == sorted[k]);
        }
        expectThrow<std::out_of_range>([&] { quickselect(nums, n); });
        expectThrow<std::out_of_range>([&] { kthLargest(nums, 0); });
        long long expectedPairs = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) expectedPairs += nums[i] > 2LL * nums[j];
        }
        auto copy = nums;
        assert(countReversePairs(copy) == expectedPairs);
        assert(copy == sorted);
        copy = nums;
        mergeSort(copy);
        assert(copy == sorted);
        if (n > 0) std::rotate(sorted.begin(), sorted.begin() + random() % n, sorted.end());
        for (int target = -12; target <= 12; ++target) {
            assert(searchRotatedWithDuplicates(sorted, target) == (std::find(nums.begin(), nums.end(), target) != nums.end()));
        }
        std::vector<int> distinct(n);
        std::iota(distinct.begin(), distinct.end(), -n / 2);
        if (n > 0) std::rotate(distinct.begin(), distinct.begin() + random() % n, distinct.end());
        for (int target = -n - 1; target <= n + 1; ++target) {
            auto it = std::find(distinct.begin(), distinct.end(), target);
            int expected = it == distinct.end() ? -1 : static_cast<int>(it - distinct.begin());
            assert(searchRotated(distinct, target) == expected);
        }
        std::vector<int> positive(1 + random() % 8);
        for (auto& num : positive) num = static_cast<int>(random() % 8);
        int groups = 1 + static_cast<int>(random() % 10);
        long long brute = *std::max_element(positive.begin(), positive.end());
        for (;; ++brute) {
            int count = 1;
            long long sum = 0;
            for (int num : positive) {
                if (sum + num > brute) { ++count; sum = 0; }
                sum += num;
            }
            if (count <= groups) break;
        }
        assert(minLargestGroupSum(positive, groups) == brute);
        // Independent exhaustive partition DP validates greedy feasibility.
        int length = static_cast<int>(positive.size());
        std::vector<std::vector<long long>> dp(length + 1, std::vector<long long>(length + 1, LLONG_MAX));
        dp[0][0] = 0;
        for (int end = 1; end <= length; ++end) {
            for (int count = 1; count <= end; ++count) {
                long long sum = 0;
                for (int start = end - 1; start >= 0; --start) {
                    sum += positive[start];
                    if (dp[start][count - 1] != LLONG_MAX) {
                        dp[end][count] = std::min(dp[end][count], std::max(dp[start][count - 1], sum));
                    }
                }
            }
        }
        long long expectedCapacity = LLONG_MAX;
        for (int count = 1; count <= std::min(groups, length); ++count) {
            expectedCapacity = std::min(expectedCapacity, dp[length][count]);
        }
        assert(minLargestGroupSum(positive, groups) == expectedCapacity);
        long long hours = static_cast<long long>(positive.size()) + random() % 12;
        int speed = *std::max_element(positive.begin(), positive.end()) == 0 ? 0 : 1;
        for (; speed > 0; ++speed) {
            long long used = 0;
            for (int num : positive) used += num / speed + (num % speed != 0);
            if (used <= hours) break;
        }
        assert(minEatingSpeed(positive, hours) == speed);
    }
    std::cout << "search-and-sort: 600 seeded differential cases passed\n";
}
