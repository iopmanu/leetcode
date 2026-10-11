class Solution {
    std::unordered_set<char> vowels{'a', 'e', 'i', 'o', 'u'};
public:
    int maxVowels(string s, int k) {
        int count = 0;
        for (int i = 0; i < k; i++) {
            if (vowels.contains(s[i])) {
                ++count;
            }
        }

        int result = count;

        for (int i = k; i < s.size(); i++) {
            if (vowels.contains(s[i])) {
                ++count;
            }

            if (vowels.contains(s[i - k])) {
                --count;
            }

            result = std::max(result, count);
        }

        return result;
    }
};