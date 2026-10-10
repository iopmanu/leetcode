    int findJudge(int n, vector<vector<int>>& trust) {
        std::unordered_map<int, std::vector<int>> trusts{};
        std::unordered_map<int, std::vector<int>> whoTrust{};

        if (n == 1) {
            return 1;
        }

        std::vector<int> candidates{};
        for (auto t : trust) {
            trusts[t[1]].push_back(t[0]);
            whoTrust[t[0]].push_back(t[1]);

            if (trusts[t[1]].size() == (n - 1)) {
                candidates.push_back(t[1]);
            }
        }

        for (auto c : candidates) {
            if (whoTrust[c].empty()) {
                return c;
            }
        }

        return -1;
    }