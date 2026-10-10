#pragma once

#include <algorithm>
#include <deque>
#include <functional>
#include <queue>
#include <set>
#include <stack>
#include <stdexcept>
#include <unordered_map>
#include <utility>
#include <vector>

namespace patterns::monotonic {

// Vector sizes and index differences must fit in int.
inline std::vector<int> nextGreaterDistances(const std::vector<int>& nums) {
    std::stack<int> positions;
    std::vector<int> result(nums.size(), 0);
    for (int i = 0; i < static_cast<int>(nums.size()); ++i) {
        while (!positions.empty() && nums[positions.top()] < nums[i]) {
            result[positions.top()] = i - positions.top();
            positions.pop();
        }
        positions.push(i);
    }
    return result;
}

inline long long largestRectangle(const std::vector<int>& heights) {
    for (int height : heights) {
        if (height < 0) throw std::invalid_argument("heights must be nonnegative");
    }
    std::stack<int> positions;
    long long result = 0;
    int n = static_cast<int>(heights.size());
    for (int i = 0; i <= n; ++i) {
        while (!positions.empty() && (i == n || heights[positions.top()] > heights[i])) {
            int pivot = positions.top();
            positions.pop();
            int left = positions.empty() ? -1 : positions.top();
            result = std::max(result, 1LL * heights[pivot] * (i - (left + 1)));
        }
        if (i < n) positions.push(i);
        else break;
    }
    return result;
}

class StockSpanner {
    std::stack<std::pair<int, long long>> values;
public:
    long long next(int price) {
        long long days = 1;
        while (!values.empty() && values.top().first <= price) {
            days += values.top().second;
            values.pop();
        }
        values.push(std::make_pair(price, days));
        return days;
    }
};

// Previous <=, next < gives each equal-minimum subarray one owner.
inline int sumSubarrayMinimums(const std::vector<int>& nums) {
    constexpr long long mod = 1'000'000'007;
    long long result = 0;
    std::deque<int> positions;
    int n = static_cast<int>(nums.size());
    for (int i = 0; i <= n; ++i) {
        while (!positions.empty() && (i == n || nums[i] < nums[positions.back()])) {
            int index = positions.back();
            positions.pop_back();
            int left = positions.empty() ? -1 : positions.back();
            long long value = (static_cast<long long>(nums[index]) % mod + mod) % mod;
            long long contribution = value * (index - left) % mod * (i - index) % mod;
            result = (result + contribution) % mod;
        }
        if (i < n) positions.push_back(i);
        else break;
    }
    return static_cast<int>(result);
}

// #239 is a heap in the observed source. Expired buried entries remain.
inline std::vector<int> slidingWindowMaximum(const std::vector<int>& nums, int k) {
    int n = static_cast<int>(nums.size());
    if (k < 1 || k > n) throw std::invalid_argument("window must be in [1,n]");
    std::priority_queue<std::pair<int, int>> heap;
    std::vector<int> result;
    for (int i = 0; i < n; ++i) {
        heap.push(std::make_pair(nums[i], i));
        while (heap.top().second <= i - k) heap.pop();
        if (i >= k - 1) result.push_back(heap.top().first);
    }
    return result;
}

// Source orientation: newest candidate at front, oldest/minimum at back.
// Returns the shortest NONEMPTY subarray length, or -1.
inline int shortestSubarrayAtLeast(const std::vector<int>& nums, long long target) {
    int n = static_cast<int>(nums.size());
    std::vector<long long> prefixes(nums.size() + 1, 0);
    for (int i = 0; i < n; ++i) prefixes[i + 1] = prefixes[i] + nums[i];
    std::deque<int> positions;
    int result = -1;
    for (int i = 0; i <= n; ++i) {
        while (!positions.empty() && prefixes[i] - prefixes[positions.back()] >= target) {
            int length = i - positions.back();
            if (result == -1 || length < result) result = length;
            positions.pop_back();
        }
        while (!positions.empty() && prefixes[i] <= prefixes[positions.front()]) {
            positions.pop_front();
        }
        positions.push_front(i);
        if (i == n) break;
    }
    return result;
}

class StreamMedian {
    std::priority_queue<int> leftHeap;
    std::priority_queue<int, std::vector<int>, std::greater<int>> rightHeap;
public:
    void addNum(int num) {
        if (leftHeap.empty() || num < leftHeap.top()) leftHeap.push(num);
        else rightHeap.push(num);
        if (leftHeap.size() > rightHeap.size() + 1) {
            rightHeap.push(leftHeap.top());
            leftHeap.pop();
        } else if (rightHeap.size() > leftHeap.size()) {
            leftHeap.push(rightHeap.top());
            rightHeap.pop();
        }
    }
    double findMedian() const {
        if (leftHeap.empty()) throw std::out_of_range("median of an empty stream");
        if (leftHeap.size() == rightHeap.size()) {
            return (static_cast<double>(leftHeap.top()) + rightHeap.top()) / 2.0;
        }
        return leftHeap.top();
    }
};

// #480: two ordered multisets with index -> iterator maps, not lazy heaps.
// Live indices are unique. remove(missing) is a no-op returning false.
class IndexedMedian {
    using LeftSet = std::multiset<std::pair<int, int>, std::greater<std::pair<int, int>>>;
    using RightSet = std::multiset<std::pair<int, int>>;
    LeftSet leftHeap;
    RightSet rightHeap;
    std::unordered_map<int, LeftSet::iterator> leftMapping;
    std::unordered_map<int, RightSet::iterator> rightMapping;

