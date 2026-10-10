class Solution {
public:
    string mergeAlternately(string word1, string word2) {
        int first = 0; int second = 0;

        std::ostringstream os{};
        while (first < word1.size() && second < word2.size()) {
            os << word1[first++] << word2[second++];
        }

        while (first < word1.size()) {
            os << word1[first++];
        }

        while (second < word2.size()) {
            os << word2[second++];
        }

        return os.str();
    }
};