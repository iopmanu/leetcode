class Solution {
public:
    int largestOverlap(vector<vector<int>>& img1, vector<vector<int>>& img2) {
        std::vector<std::vector<int>> firstCoord{}, secondCoord{};
        fillCoord(img1, firstCoord); fillCoord(img2, secondCoord);
        
        int n = img1.size();

        std::unordered_map<uint64_t, int> diffs{};
        for (const auto& f : firstCoord) {
            for (const auto& s: secondCoord) {
                auto dx = s[0] - f[0];
                auto dy = s[1] - f[1];
                
                const std::uint64_t key = (std::uint64_t)(std::uint32_t)dx << 32 | (std::uint32_t)dy;
                ++diffs[key];
            }
        }

        auto result = 0;
        for (auto&& [k, v] : diffs) {
            result = std::max(v, result);
        }

        return result;
    }

    void fillCoord(auto& img, auto& coord) {
        for (int i = 0; i < img.size(); ++i) {
            for (int j = 0; j < img[0].size(); ++j) {
                if (img[i][j]) {
                    coord.push_back({i, j});
                }
            }
        }
    }
};