class Solution {
public:
    bool isAlienSorted(vector<string>& words, string order) {
        std::unordered_map<char, int> mapping{};
        for (int i = 0; i < order.size(); i++) {
            mapping[order[i]] = i;
        }

        for (int i = 0 ; i < words.size() - 1; i++) {
            for (int j = 0; j < words[i].size(); j++) {
                if (j >= words[i + 1].size()) {
                    return false;
                }

                if (words[i][j] != words[i + 1][j]) {
                    if (mapping[words[i][j]] > mapping[words[i + 1][j]]) {
                        return false;
                    }

                    break;
                }
            }
        }

        return true;
    }
};