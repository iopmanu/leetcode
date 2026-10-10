class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        std::stack<int> values{};
        for (auto&& token : tokens) {
            if (token == "+") {
                auto l = values.top();
                values.pop();
                values.top() += l;                
            } else if (token == "*") {
                auto l = values.top();
                values.pop();
                values.top() *= l;
            } else if (token == "/") {
                auto l = values.top();
                values.pop();
                auto r = values.top();
                values.pop();
                values.push(r / l);
            } else if (token == "-") {
                auto l = values.top();
                values.pop();
                auto r = values.top();
                values.pop();
                values.push(r - l);
            } else {
                values.push(std::stoi(token));
            }
        }

        return values.top();
    }
};