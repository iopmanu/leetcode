#include <vector>

class Solution {
public:
    int findLonelyPixel(
            const std::vector<std::vector<char>>& picture
    ) {
        if (picture.empty()) {
            return 0;
        }

        std::vector<int> rowCount(picture.size(), 0);
        std::vector<int> columnCount(picture[0].size(), 0);

        for (int i = 0; i < picture.size(); ++i) {
            for (int j = 0; j < picture[0].size(); ++j) {
                if (picture[i][j] == 'B') {
                    ++rowCount[i];
                    ++columnCount[j];
                }
            }
        }

        int result = 0;

        for (int i = 0; i < picture.size(); ++i) {
            for (int j = 0; j < picture[0].size(); ++j) {
                result += (
                    picture[i][j] == 'B' &&
                    rowCount[i] == 1 &&
                    columnCount[j] == 1
                );
            }
        }

        return result;
    }
};
