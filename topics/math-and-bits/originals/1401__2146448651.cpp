class Solution {
public:
    bool checkOverlap(int radius, int xCenter, int yCenter, int x1, int y1, int x2, int y2) {
        int dx = x2 - x1; int dy = y2 - y1;

        std::vector<int> closestPoint = {INT_MAX, INT_MAX, INT_MAX};
        using TPoints = std::vector<std::pair<int, int>>;
        for (auto [x, y] : TPoints{{x1, y1}, {x1, y2}, {x2, y1}, {x2, y2}}) {
            int dist = (xCenter - x) * (xCenter - x) + (yCenter - y) * (yCenter - y);
            if (dist < closestPoint[0]) {
                closestPoint[0] = dist;
                closestPoint[1] = x;
                closestPoint[2] = y;
            }
        }

        if (closestPoint[0] <= radius * radius) {
            return true;
        }

        int projX = std::max(x1, std::min(xCenter, x2));
        int projY = std::max(y1, std::min(yCenter, y2));
        
        int dist = (xCenter - projX) * (xCenter - projX) + (yCenter - projY) * (yCenter - projY);

        return dist <= radius * radius;
    }
};