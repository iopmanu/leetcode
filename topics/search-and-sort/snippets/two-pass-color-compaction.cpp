    void sortColors(vector<int>& nums) {
        int ptr = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] == 0) {
                std::swap(nums[ptr++], nums[i]);
            }
        }

        for (int i = ptr; i < nums.size(); i++) {
            if (nums[i] == 1) {
                std::swap(nums[ptr++], nums[i]);
            }
        }
    }
