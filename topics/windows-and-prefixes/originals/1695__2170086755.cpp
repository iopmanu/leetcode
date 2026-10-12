class Solution {
public:
    int maximumUniqueSubarray(vector<int>& nums) {
        int maxScore = 0; int score = 0;
        std::vector<int> counts(1e6, 0);

        int left = 0;
        for (int right = 0; right < nums.size(); right++) {
            ++counts[nums[right]];
            score += nums[right];

            while (left <= right && counts[nums[right]] >= 2) {
                counts[nums[left]]--;
                score -= nums[left++];
            }

            maxScore = std::max(score, maxScore);
        }

        return maxScore;
    }
};