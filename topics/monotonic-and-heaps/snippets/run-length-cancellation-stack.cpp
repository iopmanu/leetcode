class Solution {
public:
    string removeDuplicates(string s, int k) {
        std::deque<std::pair<char, int>> stk{};
        for (int i = 0; i < s.size(); i++) {
            char ch = s[i];
            if (stk.empty() || stk.back().first != ch) {
                stk.push_back(std::make_pair(ch, 1));
                continue;
            }
            
            ++stk.back().second;
            if (stk.back().second >= k) {
                stk.pop_back();
            }
        }

        std::string result{};
        for (auto&& p : stk) {
            result += std::string(p.second, p.first);
        }

        return result;
    }
};