class Solution {
public:
    string minWindow(string s, string t) {
        std::unordered_map<char, int> counts{};
        for (int i = 0; i < t.size(); ++i) {
            ++counts[t[i]];
        }

        int matches = counts.size();
        int ll = -1; int rr = -1;
        int left = 0;
        for (int right = 0; right < s.size(); ++right) {
            if (auto it = counts.find(s[right]); it != counts.end()) {
                it->second--;
                matches -= (it->second == 0);
            }

            while (matches == 0) {
                if (ll == -1 || right - left < rr - ll) {
                    ll = left; rr = right;
                }

                if (auto it = counts.find(s[left++]); it != counts.end()) {
                    matches += (++it->second > 0);
                }
            }
        }

        if (ll == -1) {
            return "";
        }

        return s.substr(ll, rr - ll + 1);
    }
};