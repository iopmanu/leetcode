#include <string>
#include <unordered_map>

class Solution {
public:
    bool canPermutePalindrome(const std::string& s) {
        std::unordered_map<char, int> counts{};

        for (char ch : s) {
            ++counts[ch];
        }

        int oddCount = 0;
        for (const auto& [_, value] : counts) {
            oddCount += (value % 2 == 1);
        }

        if (oddCount == 1 && s.size() % 2 != 0) {
            return true;
        } else if (oddCount == 0 && s.size() % 2 == 0) {
            return true;
        }

        return false;
    }
};
