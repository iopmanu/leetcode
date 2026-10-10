class Solution {
public:
    int threeSumMulti(vector<int>& arr, int target) {
        std::sort(arr.begin(), arr.end());

        int MOD = (int) 1e9 + 7;

        std::unordered_map<int, int> counts{};
        for (auto num : arr) {
            ++counts[num];
        }

        int result = 0;
        int i = 0;
        while (i < arr.size()) {
            int j = i; int k = arr.size() - 1;
            while (j < k) {
                int sum = arr[i] + arr[j] + arr[k];

                if (sum > target) {
                    k -= counts[arr[k]];
                } else if (sum < target) {
                    j += counts[arr[j]];
                } else {
                    if (arr[i] != arr[j] && arr[j] != arr[k] && arr[i] != arr[k]) {
                        result = (result + 1LL * counts[arr[i]] * counts[arr[j]] * counts[arr[k]]) % MOD;
                    } else if (arr[i] == arr[j] && arr[i] != arr[k]) {
                        result = (result + 1LL * counts[arr[i]] * (counts[arr[i]] - 1) * counts[arr[k]] / 2) % MOD;
                    } else if (arr[j] == arr[k] && arr[i] != arr[j]) {
                        result = (result + 1LL * counts[arr[j]] * (counts[arr[j]] - 1) * counts[arr[i]] / 2) % MOD;
                    } else {
                        result = (result + 1LL * counts[arr[i]] * (counts[arr[i]] - 1) * (counts[arr[i]] - 2) / 6) % MOD;
                    }

                    j += counts[arr[j]];
                    k -= counts[arr[k]];
                }
            }

            i += counts[arr[i]];
        }

        return result;
    }
};