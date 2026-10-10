class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        std::stack<int> numbers{};
        std::unordered_set<string> availableOperations{"+", "-", "/", "*"};

        for (int i = 0; i < tokens.size(); ++i) {
            if (!availableOperations.contains(tokens[i])) {
                numbers.push(std::atoi(tokens[i].data()));
            } else {
                auto l = numbers.top(); numbers.pop();
                auto r = numbers.top(); numbers.pop();

                if (tokens[i] == "+") {
                    numbers.push(l + r);
                } else if (tokens[i] == "-") {
                    numbers.push(r - l);
                } else if (tokens[i] == "/") {
                    numbers.push(r / l);
                } else if (tokens[i] == "*") {
                    numbers.push(r * l);
                }
            }
        }

        return numbers.top();
    }
};