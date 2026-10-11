    int minIncrementForUnique(vector<int>& nums) {
        int max = *std::max_element(nums.begin(), nums.end());
        std::vector<int> counts(max + nums.size(), 0);
        for (int num : nums) {
            ++counts[num];
        }

        int result = 0;
        for (int v = 0; v < counts.size() - 1; ++v) {
            if (counts[v] > 1) {
                int duplicates = counts[v] - 1;
                counts[v + 1] += duplicates;
                result += duplicates;
            }
        }

        return result;
    }
