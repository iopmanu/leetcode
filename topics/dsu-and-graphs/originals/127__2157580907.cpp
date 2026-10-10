class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        std::unordered_set<std::string> words{wordList.begin(), wordList.end()};

        std::deque<std::pair<int, std::string>> q{};
        q.push_back(std::make_pair(0, beginWord));

        while (!q.empty()) {
            int currentSize = q.size();
            for (int i = 0; i < currentSize; i++) {
                auto [transforms, current] = q.front(); q.pop_front();
                if (current == endWord) {
                    return transforms + 1;
                }

                for (int i = 0; i < current.size(); i++) {
                    char ch = current[i];
                    for (char replace = 'a'; replace <= 'z'; replace++) {
                        current[i] = replace;
                        if (words.contains(current)) {
                            q.push_back(std::make_pair(transforms + 1, current));
                            words.erase(current);
                        }
                    }

                    current[i] = ch;
                } 
            }
        }

        return 0;
    }
};