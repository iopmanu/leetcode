class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        for (int i = 0; i < numbers.size(); ++i) {
            auto toFind = target - numbers[i];
            auto it = std::lower_bound(
                numbers.begin(), numbers.end(), toFind
            );
            if (it != numbers.end() && *it == toFind) {
                int j = std::distance(numbers.begin(), it);

                if (i != j) {
                    return std::vector<int>{
                        std::min(i, j) + 1,
                        std::max(i, j) + 1 
                    };
                }
            }
        }

        return {};
    }
};