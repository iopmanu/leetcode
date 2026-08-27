#include <algorithm>
#include <unordered_set>
#include <vector>

class Solution {
public:
    int smallestCommonElement(
            const std::vector<std::vector<int>>& mat
    ) {
        if (mat.empty()) {
            return -1;
        }

        std::unordered_set<int> common{
            mat[0].begin(),
            mat[0].end()
        };

        for (const auto& row : mat) {
            std::unordered_set<int> values{
                row.begin(),
                row.end()
            };

            for (auto it = common.begin();
                 it != common.end();) {
                if (!values.contains(*it)) {
                    it = common.erase(it);
                } else {
                    ++it;
                }
            }
        }

        auto smallest = std::min_element(
            common.begin(),
            common.end()
        );

        return smallest == common.end()
            ? -1
            : *smallest;
    }
};
