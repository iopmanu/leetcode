class Solution {
public:
    int repeatedStringMatch(string a, string b) {
        std::vector<int> lps = buildLPS(b);

        int i = 0; int j = 0;
        int n = a.size();

        int repeat = 0;
        int maxLen = a.size() * 2 + b.size();
        while (i < maxLen) {
            if (a[i % n] == b[j]) {
                i++; j++;
            } else {
                if (j == 0) {
                    i++;
                } else {
                    j = lps[j - 1];
                }
            }

            if (j == b.size()) {
                return (i - 1) / n + 1;
            }
        }

        return -1;
    }

    std::vector<int> buildLPS(const std::string& s) {
        std::vector<int> lps(s.size());
        int prevLps = 0; int i = 1;
        while (i < s.size()) {
            if (s[i] == s[prevLps]) {
                lps[i] = ++prevLps;
                ++i;
            } else if (prevLps == 0) {
                lps[i] = 0;
                ++i;
            } else {
                prevLps = lps[prevLps - 1];
            }
        }

        return lps;
    } 
};