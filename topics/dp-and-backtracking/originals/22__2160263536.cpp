class Solution {
public:
    std::vector<std::string> generateParenthesis(int n) {
        std::vector<std::string> result{};
        
        std::function<void(int, int, std::string&)> generate = [&](int idx, int balance, std::string& buffer) {
            if (idx == 2 * n) {
                if (balance == 0) {
                    result.push_back(buffer);
                }
                return;
            }

            if (balance < 0 || (2 * n - idx) < balance) {
                return;
            }

            if (balance > 0) {
                buffer.push_back(')');
                generate(idx + 1, balance - 1, buffer);
                buffer.pop_back();
            }

            buffer.push_back('(');
            generate(idx + 1, balance + 1, buffer);
            buffer.pop_back();
        };

        std::string buffer{};
        generate(0, 0, buffer);

        return result;
    }
};
