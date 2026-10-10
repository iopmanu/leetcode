class Solution {
public:

    // baab
    // 000
    int strStr(string haystack, string needle) {
        std::vector<int> lps(needle.size());
        int prevLps = 0; int i  = 1;
        while (i < needle.size()) {
            if (needle[i] == needle[prevLps]) {
                lps[i] = ++prevLps;
                ++i;
            } else if (prevLps == 0) {
                lps[i] = 0;
                i++;
            } else {
                prevLps = lps[prevLps - 1];
            }
        }

        i = 0; int j = 0;
        while (i < haystack.size()) {
            if (haystack[i] == needle[j]) {
                ++i; ++j;
            } else {
                if (j == 0) {
                    i++;
                } else {
                    j = lps[j - 1];
                }
            }

            if (j == needle.size()) {
                return i - needle.size();
            }
        }

        return -1;
    }
};