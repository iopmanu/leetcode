class Solution {
public:
    int islandPerimeter(vector<vector<int>>& grid) {
        int result = 0;
        std::vector<std::pair<int, int>> dir{{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        std::unordered_set<uint64_t> visited{};

        std::function<void(int, int)> dfs = [&](int i, int j) {
            uint64_t key = (uint64_t(i) << 32) | (uint64_t) j;
            if (visited.contains(key)) {
                return;
            }
            visited.insert(key);

            for (auto [dx, dy] : dir) {
                auto newX = i + dx; auto newY = j + dy;
                if (newX < 0 || newX >= grid.size()) {
                    ++result;
                    continue;
                }

                if (newY < 0 || newY >= grid[0].size()) {
                    ++result;
                    continue;
                }

                if (!grid[newX][newY]) {
                    ++result;
                    continue;
                }

                dfs(newX, newY);
            }
        };

        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[0].size(); j++) {
                if (grid[i][j]) {
                    dfs(i, j);
                    break;
                }
            }
        }

        return result;
    }
};