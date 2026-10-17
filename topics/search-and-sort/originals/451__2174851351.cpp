class Solution {
public:
    string frequencySort(string s) {
        std::unordered_map<char, int> frequencies{};
        for (auto ch : s) {
            frequencies[ch]++;
        }

        std::sort(s.rbegin(), s.rend(), [&](auto l, auto r) {
            if (frequencies[l] != frequencies[r]) {
                return frequencies[l] < frequencies[r];
            }

            return l < r;
        });

        return s;
    }
};