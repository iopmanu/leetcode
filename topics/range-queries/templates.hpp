#ifndef PATTERNS_RANGE_QUERIES_HPP
#define PATTERNS_RANGE_QUERIES_HPP

#include <algorithm>
#include <array>
#include <cstddef>
#include <limits>
#include <stdexcept>
#include <utility>
#include <vector>

namespace patterns {
namespace detailRangeQueries {
// Keeping 4*n and zero-root child indices in int is an explicit size contract.
inline int checkedSize(std::size_t size) {
    if (size > static_cast<std::size_t>(std::numeric_limits<int>::max() / 4)) {
        throw std::length_error("range structure is too large for int node indices");
    }
    return static_cast<int>(size);
}
inline std::vector<long long> filled(int n, long long value) {
    if (n < 0) throw std::invalid_argument("negative size");
    checkedSize(static_cast<std::size_t>(n));
    return std::vector<long long>(n, value);
}
inline void checkIndex(int index, int n) {
    if (index < 0 || index >= n) throw std::out_of_range("invalid index");
}
inline void checkRange(int l, int r, int n) {
    // The caller handles l > r as the empty interval before this check.
    if (l < 0 || r >= n) throw std::out_of_range("invalid inclusive range");
}
inline int checkedModulus(int k) {
    if (k <= 0) throw std::invalid_argument("modulus must be positive");
    return k;
}
inline int remainder(long long value, int k) {
    int result = static_cast<int>(value % k);
    return result < 0 ? result + k : result;
}
}  // namespace detailRangeQueries

// 307: public indices are zero-based; internal Fenwick cells are one-based.
// All cell sums, prefix sums, values, update deltas and returned differences
// must fit long long. This is a numeric precondition, not saturating arithmetic.
struct FenwickSum {
    explicit FenwickSum(int size)
        : FenwickSum(detailRangeQueries::filled(size, 0)) {}

    explicit FenwickSum(const std::vector<long long>& nums)
        : n(detailRangeQueries::checkedSize(nums.size())), tree(n + 1), arr(nums) {
        for (int i = 0; i < n; ++i) tree[i + 1] = arr[i];
        // O(n) construction: every cell forwards its accumulated block once.
        for (int i = 1; i <= n; ++i) {
            int parent = i + (i & -i);
            if (parent <= n) tree[parent] += tree[i];
        }
    }

    void add(int index, long long delta) {
        detailRangeQueries::checkIndex(index, n);
        arr[index] += delta;
        for (++index; index <= n; index += index & -index) tree[index] += delta;
    }

    void update(int index, long long value) {
        detailRangeQueries::checkIndex(index, n);
        long long delta = value - arr[index];
        add(index, delta);
    }

    long long query(int index) const {
        if (index < -1 || index >= n) throw std::out_of_range("invalid prefix end");
        long long sum = 0;
        for (++index; index > 0; index -= index & -index) sum += tree[index];
        return sum;
    }

    long long sumRange(int l, int r) const {
        if (l > r) return 0;
        detailRangeQueries::checkRange(l, r, n);
        return query(r) - query(l - 1);
    }

private:
    int n;
    std::vector<long long> tree;
    std::vector<long long> arr;
};

// 406: count tree; kth is zero-based and does not mutate, updateAndFind
// removes one occurrence. Invalid ranks return -1 without any mutation.
struct OrderStatisticTree {
    explicit OrderStatisticTree(int size)
        : OrderStatisticTree(detailRangeQueries::filled(size, 1)) {}

    explicit OrderStatisticTree(const std::vector<long long>& frequencies)
        : n(detailRangeQueries::checkedSize(frequencies.size())), tree(4 * n), counts(frequencies) {
        long long sum = 0;
        for (long long count : counts) {
            if (count < 0) throw std::invalid_argument("negative count");
            if (count > std::numeric_limits<long long>::max() - sum) {
                throw std::overflow_error("total count overflows");
            }
            sum += count;
        }
        if (n > 0) build(0, 0, n - 1);
    }

    long long total() const { return n == 0 ? 0 : tree[0]; }

