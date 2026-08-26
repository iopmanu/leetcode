#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>

class Solution {
public:
    int shortestWay(
            const std::string& source,
            const std::string& target
    ) {
        std::unordered_map<char, std::vector<int>> positions;

        for (int i = 0; i < static_cast<int>(source.size()); ++i) {
            positions[source[i]].push_back(i);
        }

        int result = target.empty() ? 0 : 1;
        int previousPosition = -1;

        for (char character : target) {
            const auto found = positions.find(character);
            if (found == positions.end()) {
                return -1;
            }

            const auto& indices = found->second;
            const auto next = std::upper_bound(
                indices.begin(),
                indices.end(),
                previousPosition
            );

            if (next == indices.end()) {
                ++result;
                previousPosition = indices.front();
            } else {
                previousPosition = *next;
            }
        }

        return result;
    }
};
