class Solution {
public:
    int calPoints(vector<string>& operations) {
        std::deque<int> numbers{};
        std::set<string> special = {"C", "D", "+"};

        for (auto&& op : operations) {
            if (!special.contains(op)) {
                numbers.push_back(std::stoi(op));
                continue;
            }

            if (op == "C" && !numbers.empty()) {
                numbers.pop_back();
            } else if (op == "D") {
                numbers.push_back(numbers.back() * 2);
            } else if (numbers.size() > 1) {
                auto l = numbers.back();
                numbers.pop_back();

                auto newScore = l + numbers.back();
                numbers.push_back(l);
                numbers.push_back(newScore);
            }
        }

        int result = 0;
        while (!numbers.empty()) {
            result += numbers.back();
            numbers.pop_back();
        }

        return result;
    }
};