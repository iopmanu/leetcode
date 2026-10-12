class Solution {
public:
    vector<int> successfulPairs(vector<int>& spells, vector<int>& potions, long long success) {
        std::vector<int> result(spells.size(), 0);
        std::sort(potions.begin(), potions.end());
        for (int i = 0; i < spells.size(); i++) {
            int spell = spells[i];
            long left = 0; int right = potions.size() - 1;
            while (left <= right) {
                int mid = left + ((right - left) >> 1);
                if (1LL * spell * potions[mid] < success) {
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }

            result[i] = potions.size() - left;
        }

        return result;
    }
};