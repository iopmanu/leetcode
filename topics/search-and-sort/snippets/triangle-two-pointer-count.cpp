    int triangleNumber(vector<int>& nums) {
        std::sort(nums.begin(), nums.end());

        int count = 0;
        for (int i = 2; i < nums.size(); i++) {
            int left = 0; int right = i - 1;

            while (left < right) {
                if (nums[i] < nums[left] + nums[right]) {
                    count += (right - left);
                    --right;
                } else {
                    ++left;
                }
            }
        }

        return count;
    }
