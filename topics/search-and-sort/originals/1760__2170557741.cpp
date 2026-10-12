class Solution {
public:
    int minimumSize(vector<int>& nums, int maxOperations) {
        int left = 1; int right = 1e9;

        auto check = [&](int toCheck) {
            long long operations = 0;
            for (auto bag : nums) {
                operations += 0LL + (bag + toCheck - 1) / toCheck - 1;
            }

            return operations <= maxOperations;
        };

        while (left <= right) {
            int mid = left + ((right - left) >> 1);
            if (check(mid)) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }

        return left;
    }
};