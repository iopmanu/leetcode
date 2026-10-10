class Solution {
public:
    int maximumBags(vector<int>& capacity, vector<int>& rocks, int additionalRocks) {
        std::vector<std::pair<int , int>> glued{};
        for (int i = 0; i < capacity.size(); ++i) {
            glued.emplace_back(std::make_pair(capacity[i], rocks[i]));
        }

        std::sort(glued.begin(), glued.end(), [](const auto& a, const auto& b) {
            return (a.first - a.second) < (b.first - b.second);
        });

        int bags = 0;
        for (const auto& e : glued) {
            additionalRocks -= (e.first - e.second);
            if (additionalRocks >= 0) {
                ++bags;
            } else {
                break;
            }
        }

        return bags;
    }
};