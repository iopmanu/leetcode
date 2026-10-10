class KthLargest {
    std::priority_queue<int, std::vector<int>, std::greater<int>> pq{};
    int k;
public:
    KthLargest(int k, vector<int>& nums) : k(k) {
        for (int i = 0; i < nums.size(); ++i) {
            add(nums[i]);
        }
    }
    
    int add(int val) {
        pq.push(val);

        if (pq.size() > k) {
            pq.pop();
        }

        return pq.top();
    }
};

/**
 * Your KthLargest object will be instantiated and called as such:
 * KthLargest* obj = new KthLargest(k, nums);
 * int param_1 = obj->add(val);
 */