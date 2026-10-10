class Solution {
public:
    int splitArray(vector<int>& nums, int k) {
        int current = 0;
        for (auto num : nums) {
            current += num;
        }

        auto count = [&, k](int sum) {
            int count = 0;
            int current = 0;
            for (auto num : nums) {
                if (num > sum) {
                    return true;
                }

                if (current + num > sum) {
                    current = 0;
                    ++count;
                }

                current += num;
            }

            return count >= k;
        };

        int left = 0; int right = current;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (count(mid)) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }

        return left;
    }
};