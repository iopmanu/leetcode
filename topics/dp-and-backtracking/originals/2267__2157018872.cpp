class Solution {
public:
    bool hasValidPath(vector<vector<char>>& grid) {
        std::unordered_map<uint64_t, bool> cache{};

        int n = grid.size(); int m = grid[0].size();
        std::function<bool(int, int, int)> traverse = [&](int i, int j, int balance){
            if (i >= n || j >= m) {
                return false;
            }

            balance += (grid[i][j] == '(');
            balance -= (grid[i][j] == ')');

            if (i == n - 1 && j == m - 1) {
                return balance == 0;
            }

            if (balance < 0) {
                return false;
            }

            uint64_t key = (uint64_t(balance) << 32) | (uint64_t(i) << 16) | (uint32_t) j;
            if (cache.contains(key)) {
                return cache[key];
            }

            cache[key] = traverse(i + 1, j, balance) | traverse(i, j + 1, balance);
            return cache[key];
        };

        return traverse(0, 0, 0);
    }
};