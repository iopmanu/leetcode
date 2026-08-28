#include <string>
#include <vector>

class Solution {
public:
    bool validWordSquare(
            const std::vector<std::string>& words
    ) {
        for (std::size_t i = 0; i < words.size(); ++i) {
            for (std::size_t j = 0;
                 j < words[i].size();
                 ++j) {
                if (j >= words.size() ||
                    i >= words[j].size() ||
                    words[i][j] != words[j][i]) {
                    return false;
                }
            }
        }

        return true;
    }
};
