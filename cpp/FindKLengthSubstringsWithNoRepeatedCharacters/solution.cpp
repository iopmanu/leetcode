#include <algorithm>
#include <string>
#include <unordered_map>

class Solution {
public:
    int numKLenSubstrNoRepeats(const std::string& s, int k) {
        std::unordered_map<char, int> lastPos{};

        int result = 0;
        int left = 0;
        for (int right = 0; right < s.size(); ++right) {
            if (lastPos.find(s[right]) != lastPos.end()) {
                left = std::max(lastPos[s[right]] + 1, left);
            }

            if ((right - left + 1) >= k) {
                ++result;
            }

            lastPos[s[right]] = right;
        }

        return result;
    }
};