    int kth(long long k) const {
        if (k < 0 || k >= total()) return -1;
        return find(0, 0, n - 1, k);
    }

    int updateAndFind(long long k) {
        int index = kth(k);
        if (index >= 0) add(index, -1);
        return index;
    }

    void add(int index, long long delta) {
        detailRangeQueries::checkIndex(index, n);
        if (delta < 0 && delta < -counts[index]) throw std::invalid_argument("count would be negative");
        if (delta > 0 && total() > std::numeric_limits<long long>::max() - delta) {
            throw std::overflow_error("total count overflows");
        }
        counts[index] += delta;
        add(0, 0, n - 1, index, delta);
    }

private:
    int n;
    std::vector<long long> tree;
    std::vector<long long> counts;

    void build(int node, int start, int end) {
        if (start == end) { tree[node] = counts[start]; return; }
        int m = start + (end - start) / 2;
        build(2 * node + 1, start, m);
        build(2 * node + 2, m + 1, end);
        tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
    }

    int find(int node, int start, int end, long long k) const {
        if (start == end) return start;
        int m = start + (end - start) / 2;
        long long leftCount = tree[2 * node + 1];
        if (leftCount > k) return find(2 * node + 1, start, m, k);
        return find(2 * node + 2, m + 1, end, k - leftCount);
    }

    void add(int node, int start, int end, int index, long long delta) {
        tree[node] += delta;
        if (start == end) return;
        int m = start + (end - start) / 2;
        if (index <= m) add(2 * node + 1, start, m, index, delta);
        else add(2 * node + 2, m + 1, end, index, delta);
    }
};

// 699: range ASSIGNMENT, range MAXIMUM. A flag distinguishes an absent tag
// from an assignment of zero, a negative value, or LLONG_MIN.
struct RangeAssignMaxTree {
    explicit RangeAssignMaxTree(int size, long long initialValue = 0)
        : RangeAssignMaxTree(detailRangeQueries::filled(size, initialValue)) {}

    explicit RangeAssignMaxTree(const std::vector<long long>& nums)
        : n(detailRangeQueries::checkedSize(nums.size())), tree(4 * n), lazy(4 * n), hasLazy(4 * n) {
        if (n > 0) build(0, 0, n - 1, nums);
    }

    void update(int l, int r, long long value) {
        if (l > r) return;
        detailRangeQueries::checkRange(l, r, n);
        update(0, 0, n - 1, l, r, value);
    }

    long long query(int l, int r) {
        if (l > r) return std::numeric_limits<long long>::lowest();
        detailRangeQueries::checkRange(l, r, n);
        return query(0, 0, n - 1, l, r);
    }

private:
    int n;
    std::vector<long long> tree;
    std::vector<long long> lazy;
    std::vector<unsigned char> hasLazy;

    void build(int node, int start, int end, const std::vector<long long>& nums) {
        if (start == end) { tree[node] = nums[start]; return; }
        int m = start + (end - start) / 2;
        build(2 * node + 1, start, m, nums);
        build(2 * node + 2, m + 1, end, nums);
        tree[node] = std::max(tree[2 * node + 1], tree[2 * node + 2]);
    }

    void apply(int node, long long value) {
        tree[node] = value;
        lazy[node] = value;
        hasLazy[node] = 1;
    }

    // Called only on a non-leaf before partial descent.
    void push(int node) {
        if (!hasLazy[node]) return;
        apply(2 * node + 1, lazy[node]);
        apply(2 * node + 2, lazy[node]);
        hasLazy[node] = 0;
    }

    void update(int node, int start, int end, int l, int r, long long value) {
        if (r < start || end < l) return;
        if (l <= start && end <= r) { apply(node, value); return; }
        push(node);
        int m = start + (end - start) / 2;
        update(2 * node + 1, start, m, l, r, value);
        update(2 * node + 2, m + 1, end, l, r, value);
        tree[node] = std::max(tree[2 * node + 1], tree[2 * node + 2]);
    }

