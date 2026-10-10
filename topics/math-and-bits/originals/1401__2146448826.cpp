class Solution {
public:
    bool checkOverlap(int radius, int xCenter, int yCenter, int x1, int y1, int x2, int y2) {


        int projX = std::max(x1, std::min(xCenter, x2));
        int projY = std::max(y1, std::min(yCenter, y2));
        
        int dist = (xCenter - projX) * (xCenter - projX) + (yCenter - projY) * (yCenter - projY);

        return dist <= radius * radius;
    }
};