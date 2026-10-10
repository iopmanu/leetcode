class Solution {
public:
    int findLUSlength(vector<string>& strs) {
        if (strs.empty()) {
            return -1;
        }

        std::unordered_map<std::string, int> frequencies = {};
        for (auto&& str : strs) {
            frequencies[str]++;
        }

        std::sort(strs.begin(), strs.end(), [](const auto& lhs, const auto& rhs){
            return lhs.size() > rhs.size();
        });

        for (auto&& str : strs) {
            if (frequencies[str] > 1) {
                continue;
            }

            bool isSubsequence = false;
            for (auto&& [s, _] : frequencies) {
                if (s == str) {
                    continue;
                }

                isSubsequence |= this->isSubsequence(str, s);
                if (isSubsequence) {
                    isSubsequence = true;
                    break;
                }
            }

            if (!isSubsequence) {
                return str.size();
            }
        }

        return -1;
    }

    bool isSubsequence(const std::string& subsequence, const std::string& str) {
        int i = 0, j = 0;
        while (i < subsequence.size() && j < str.size()) {
            if (subsequence[i] == str[j]) {
                ++i;
            }
            ++j;
        }

        return i == subsequence.size();
    }
};