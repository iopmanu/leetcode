class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        if (nums.size() < 4) {
            return {};
        }

        std::sort(nums.begin(), nums.end());

        std::vector<std::vector<int>> result{};
        for (int i = 0; i < nums.size() - 3; i++) {
            for (int j = i + 1; j < nums.size() - 2; j++) {
                int k = j + 1; int m = nums.size() - 1;
                while (k < m) {
                    long long toFind = (long long) target - nums[i] - nums[j] + 0LL;
                    if (nums[k] + nums[m] == toFind) {
                        result.push_back({nums[i], nums[j], nums[k], nums[m]});
                        k++; --m;

                        while (k < m && nums[k] == nums[k - 1]) {
                            ++k;
                        }

                        while (k < m && nums[m] == nums[m + 1]) {
                            --m;
                        }
                    } else if (nums[k] + nums[m] > toFind) {
                        --m;
                    } else {
                        ++k;
                    }
                }
                while (j + 1 < nums.size() && nums[j] == nums[j + 1]) {
                    ++j;
                }
            }

            while (i + 1 < nums.size() && nums[i] == nums[i + 1]) {
                ++i;
            }
        }

        return result;
    }
};