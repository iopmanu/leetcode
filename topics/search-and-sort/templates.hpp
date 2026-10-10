#pragma once

#include <algorithm>
#include <numeric>
#include <stdexcept>
#include <vector>

namespace patterns::search {

// All vector APIs use signed indices; size must fit in int.
inline int lowerBound(const std::vector<int>& nums, int target) {
    int left = 0;
    int right = static_cast<int>(nums.size()) - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return left;
}

// Generalization of #35: change the discarded prefix from < to <=.
inline int upperBound(const std::vector<int>& nums, int target) {
    int left = 0;
    int right = static_cast<int>(nums.size()) - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] <= target) left = mid + 1;
        else right = mid - 1;
    }
    return left;
}

inline int binarySearch(const std::vector<int>& nums, int target) {
    int left = 0;
    int right = static_cast<int>(nums.size()) - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] == target) return mid;
        if (nums[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

// check is pure and false...false,true...true on [left,right].
// Require a feasible right endpoint; throws if that bracket is invalid.
template <class Predicate>
long long firstTrue(long long left, long long right, Predicate check) {
    if (left > right || !check(right)) {
        throw std::invalid_argument("firstTrue requires a feasible closed bracket");
    }
    while (left < right) {
        long long mid = std::midpoint(left, right);
        if (check(mid)) right = mid;
        else left = mid + 1;
    }
    return left;
}

// #1011 / #410: minimum capacity for at most groups nonempty contiguous
// groups of nonnegative values. Empty input has answer 0.
inline long long minLargestGroupSum(const std::vector<int>& nums, int groups) {
    if (groups <= 0) throw std::invalid_argument("groups must be positive");
    long long left = 0;
    long long right = 0;
    for (int num : nums) {
        if (num < 0) throw std::invalid_argument("values must be nonnegative");
        left = std::max(left, static_cast<long long>(num));
        right += num;
    }
    if (nums.empty()) return 0;
    auto canSplit = [&](long long guess) {
        int count = 1;
        long long current = 0;
        for (int num : nums) {
            if (current + num > guess) {
                if (count == groups) return false;
                ++count;
                current = 0;
            }
            current += num;
        }
        return true;
    };
    return firstTrue(left, right, canSplit);
}

inline int minEatingSpeed(const std::vector<int>& piles, long long hours) {
    if (hours < 0) throw std::invalid_argument("hours must be nonnegative");
    int maxPile = 0;
    long long nonempty = 0;
    for (int pile : piles) {
        if (pile < 0) throw std::invalid_argument("piles must be nonnegative");
        maxPile = std::max(maxPile, pile);
        nonempty += pile > 0;
    }
    if (hours < nonempty) throw std::invalid_argument("no feasible eating speed");
    if (maxPile == 0) return 0;
    auto canEat = [&](long long guess) {
        long long current = 0;
        for (int pile : piles) {
            current += pile / guess + (pile % guess != 0);
            if (current > hours) return false;
        }
        return true;
    };
    return static_cast<int>(firstTrue(1, maxPile, canEat));
}

// Distinct values only: locate rotation, binary search virtual sorted indices.
inline int searchRotated(const std::vector<int>& nums, int target) {
    int n = static_cast<int>(nums.size());
    if (n == 0) return -1;
    int left = 0;
    int right = n - 1;
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] > nums.back()) left = mid + 1;
        else right = mid;
    }
    int rotation = left;
    left = 0;
    right = n - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int realMid = static_cast<int>((static_cast<long long>(mid) + rotation) % n);
        if (nums[realMid] == target) return realMid;
        if (nums[realMid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

inline bool searchRotatedWithDuplicates(const std::vector<int>& nums, int target) {
    int left = 0;
    int right = static_cast<int>(nums.size()) - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] == target) return true;
        if (nums[left] == nums[mid] && nums[right] == nums[mid]) {
            ++left;
            --right;
        } else if (nums[left] <= nums[mid]) {
            if (nums[left] <= target && target < nums[mid]) right = mid - 1;
            else left = mid + 1;
        } else {
            if (nums[mid] < target && target <= nums[right]) left = mid + 1;
            else right = mid - 1;
        }
    }
    return false;
}

// Zero-based rank in ascending order. Mutates nums. Deterministic pivot.
inline int quickselect(std::vector<int>& nums, int k) {
    int n = static_cast<int>(nums.size());
    if (k < 0 || k >= n) throw std::out_of_range("rank must be in [0,n)");
    int left = 0;
    int right = n - 1;
    while (left < right) {
        int i = left;
        int j = right;
        int pivot = nums[left + (right - left) / 2];
        while (i <= j) {
            while (nums[i] < pivot) ++i;
            while (nums[j] > pivot) --j;
            if (i <= j) std::swap(nums[i++], nums[j--]);
        }
        if (k <= j) right = j;
        else if (k >= i) left = i;
        else return nums[k];
    }
    return nums[k];
}

inline int kthLargest(std::vector<int>& nums, int k) {
    int n = static_cast<int>(nums.size());
    if (k < 1 || k > n) throw std::out_of_range("k must be in [1,n]");
    return quickselect(nums, n - k);
}

namespace detail {
inline long long mergeCount(std::vector<int>& nums, int left, int right, bool countPairs) {
    if (left >= right) return 0;
    int mid = left + (right - left) / 2;
    long long result = mergeCount(nums, left, mid, countPairs)
                     + mergeCount(nums, mid + 1, right, countPairs);
    std::vector<int> lhs(nums.begin() + left, nums.begin() + mid + 1);
    std::vector<int> rhs(nums.begin() + mid + 1, nums.begin() + right + 1);
    int n1 = static_cast<int>(lhs.size());
    int n2 = static_cast<int>(rhs.size());
    int i = 0;
    int j = 0;
    if (countPairs) {
        while (i < n1 && j < n2) {
            if (lhs[i] > 2LL * rhs[j]) { result += n1 - i; ++j; }
            else ++i;
        }
    }
    i = 0;
    j = 0;
    int k = left;
    while (i < n1 && j < n2) {
        if (lhs[i] <= rhs[j]) nums[k++] = lhs[i++];
        else nums[k++] = rhs[j++];
    }
    while (i < n1) nums[k++] = lhs[i++];
    while (j < n2) nums[k++] = rhs[j++];
    return result;
}
}  // namespace detail

inline void mergeSort(std::vector<int>& nums) {
    detail::mergeCount(nums, 0, static_cast<int>(nums.size()) - 1, false);
}

// Count original i<j with nums[i]>2*nums[j]; nums is sorted on return.
inline long long countReversePairs(std::vector<int>& nums) {
    return detail::mergeCount(nums, 0, static_cast<int>(nums.size()) - 1, true);
}

}  // namespace patterns::search
