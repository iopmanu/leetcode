#include <algorithm>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

struct TrieNode {
    std::unordered_map<char, int> next{};
    bool terminal = false;
};

struct Trie {
    std::vector<TrieNode> nodes{};

    Trie() : nodes(1) {}

    void insert(const std::string& word) {
        int node = 0;

        for (auto ch : word) {
            auto it = nodes[node].next.find(ch);

            if (it == nodes[node].next.end()) {
                int nextNode = nodes.size();

                nodes[node].next[ch] = nextNode;
                nodes.emplace_back();

                node = nextNode;
            } else {
                node = it->second;
            }
        }

        nodes[node].terminal = true;
    }

    int longestMatch(const std::string& word, int start) const {
        int node = 0;
        int result = 0;

        for (int i = start; i < static_cast<int>(word.size()); ++i) {
            auto it = nodes[node].next.find(word[i]);
            if (it == nodes[node].next.end()) {
                break;
            }

            node = it->second;

            if (nodes[node].terminal) {
                result = i - start + 1;
            }
        }

        return result;
    }
};

class Solution {
public:
    std::string addBoldTag(
            const std::string& s,
            const std::vector<std::string>& words
    ) {
        Trie trie{};
        for (const auto& word : words) {
            if (!word.empty()) {
                trie.insert(word);
            }
        }

        std::ostringstream result{};
        int boldEnd = 0;
        bool bold = false;

        for (int i = 0; i < static_cast<int>(s.size()); ++i) {
            const int longestMatch = trie.longestMatch(s, i);
            boldEnd = std::max(boldEnd, i + longestMatch);
            const bool shouldBeBold = i < boldEnd;

            if (shouldBeBold && !bold) {
                result << "<b>";
                bold = true;
            }

            if (!shouldBeBold && bold) {
                result << "</b>";
                bold = false;
            }

            result << s[i];
        }

        if (bold) {
            result << "</b>";
        }

        return result.str();
    }
};
