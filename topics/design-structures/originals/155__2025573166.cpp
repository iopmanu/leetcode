class MinStack {
private:
    std::stack<int> minStack;
    std::stack<int> stack;

public:
    MinStack() {}
    
    void push(int value) {
        minStack.push(minStack.empty() ? value : std::min(minStack.top(), value));
        stack.push(value);
    }
    
    void pop() {
        minStack.pop();
        stack.pop();
    }
    
    int top() {
        return stack.top();
    }
    
    int getMin() {
        return minStack.top();
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