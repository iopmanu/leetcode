class Solution {
    template <typename T>
    struct MergeSortTree {
        std::vector<std::vector<T>> tree;
        std::vector<T> arr;
        int n;

        MergeSortTree(const std::vector<T>& nums) : arr(nums), n(nums.size()) {
            if (n > 0) {
                tree.resize(4 * n);
                build(0, 0, n - 1);
            }
        }

        int query(int l, int r, T val) {
            if (n == 0 || l > r || l < 0 || r >= n) return 0;
            return query(0, 0, n - 1, l, r, val);
        }

        void build(int node, int start, int end) {
            if (start == end) {
                tree[node] = {arr[start]};
                return;
            }

            int m = mid(start, end);
            build(left(node), start, m);
            build(right(node), m + 1, end);

            tree[node].resize(tree[left(node)].size() + tree[right(node)].size());
            std::merge(tree[left(node)].begin(), tree[left(node)].end(),
                    tree[right(node)].begin(), tree[right(node)].end(),
                    tree[node].begin());
        }

        int query(int node, int start, int end, int l, int r, T val) {
            if (r < start || l > end) {
                return 0;
            }

            if (l <= start && end <= r) {
                return std::lower_bound(tree[node].begin(), tree[node].end(), val) - tree[node].begin();
            }

            int m = mid(start, end);
            int leftCount = query(left(node), start, m, l, r, val);
            int rightCount = query(right(node), m + 1, end, l, r, val);

            return leftCount + rightCount;
        }

        int left(int node) { return 2 * node + 1; }
        int right(int node) { return 2 * node + 2; }
        int mid(int l, int r) { return l + (r - l) / 2; }

    };

public:
    vector<int> countSmaller(vector<int>& nums) {
        MergeSortTree<int> st{nums};
        std::vector<int> result{};
        for (int i = 0; i < nums.size(); i++) {
            result.push_back(st.query(i + 1, nums.size() - 1, nums[i]));
        }

        return result;
    }
};