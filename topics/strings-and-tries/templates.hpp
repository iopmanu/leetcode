#pragma once

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <limits>
#include <stdexcept>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

namespace patterns {

// Sources: 28/214/459/686. These functions compare bytes, not Unicode characters.
struct Kmp {
    // lps[i]: longest proper prefix equal to a suffix of pattern[0..i].
    static std::vector<std::size_t> buildLps(std::string_view pattern) {
        std::vector<std::size_t> lps(pattern.size(), 0);
        std::size_t prevLps = 0;
        std::size_t i = 1;
        while (i < pattern.size()) {
            if (pattern[i] == pattern[prevLps]) {
                lps[i++] = ++prevLps;
            } else if (prevLps == 0) {
                lps[i++] = 0;
            } else {
                prevLps = lps[prevLps - 1];
            }
        }
        return lps;
    }

    // Includes overlapping matches. Empty pattern matches all n+1 boundaries.
    static std::vector<std::size_t> searchAll(std::string_view text, std::string_view pattern) {
        std::vector<std::size_t> result;
        if (pattern.empty()) {
            for (std::size_t i = 0; i < text.size(); ++i) result.push_back(i);
            result.push_back(text.size());
            return result;
        }
        auto lps = buildLps(pattern);
        std::size_t matched = 0;
        for (std::size_t i = 0; i < text.size(); ++i) {
            while (matched > 0 && text[i] != pattern[matched]) matched = lps[matched - 1];
            if (text[i] == pattern[matched]) ++matched;
            if (matched == pattern.size()) {
                result.push_back(i + 1 - pattern.size());
                matched = lps[matched - 1];
            }
        }
        return result;
    }

    // At least two copies of one nonempty block; empty input is false.
    static bool isRepeatedPattern(std::string_view text) {
        if (text.empty()) return false;
        auto lps = buildLps(text);
        std::size_t border = lps.back();
        return border > 0 && text.size() % (text.size() - border) == 0;
    }

    // Prepend the fewest bytes to make a palindrome. No reserved delimiter.
    static std::string shortestPalindrome(std::string_view text) {
        if (text.empty()) return {};
        auto lps = buildLps(text);
        std::size_t matched = 0;
        for (auto it = text.rbegin(); it != text.rend(); ++it) {
            while (matched > 0 && *it != text[matched]) matched = lps[matched - 1];
            if (*it == text[matched]) ++matched;
            // A full match can occur only after the last of exactly n bytes.
        }
        std::string extra(text.substr(matched));
        std::reverse(extra.begin(), extra.end());
        extra.append(text);
        return extra;
    }
};

// Source: 208. Value-owned children preserve the original nested-helper style.
class Trie {
    struct Node {
        std::unordered_map<char, Node> level;
        bool leaf = false;
    };
    Node root;

    const Node* getLeaf(std::string_view text) const {
        const Node* current = &root;
        for (char ch : text) {
            auto it = current->level.find(ch);
            if (it == current->level.end()) return nullptr;
            current = &it->second;
        }
        return current;
    }

public:
    void insert(std::string_view word) {
        Node* current = &root;
        for (char ch : word) current = &current->level.try_emplace(ch).first->second;
        current->leaf = true;
    }

    bool search(std::string_view word) const {
        const Node* leaf = getLeaf(word);
        return leaf != nullptr && leaf->leaf;
    }

    bool startsWith(std::string_view prefix) const { return getLeaf(prefix) != nullptr; }
};

// Source: 921. Each unmatched close needs one open; remaining opens need closes.
// Only '(' and ')' are accepted.
inline std::size_t minAddToMakeValid(std::string_view text) {
    std::size_t open = 0;
    std::size_t missing = 0;
    for (char ch : text) {
        if (ch == '(') {
            ++open;
        } else if (ch == ')') {
            if (open > 0) --open;
            else ++missing;
        } else {
            throw std::invalid_argument("expected parentheses only");
        }
    }
    return open + missing;
}

// Source: 1021. Decrement before a close; increment after an open.
// Throws invalid_argument unless the entire input is balanced parentheses.
inline std::string removeOuterParentheses(std::string_view text) {
    std::string result;
    std::size_t open = 0;
    for (char ch : text) {
        if (ch != '(' && ch != ')') throw std::invalid_argument("expected parentheses only");
        if (ch == ')') {
            if (open == 0) throw std::invalid_argument("unmatched close");
            --open;
        }
        if (open > 0) result += ch;
        if (ch == '(') ++open;
    }
    if (open != 0) throw std::invalid_argument("unmatched open");
    return result;
}

// Source: 856. () = 1, (A) = 2*score(A), AB = score(A)+score(B).
// Empty input scores 0. Malformed input and uint64_t overflow are rejected.
inline std::uint64_t scoreParentheses(std::string_view text) {
    std::vector<std::uint64_t> stack{0};
    constexpr auto maxScore = std::numeric_limits<std::uint64_t>::max();
    for (char ch : text) {
        if (ch == '(') {
            stack.push_back(0);
        } else if (ch == ')') {
            if (stack.size() == 1) throw std::invalid_argument("unmatched close");
            std::uint64_t inside = stack.back();
            stack.pop_back();
            if (inside > maxScore / 2) throw std::overflow_error("parentheses score overflow");
            std::uint64_t contribution = inside == 0 ? 1 : 2 * inside;
            if (stack.back() > maxScore - contribution) throw std::overflow_error("parentheses score overflow");
            stack.back() += contribution;
        } else {
            throw std::invalid_argument("expected parentheses only");
        }
    }
    if (stack.size() != 1) throw std::invalid_argument("unmatched open");
    return stack.back();
}

} // namespace patterns
