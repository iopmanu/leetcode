class Solution {
public:
    int characterReplacement(string s, int k) {
        int result = 0, left = 0;
        int maxFreq = 0;
        std::unordered_map<char, int> frequencies{};

        for (int right = 0; right < s.size(); ++right) {
            frequencies[s[right]] += 1;
            maxFreq = std::max(frequencies[s[right]], maxFreq);

            int windowLength = right - left + 1;

            if (windowLength - maxFreq <= k) {
                result = std::max(result, windowLength);
            } else {
                frequencies[s[left]]--;;
                ++left;
            }
        }

        return result;
    }
};