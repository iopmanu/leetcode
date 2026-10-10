class StockSpanner {
    std::stack<std::pair<int, int>> s{};
public:
    StockSpanner() {
        
    }
    
    int next(int price) {
        if (s.empty()) {
            s.push(std::make_pair(price, 1));
            return 1;
        }

        int days = 1;
        while (!s.empty() && s.top().first <= price) {
            days += s.top().second;
            s.pop();
        }

        s.push(std::make_pair(price, days));
        return days;
    }
};

// [100, 1] -> [100, 1], [80, 1], [60, 1] -> [100, 1], [80, 1], [70, 2]
// [100, 1], [80, 1], [70, 2], [60, 1] -> [100, 1], [80, 1], [75, 4]
// [100, 1], [85, 6]

/**
 * Your StockSpanner object will be instantiated and called as such:
 * StockSpanner* obj = new StockSpanner();
 * int param_1 = obj->next(price);
 */