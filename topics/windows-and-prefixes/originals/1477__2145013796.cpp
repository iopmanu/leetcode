class Solution {

// prefix[r] - prefix[l] == target
// prefix[l] = prefix[r] - target
public:
    int minSumOfLengths(vector<int>& arr, int target) {
        int result = arr.size() + 1;
        int current = 0;
        
        std::vector<int> dp(arr.size() + 1, arr.size() + 1);
        int left = 0;
        for (int right = 0; right < arr.size(); ++right) {
            current += arr[right];
            while (current > target) {
                current -= arr[left++];
            }

            dp[right + 1] = dp[right];
            if (current == target) {
                int len = right - left + 1;

                result = std::min(result, len + dp[left]);
                dp[right + 1] = std::min(dp[right], len);
            }
        }

        return result == arr.size() + 1 ? -1 : result;
    }
};