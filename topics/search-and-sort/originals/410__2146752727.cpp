class Solution {
public:
    int splitArray(vector<int>& nums, int k) {
        int left = 0;
        int right = std::accumulate(nums.begin(), nums.end(), 0);

        auto canSplit = [&](int guess) {
            int current = 0;
            int groups = 0;

            for (auto num : nums) {
                if (current + num > guess) {
                    ++groups;
                    current = 0;
                }

                if (num > guess) {
                    return true;
                }

                current += num;
            }

            return groups >= k;
        };

        while (left < right) {
            int mid = left + (right - left) / 2;
            
            if (canSplit(mid)) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }

        return left;
    }
};