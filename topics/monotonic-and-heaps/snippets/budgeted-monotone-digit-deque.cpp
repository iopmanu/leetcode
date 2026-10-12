class Solution {
public:
    string removeKdigits(string num, int k) {
        if (k >= num.size()) {
            return "0";
        }

        std::deque<char> stk{};
        for (int i = 0; i < num.size(); i++) {
            while (k > 0 && !stk.empty() && stk.back() > num[i]) {
                --k;
                stk.pop_back();
            }

            stk.push_back(num[i]);
        }

        while (!stk.empty() && k > 0) {
            stk.pop_back();
            --k;
        }

        while (!stk.empty() && stk.front() == '0') {
            stk.pop_front();
        }

        if (stk.empty()) {
            return "0";
        }

        return {stk.begin(), stk.end()};
    }
};