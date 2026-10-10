#include "templates.hpp"
#include <algorithm>
#include <cassert>
#include <climits>
#include <iostream>
#include <random>
#include <stdexcept>
#include <type_traits>
#include <vector>

using namespace patterns::monotonic;

template <class Exception, class Function>
void expectThrow(Function function) {
    bool threw = false;
    try { function(); } catch (const Exception&) { threw = true; }
    assert(threw);
}

double sortedMedian(std::vector<int> nums) {
    std::sort(nums.begin(), nums.end());
    int n = static_cast<int>(nums.size());
    if (n % 2) return nums[n / 2];
    return (static_cast<double>(nums[n / 2 - 1]) + nums[n / 2]) / 2;
}

int main() {
    static_assert(!std::is_copy_constructible_v<IndexedMedian>);
    static_assert(!std::is_move_constructible_v<IndexedMedian>);
    assert(largestRectangle({2, 1, 5, 6, 2, 3}) == 10);
    assert(largestRectangle({INT_MAX, INT_MAX}) == 2LL * INT_MAX);
    assert(largestRectangle({}) == 0);
    expectThrow<std::invalid_argument>([] { largestRectangle({-1}); });
    assert(sumSubarrayMinimums({3, 1, 2, 4}) == 17);
    assert(sumSubarrayMinimums({2, 2}) == 6);
    assert(sumSubarrayMinimums({-1, -1}) == 1000000004);
    assert(shortestSubarrayAtLeast({84, -37, 32, 40, 95}, 167) == 3);
    assert(shortestSubarrayAtLeast({INT_MAX, INT_MAX}, 2LL * INT_MAX) == 2);
    assert(shortestSubarrayAtLeast({}, 0) == -1);
    expectThrow<std::invalid_argument>([] { slidingWindowMaximum({}, 0); });
    expectThrow<std::invalid_argument>([] { slidingWindowMaximum({1}, 2); });
    expectThrow<std::invalid_argument>([] { slidingWindowMedian({1}, 0); });
    StreamMedian stream;
    IndexedMedian indexed;
    expectThrow<std::out_of_range>([&] { stream.findMedian(); });
    expectThrow<std::out_of_range>([&] { indexed.findMedian(); });
    assert(!indexed.remove(4));
    indexed.push(4, INT_MAX);
    expectThrow<std::invalid_argument>([&] { indexed.push(4, 0); });
    indexed.push(5, INT_MIN);
    assert(indexed.findMedian() == -0.5);
    assert(indexed.remove(4));
    assert(indexed.findMedian() == INT_MIN);
    assert(indexed.remove(5));
    assert(indexed.size() == 0);
    indexed.push(4, 7);
    assert(indexed.findMedian() == 7);
    assert(indexed.remove(4));
    std::mt19937 random(84907480);
    for (int run = 0; run < 500; ++run) {
        int n = static_cast<int>(random() % 35);
        std::vector<int> nums(n);
        for (auto& num : nums) num = static_cast<int>(random() % 21) - 10;
        if (run == 1) nums = {INT_MIN, INT_MAX, INT_MAX, INT_MIN};
        n = static_cast<int>(nums.size());
        auto next = nextGreaterDistances(nums);
        for (int i = 0; i < n; ++i) {
            int expected = 0;
            for (int j = i + 1; j < n; ++j) {
                if (nums[j] > nums[i]) { expected = j - i; break; }
            }
            assert(next[i] == expected);
        }
        StockSpanner spanner;
        StreamMedian running;
        IndexedMedian dynamic;
        std::vector<int> prefix;
        for (int i = 0; i < n; ++i) {
            int span = 1;
            for (int j = i - 1; j >= 0 && nums[j] <= nums[i]; --j) ++span;
            assert(spanner.next(nums[i]) == span);
            prefix.push_back(nums[i]);
            running.addNum(nums[i]);
            dynamic.push(i, nums[i]);
            assert(running.findMedian() == sortedMedian(prefix));
            assert(dynamic.findMedian() == sortedMedian(prefix));
        }
        std::vector<int> order(n);
        for (int i = 0; i < n; ++i) order[i] = i;
        std::shuffle(order.begin(), order.end(), random);
        std::vector<bool> alive(n, true);
        for (int index : order) {
            assert(dynamic.remove(index));
            alive[index] = false;
            std::vector<int> left;
            for (int i = 0; i < n; ++i) if (alive[i]) left.push_back(nums[i]);
            assert(dynamic.size() == left.size());
            if (!left.empty()) assert(dynamic.findMedian() == sortedMedian(left));
        }
        long long expectedSum = 0;
        for (int i = 0; i < n; ++i) {
            int minimum = nums[i];
            for (int j = i; j < n; ++j) {
                minimum = std::min(minimum, nums[j]);
                expectedSum = (expectedSum + minimum) % 1000000007;
            }
        }
        expectedSum = (expectedSum + 1000000007) % 1000000007;
        assert(sumSubarrayMinimums(nums) == expectedSum);
        long long target = static_cast<int>(random() % 41) - 20;
        int best = n + 1;
        for (int i = 0; i < n; ++i) {
            long long sum = 0;
            for (int j = i; j < n; ++j) {
                sum += nums[j];
                if (sum >= target) best = std::min(best, j - i + 1);
            }
        }
        assert(shortestSubarrayAtLeast(nums, target) == (best == n + 1 ? -1 : best));
        for (int k = 1; k <= n; ++k) {
            auto maxima = slidingWindowMaximum(nums, k);
            auto medians = slidingWindowMedian(nums, k);
            for (int i = 0; i + k <= n; ++i) {
                assert(maxima[i] == *std::max_element(nums.begin() + i, nums.begin() + i + k));
                assert(medians[i] == sortedMedian({nums.begin() + i, nums.begin() + i + k}));
            }
        }
        std::vector<int> heights(n);
        for (auto& value : heights) value = static_cast<int>(random() % 12);
        long long area = 0;
        for (int i = 0; i < n; ++i) {
            int minimum = heights[i];
            for (int j = i; j < n; ++j) {
                minimum = std::min(minimum, heights[j]);
                area = std::max(area, 1LL * minimum * (j - i + 1));
            }
        }
        assert(largestRectangle(heights) == area);
    }
    std::cout << "monotonic-and-heaps: 500 seeded differential cases passed\n";
}
