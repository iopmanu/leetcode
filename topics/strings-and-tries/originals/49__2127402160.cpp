class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        std::unordered_map<std::string, std::vector<std::string>> groups{};
        for (const auto& s : strs) {
            auto c = s;
            std::sort(c.begin(), c.end());
            groups[c].push_back(s);
        }

        std::vector<std::vector<std::string>> result{};
        for (auto&& [_, v] : groups) {
            result.emplace_back(v);
        }

        return result;
    }
};