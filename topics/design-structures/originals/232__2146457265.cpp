class MyQueue {
    std::stack<int> l;
    std::stack<int> r;

public:
    MyQueue() {
    }
    
    void push(int x) {
        l.push(x);
    }
    
    int pop() {
        int val = peek();
        r.pop();
        return val;
    }
    
    int peek() {
        if (r.empty()) {
            while (!l.empty()) {
                r.push(l.top());
                l.pop();
            }
        }

        int val = r.top();
        return val;
    }
    
    bool empty() {
        return l.empty() && r.empty();
    }
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */