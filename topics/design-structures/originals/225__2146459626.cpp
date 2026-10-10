class MyStack {
    std::queue<int> f;
    std::queue<int> s;

public:
    MyStack() {
        
    }
    
    void push(int x) {
        s.push(x);

        while (!f.empty()) {
            s.push(f.front());
            f.pop();
        }

        std::swap(f, s);
    }
    
    int pop() {
        int v = f.front();
        f.pop();
        return v;
    }
    
    int top() {
        return f.front();
    }
    
    bool empty() {
        return f.empty();
    }
};

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */