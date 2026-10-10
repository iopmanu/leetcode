#include "templates.hpp"

#include <algorithm>
#include <array>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <numeric>
#include <random>
#include <stdexcept>
#include <string>
#include <vector>

namespace {
void require(bool condition, const char* message) {
    if (!condition) throw std::runtime_error(message);
}
template <typename Exception, typename Function>
void requireThrows(Function function) {
    bool caught = false;
    try { function(); } catch (const Exception&) { caught = true; }
    require(caught, "expected checked contract failure");
}
long long sum(const std::vector<long long>& values, int l, int r) {
    long long result = 0;
    for (int i = l; i <= r; ++i) result += values[i];
    return result;
}
void testFenwick() {
    patterns::FenwickSum tree(std::vector<long long>{1, 3, 5});
    require(tree.sumRange(0, 2) == 9, "Fenwick linear build");
    require(tree.query(-1) == 0, "Fenwick empty prefix");
    tree.update(1, 2);
    tree.add(0, -4);
    require(tree.sumRange(0, 2) == 4, "Fenwick assignment plus addition");
    tree.update(0, 7);
    require(tree.query(0) == 7, "Fenwick assignment uses current value after add");
    require(tree.sumRange(2, 1) == 0, "Fenwick empty interval");
    patterns::FenwickSum empty(0);
    require(empty.query(-1) == 0 && empty.sumRange(0, -1) == 0, "empty Fenwick");
    requireThrows<std::out_of_range>([&] { empty.add(0, 1); });
    requireThrows<std::out_of_range>([&] { tree.query(-2); });
    requireThrows<std::out_of_range>([&] { tree.query(3); });
    requireThrows<std::out_of_range>([&] { tree.update(-1, 0); });
    requireThrows<std::invalid_argument>([] { patterns::FenwickSum bad(-1); });
    requireThrows<std::length_error>([] {
        patterns::FenwickSum bad(std::numeric_limits<int>::max());
    });
    patterns::FenwickSum wide(std::vector<long long>{3000000000LL, 4000000000LL});
    require(wide.query(1) == 7000000000LL, "Fenwick wide sum");
    std::mt19937 random(307);
    for (int n = 1; n <= 65; ++n) {
        std::vector<long long> values(n);
        for (auto& value : values) value = static_cast<int>(random() % 101) - 50;
        patterns::FenwickSum current(values);
        for (int step = 0; step < 500; ++step) {
            int index = static_cast<int>(random() % n);
            long long value = static_cast<int>(random() % 101) - 50;
            if (step % 3 == 0) { current.add(index, value); values[index] += value; }
            if (step % 3 == 1) { current.update(index, value); values[index] = value; }
            int l = static_cast<int>(random() % n), r = static_cast<int>(random() % n);
            if (l > r) std::swap(l, r);
            require(current.query(r) == sum(values, 0, r), "random Fenwick prefix");
            require(current.sumRange(l, r) == sum(values, l, r), "random Fenwick range");
        }
    }
}
void testOrderStatistics() {
    patterns::OrderStatisticTree tree(5);
    require(tree.total() == 5 && tree.kth(2) == 2, "order statistic initial counts");
    require(tree.updateAndFind(2) == 2 && tree.total() == 4, "destructive selection");
    require(tree.kth(2) == 3, "selection skips exhausted positions");
    require(tree.kth(-1) == -1 && tree.updateAndFind(4) == -1 && tree.total() == 4,
            "invalid rank leaves counts unchanged");
    patterns::OrderStatisticTree weighted(std::vector<long long>{2, 0, 3});
    require(weighted.kth(1) == 0 && weighted.kth(2) == 2, "weighted count selection");
    weighted.add(1, 2);
    require(weighted.kth(3) == 1 && weighted.total() == 7, "count add");
    requireThrows<std::invalid_argument>([&] { weighted.add(0, -3); });
    require(weighted.total() == 7, "rejected count change is atomic");
    requireThrows<std::invalid_argument>([] {
        patterns::OrderStatisticTree bad(std::vector<long long>{1, -1});
    });
    patterns::OrderStatisticTree full(std::vector<long long>{std::numeric_limits<long long>::max()});
    requireThrows<std::overflow_error>([&] { full.add(0, 1); });
    require(full.total() == std::numeric_limits<long long>::max(), "overflow check preserves counts");
    requireThrows<std::invalid_argument>([&] { full.add(0, std::numeric_limits<long long>::lowest()); });
    requireThrows<std::overflow_error>([] {
        patterns::OrderStatisticTree bad(std::vector<long long>{std::numeric_limits<long long>::max(), 1});
    });
    patterns::OrderStatisticTree empty(0);
    require(empty.total() == 0 && empty.kth(0) == -1 && empty.updateAndFind(0) == -1,
            "empty order tree");
    requireThrows<std::out_of_range>([&] { empty.add(0, 1); });
    std::mt19937 random(406);
    for (int n = 1; n <= 60; ++n) {
        std::vector<long long> counts(n, 1);
        patterns::OrderStatisticTree current(n);
        for (int step = 0; step < 400; ++step) {
            int index = static_cast<int>(random() % n);
            if (step % 3 == 0) { current.add(index, 1); ++counts[index]; }
            long long total = std::accumulate(counts.begin(), counts.end(), 0LL);
            long long k = static_cast<long long>(random() % (total + 2)) - 1;
            int expected = -1;
            if (k >= 0 && k < total) {
                long long prefix = 0;
                for (int i = 0; i < n; ++i) {
                    prefix += counts[i];
                    if (prefix > k) { expected = i; break; }
                }
            }
            require(current.kth(k) == expected, "random kth vs count scan");
            if (step % 3 == 1) {
                require(current.updateAndFind(k) == expected, "random destructive kth");
                if (expected >= 0) { --counts[expected]; --total; }
            }
            require(current.total() == total, "random total count invariant");
        }
    }
}
void testAssignmentMax() {
    patterns::RangeAssignMaxTree tree(std::vector<long long>{-7, -3, -9, -1});
    require(tree.query(0, 2) == -3, "negative max has negative identity");
    tree.update(0, 3, 0);
    tree.update(1, 2, -5);
    require(tree.query(0, 0) == 0 && tree.query(1, 2) == -5 && tree.query(3, 3) == 0,
            "zero lazy assignment survives partial descent");
    tree.update(0, 3, -11);
    tree.update(2, 3, -20);
    require(tree.query(0, 3) == -11 && tree.query(2, 3) == -20,
            "negative overwrite replaces older assignment");
    tree.update(2, 1, 100);
    require(tree.query(2, 1) == std::numeric_limits<long long>::lowest(), "empty max identity");
    patterns::RangeAssignMaxTree empty(0);
    require(empty.query(0, -1) == std::numeric_limits<long long>::lowest(), "empty max tree");
    requireThrows<std::out_of_range>([&] { tree.update(-1, 2, 0); });
    requireThrows<std::out_of_range>([&] { empty.query(0, 0); });
    std::mt19937 random(699);
    for (int n = 1; n <= 60; ++n) {
        std::vector<long long> values(n, -10);
        patterns::RangeAssignMaxTree current(n, -10);
        for (int step = 0; step < 400; ++step) {
            int l = static_cast<int>(random() % n), r = static_cast<int>(random() % n);
            if (l > r) std::swap(l, r);
            long long value = static_cast<int>(random() % 61) - 40;
            current.update(l, r, value);
            std::fill(values.begin() + l, values.begin() + r + 1, value);
            l = static_cast<int>(random() % n); r = static_cast<int>(random() % n);
            if (l > r) std::swap(l, r);
            require(current.query(l, r) == *std::max_element(values.begin() + l, values.begin() + r + 1),
                    "random lazy assignment vs vector");
        }
    }
    patterns::RangeAssignMaxTree limit(2);
    limit.update(0, 1, std::numeric_limits<long long>::lowest());
    require(limit.query(1, 1) == std::numeric_limits<long long>::lowest(), "lowest value is assignable");
}
void testMergeSortTree() {
    patterns::MergeSortTree<int> tree({5, 2, 6, 1, 2});
    require(tree.query(1, 4, 2) == 1, "strict less excludes duplicates");
    require(tree.query(0, 4, 7) == 5, "merge-sort full cover");
    require(tree.query(5, 4, 2) == 0, "merge-sort empty suffix");
    patterns::MergeSortTree<std::string> words({"b", "a", "a", "c"});
    require(words.query(0, 3, std::string("b")) == 2, "constructor respects template type");
    patterns::MergeSortTree<int> empty({});
    require(empty.query(0, -1, 0) == 0, "empty merge-sort tree");
    requireThrows<std::out_of_range>([&] { tree.query(-1, 2, 0); });
    std::mt19937 random(315);
    for (int n = 1; n <= 80; ++n) {
        std::vector<int> values(n);
        for (auto& value : values) value = static_cast<int>(random() % 21) - 10;
        patterns::MergeSortTree<int> current(values);
        for (int step = 0; step < 200; ++step) {
            int l = static_cast<int>(random() % n), r = static_cast<int>(random() % n);
            if (l > r) std::swap(l, r);
            int threshold = static_cast<int>(random() % 31) - 15;
            int expected = 0;
            for (int i = l; i <= r; ++i) expected += values[i] < threshold;
            require(current.query(l, r, threshold) == expected, "random static range count");
        }
    }
}
int remainder(long long value, int k) {
    int result = static_cast<int>(value % k);
    return result < 0 ? result + k : result;
}
std::vector<long long> prefixCounts(const std::vector<long long>& values, int l, int r, int k) {
    std::vector<long long> counts(k);
    int product = 1 % k;
    for (int i = l; i <= r; ++i) {
        product = static_cast<int>(1LL * product * remainder(values[i], k) % k);
        ++counts[product];
    }
    return counts;
}
void testProductPrefixes() {
    patterns::ProductPrefixTree tree({2, 3}, 5);
    require(tree.query(0, 1).counts == std::vector<long long>({0, 1, 1, 0, 0}),
            "prefix merge preserves left-to-right order");
    patterns::ProductPrefixTree reversed({3, 2}, 5);
    require(reversed.query(0, 1).counts != tree.query(0, 1).counts, "merge is noncommutative");
    tree.update(0, -1);
    require(tree.query(0, 1).counts == prefixCounts({-1, 3}, 0, 1, 5), "negative remainder normalization");
    patterns::ProductPrefixTree empty({}, 7);
    require(empty.query(0, -1).product == 1 && empty.query(0, -1).counts == std::vector<long long>(7),
            "prefix aggregate identity");
    requireThrows<std::invalid_argument>([] { patterns::ProductPrefixTree bad({1}, 0); });
    requireThrows<std::out_of_range>([&] { tree.query(0, 2); });
    requireThrows<std::out_of_range>([&] { empty.update(0, 1); });
    std::mt19937 random(3525);
    for (int k = 1; k <= 9; ++k) for (int n = 1; n <= 35; ++n) {
        std::vector<long long> values(n);
        for (auto& value : values) value = static_cast<int>(random() % 101) - 50;
        patterns::ProductPrefixTree current(values, k);
        for (int step = 0; step < 100; ++step) {
            int index = static_cast<int>(random() % n);
            values[index] = static_cast<int>(random() % 101) - 50;
            current.update(index, values[index]);
            int l = static_cast<int>(random() % n), r = static_cast<int>(random() % n);
            if (l > r) std::swap(l, r);
            auto actual = current.query(l, r);
            require(actual.counts == prefixCounts(values, l, r, k), "random ordered prefix counts");
            int product = 1 % k;
            for (int i = l; i <= r; ++i) product = static_cast<int>(1LL * product * remainder(values[i], k) % k);
            require(actual.product == product, "random aggregate product");
        }
    }
    patterns::ProductPrefixTree extreme({std::numeric_limits<long long>::lowest(), 0}, 7);
    require(extreme.query(0, 1).counts == prefixCounts({std::numeric_limits<long long>::lowest(), 0}, 0, 1, 7),
            "minimum integer remainder");
}
void testRangeSumCounting() {
    require(patterns::countRangeSum({-2, 5, -1}, -2, 2) == 3, "range-sum example");
    require(patterns::countRangeSum({0, 0, 0}, 0, 0) == 6, "duplicate compressed prefixes");
    require(patterns::countRangeSum({}, -1, 1) == 0, "empty range-sum count");
    require(patterns::countRangeSum({1, 2}, 2, 1) == 0, "empty value interval");
    require(patterns::countRangeSum({std::numeric_limits<int>::max(), std::numeric_limits<int>::max()},
                                  std::numeric_limits<int>::min(), std::numeric_limits<int>::max()) == 2,
            "wide prefixes and candidate bounds");
    std::mt19937 random(327);
    for (int n = 0; n <= 55; ++n) for (int trial = 0; trial < 100; ++trial) {
        std::vector<int> values(n);
        for (auto& value : values) value = static_cast<int>(random() % 11) - 5;
        int lower = static_cast<int>(random() % 31) - 15;
        int upper = static_cast<int>(random() % 31) - 15;
        long long expected = 0;
        for (int l = 0; l < n; ++l) {
            long long total = 0;
            for (int r = l; r < n; ++r) {
                total += values[r];
                expected += lower <= total && total <= upper;
            }
        }
        require(patterns::countRangeSum(values, lower, upper) == expected, "random subarray sum count");
    }
}
void testFallingSquares() {
    require(patterns::fallingSquares({{1, 2}, {2, 3}, {6, 1}}) == std::vector<long long>({2, 5, 5}),
            "falling squares overlap");
    require(patterns::fallingSquares({{1, 2}, {3, 2}}) == std::vector<long long>({2, 2}),
            "touching endpoints are disjoint");
    require(patterns::fallingSquares({}).empty(), "empty falling squares");
    require(patterns::fallingSquares({{std::numeric_limits<int>::max(), 2},
                                     {std::numeric_limits<int>::max(), 3}}) == std::vector<long long>({2, 5}),
            "widen coordinate before addition");
    requireThrows<std::invalid_argument>([] { patterns::fallingSquares({{0, 0}}); });
    std::mt19937 random(699327);
    for (int trial = 0; trial < 300; ++trial) {
        std::vector<std::array<int, 2>> squares;
        std::vector<long long> expected;
        std::vector<long long> height(50);
        long long maximum = 0;
        int n = static_cast<int>(random() % 40);
        for (int i = 0; i < n; ++i) {
            int l = static_cast<int>(random() % 35), side = 1 + static_cast<int>(random() % 10);
            squares.push_back({l - 20, side});
            long long top = *std::max_element(height.begin() + l, height.begin() + l + side) + side;
            std::fill(height.begin() + l, height.begin() + l + side, top);
            maximum = std::max(maximum, top);
            expected.push_back(maximum);
        }
        require(patterns::fallingSquares(squares) == expected, "random compressed squares vs unit cells");
    }
}
void testProductDp() {
    require(patterns::countProductRemainders({1, 2, 3}, 3) == std::vector<long long>({3, 1, 2}),
            "subarray product remainder DP");
    require(patterns::countProductRemainders({}, 1) == std::vector<long long>({0}), "empty product DP");
    requireThrows<std::invalid_argument>([] { patterns::countProductRemainders({1}, -1); });
    std::mt19937 random(3524);
    for (int k = 1; k <= 9; ++k) for (int n = 0; n <= 45; ++n) {
        std::vector<long long> values(n);
        for (auto& value : values) value = static_cast<int>(random() % 101) - 50;
        std::vector<long long> expected(k);
        for (int l = 0; l < n; ++l) {
            auto counts = prefixCounts(values, l, n - 1, k);
            for (int r = 0; r < k; ++r) expected[r] += counts[r];
        }
        require(patterns::countProductRemainders(values, k) == expected, "random product DP vs all subarrays");
    }
}
}  // namespace
int main(int argc, char** argv) {
    const std::vector<std::pair<std::string, void (*)()>> tests = {
        {"fenwick", testFenwick}, {"order", testOrderStatistics}, {"assign", testAssignmentMax},
        {"merge", testMergeSortTree}, {"product", testProductPrefixes}, {"count", testRangeSumCounting},
        {"squares", testFallingSquares}, {"dp", testProductDp}
    };
    int ran = 0;
    try {
        for (const auto& [name, test] : tests) {
            if (argc == 1 || name == argv[1]) { test(); ++ran; std::cout << "PASS " << name << '\n'; }
        }
        require(ran > 0, "unknown test group");
    } catch (const std::exception& error) {
        std::cerr << "FAIL: " << error.what() << '\n';
        return EXIT_FAILURE;
    }
    std::cout << "All " << ran << " selected groups passed.\n";
}
