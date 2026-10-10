class Solution {
    std::string expression;
    int idx;

    std::set<std::string> item() {
        set<string> result{};
        if (expression[idx] == '{') {
            idx++;
            result = eval();
        } else {
            result = {std::string(1, expression[idx])};
        }
        idx++;
        return result;
    }

    std::set<std::string> term() {
        std::set<string> result = {""};

        while (idx < expression.size() && 
            (expression[idx] == '{' || std::isalpha(expression[idx]))) {
            
            auto sub = item();
            std::set<string> tmp{};
            for (auto& i : result) {
                for (auto& j : sub) {
                    tmp.insert(i + j);
                }
            }

            result = std::move(tmp);
        }

        return result;
    }

    std::set<std::string> eval() {
        set<string> result{};
        while (true) {
            result.merge(term());

            if (idx < expression.size() && expression[idx] == ',') {
                idx++;
                continue;
            } else {
                break;
            }
        }

        return result;
    }

public:
    vector<string> braceExpansionII(string expression) {
        this->expression = expression;
        this->idx = 0;
        auto result = eval();
        return {result.begin(), result.end()};
    }
};