class Solution {
    static constexpr int MOD = 1e9 + 7;
    
    struct SegmentTree {
        struct Node {
            int sum_sq = 0;
            int sum_x = 0;
            int lazy = 0;
        };

        std::vector<Node> tree;
        int n;

        SegmentTree(int size) : n(size) {
            tree.resize(4 * n);
        }

        void apply(int node, int start, int end, int value) {
            long long len = end - start + 1;
            long long val_sq = (1LL * value * value) % MOD;

            tree[node].sum_sq = (tree[node].sum_sq + 2LL * value * tree[node].sum_x + len * val_sq) % MOD;
            tree[node].sum_x = (tree[node].sum_x + len * value) % MOD;
            tree[node].lazy = (tree[node].lazy + value) % MOD;
        }

        void push(int node, int start, int m, int end) {
            if (tree[node].lazy != 0) {
                apply(2 * node + 1, start, m, tree[node].lazy);
                apply(2 * node + 2, m + 1, end, tree[node].lazy);
                tree[node].lazy = 0;
            }
        }

        void update(int node, int start, int end, int ql, int qr, int value) {
            if (ql > end || qr < start) return;

            if (ql <= start && end <= qr) {
                apply(node, start, end, value);
                return;
            }

            int m = start + (end - start) / 2;
            push(node, start, m, end);

            update(2 * node + 1, start, m, ql, qr, value);
            update(2 * node + 2, m + 1, end, ql, qr, value);

            tree[node].sum_sq = (tree[2 * node + 1].sum_sq + tree[2 * node + 2].sum_sq) % MOD;
            tree[node].sum_x = (tree[2 * node + 1].sum_x + tree[2 * node + 2].sum_x) % MOD;
        }
    };

public:
    int sumCounts(std::vector<int>& nums) {
        int n = nums.size();
        std::vector<int> lastSeen(1e5 + 1, -1);
        SegmentTree st(n);

        long long result = 0;
        for (int i = 0; i < n; i++) {
            int starts = (lastSeen[nums[i]] == -1 ? 0 : lastSeen[nums[i]] + 1);
            lastSeen[nums[i]] = i;

            st.update(0, 0, n - 1, starts, i, 1);
            result = (result + st.tree[0].sum_sq) % MOD;
        }

        return result;
    }
};
