class Solution {
public:
    int longestCommonPrefix(vector<int>& arr1, vector<int>& arr2) {
        auto lPrefixes = getPrefixes(arr1);
        auto rPrefixes = getPrefixes(arr2);

        int result = 0;
        for (auto l : lPrefixes) {
            if (rPrefixes.contains(l)) {
                result = std::max(result, countDigits(l));
            }
        }

        return result;
    }

private:
    int countDigits(int number) {
        return number == 0 ? 1 : floor(log10(abs(number))) + 1;
    }

    std::unordered_set<int> getPrefixes(const std::vector<int>& arr) {
        std::unordered_set<int> prefixes = {};
        prefixes.reserve(arr.size() * 8);

        for (auto num : arr) {
            while (num != 0) { 
                prefixes.insert(num);
                num /= 10;
            }
        }

        return prefixes;
    }
};