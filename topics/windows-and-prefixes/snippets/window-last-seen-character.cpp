    int lengthOfLongestSubstring(string s) {
        std::unordered_map<char, int> symbols{};

        int result = 0, left = 0;
        for (int right = 0; right < s.size(); ++right) {
            if (symbols.contains(s[right])) {
                left = max(left, symbols[s[right]] + 1);
            }

            symbols[s[right]] = right;
            result = std::max(result, right - left + 1);
        }

        return result;
    }
