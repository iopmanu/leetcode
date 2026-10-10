    std::vector<int> buildLps(const std::string& s) {
        int n = s.size();
        std::vector<int> lps(n);
        int prevLps = 0; int i = 1;
        while (i < n) {
            if (s[i] == s[prevLps]) {
                lps[i++] = ++prevLps;
            } else if (prevLps == 0) {
                lps[i++] = 0;
            } else {
                prevLps = lps[prevLps - 1];
            }
        }

        return lps;
    }
