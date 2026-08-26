#include <algorithm>
#include <string>
#include <unordered_map>

class Solution {
public:
    int lengthOfLongestSubstringTwoDistinct(const std::string& s) {
       std::unordered_map<char, int> counts{};
       
       int left = 0;
       int result = 0;
       for (int right = 0; right < s.size(); ++right) {
            ++counts[s[right]];
            while (left < right && counts.size() > 2) {
                int newCount = --counts[s[left]];
                if (newCount == 0) {
                    counts.erase(s[left]);
                }
                
                ++left;
            }
           
           result = std::max(result, right - left + 1);
       }
       
       return result;
    }
};
