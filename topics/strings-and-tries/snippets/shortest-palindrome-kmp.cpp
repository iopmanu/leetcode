class Solution {

    // aacecaaa
    // aaacecaa


    // aacecaaa # aaacecaa

    // Индекс	0	1	2	3	4	5	6	7	8	9	10	11	12	13	14	15	16
    // Символ	a	a	c	e	c	a	a	a	#	a	a	a	c	e	c	a	a
    //  LPS	    0	1	0	0	0	1	2	2	0	1	2	2	3	4	5	6	7
public:
    string shortestPalindrome(string s) {
        if (s.empty()) {
            return "";
        }

        std::string reversed = s;
        std::reverse(reversed.begin(), reversed.end());
        reversed = s + "#" + reversed;

        std::vector<int> lps = buildLps(reversed);
        
        int idx = lps[reversed.size() - 1];
        std::string extra = s.substr(idx);
        std::reverse(extra.begin(), extra.end());

        return extra + s;
    }

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
};