class Solution {
public:
    bool isAnagram(string s, string t) {
        std::unordered_map<char, int> l, r;
        for (auto ch : s) {
            ++l[ch];
        }

        for (auto ch : t) {
            ++r[ch];
        }

        for (auto [k, v] : l) {
            if (auto found = r.find(k); found == r.end() || found->second != v) {
                return false;
            }
        }

        for (auto [k, v] : r) {
            if (auto found = l.find(k); found == l.end() || found->second != v) {
                return false;
            }
        }

        return true;
    }
};