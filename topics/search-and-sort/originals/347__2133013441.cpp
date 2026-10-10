class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        std::unordered_map<int, int> counts{};
        for (int i = 0; i < nums.size(); ++i) {
            ++counts[nums[i]];
        }

        std::vector<std::pair<int, int>> pairs{};
        for (auto it : counts) {
            pairs.emplace_back(std::make_pair(it.first, it.second));
        }

        int n = pairs.size();
        quickselect(pairs, 0, n - 1, n - k);
        std::vector<int> result;
        for (int i = n - k; i < n; ++i) {
            result.push_back(pairs[i].first);
        }

        return result;
    }

    void quickselect(std::vector<std::pair<int, int>>& nums, int left, int right, int target) {
        auto pivot = nums[right];
        int i = left; int j = right;
        while (i <= j) {
            while (nums[i].second < pivot.second) {
                i++;
            }

            while (nums[j].second > pivot.second) {
                j--;
            }

            if (i <= j) {
                std::swap(nums[i++], nums[j--]);
            }
        }

        if (target <= j) {
            quickselect(nums, left, j, target);
        } else if (target >= i) {
            quickselect(nums, i, right, target);
        } else {
            return;
        }
    }
};