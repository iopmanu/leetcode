class Solution {
public:
    bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
        std::deque<int> stk{};
        int l = 0; int r = 0;
        for (; l < pushed.size(); ++l) {
            stk.push_back(pushed[l]);
            while (!stk.empty() && stk.back() == popped[r]) {
                stk.pop_back();
                r++;
            }
        }

        return stk.empty();
    }
};