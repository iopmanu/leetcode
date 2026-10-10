class Solution {
public:
    string minWindow(string s, string t) {
        std::unordered_map<char, int> counts{};
        for (auto ch : t) {
            ++counts[ch];
        }
        int check = counts.size();

        int matches = 0;
        int left = 0;
        int lr = -1, rr = -1;
        for (int right = 0; right < s.size(); ++right) {
            if (counts.contains(s[right])) {
                matches += (--counts[s[right]] == 0);
            }
            
            while (matches == check) {
                if (lr == -1 || right - left < rr - lr) {
                    lr = left; rr = right;
                }

                if (auto ch = s[left++]; counts.contains(ch)) {
                    matches -= (counts[ch]++ == 0);
                }
            }
        }

        if (lr == -1 && rr == -1) {
            return "";
        }

        std::ostringstream result;
        for (int i = lr; i <= rr; ++i) {
            result << s[i];
        }
        return result.str();
    }
};