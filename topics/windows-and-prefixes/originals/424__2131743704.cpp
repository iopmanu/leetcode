class Solution {
public:
    int characterReplacement(string s, int k) {
        int left = 0;
        std::unordered_map<char, int> count;

        int maxCount = 0;

        int result = 0;
        for (int right = 0; right < s.size(); ++right) {
            auto newCount = ++count[s[right]];
            maxCount = max(maxCount, newCount);

            if (right - left + 1 - maxCount > k) {
                --count[s[left++]];
            }

            result = std::max(result, right - left + 1);
        }

        return result;
    }
};