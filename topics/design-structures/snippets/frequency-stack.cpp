#include <set>
#include <unordered_map>
#include <vector>

class FreqStack {
    std::unordered_map<int, std::vector<int>> freqs{};
    std::unordered_map<int, int> route{};

    int maxFreq = -1;

public:
    FreqStack() {

    }
    
    void push(int val) {
        int freq = route[val];
        int newFreq = freq + 1;
        maxFreq = std::max(maxFreq, newFreq);
        freqs[newFreq].push_back(val);
        route[val] = newFreq;
    }
    
    int pop() {
        auto val = freqs[maxFreq].back();
        freqs[maxFreq].pop_back();
        route[val]--;
        maxFreq -= (freqs[maxFreq].empty());

        return val;
    }
};


/**
 * Your FreqStack object will be instantiated and called as such:
 * FreqStack* obj = new FreqStack();
 * obj->push(val);
 * int param_2 = obj->pop();
 */