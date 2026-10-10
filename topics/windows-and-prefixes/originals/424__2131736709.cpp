class Solution {
public:
    int characterReplacement(string s, int k) {
        int left = 0;
        std::unordered_map<char, int> count;

        auto maxCh = s[0];
        auto maxCount = 0;

        int result = 0;
        for (int right = 0; right < s.size(); ++right) {
            ++count[s[right]];

            auto max = std::max_element(
                count.begin(), count.end(),
                [](const auto& a, const auto& b) { return a.second < b.second; }
            );

            while ((right - left + 1 - max->second) > k) {
                if (auto ch = s[left++]; --count[ch] == 0) {
                    count.erase(ch);
                }

                max = std::max_element(
                    count.begin(), count.end(),
                    [](const auto& a, const auto& b) { return a.second < b.second; }
                );
                
            }

            result = std::max(result, right - left + 1);
        }

        return result;
    }
};