class Solution {
public:
    long long minSumSquareDiff(vector<int>& nums1, vector<int>& nums2, int k1, int k2) {
        long long k = k1 + k2;
        long long sum = 0;
        int n = nums1.size();
        int maxDiff = 0;

        std::unordered_map<long long, int> differences{};
        for (int i = 0; i < n; i++) {
            int d = std::abs(nums1[i] - nums2[i]);
            sum += d;
            differences[d]++;
            maxDiff = std::max(d, maxDiff);
        }
        
        if (sum <= k) {
            return 0;
        }

        for (int i = maxDiff; i> 0 && k > 0; i--) {
            long long move = std::min(k, (long long) differences[i]);
            differences[i] -= move;
            differences[i - 1] += move;
            k -= move;
        }

        long long result = 0;
        for (long long i = 0; i <= maxDiff; i++) {
            result += i * i * differences[i];
        }

        return result;
    }
};