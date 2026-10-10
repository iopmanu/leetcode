class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        if (nums.size() < 4) {
            return {};
        }

        std::sort(nums.begin(), nums.end());

        std::set<std::vector<int>> result{};
        for (int i = 0; i < nums.size() - 3; ++i) {
            for (int j = i + 1; j < nums.size() - 2; ++j) {
                int k = j + 1, m = nums.size() - 1;
                while (k < m) {
                    long long sum = (long long) nums[i] + nums[j] + nums[k] + nums[m] + 0u;

                    if (sum == target) {
                        result.insert({nums[i], nums[j], nums[k], nums[m]});
                        ++k; --m;
                    } else if (sum < target) {
                        ++k;
                    } else {
                        --m;
                    }
                }
            }
        }

        return {result.begin(), result.end()};
    }
};