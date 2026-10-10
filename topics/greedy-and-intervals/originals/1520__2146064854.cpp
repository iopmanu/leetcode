class Solution {
public:
    vector<string> maxNumOfSubstrings(string s) {
        int count[26] = {};
        int first[26], last[26];

        std::fill(first, first + 26, -1);
        std::fill(last, last + 26, -1);

        std::vector<int> order{};

        for (int i = 0; i < s.size(); ++i) {
            int ch = s[i] - 'a';

            if (count[ch] == 0) {
                first[ch] = i;
                order.push_back(ch);
            }

            ++count[ch];
            last[ch] = i;
        }

        std::vector<std::string> result;
        deque<array<int, 3>> q{};

        for (int ch : order) {
            q.push_front({first[ch], last[ch], count[ch]});

            int left = INT_MAX;
            int right = INT_MIN;
            int total = 0;

            for (auto& item : q) {
                total += item[2];
                left = std::min(left, item[0]);
                right = std::max(right, item[1]);

                if (total == right - left + 1) {
                    break;
                }
            }

            if (total == right - left + 1) {
                result.push_back(s.substr(left, right - left + 1));
                q.clear();
            }
        }

        return result;
    }
};