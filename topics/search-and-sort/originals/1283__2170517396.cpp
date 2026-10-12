class Solution {
public:
    int smallestDivisor(vector<int>& nums, int threshold) {
        int left = 1; int right = 5 * 1e7;
        auto check = [&](int divisor) {
            int sum = 0;
            for (auto num : nums) {
                sum += (num + divisor - 1) / divisor;
            }

            return sum;
        };

        while (left < right) {
            int mid = left + ((right - left) >> 1);
            if (check(mid) <= threshold) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }

        return left;
    }
};