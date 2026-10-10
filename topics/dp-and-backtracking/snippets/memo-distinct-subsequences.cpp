class Solution {
    std::unordered_map<long long, int> memoization;
public:
    int numDistinct(string s, string t) {
        return helper(s.size() - 1, t.size() - 1, s, t);
    }

    int helper(int i, int j, const string&s, const string&t) {
        if (j < 0) {
            return 1;
        }

        if (i < 0) {
            return 0;
        }
        
        long long key = ((long long) i << 32 | (long long) j);
        if (auto it = memoization.find(key); it != memoization.end()) {
            return it->second;
        }
        if (s[i] != t[j]) {
            memoization[key] = helper(i - 1, j, s, t);
        } else {
            memoization[key] = helper(i - 1, j - 1, s, t) + helper(i - 1, j, s, t);
        }

        return memoization[key];
    }
};