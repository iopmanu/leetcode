#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class Solution {
public:
    bool areSentencesSimilar(
            const std::vector<std::string>& sentence1,
            const std::vector<std::string>& sentence2,
            const std::vector<std::vector<std::string>>& similarPairs
    ) {
        if (sentence1.size() != sentence2.size()) {
            return false;
        }

        std::unordered_map<std::string, std::unordered_set<std::string>> similar{};

        for (const auto& pair : similarPairs) {
            const auto& left = pair[0];
            const auto& right = pair[1];

            similar[left].insert(right);
            similar[right].insert(left);
        }

        for (int i = 0; i < sentence2.size(); ++i) {
            if (auto found = similar.find(sentence2[i]); found != similar.end()) {
                if (found->second.find(sentence1[i]) != found->second.end()) {
                    continue;
                }
            }

            if (sentence1[i] != sentence2[i]) {
                return false;
            }
        }

        return true;
    }
};