    void balance() {
        if (leftHeap.size() > rightHeap.size() + 1) {
            auto node = *leftHeap.begin();
            leftHeap.erase(leftHeap.begin());
            leftMapping.erase(node.second);
            rightMapping[node.second] = rightHeap.insert(node);
        } else if (rightHeap.size() > leftHeap.size()) {
            auto node = *rightHeap.begin();
            rightHeap.erase(rightHeap.begin());
            rightMapping.erase(node.second);
            leftMapping[node.second] = leftHeap.insert(node);
        }
    }
public:
    IndexedMedian() = default;
    IndexedMedian(const IndexedMedian&) = delete;
    IndexedMedian& operator=(const IndexedMedian&) = delete;
    IndexedMedian(IndexedMedian&&) = delete;
    IndexedMedian& operator=(IndexedMedian&&) = delete;

    void push(int index, int num) {
        if (leftMapping.contains(index) || rightMapping.contains(index)) {
            throw std::invalid_argument("live index must be unique");
        }
        if (leftHeap.empty() || num <= leftHeap.begin()->first) {
            leftMapping[index] = leftHeap.insert(std::make_pair(num, index));
        } else {
            rightMapping[index] = rightHeap.insert(std::make_pair(num, index));
        }
        balance();
    }
    bool remove(int index) {
        auto left = leftMapping.find(index);
        auto right = rightMapping.find(index);
        if (left != leftMapping.end()) {
            leftHeap.erase(left->second);
            leftMapping.erase(left);
        } else if (right != rightMapping.end()) {
            rightHeap.erase(right->second);
            rightMapping.erase(right);
        } else return false;
        balance();
        return true;
    }
    std::size_t size() const { return leftHeap.size() + rightHeap.size(); }
    double findMedian() const {
        if (leftHeap.empty()) throw std::out_of_range("median of an empty collection");
        if (leftHeap.size() == rightHeap.size()) {
            return (static_cast<double>(leftHeap.begin()->first) + rightHeap.begin()->first) / 2.0;
        }
        return leftHeap.begin()->first;
    }
};

inline std::vector<double> slidingWindowMedian(const std::vector<int>& nums, int k) {
    int n = static_cast<int>(nums.size());
    if (k < 1 || k > n) throw std::invalid_argument("window must be in [1,n]");
    IndexedMedian finder;
    std::vector<double> result;
    for (int i = 0; i < n; ++i) {
        finder.push(i, nums[i]);
        if (i >= k) finder.remove(i - k);
        if (i >= k - 1) result.push_back(finder.findMedian());
    }
    return result;
}

}  // namespace patterns::monotonic
