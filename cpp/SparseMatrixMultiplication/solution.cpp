#include <unordered_map>
#include <vector>

class Solution {
public:
    std::vector<std::vector<int>> multiply(
            const std::vector<std::vector<int>>& mat1,
            const std::vector<std::vector<int>>& mat2
    ) {
        if (mat1.empty() || mat2.empty()) {
            return {};
        }

        const int rows = static_cast<int>(mat1.size());
        const int shared = static_cast<int>(mat1[0].size());
        const int columns = static_cast<int>(mat2[0].size());

        std::unordered_map<
            int,
            std::unordered_map<int, int>
        > sparse1;

        for (int row = 0; row < rows; ++row) {
            for (int k = 0; k < shared; ++k) {
                if (mat1[row][k] != 0) {
                    sparse1[k][row] = mat1[row][k];
                }
            }
        }

        std::unordered_map<
            int,
            std::unordered_map<int, int>
        > sparse2;

        for (int k = 0; k < shared; ++k) {
            for (int column = 0; column < columns; ++column) {
                if (mat2[k][column] != 0) {
                    sparse2[k][column] = mat2[k][column];
                }
            }
        }

        std::vector<std::vector<int>> result(
            rows,
            std::vector<int>(columns, 0)
        );

        for (int k = 0; k < shared; ++k) {
            auto first = sparse1.find(k);
            auto second = sparse2.find(k);

            if (first == sparse1.end() ||
                second == sparse2.end()) {
                continue;
            }

            for (const auto& [row, left] : first->second) {
                for (const auto& [column, right] : second->second) {
                    result[row][column] += left * right;
                }
            }
        }

        return result;
    }
};
