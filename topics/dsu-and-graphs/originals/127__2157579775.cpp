class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        std::unordered_map<std::string, int> enumerate{};
        int rank = 0;
        for (auto&& word : wordList) {
            enumerate[word] = ++rank;
        }
        
        int end = enumerate[endWord];

        std::deque<std::pair<int, std::string>> q{};
        q.push_back(std::make_pair(0, beginWord));

        std::unordered_set<std::string> visited{};

        while (!q.empty()) {
            int currentSize = q.size();
            for (int i = 0; i < currentSize; i++) {
                auto [transforms, current] = q.front(); q.pop_front();
                if (visited.contains(current)) {
                    continue;
                }

                if (current == endWord) {
                    return transforms + 1;
                }

                visited.insert(current);

                for (int i = 0; i < current.size(); i++) {
                    char ch = current[i];
                    for (char replace = 'a'; replace <= 'z'; replace++) {
                        current[i] = replace;
                        if (enumerate[current]) {
                            q.push_back(std::make_pair(transforms + 1, current));
                        }
                    }

                    current[i] = ch;
                } 
            }
        }

        return 0;
    }
};