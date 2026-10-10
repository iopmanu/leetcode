class Solution {
    struct SegmentTree{
        int n;
        std::vector<int> tree;

        SegmentTree(int n) : n(n), tree(4 * n) {
            build(0, 0, n - 1);
        }

        void build(int node, int start, int end) {
            if (start == end) {
                tree[node] = 1;
                return;
            }

            int m = mid(start, end);
            build(left(node), start, m);
            build(right(node), m + 1, end);
            tree[node] = tree[left(node)] + tree[right(node)];
        }

        int updateAndFind(int node, int start, int end, int k) {
            tree[node]--;
            if (start == end) {
                return start;
            }

            int m = mid(start, end);
            if (tree[left(node)] > k) {
                return updateAndFind(left(node), start, m, k);
            } else {
                return updateAndFind(right(node), m + 1, end, k - tree[left(node)]);
            }
        }

        int mid(int l, int r) {
            return l + (r - l) / 2;
        }

        int left(int node) {
            return 2 * node + 1;
        }

        int right(int node) {
            return 2 * node + 2;
        }
    };

public:
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        std::sort(people.begin(), people.end(), [](const auto& a, const auto& b) {
            if (a[0] == b[0]) return a[1] > b[1];
            return a[0] < b[0];
        });

        int n = people.size();
        std::vector<std::vector<int>> result(n);
        SegmentTree st(n);

        for (const auto& p : people) {
            int idx = st.updateAndFind(0, 0, n - 1, p[1]);
            result[idx] = p;
        }

        return result;
    }
};