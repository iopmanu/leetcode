class Solution {
public:
    int totalNumbers(vector<int>& digits) {
        std::unordered_map<int, int> freq{};
        bool hasEven = false;
        for (int num : digits) {
            freq[num] += (freq[num] < 3);
            hasEven |= (num%2==0);
        }

        if (!hasEven) {
            return 0;
        }

        int result = 0;
        for (int i = 1; i < 10; ++i) {
            if (freq[i] <= 0) {
                continue;
            }
            freq[i]--;

            for (int j = 0; j < 10; ++j) {
                if (freq[j] <= 0) {
                    continue;
                }
                freq[j]--;
                for (int k = 0; k < 10; k+=2) {
                    if (freq[k] <= 0) {
                        continue;
                    }
                    result += 1;
                }
                freq[j]++;
            }

            freq[i]++;
        }

        return result;
    }
};