class Solution {
    int global = 0;
    std::unordered_map<int, int> mapping{};

    struct SegmentTree{
        std::vector<int> tree;
        std::vector<int> lazy;
        int n;

        SegmentTree(int N) : n(N) {
            tree.resize(n * 4, 0);
            lazy.resize(n * 4, 0);
        }

        void push(int node) {
            if (lazy[node] != 0) {
                tree[left(node)] = lazy[node];
                tree[right(node)] = lazy[node];

                lazy[left(node)] = lazy[node];
                lazy[right(node)] = lazy[node];

                lazy[node] = 0;
            }
        }

        void update(int node, int start, int end, int ql, int qr, int val) {
            if (ql > end || qr < start) {
                return;
            }

            if (ql <= start && end <= qr) {
                tree[node] = val;
                lazy[node] = val;
                return;
            }

            push(node);

            int m = mid(start, end);
            update(left(node), start, m, ql, qr, val);
            update(right(node), m + 1, end, ql, qr, val);
            
            tree[node] = std::max(tree[left(node)], tree[right(node)]);
        }

        int query(int node, int start, int end, int ql, int qr) {
            if (ql > end || qr < start) {
                return 0;
            }

            if (ql <= start && end <= qr) {
                return tree[node];
            }

            push(node);

            int m = mid(start, end);
            return std::max(
                query(left(node), start, m, ql, qr),
                query(right(node), m + 1, end, ql, qr)
            );
        }

    private:
        int left(int node) {
            return node * 2 + 1;
        }

        int right(int node) {
            return node * 2 + 2;
        }

        int mid(int l, int r) {
            return l + ((r - l) >> 1);
        }
    };

public:
    vector<int> fallingSquares(vector<vector<int>>& positions) {
        std::vector<int> coords{};
        for (auto sq : positions) {
            coords.push_back(sq[0]);
            coords.push_back(sq[0] + sq[1]);
        }

        std::sort(coords.begin(), coords.end());
        coords.erase(std::unique(coords.begin(), coords.end()), coords.end());
        for (auto c : coords) {
            mapping[c] = global++;
        }

        int n = mapping.size();
        SegmentTree st(n);

        std::vector<int> result{};
        for (auto&& event : positions) {
            int l = mapping[event[0]];
            int r = mapping[event[0] + event[1]];
            int h = event[1];

            int current = st.query(0, 0, n - 1, l, r - 1);
            st.update(0, 0, n - 1, l, r - 1, current + h);
            result.push_back(st.query(0, 0, n - 1, 0, n - 1));
        }

        return result;
    }
};