    long long query(int node, int start, int end, int l, int r) {
        if (r < start || end < l) return std::numeric_limits<long long>::lowest();
        if (l <= start && end <= r) return tree[node];
        push(node);
        int m = start + (end - start) / 2;
        return std::max(query(2 * node + 1, start, m, l, r),
                        query(2 * node + 2, m + 1, end, l, r));
    }
};

// 315: immutable array. Each tree node stores its segment in sorted order.
// query(l,r,value) counts elements strictly less than value in [l,r].
template <typename T>
struct MergeSortTree {
    explicit MergeSortTree(const std::vector<T>& nums)
        : n(detailRangeQueries::checkedSize(nums.size())), tree(4 * n) {
        if (n > 0) build(0, 0, n - 1, nums);
    }

    int query(int l, int r, const T& value) const {
        if (l > r) return 0;
        detailRangeQueries::checkRange(l, r, n);
        return query(0, 0, n - 1, l, r, value);
    }

private:
    int n;
    std::vector<std::vector<T>> tree;

    void build(int node, int start, int end, const std::vector<T>& nums) {
        if (start == end) { tree[node] = {nums[start]}; return; }
        int m = start + (end - start) / 2;
        build(2 * node + 1, start, m, nums);
        build(2 * node + 2, m + 1, end, nums);
        const auto& left = tree[2 * node + 1];
        const auto& right = tree[2 * node + 2];
        tree[node].resize(left.size() + right.size());
        std::merge(left.begin(), left.end(), right.begin(), right.end(), tree[node].begin());
    }

    int query(int node, int start, int end, int l, int r, const T& value) const {
        if (r < start || end < l) return 0;
        if (l <= start && end <= r) {
            return static_cast<int>(std::lower_bound(tree[node].begin(), tree[node].end(), value)
                                    - tree[node].begin());
        }
        int m = start + (end - start) / 2;
        return query(2 * node + 1, start, m, l, r, value)
             + query(2 * node + 2, m + 1, end, l, r, value);
    }
};

// 3525: counts products of NONEMPTY prefixes of a queried interval modulo k.
// merge(left,right) is associative, but MUST preserve left-to-right order.
struct ProductPrefixTree {
    struct Aggregate {
        int product;
        std::vector<long long> counts;
    };

    ProductPrefixTree(const std::vector<long long>& nums, int modulus)
        : n(detailRangeQueries::checkedSize(nums.size())), k(detailRangeQueries::checkedModulus(modulus)),
          tree(4 * n) {
        if (n > 0) build(0, 0, n - 1, nums);
    }

    void update(int index, long long value) {
        detailRangeQueries::checkIndex(index, n);
        update(0, 0, n - 1, index, value);
    }

    Aggregate query(int l, int r) const {
        if (l > r) return identity();
        detailRangeQueries::checkRange(l, r, n);
        return query(0, 0, n - 1, l, r);
    }

private:
    int n;
    int k;
    std::vector<Aggregate> tree;

    Aggregate identity() const { return {1 % k, std::vector<long long>(k)}; }

    Aggregate makeLeaf(long long value) const {
        Aggregate result = identity();
        result.product = detailRangeQueries::remainder(value, k);
        result.counts[result.product] = 1;
        return result;
    }

    Aggregate mergePre(const Aggregate& left, const Aggregate& right) const {
        Aggregate result = identity();
        result.product = static_cast<int>(1LL * left.product * right.product % k);
        for (int x = 0; x < k; ++x) result.counts[x] = left.counts[x];
        for (int x = 0; x < k; ++x) {
            int remainder = static_cast<int>(1LL * left.product * x % k);
            result.counts[remainder] += right.counts[x];
        }
        return result;
    }

    void build(int node, int start, int end, const std::vector<long long>& nums) {
        if (start == end) { tree[node] = makeLeaf(nums[start]); return; }
        int m = start + (end - start) / 2;
        build(2 * node + 1, start, m, nums);
        build(2 * node + 2, m + 1, end, nums);
        tree[node] = mergePre(tree[2 * node + 1], tree[2 * node + 2]);
    }

    void update(int node, int start, int end, int index, long long value) {
        if (start == end) { tree[node] = makeLeaf(value); return; }
        int m = start + (end - start) / 2;
        if (index <= m) update(2 * node + 1, start, m, index, value);
        else update(2 * node + 2, m + 1, end, index, value);
        tree[node] = mergePre(tree[2 * node + 1], tree[2 * node + 2]);
    }

