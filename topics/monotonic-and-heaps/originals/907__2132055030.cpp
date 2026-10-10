class Solution {
public:
    int sumSubarrayMins(vector<int>& arr) {
        constexpr long long MOD = 1'000'000'007;

        long long result = 0;
        std::deque<int> s;

        for (int i = 0; i <= arr.size(); ++i) {
            while (!s.empty() &&
                   (i == arr.size() || arr[i] < arr[s.back()])) {
                int index = s.back();
                s.pop_back();

                int l = s.empty() ? -1 : s.back();

                result += static_cast<long long>(arr[index])
                        * (index - l)
                        * (i - index);

                result %= MOD;
            }

            if (i < arr.size()) {
                s.push_back(i);
            }
        }

        return static_cast<int>(result);
    }
};