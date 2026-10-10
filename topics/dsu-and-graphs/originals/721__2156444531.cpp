class Solution {
    struct UnionFind {
        std::vector<int> parent{};
        std::vector<int> size{};

        UnionFind(int n) {
            parent.resize(n);
            size.resize(n, 1);

            for (int i = 0; i < parent.size(); i++) {
                parent[i] = i;
            }
        }

        int find(int i) {
            if (parent[i] == i) {
                return i;
            }

            return parent[i] = find(parent[i]);
        }

        void uni(int i, int j) {
            int parentI = find(i);
            int parentJ = find(j);

            if (parentI == parentJ) {
                return;
            }

            if (size[parentI] > size[parentJ]) {
                parent[parentJ] = parentI;
                size[parentJ] += size[parentI];
            } else {
                parent[parentI] = parentJ;
                size[parentI] += size[parentJ];
            }
        }
    };

public:
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        std::unordered_map<std::string, int> enumerate{};
        std::unordered_map<int, std::pair<std::string_view, std::string_view>> inverted{};
        int rank = 0;

        for (int j = 0; j < accounts.size(); j++) {
            auto& details = accounts[j];
            for (int i = 1; i < details.size(); i++) {
                if (!enumerate.contains(details[i])) {
                    enumerate[details[i]] = rank++;
                    inverted[enumerate[details[i]]] = std::make_pair(
                        std::string_view(details[i]),
                        std::string_view(details[0])
                    );
                }
            }
        }

        auto uf = UnionFind(rank);
        for (auto&& details : accounts) {
            for (int i = 2; i < details.size(); i++) {
                uf.uni(enumerate[details[i - 1]], enumerate[details[i]]);
            }
        }

        std::unordered_map<int, std::vector<std::string>> createChildrens{};
        for (auto [k, v] : inverted) {
            createChildrens[uf.find(k)].push_back(std::string(v.first));
        }

        std::vector<std::vector<std::string>> result{};
        for (auto [k, v] : createChildrens) {
            v.insert(v.begin(), std::string(inverted[k].second));
            std::sort(v.begin() + 1, v.end());
            result.push_back(std::move(v));
        }

        return result;
    }
};