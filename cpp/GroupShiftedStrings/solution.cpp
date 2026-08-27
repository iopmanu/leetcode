#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

class Solution {
public:
    std::vector<std::vector<std::string>> groupStrings(
            const std::vector<std::string>& strings
    ) {
        std::unordered_map<std::string, std::vector<std::string>> counts{};

        for (const auto& s : strings) {
            std::ostringstream oss;

            for (int i = 1; i < s.size(); ++i) {
                oss << (s[i] - s[i - 1] + 26) % 26;
                oss << " ";
            }

            counts[oss.str()].push_back(s);
        }

        std::vector<std::vector<std::string>> result{};
        result.reserve(counts.size());

        for (const auto& [k, v] : counts) {
            result.emplace_back(std::move(v));
        }

        return result;
    }
};
