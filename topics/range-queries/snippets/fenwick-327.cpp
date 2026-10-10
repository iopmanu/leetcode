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