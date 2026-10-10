class Solution {
public:
    int openLock(vector<string>& deadends, string target) {
        std::unordered_set<std::string> de, visited{};
        for (auto&& d : deadends) {
            de.insert(d);
        }

        if (de.contains("0000")) {
            return -1;
        }

        std::deque<std::pair<std::string, int>> q{};
        q.push_back(std::make_pair("0000", 0));
        visited.insert("0000");

        while (!q.empty()) {
            auto [current, moves] = q.front();
            q.pop_front();

            if (current == target) {
                return moves;
            }

            for (int i = 0; i < 4; i++) {
                for (int delta : std::vector<int>{-1, 1}) {
                    char newSymbol = (current[i] - '0' + delta + 10) % 10 + '0';
                    std::string comb = current.substr(0, i) 
                        + newSymbol 
                        + current.substr(i + 1, current.size());

                    if (visited.contains(comb) || de.contains(comb)) {
                        continue;
                    }

                    visited.insert(comb);
                    q.push_back(std::make_pair(comb, moves + 1));
                }
            }
        }

        return -1;
    }
};