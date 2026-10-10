class Solution {
public:
    int maxFrequencyElements(vector<int>& nums) {
        std::unordered_map<int, int> freqs;
        int max_freq = 0;
        for (auto&& elem : nums) {
            freqs[elem] += 1;
            max_freq = max(max_freq, freqs[elem]);
        }

        int retval = 0;
        for (auto&& pair : freqs) {
            if (pair.second == max_freq) {
                retval += max_freq;
            }
        }

        return retval;
    }
};