    void rotate(vector<int>& nums, int k) {
        k = k % nums.size();

        std::reverse(nums.begin() + (nums.size() - k), nums.end());
        std::reverse(nums.begin(), nums.begin() + (nums.size() - k));
        std::reverse(nums.begin(), nums.end());
    }
