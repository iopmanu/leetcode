class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        if (grid.empty()) {
            return 0;
        }

        std::vector<std::vector<bool>> visited(
            grid.size(),
            std::vector<bool>(grid[0].size(), false)
        );

        int count = 0;

        for (int i = 0; i < grid.size(); ++i) {
            for (int j = 0; j < grid[0].size(); ++j) {
                if (!visited[i][j] && grid[i][j] == '1') {
                    mark(grid, visited, i, j);
                    ++count;
                }
            }
        }

        return count;
    }

    void mark(
        const std::vector<std::vector<char>>& grid,
        std::vector<std::vector<bool>>& visited,
        int i, int j
    ) {
        if (i < 0 || i >= grid.size() || j < 0 || j >= grid[0].size()) {
            return;
        }

        if (visited[i][j] || grid[i][j] == '0') {
            return;
        }

        visited[i][j] = true;

        mark(grid, visited, i - 1, j);
        mark(grid, visited, i + 1, j);
        mark(grid, visited, i, j - 1);
        mark(grid, visited, i, j + 1);
    }
};