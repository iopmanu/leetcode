class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        if (s.size() < p.size()) {
            return {};
        }

        unordered_map<char, int> orig, current;
        for (int i = 0; i < p.size(); i++) {
            orig[p[i]]++;
            current[s[i]]++;
        }

        int matches = 0;
        for (auto [c, freq] : orig) {
            if (current[c] == freq) {
                matches++;
            }
        }

        vector<int> result;
        if (matches == (int)orig.size()) {
            result.push_back(0);
        }

        for (int i = p.size(); i < s.size(); i++) {
            char right = s[i];
            char left  = s[i - p.size()];

            current[right]++;
            if (orig.contains(right)) {
                if (current[right] == orig[right]) {
                    matches++;
                } else if (current[right] == orig[right] + 1) {
                    matches--;
                }
            }

            current[left]--;
            if (orig.contains(left)) {
                if (current[left] == orig[left]) {
                    matches++;
                } else if (current[left] == orig[left] - 1) {
                    matches--;
                }
            }

            if (matches == (int)orig.size()) {
                result.push_back(i - (int)p.size() + 1);
            }
        }

        return result;
    }
};