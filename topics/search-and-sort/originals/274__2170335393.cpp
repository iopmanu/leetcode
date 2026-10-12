class Solution {
public:
    int hIndex(vector<int>& citations) {
        std::sort(citations.rbegin(), citations.rend());
        for (int i = 0; i < citations.size(); i++) {
            if (i >= citations[i]) {
                return i;
            }
        }

        return citations.size();
    }
};