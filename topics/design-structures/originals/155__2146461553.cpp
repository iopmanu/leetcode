class MinStack {
    std::vector<std::pair<int, int>> storage{};
public:
    MinStack() {
        
    }
    
    void push(int value) {
        int min = storage.empty() ? value : std::min(storage.back().second, value);
        storage.emplace_back(std::make_pair(value, min));
    }
    
    void pop() {
        storage.pop_back();
    }
    
    int top() {
        return storage.back().first;
    }
    
    int getMin() {
        return storage.back().second ;
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(value);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */