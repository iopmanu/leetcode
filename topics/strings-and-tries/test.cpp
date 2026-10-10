#include "templates.hpp"

#include <algorithm>
#include <functional>
#include <iostream>
#include <random>
#include <set>
#include <stdexcept>
#include <string>

namespace {
void check(bool condition, const std::string& message) {
    if (!condition) throw std::runtime_error(message);
}

template<class Exception, class Function>
void checkThrows(Function function, const std::string& message) {
    bool threw = false;
    try { function(); } catch (const Exception&) { threw = true; }
    check(threw, message);
}

std::string randomString(std::mt19937& random, int maxLength) {
    int length = static_cast<int>(random() % (maxLength + 1));
    const char alphabet[]{'a', 'b', 'c', '#', '\0'};
    std::string result;
    for (int i = 0; i < length; ++i) result += alphabet[random() % 5];
    return result;
}

void testLps() {
    check(patterns::Kmp::buildLps("ababaca") == std::vector<std::size_t>({0, 0, 1, 2, 3, 0, 1}), "LPS fallback chain");
    check(patterns::Kmp::buildLps("").empty(), "empty LPS");
    std::mt19937 random(28);
    for (int trial = 0; trial < 1500; ++trial) {
        std::string s = randomString(random, 35);
        auto actual = patterns::Kmp::buildLps(s);
        check(actual.size() == s.size(), "one LPS value per position");
        for (std::size_t i = 0; i < s.size(); ++i) {
            std::size_t expected = 0;
            for (std::size_t length = 1; length <= i; ++length)
                if (s.substr(0, length) == s.substr(i + 1 - length, length)) expected = length;
            check(actual[i] == expected, "LPS versus exhaustive borders");
        }
    }
}

std::vector<std::size_t> naiveMatches(const std::string& text, const std::string& pattern) {
    std::vector<std::size_t> result;
    for (std::size_t i = 0; i <= text.size(); ++i)
        if (pattern.size() <= text.size() - i && text.compare(i, pattern.size(), pattern) == 0)
            result.push_back(i);
    return result;
}

void testSearch() {
    check(patterns::Kmp::searchAll("aaaaa", "aaa") == std::vector<std::size_t>({0, 1, 2}), "overlapping matches");
    check(patterns::Kmp::searchAll("abc", "") == std::vector<std::size_t>({0, 1, 2, 3}), "empty pattern matches boundaries");
    check(patterns::Kmp::searchAll("", "") == std::vector<std::size_t>({0}), "both empty");
    check(patterns::Kmp::searchAll("", "a").empty(), "no text");
    check(patterns::Kmp::searchAll("abc", "abcd").empty(), "pattern longer than text");
    std::mt19937 random(686);
    for (int trial = 0; trial < 2500; ++trial) {
        std::string text = randomString(random, 50);
        std::string pattern = randomString(random, 12);
        check(patterns::Kmp::searchAll(text, pattern) == naiveMatches(text, pattern), "KMP versus naive scan");
    }
}

void testPeriod() {
    check(patterns::Kmp::isRepeatedPattern("abab"), "repeated period");
    check(!patterns::Kmp::isRepeatedPattern("aba"), "border does not imply full period");
    check(!patterns::Kmp::isRepeatedPattern(""), "empty has no repeated nonempty block");
    check(!patterns::Kmp::isRepeatedPattern("a"), "one copy is not repetition");
    std::mt19937 random(459);
    for (int trial = 0; trial < 1000; ++trial) {
        std::string s = randomString(random, 30);
        bool expected = false;
        for (std::size_t length = 1; length < s.size(); ++length) {
            if (s.size() % length != 0) continue;
            bool matches = true;
            for (std::size_t i = length; i < s.size(); ++i)
                if (s[i] != s[i % length]) matches = false;
            expected = expected || matches;
        }
        check(patterns::Kmp::isRepeatedPattern(s) == expected, "period versus direct divisors");
    }
}

void testPalindrome() {
    check(patterns::Kmp::shortestPalindrome("aacecaaa") == "aaacecaaa", "palindromic prefix");
    check(patterns::Kmp::shortestPalindrome("abcd") == "dcbabcd", "one-symbol prefix");
    check(patterns::Kmp::shortestPalindrome("").empty(), "empty palindrome");
    check(patterns::Kmp::shortestPalindrome("#a#") == "#a#", "separator-safe input");
    std::mt19937 random(214);
    for (int trial = 0; trial < 1500; ++trial) {
        std::string s = randomString(random, 40);
        std::size_t prefix = s.size();
        for (;;) {
            std::string candidate = s.substr(0, prefix);
            std::string reversed(candidate.rbegin(), candidate.rend());
            if (candidate == reversed) break;
            --prefix;
        }
        std::string extra = s.substr(prefix);
        std::reverse(extra.begin(), extra.end());
        check(patterns::Kmp::shortestPalindrome(s) == extra + s, "shortest palindrome versus prefix enumeration");
    }
}

void testTrie() {
    patterns::Trie trie;
    check(trie.startsWith(""), "empty prefix always exists");
    check(!trie.search(""), "empty word initially absent");
    trie.insert("apple");
    check(trie.search("apple") && trie.startsWith("app") && !trie.search("app"), "terminal versus prefix");
    trie.insert("app");
    trie.insert("app");
    check(trie.search("app") && !trie.search("apricot"), "inserted prefix word and failed query");
    trie.insert("");
    check(trie.search(""), "explicit empty insertion");
    const auto& readOnly = trie;
    check(readOnly.search("apple") && readOnly.startsWith("ap"), "queries are const");
    std::set<std::string> words{"", "apple", "app"};
    std::mt19937 random(208);
    for (int trial = 0; trial < 2000; ++trial) {
        std::string s = randomString(random, 12);
        if (random() % 3 == 0) { trie.insert(s); words.insert(s); }
        check(trie.search(s) == words.contains(s), "trie versus set membership");
        bool prefix = s.empty();
        for (const auto& word : words) if (word.starts_with(s)) prefix = true;
        check(trie.startsWith(s) == prefix, "trie versus prefix scan");
    }
}

bool balanced(const std::string& s) {
    int depth = 0;
    for (char ch : s) {
        depth += ch == '(' ? 1 : -1;
        if (depth < 0) return false;
    }
    return depth == 0;
}

std::vector<std::string> allParentheses(int maxLength) {
    std::vector<std::string> result;
    for (int length = 0; length <= maxLength; ++length) {
        for (unsigned mask = 0; mask < (1U << length); ++mask) {
            std::string s;
            for (int i = 0; i < length; ++i) s += (mask & (1U << i)) ? '(' : ')';
            result.push_back(s);
        }
    }
    return result;
}

void testBalance() {
    check(patterns::minAddToMakeValid("()))((") == 4, "unmatched sides add independently");
    check(patterns::minAddToMakeValid("") == 0, "empty needs nothing");
    checkThrows<std::invalid_argument>([] { patterns::minAddToMakeValid("(x)"); }, "reject nonparenthesis");
    for (const auto& s : allParentheses(11)) {
        int depth = 0;
        int lowest = 0;
        for (char ch : s) { depth += ch == '(' ? 1 : -1; lowest = std::min(lowest, depth); }
        std::size_t expected = static_cast<std::size_t>(depth - 2 * lowest);
        check(patterns::minAddToMakeValid(s) == expected, "balance versus minimum-prefix formula");
    }
}

void testRemoveOuter() {
    check(patterns::removeOuterParentheses("(()())(())") == "()()()", "outer pair per primitive");
    check(patterns::removeOuterParentheses("").empty(), "empty removal");
    for (const std::string s : {"(", ")", "())(", "(x)"})
        checkThrows<std::invalid_argument>([&] { patterns::removeOuterParentheses(s); }, "reject malformed outer removal");
    for (const auto& s : allParentheses(12)) {
        if (!balanced(s)) continue;
        std::string expected;
        std::size_t start = 0;
        int depth = 0;
        for (std::size_t i = 0; i < s.size(); ++i) {
            depth += s[i] == '(' ? 1 : -1;
            if (depth == 0) { expected += s.substr(start + 1, i - start - 1); start = i + 1; }
        }
        check(patterns::removeOuterParentheses(s) == expected, "outer removal versus primitive splitting");
    }
}

void testScore() {
    check(patterns::scoreParentheses("(()(()))") == 6, "nested and concatenated scoring");
    check(patterns::scoreParentheses("") == 0, "empty score");
    for (const std::string s : {"(", ")", "())(", "a"})
        checkThrows<std::invalid_argument>([&] { patterns::scoreParentheses(s); }, "reject malformed score");
    checkThrows<std::overflow_error>([] {
        patterns::scoreParentheses(std::string(65, '(') + std::string(65, ')'));
    }, "reject overflowing nesting score");
    std::string large = std::string(64, '(') + std::string(64, ')');
    check(patterns::scoreParentheses(large) == (std::uint64_t{1} << 63), "maximum-depth power fits uint64");
    checkThrows<std::overflow_error>([&] { patterns::scoreParentheses(large + large); }, "reject overflowing sum");
    for (const auto& s : allParentheses(12)) {
        if (!balanced(s)) continue;
        // Independent primitive-splitting recursive definition.
        std::function<std::uint64_t(std::string_view)> reference = [&](std::string_view text) {
            std::uint64_t total = 0;
            std::size_t start = 0;
            int depth = 0;
            for (std::size_t i = 0; i < text.size(); ++i) {
                depth += text[i] == '(' ? 1 : -1;
                if (depth != 0) continue;
                total += i == start + 1 ? 1 : 2 * reference(text.substr(start + 1, i - start - 1));
                start = i + 1;
            }
            return total;
        };
        check(patterns::scoreParentheses(s) == reference(s), "stack score versus recursive grammar");
    }
}
} // namespace

int main(int argc, char** argv) {
    try {
        std::string group = argc > 1 ? argv[1] : "all";
        if (group == "all" || group == "lps") testLps();
        if (group == "all" || group == "search") testSearch();
        if (group == "all" || group == "period") testPeriod();
        if (group == "all" || group == "palindrome") testPalindrome();
        if (group == "all" || group == "trie") testTrie();
        if (group == "all" || group == "balance") testBalance();
        if (group == "all" || group == "outer") testRemoveOuter();
        if (group == "all" || group == "score") testScore();
        std::cout << "strings-and-tries: " << group << " passed\n";
    } catch (const std::exception& error) {
        std::cerr << "FAIL: " << error.what() << '\n';
        return 1;
    }
}
