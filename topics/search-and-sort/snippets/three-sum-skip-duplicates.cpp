    vector<vector<int>> threeSum(vector<int>& nums) {
        std::sort(nums.begin(), nums.end());

        std::vector<std::vector<int>> result;
        for (int i = 0; i < nums.size() - 2; i++) {
            if (i > 0 && nums[i] == nums[i - 1]) {
                continue;
            }

            int j = i + 1; int k = nums.size() - 1;
            while (j < k) {
                int sum = nums[i] + nums[j] + nums[k];

                if (sum == 0) {
                    result.emplace_back(std::vector<int>{nums[i], nums[j], nums[k]});
                    ++j;
                    --k;
                    while (j < k && nums[j] == nums[j - 1]) {
                        ++j;
                    }
                    while (j < k && nums[k] == nums[k + 1]) {
                        --k;
                    }
                } else if (sum > 0) {
                    k--;
                } else {
                    j++;
                }
            }
        }

        return result;
    }