    Aggregate query(int node, int start, int end, int l, int r) const {
        if (r < start || end < l) return identity();
        if (l <= start && end <= r) return tree[node];
        int m = start + (end - start) / 2;
        Aggregate left = query(2 * node + 1, start, m, l, r);
        Aggregate right = query(2 * node + 2, m + 1, end, l, r);
        return mergePre(left, right);
    }
};

// 327 adaptation: unique coordinates with true frequencies; remove the current
// prefix, then count strictly future prefixes in [current+lower,current+upper].
inline long long countRangeSum(const std::vector<int>& nums, int lower, int upper) {
    if (lower > upper) return 0;
    int n = detailRangeQueries::checkedSize(nums.size());
    std::vector<long long> prefix(n + 1);
    for (int i = 0; i < n; ++i) prefix[i + 1] = prefix[i] + nums[i];
    std::vector<long long> sorted(prefix);
    std::sort(sorted.begin(), sorted.end());
    sorted.erase(std::unique(sorted.begin(), sorted.end()), sorted.end());
    std::vector<long long> frequencies(sorted.size());
    for (long long value : prefix) {
        int index = static_cast<int>(std::lower_bound(sorted.begin(), sorted.end(), value) - sorted.begin());
        ++frequencies[index];
    }
    FenwickSum tree(frequencies);
    long long result = 0;
    for (long long value : prefix) {
        int index = static_cast<int>(std::lower_bound(sorted.begin(), sorted.end(), value) - sorted.begin());
        tree.add(index, -1);
        int l = static_cast<int>(std::lower_bound(sorted.begin(), sorted.end(), value + lower) - sorted.begin());
        int r = static_cast<int>(std::upper_bound(sorted.begin(), sorted.end(), value + upper) - sorted.begin()) - 1;
        result += tree.sumRange(l, r);
    }
    return result;
}

// 699 adaptation: each leaf represents [coords[i], coords[i+1]); touching
// squares share no cells. Input int coordinates/sides are widened before sum.
inline std::vector<long long> fallingSquares(const std::vector<std::array<int, 2>>& squares) {
    detailRangeQueries::checkedSize(squares.size());
    if (squares.empty()) return {};
    std::vector<long long> coords;
    for (const auto& square : squares) {
        if (square[1] <= 0) throw std::invalid_argument("square side must be positive");
        coords.push_back(square[0]);
        coords.push_back(1LL * square[0] + square[1]);
    }
    std::sort(coords.begin(), coords.end());
    coords.erase(std::unique(coords.begin(), coords.end()), coords.end());
    int cells = detailRangeQueries::checkedSize(coords.size() - 1);
    RangeAssignMaxTree tree(cells);
    std::vector<long long> result;
    for (const auto& square : squares) {
        int l = static_cast<int>(std::lower_bound(coords.begin(), coords.end(), square[0]) - coords.begin());
        int r = static_cast<int>(std::lower_bound(coords.begin(), coords.end(),
                                                1LL * square[0] + square[1]) - coords.begin()) - 1;
        long long top = tree.query(l, r) + square[1];
        tree.update(l, r, top);
        result.push_back(tree.query(0, cells - 1));
    }
    return result;
}

// 3524: rolling DP over all subarrays ending at the current index.
inline std::vector<long long> countProductRemainders(const std::vector<long long>& nums, int k) {
    detailRangeQueries::checkedModulus(k);
    detailRangeQueries::checkedSize(nums.size());
    std::vector<long long> result(k), dp(k);
    for (long long value : nums) {
        int x = detailRangeQueries::remainder(value, k);
        std::vector<long long> next(k);
        ++next[x];
        for (int r = 0; r < k; ++r) {
            int product = static_cast<int>(1LL * r * x % k);
            next[product] += dp[r];
        }
        dp = std::move(next);
        for (int r = 0; r < k; ++r) result[r] += dp[r];
    }
    return result;
}

}  // namespace patterns
#endif  // PATTERNS_RANGE_QUERIES_HPP
