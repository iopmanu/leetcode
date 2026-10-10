#include "templates.hpp"
#include <algorithm>
#include <array>
#include <iostream>
#include <random>
#include <set>

namespace {
int failures = 0;
void check(bool condition, const char* name) {
    if (!condition) { if (failures < 20) { std::cerr << "FAIL: " << name << '\n'; } ++failures; }
}
std::string bruteCover(const std::string& s, const std::string& t) {
    if (t.empty()) { return ""; }
    std::array<int, 256> need{};
    for (unsigned char ch : t) { ++need[ch]; }
    std::string best;
    for (int l = 0; l < static_cast<int>(s.size()); ++l) {
        std::array<int, 256> have{};
        for (int r = l; r < static_cast<int>(s.size()); ++r) {
            ++have[static_cast<unsigned char>(s[r])];
            bool valid = true;
            for (int ch = 0; ch < 256; ++ch) { if (have[ch] < need[ch]) { valid = false; } }
            if (valid && (best.empty() || r - l + 1 < static_cast<int>(best.size()))) {
                best = s.substr(l, r - l + 1);
            }
        }
    }
    return best;
}
bool brutePermutation(std::string p, const std::string& s) {
    std::sort(p.begin(), p.end());
    for (std::size_t i = 0; i + p.size() <= s.size(); ++i) {
        std::string part = s.substr(i, p.size()); std::sort(part.begin(), part.end());
        if (part == p) { return true; }
    }
    return false;
}
int bruteReplacement(const std::string& s, int k) {
    int best = 0;
    for (int l = 0; l < static_cast<int>(s.size()); ++l) {
        std::array<int, 256> count{};
        int most = 0;
        for (int r = l; r < static_cast<int>(s.size()); ++r) {
            most = std::max(most, ++count[static_cast<unsigned char>(s[r])]);
            if (r - l + 1 - most <= k) { best = std::max(best, r - l + 1); }
        }
    }
    return best;
}
std::vector<int> bruteWords(const std::string& s, const std::vector<std::string>& words) {
    if (words.empty()) { return {}; }
    std::multiset<std::string> wanted(words.begin(), words.end());
    std::vector<int> answer;
    for (std::size_t i = 0; i + words.size() * words[0].size() <= s.size(); ++i) {
        std::multiset<std::string> found;
        for (std::size_t j = 0; j < words.size(); ++j) { found.insert(s.substr(i + j * words[0].size(), words[0].size())); }
        if (found == wanted) { answer.push_back(static_cast<int>(i)); }
    }
    return answer;
}
}
int main() {
    using namespace patterns;
    check(minWindow("ADOBECODEBANC", "ABC") == "BANC", "minimum covering window");
    check(minWindow("abc", "").empty(), "empty target");
    check(containsPermutation("ab", "eidbaooo"), "permutation found");
    check(containsPermutation("", ""), "empty permutation");
    check(longestReplacementWindow("AABABBA", 1) == 4, "stale maximum");
    check(longestOnes({1, 0, 0, 1}, 1) == 2, "zero budget");
    check(longestOnesAfterDeletion({1, 1, 1}) == 2, "deletion is mandatory");
    check(minSubarrayLength({2, 3, 1, 2, 4, 3}, 7) == 2, "minimum positive window");
    check(minEndRemovals({1, 1, 4, 2, 3}, 5) == 2, "complement window");
    check(minEndRemovals({0, 0}, 0) == 0, "keep zero-sum zeros");
    check(minEndRemovals({}, 0) == 0, "empty complement");
    check(countSubarraysSum({1, -1, 0}, 0) == 3, "signed prefix counts");
    check(countFixedBoundSubarrays({1, 3, 5, 2, 7, 5}, 1, 5) == 2, "fixed extrema");
    check(productExceptSelf({1, 2, 0, 4}) == std::vector<long long>({0, 0, 8, 0}), "product with zero");
    check(minTwoTargetLengths({3, 2, 2, 4, 3}, 3) == 2, "nonoverlap prefix best");
    check(firstStableIndex({4, 2, 3}, 2) == 0, "inclusive stable boundary");
    auto positions = findWordConcatenations("barfoofoobarthefoobarman", {"bar", "foo", "the"});
    std::sort(positions.begin(), positions.end());
    check(positions == std::vector<int>({6, 9, 12}), "word stride windows");
    bool rejected = false;
    try { (void)findWordConcatenations("ab", {"", ""}); } catch (const std::invalid_argument&) { rejected = true; }
    check(rejected, "zero word size rejected");
    const std::string bytes{static_cast<char>(255), 'a', static_cast<char>(255)};
    check(minWindow(bytes, std::string(1, static_cast<char>(255))).size() == 1, "unsigned byte indexing");
    std::mt19937 rng(5602444);
    for (int trial = 0; trial < 600; ++trial) {
        int n = static_cast<int>(rng() % 9), k = static_cast<int>(rng() % 4);
        std::string s, t;
        std::vector<int> a, positive, bits;
        for (int i = 0; i < n; ++i) {
            s += static_cast<char>('a' + rng() % 3);
            a.push_back(static_cast<int>(rng() % 7) - 3);
            positive.push_back(static_cast<int>(rng() % 4) + 1);
            bits.push_back(static_cast<int>(rng() % 2));
        }
        for (unsigned i = 0, m = rng() % 5; i < m; ++i) { t += static_cast<char>('a' + rng() % 3); }
        check(minWindow(s, t) == bruteCover(s, t), "random cover");
        check(containsPermutation(t, s) == brutePermutation(t, s), "random permutation");
        check(longestReplacementWindow(s, k) == bruteReplacement(s, k), "random replacement");
        long long target = static_cast<int>(rng() % 9) - 4, sums = 0, bounds = 0;
        int ones = 0, oneZero = 0, shortest = n + 1, twoBest = n + 1;
        int positiveTarget = static_cast<int>(rng() % 9) + 1;
        std::vector<std::array<int, 2>> targetIntervals;
        for (int l = 0; l < n; ++l) {
            long long sum = 0, posSum = 0;
            int low = a[l], high = a[l], zeroes = 0;
            for (int r = l; r < n; ++r) {
                sum += a[r]; posSum += positive[r]; zeroes += bits[r] == 0;
                low = std::min(low, a[r]); high = std::max(high, a[r]);
                sums += sum == target; bounds += low == -1 && high == 2;
                if (zeroes <= k) { ones = std::max(ones, r - l + 1); }
                if (zeroes <= 1) { oneZero = std::max(oneZero, r - l); }
                if (posSum >= positiveTarget) { shortest = std::min(shortest, r - l + 1); }
                if (posSum == positiveTarget) { targetIntervals.push_back({l, r}); }
            }
        }
        for (const auto& x : targetIntervals) {
            for (const auto& y : targetIntervals) {
                if (x[1] < y[0]) { twoBest = std::min(twoBest, x[1] - x[0] + y[1] - y[0] + 2); }
            }
        }
        check(countSubarraysSum(a, target) == sums, "random signed sums");
        check(countFixedBoundSubarrays(a, -1, 2) == bounds, "random fixed bounds");
        check(longestOnes(bits, k) == ones, "random zero budget");
        check(longestOnesAfterDeletion(bits) == oneZero, "random mandatory deletion");
        check(minSubarrayLength(positive, positiveTarget) == (shortest == n + 1 ? 0 : shortest), "random minimum window");
        check(minTwoTargetLengths(positive, positiveTarget) == (twoBest == n + 1 ? -1 : twoBest), "random two targets");
        std::vector<long long> products(n, 1);
        for (int i = 0; i < n; ++i) { for (int j = 0; j < n; ++j) { if (i != j) { products[i] *= a[j]; } } }
        check(productExceptSelf(a) == products, "random exclusive products");
        int x = static_cast<int>(rng() % 20), removalBest = n + 1;
        for (int left = 0; left <= n; ++left) {
            for (int right = 0; right + left <= n; ++right) {
                long long removed = 0;
                for (int i = 0; i < left; ++i) { removed += positive[i]; }
                for (int i = n - right; i < n; ++i) { removed += positive[i]; }
                if (removed == x) { removalBest = std::min(removalBest, left + right); }
            }
        }
        check(minEndRemovals(positive, x) == (removalBest == n + 1 ? -1 : removalBest), "random end removals");
        int stable = -1;
        for (int i = 0; i < n; ++i) {
            int low = *std::min_element(a.begin() + i, a.end());
            int high = *std::max_element(a.begin(), a.begin() + i + 1);
            if (static_cast<long long>(high) - low <= k) { stable = i; break; }
        }
        check(firstStableIndex(a, k) == stable, "random inclusive extrema");
        std::vector<std::string> words;
        for (unsigned i = 0, m = 1 + rng() % 3; i < m; ++i) {
            std::string word;
            for (int j = 0; j < 2; ++j) { word += static_cast<char>('a' + rng() % 3); }
            words.push_back(word);
        }
        auto actual = findWordConcatenations(s, words); std::sort(actual.begin(), actual.end());
        check(actual == bruteWords(s, words), "random word windows");
    }
    check(countSubarraysSum(std::vector<int>(100000, 0), 0) == 5000050000LL, "64-bit answer");
    if (failures != 0) { std::cerr << failures << " checks failed\n"; return 1; }
    std::cout << "windows-and-prefixes: deterministic + 600 seeded differential cases passed\n";
}
