class Solution {
public:
    vector<int> maxDepthAfterSplit(string seq) {
        int depth = 0;
        std::vector<int> result;
        for (char ch : seq) {
            if (ch == '(') {
                ++depth;
                result.push_back(depth % 2);
            } else {
                result.push_back(depth % 2);
                --depth;
            }
        }

        return result;
    }
};