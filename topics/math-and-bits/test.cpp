#include "templates.hpp"
#include <algorithm>
#include <array>
#include <climits>
#include <cmath>
#include <iostream>
#include <map>
#include <random>
#include <set>
#include <string>

namespace {
int failures = 0;
void check(bool condition, const char* name) {
    if (!condition) { if (failures < 20) { std::cerr << "FAIL: " << name << '\n'; } ++failures; }
}
bool brutePalindrome(long long value) {
    std::string a = std::to_string(value), b = a; std::reverse(b.begin(), b.end()); return a == b;
}
int bruteSuper(long long left, long long right) {
    int count = 0;
    for (long long root = 0; root * root <= right; ++root) {
        count += root * root >= left && brutePalindrome(root) && brutePalindrome(root * root);
    }
    return count;
}
int bruteOverlap(const std::vector<std::array<int, 2>>& a, const std::vector<std::array<int, 2>>& b) {
    std::set<std::array<int, 2>> points(b.begin(), b.end()); int best = 0;
    for (int dx = -8; dx <= 8; ++dx) {
        for (int dy = -8; dy <= 8; ++dy) {
            int count = 0;
            for (auto p : a) { count += points.contains({p[0] + dx, p[1] + dy}); }
            best = std::max(best, count);
        }
    }
    return best;
}
}
int main() {
    using namespace patterns;
    check(decimalPalindrome(0) && decimalPalindrome(12321) && !decimalPalindrome(123), "decimal palindrome");
    check(!decimalPalindrome(-121) && !decimalPalindrome(LLONG_MAX), "wide palindrome input");
    check(palindromicRoot(123, true) == 12321 && palindromicRoot(123, false) == 123321, "mirror seed");
    check(countSuperPalindromes(4, 1000) == 4, "palindromic roots");
    check(countSuperPalindromes(0, 0) == 1, "zero counted once");
    check(countSuperPalindromes(1, 1'000'000'000'000'000'000LL) == 70, "full original bound");
    check(threeSumMultiplicity({1, 1, 2, 2, 3, 3, 4, 4, 5, 5}, 8) == 20, "value triple multiplicities");
    check(threeSumMultiplicity({0, 0, 0, 0}, 0) == 4, "all equal choose three");
    check(threeSumMultiplicity({INT_MAX, INT_MAX, INT_MAX}, 3LL * INT_MAX) == 1, "wide triple sum");
    check(packSignedPair(-1, 0) != packSignedPair(0, -1), "ordered signed lanes");
    check(maximumTranslationOverlap({{0, 0}, {1, 0}}, {{-3, 4}, {-2, 4}}) == 2, "negative translation");
    check(rectanglesOverlap({0, 0, 2, 2}, {1, 1, 3, 3}), "positive rectangle area");
    check(!rectanglesOverlap({0, 0, 1, 1}, {1, 0, 2, 1}), "touching rectangles have zero area");
    check(circleRectangleOverlap(1, 0, 0, {1, -1, 2, 1}), "circle tangency counts");
    check(!circleRectangleOverlap(1, 0, 0, {1, 1, 2, 2}), "circle corner too far");
    check(!circleRectangleOverlap(1'000'000'000, -1'000'000'000, -1'000'000'000,
        {1'000'000'000, 1'000'000'000, 1'000'000'000, 1'000'000'000}), "wide squared distance");
    std::set<std::uint64_t> packed;
    for (int x = -20; x <= 20; ++x) { for (int y = -20; y <= 20; ++y) { packed.insert(packSignedPair(x, y)); } }
    check(packed.size() == 41 * 41, "packing has no collisions");
    std::mt19937 rng(906923835);
    for (int trial = 0; trial < 500; ++trial) {
        int n = static_cast<int>(rng() % 12), target = static_cast<int>(rng() % 19) - 9;
        std::vector<int> nums;
        for (int i = 0; i < n; ++i) { nums.push_back(static_cast<int>(rng() % 11) - 5); }
        int triples = 0;
        for (int i = 0; i < n; ++i) { for (int j = i + 1; j < n; ++j) { for (int k = j + 1; k < n; ++k) { triples += nums[i] + nums[j] + nums[k] == target; } } }
        check(threeSumMultiplicity(nums, target) == triples, "random index triples");
        std::vector<std::array<int, 2>> a, b;
        for (int row = 0; row < 5; ++row) {
            for (int col = 0; col < 5; ++col) {
                if (rng() % 4 == 0) { a.push_back({row, col}); }
                if (rng() % 4 == 0) { b.push_back({row, col}); }
            }
        }
        check(maximumTranslationOverlap(a, b) == bruteOverlap(a, b), "random translation enumeration");
        long long left = rng() % 100000, right = left + rng() % 100000;
        check(countSuperPalindromes(left, right) == bruteSuper(left, right), "random root enumeration");
        std::array<int, 4> r1, r2;
        for (int i = 0; i < 4; ++i) { r1[i] = static_cast<int>(rng() % 11) - 5; r2[i] = static_cast<int>(rng() % 11) - 5; }
        if (r1[0] > r1[2]) { std::swap(r1[0], r1[2]); }
        if (r1[1] > r1[3]) { std::swap(r1[1], r1[3]); }
        if (r2[0] > r2[2]) { std::swap(r2[0], r2[2]); }
        if (r2[1] > r2[3]) { std::swap(r2[1], r2[3]); }
        bool cellsOverlap = false;
        for (int x = -5; x < 5; ++x) {
            for (int y = -5; y < 5; ++y) {
                bool in1 = r1[0] <= x && x < r1[2] && r1[1] <= y && y < r1[3];
                bool in2 = r2[0] <= x && x < r2[2] && r2[1] <= y && y < r2[3];
                cellsOverlap |= in1 && in2;
            }
        }
        check(rectanglesOverlap(r1, r2) == cellsOverlap, "random rectangle cells");
        int x = static_cast<int>(rng() % 15) - 7, y = static_cast<int>(rng() % 15) - 7, radius = static_cast<int>(rng() % 7);
        int nearest = INT_MAX;
        for (int xx = r1[0]; xx <= r1[2]; ++xx) { for (int yy = r1[1]; yy <= r1[3]; ++yy) { nearest = std::min(nearest, (x - xx) * (x - xx) + (y - yy) * (y - yy)); } }
        check(circleRectangleOverlap(radius, x, y, r1) == (nearest <= radius * radius), "random nearest lattice point");
    }
    check(threeSumMultiplicity(std::vector<int>(3000, 0), 0) == static_cast<int>(3000LL * 2999 * 2998 / 6 % 1'000'000'007), "original count bound");
    if (failures != 0) { std::cerr << failures << " checks failed\n"; return 1; }
    std::cout << "math-and-bits: deterministic + 500 seeded differential cases passed\n";
}
