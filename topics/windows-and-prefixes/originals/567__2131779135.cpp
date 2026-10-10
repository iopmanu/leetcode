class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        std::unordered_map<char, int> counts;
        for (int i = 0; i < s1.size(); ++i) {
            ++counts[s1[i]];
        }
        int check = counts.size();

        int matches = 0;

        int left = 0;
        for (int right = 0; right < s2.size(); ++right) {
            matches += (--counts[s2[right]] == 0);

            if (right - left + 1 > s1.size()) {
                matches -= (counts[s2[left++]]++ == 0);
            }
            
            if (matches == check) {
                return true;
            }
        }
        
        return false;
    }
};