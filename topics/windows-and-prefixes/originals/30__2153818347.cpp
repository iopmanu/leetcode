class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        int wordSize = words.back().size();
        int totalWordsSize = wordSize * words.size();

        std::unordered_map<std::string_view, int> wordCounts{};
        for (auto&& word : words) {
            ++wordCounts[word];
        }

        int offset = 0;

        std::vector<int> result{};
        for (int offset = 0; offset < wordSize; offset++) {
            std::unordered_map<std::string_view, int> currentCounts = {};
            int start = offset;
            int matches = 0;

            for (int end = offset; end + wordSize <= s.size(); end += wordSize) {
                std::string_view current = std::string_view(s.data() + end, wordSize);
                if (wordCounts.contains(current)) {
                    ++currentCounts[current];
                    matches++;

                    while (currentCounts[current] > wordCounts[current]) {
                        std::string_view toDelete = std::string_view(s.data() + start, wordSize);
                        --currentCounts[toDelete];
                        start += wordSize;
                        matches--;
                    }

                    if (matches == words.size()) {
                        result.push_back(start);
                    }
                } else {
                    matches = 0;
                    start = end + wordSize;
                    currentCounts.clear();
                }
            }
        }

        return result;
    }
};