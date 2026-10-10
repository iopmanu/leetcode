class Solution {
public:
    bool isIsomorphic(string s, string t) {
        if (s.size() != t.size()) {
            return false;
        }

        std::unordered_map<char, char> sd, td;

        for (int i = 0; i < s.size(); ++i) {
            if (sd.contains(s[i]) && sd[s[i]] != t[i]) {
                return false;
            }

            if (td.contains(t[i]) && td[t[i]] != s[i]) {
                return false;
            }

            sd[s[i]] = t[i];
            td[t[i]] = s[i];
        }

        return true;
    }
};