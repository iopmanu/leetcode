class Solution {
public:
    vector<int> largestPower(vector<int>& nums) {
        int n = nums.size();
        std::vector<std::vector<int>> groups(1);
        groups[0] = nums;
        
        std::vector<int> power(15, 0);
        int idx = 0;
        for (int bit = 14; bit >= 0; --bit) {
            std::vector<std::vector<int>> newGroups{};
            bool active = true;
            int result = 0;

            for (auto& group : groups) {
                if (!active) {
                    newGroups.push_back(group);
                    continue;
                }

                std::vector<int> ones, zeros;

                for (int x : group) {
                    if (x & (1 << bit)) {
                        ones.push_back(x);
                    } else {
                        zeros.push_back(x);
                    }
                }

                result += ones.size();
                if (!ones.empty()) {
                    newGroups.push_back(ones);
                }

                if (!zeros.empty()) {
                    newGroups.push_back(zeros);
                    active = false;
                }
            }

            power[idx++] = result;
            groups = std::move(newGroups);
        }

        return power;
    }
};