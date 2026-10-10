#include <set>
#include <unordered_map>
#include <vector>

class FreqStack {
    // Хранит вектор из 3 элементов: {-частота, -таймстемп, значение}
    std::set<std::vector<int>> values{};
    
    std::unordered_map<int, int> freq_map{};
    std::unordered_map<int, std::vector<int>> timestamps_map{};
    int timer = 0;

public:
    FreqStack() {}
    
    void push(int val) {
        timer++;
        int current_freq = freq_map[val];

        if (current_freq > 0) {
            int last_ts = timestamps_map[val].back();
            values.erase({-current_freq, -last_ts, val});
        }

        current_freq++;
        freq_map[val] = current_freq;
        timestamps_map[val].push_back(timer);

        values.insert({-current_freq, -timer, val});
    }
    
    int pop() {
        auto toDelete = values.begin();
        int val = (*toDelete)[2];
        int current_freq = -(*toDelete)[0];
        
        values.erase(toDelete);
    
        timestamps_map[val].pop_back();
        current_freq--;

        if (current_freq > 0) {
            freq_map[val] = current_freq;
            int prev_ts = timestamps_map[val].back();
            values.insert({-current_freq, -prev_ts, val});
        } else {
            freq_map.erase(val);
            timestamps_map.erase(val);
        }

        return val;
    }
};


/**
 * Your FreqStack object will be instantiated and called as such:
 * FreqStack* obj = new FreqStack();
 * obj->push(val);
 * int param_2 = obj->pop();
 */