    struct UnionFind {
        std::vector<int> parent{};
        std::vector<int> size{};

        UnionFind(int V) {
            parent.resize(V);
            size.resize(V, 1);

            for (int i = 0; i < V; i++) {
                parent[i] = i;
            }
        }

        void unify(int i, int j) {
            int parentI = query(i);
            int parentJ = query(j);

            if (parentI == parentJ) {
                return;
            }

            if (size[parentI] > size[parentJ]) {
                size[parentI] += size[parentJ];
                parent[parentJ] = parentI;
            } else {
                size[parentJ] += size[parentI];
                parent[parentI] = parentJ;
            }
        }

        int query(int i) {
            int p = parent[i];
            if (i == p) {
                return i;
            }

            return parent[i] = query(p);
        }

    };