class Solution {
public:
    bool repeatedSubstringPattern(string s) {
        std::vector<int> lps = buildLps(s);
        std::unordered_map<int, int> counts{};

        int i = 0;
        while (i < lps.size() && lps[i] == 0) {
            i++;
        }

        int n = s.size();
        int len = lps.back();
        return len > 0 && (n % (n - len) == 0);
    }

    std::vector<int> buildLps(const std::string& s) {
        std::vector<int> lps(s.size());
        int i = 1; int prevLps = 0;
        while (i < s.size()) {
            if (s[i] == s[prevLps]) {
                lps[i] = ++prevLps;
                ++i;
            } else if (prevLps == 0) {
                lps[i] = 0;
                i++;
            } else {
                prevLps = lps[prevLps - 1];
            }
        }

        return lps;
    }
};