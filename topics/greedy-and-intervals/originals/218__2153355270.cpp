class Solution {
    
public:
    vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
        std::vector<std::vector<int>> events{};
        for (int i = 0; i < buildings.size(); i++) {
            events.push_back({buildings[i][0], buildings[i][2]});
            events.push_back({buildings[i][1], -buildings[i][2]});
        }
        std::sort(events.begin(), events.end(), [](auto& l, auto& r) {
            if (l[0] != r[0]) {
                return l[0] < r[0];
            }

            return l[1] > r[1];
        });

        std::vector<std::vector<int>> result{};
        std::multiset<int, std::greater<>> heights{};
        heights.insert(0);
        int prevHeight = 0;
        for (int i = 0; i < events.size(); i++) {
            int h = events[i][1];
            if (h < 0) {
                heights.erase(heights.find(-h));
            } else {
                heights.insert(h);
            }

            int currentHeight = *heights.begin();
            if (currentHeight != prevHeight) {
                result.push_back({events[i][0], currentHeight});
                prevHeight = currentHeight;
            }
        }

        return result;
    }
};