class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        if (numRows <= 0) {
            return {};
        }

        std::vector<std::vector<int>> g{};
        g.reserve(static_cast<std::size_t>(numRows));
        g.push_back(std::vector<int>{1});

        for (auto i = 1; i < numRows; ++i) {
            std::vector<int> newLevel(i + 1, 1);

            for (int j = 1; j < i; ++j) {
                newLevel[j] = g[i - 1][j - 1] + g[i - 1][j];
            }

            g.emplace_back(std::move(newLevel));
        }

        return g;
    }
};