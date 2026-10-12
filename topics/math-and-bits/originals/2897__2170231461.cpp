class Solution {
public:
    static constexpr int MOD = 1e9 + 7;
    int maxSum(vector<int>& nums, int k) {
        std::vector<int> counts(30, 0);

        for (int num : nums) {
            for (int i = 0; i < 30; i++) {
                if (num & (1 << i)) {
                    counts[i]++;
                }
            }
        }

        long long result = 0;
        for (int i = 0; i < k; i++) {
            long long current = 0;

            for (int j = 29; j >= 0; j--) {
                if (counts[j] > 0) {
                    current |= (1LL << j);
                    counts[j]--;
                }
            }

            result = (result + current * current) % MOD;
        }

        return result;
    }
};