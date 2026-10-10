class Solution {
    struct SegmentTree {
        std::vector<int> tree{};
        std::vector<int> lazy{};
        int capacity;

        SegmentTree(int n) : capacity(n) {
            tree.resize(4 * n, INT_MAX);
            lazy.resize(4 * n, INT_MAX);
        }

        void update(int ql, int qr, int val){
            update(0, 0, capacity - 1, ql, qr, val);
        }

        int query(int ql, int qr){
            return query(0, 0, capacity - 1, ql, qr);
        }

    private:
        void push(int node, int l, int r) {
            if (lazy[node] != INT_MAX) {
                tree[node] = std::min(tree[node], lazy[node]);
                if (l != r) {
                    lazy[left(node)] = std::min(lazy[left(node)], lazy[node]);
                    lazy[right(node)] = std::min(lazy[right(node)], lazy[node]);
                }

                lazy[node] = INT_MAX;
            }
        }

        void update(int node, int l, int r, int ql, int qr, int val) {
            push(node, l, r);
            if (ql > r || l > qr) {
                return;
            }

            if (l >= ql && qr >= r) {
                lazy[node] = std::min(lazy[node], val);
                push(node, l, r);
                return;
            }

            int m = mid(l, r);
            update(left(node), l, m, ql, qr, val);
            update(right(node), m + 1, r, ql, qr, val);

            tree[node] = std::min(tree[left(node)], tree[right(node)]);
        }

        int query(int node, int l, int r, int ql, int qr) {
            push(node, l, r);

            if (ql > r || qr < l) {
                return INT_MAX;
            }

            if (l >= ql && r <= qr) {
                return tree[node];
            }

            int m = mid(l, r);
            return std::min(
                query(left(node), l, m, ql, qr),
                query(right(node), m + 1, r, ql, qr)
            );
        }

        int mid(int left, int right) {
            return left + ((right - left) >> 1);
        }

        int left(int i) {
            return 2 * i + 1;
        }

        int right(int i) {
            return 2 * i + 2;
        }
    };

public:
    vector<int> minInterval(vector<vector<int>>& intervals, vector<int>& queries) {
        int maxEnd = (*std::max_element(intervals.begin(), intervals.end(), [&](auto &l, auto&r) {
            return std::max(l[0], l[1]) < std::max(r[0], r[1]);
        }))[1];

        SegmentTree tree(maxEnd + 1);
        for (auto&& i : intervals) {
            tree.update(i[0], i[1], i[1] - i[0] + 1);
        }

        std::vector<int> result{};
        for (auto&& q : queries) {
            int len = tree.query(q, q);
            result.push_back(len == INT_MAX ? -1 : len);
        }

        return result;
    }
};