class Solution {
public:
    int totalFruit(vector<int>& fruits) {
        return collectFruits(fruits, 2);
    }

    int collectFruits(std::vector<int>& trees, int baskets) {
        int result = INT_MIN;
        
        int left = 0;
        std::unordered_map<int, int> frequencies{};
        int currentFrequencies = 0;
        
        for (int right = 0; right < trees.size(); ++right) {
            frequencies[trees[right]]++;
            ++currentFrequencies;
            
            while (frequencies.size() > baskets) {
                auto freq = --frequencies[trees[left]];
                --currentFrequencies;
                if (freq == 0) {
                    frequencies.erase(trees[left]);
                }
                ++left;
            }
            
            result = std::max(result, currentFrequencies);
        }
        
        return result == INT_MIN ? 0 : result;
    }
};