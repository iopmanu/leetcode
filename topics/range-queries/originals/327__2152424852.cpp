class Solution {
    struct FenwickTree {
        std::vector<int> tree{};
        int n;

        FenwickTree(int size) : n(size), tree(size + 1, 0) {
            tree[0] = 0;
            for (int idx = 0; idx < n; ++idx) {
                add(idx, 1);
            }
        }

        void add(int idx, int val) {
            for (++idx; idx <= n; idx += idx & (-idx)) {
                tree[idx] += val;
            }
        }

        int getSum(int idx) {
            int sum = 0;
            for (++idx; idx > 0; idx -= idx & (-idx)) {
                sum += tree[idx];
            }

            return sum;
        }
    };

public:
    int countRangeSum(vector<int>& nums, int lower, int upper) {
        std::vector<long long> sum(nums.size() + 1, 0);
        for (int i = 0; i < nums.size(); i++) {
            sum[i + 1] = sum[i] + nums[i];
        }

        std::vector<long long> sorted(sum.begin(), sum.end());
        std::sort(sorted.begin(), sorted.end());
        FenwickTree ft(sorted.size());

        int result = 0;
        for (long long x : sum) {
            int idx = std::lower_bound(sorted.begin(), sorted.end(), x) - sorted.begin();
            int lowerIdx = std::lower_bound(sorted.begin(), sorted.end(), x + lower) - sorted.begin();
            int upperIdx = std::upper_bound(sorted.begin(), sorted.end(), x + upper) - sorted.begin() - 1;

            ft.add(idx, -1);

            result += ft.getSum(upperIdx) - ft.getSum(lowerIdx - 1);
        }

        return result;
    }
};