class Solution {
public:
    bool isRectangleOverlap(vector<int>& rec1, vector<int>& rec2) {
        auto intersect = [&](const auto& l, const auto& r) {
            return (l[2] > r[0] && l[0] < r[2]) 
                && (
                    (l[1] < r[3] && l[3] > r[1])
                );
        };

        return intersect(rec1, rec2) | intersect(rec2, rec1);
    }
};