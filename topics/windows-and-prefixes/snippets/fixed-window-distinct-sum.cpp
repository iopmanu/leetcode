    long long maximumSubarraySum(vector<int>& nums, int k) {
        std::unordered_map<int, int> window{};
        long long current = 0;
        for (int i = 0; i < k; i++) {
            window[nums[i]]++;
            current += nums[i];
        }

        long long result = 0;
        if (window.size() == k) {
            result = current;
        }

        for (int i = k; i < nums.size(); i++) {
            --window[nums[i - k]];
            ++window[nums[i]];
            
            current += nums[i] - nums[i - k];

            if (window[nums[i - k]] == 0) {
                window.erase(nums[i - k]);
            }

            if (window.size() == k) {
                result = std::max(result, current);
            }
        }

        return result;
    }
