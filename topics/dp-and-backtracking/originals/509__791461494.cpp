class Solution {    
public:
    
    int fib(int n) {
    vector<int> calculations(n + 1, 0);
    
    if (n <= 1)
        return n;
    calculations[1] = 1;
    
    for (int i = 2; i <= n; i++) {
        calculations[i] = calculations[i - 1] + calculations[i - 2];
    }
    
    return calculations[n];
    }
};