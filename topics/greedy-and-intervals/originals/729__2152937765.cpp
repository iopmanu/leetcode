class MyCalendar {
    std::map<int, int> intervals;
public:
    MyCalendar() {
    }
    
    bool book(int startTime, int endTime) {
        auto it = intervals.lower_bound(startTime);
        if (it != intervals.end() && it->first < endTime) {
            return false;
        }

        if (it != intervals.begin()) {
            auto prev = std::prev(it);
            if (prev->second > startTime) {
                return false;
            }
        }

        intervals[startTime] = endTime;
        return true;
    }
};

/**
 * Your MyCalendar object will be instantiated and called as such:
 * MyCalendar* obj = new MyCalendar();
 * bool param_1 = obj->book(startTime,endTime);
 */