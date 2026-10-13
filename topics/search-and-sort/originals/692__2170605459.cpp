class Solution {
    using TVector = std::vector<std::pair<std::string, int>>;
public:
    vector<string> topKFrequent(vector<string>& words, int k) {
        std::unordered_map<std::string, int> counts{};
        for (auto&& w : words) {
            ++counts[w];
        }

        TVector pairs{};
        for (auto&& [k, v] : counts) {
            pairs.push_back(std::make_pair(k, v));
        }
        
        quickselect(pairs, 0, pairs.size() - 1, pairs.size() - k - 1);

        std::vector<std::string> result{};
        for (int i = pairs.size() - k; i < pairs.size(); i++) {
            result.push_back(pairs[i].first);
        }

        std::sort(result.begin(), result.end(), [&counts](const std::string& a, const std::string& b) {
            if (counts[a] != counts[b]) {
                return counts[a] > counts[b];
            }
            return a < b;
        });

        return result;
    }

    bool less(const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
        if (a.second != b.second) {
            return a.second < b.second;
        }
        return a.first > b.first; 
    }

    void quickselect(TVector& pairs, int left, int right, int k) {
        if (left >= right) {
            return;
        }

        int mid = left + (right - left) / 2;
        auto pivot = pairs[mid];
        int l = left; int r = right;
        while (l <= r) {
            while (less(pairs[l], pivot)) {
                ++l;
            }

            while (less(pivot, pairs[r])) {
                --r;
            }

            if (l <= r) {
                std::swap(pairs[l++], pairs[r--]);
            }
        }

        if (k >= l) {
            quickselect(pairs, l, right, k);
        } else if (k <= r) {
            quickselect(pairs, left, r, k);
        }
    }
};