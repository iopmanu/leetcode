class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        std::sort(nums.begin(), nums.end());
        std::set<std::vector<int>> set{};

        if (nums.size() < 4) {
            return {};
        }

        for (size_t i = 0; i < nums.size() - 3; ++i) {
            for (size_t j = i + 1; j < nums.size() - 2; j++) {
                size_t k = j + 1, m = nums.size() - 1;
                while (k < m) {
                    long long sum = (long long) nums[i] + nums[j] + nums[k] + nums[m] + 0u;
                    if (sum == target) {
                        set.insert({nums[i], nums[j], nums[k], nums[m]});
                        ++k;
                        --m;
                    } else if (sum < target) {
                        ++k;
                    } else if (sum >= target) {
                        --m;
                    }
                }
            }
        }

        return {set.begin(), set.end()};
    }
};