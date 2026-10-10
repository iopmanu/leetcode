class NumArray {
    std::vector<int> tree{};
    std::vector<int> arr{};
    int size = 0;

public:
    NumArray(vector<int>& nums) : arr(nums), size(nums.size()), tree(nums.size() + 1) {
        for (int i = 0; i < nums.size(); ++i) {
            tree[i + 1] = nums[i];
        }

        for (int i = 1; i <= size; i++) {
            int parent = i + (i & -i);
            if (parent <= size) {
                tree[parent] += tree[i];
            }
        }
    }
    
    void update(int index, int val) {
        int delta = val - arr[index];
        arr[index] = val;
        for (index++; index <= size; index += index & (-index)) {
            tree[index] += delta;
        }
    }

    int query(int index) {
        int sum = 0;
        for (index++; index > 0; index -= index & (-index)) {
            sum += tree[index];
        }

        return sum;
    }
    
    int sumRange(int left, int right) {
        if (left > right) {
            return 0;
        }

        return query(right) - query(left - 1);
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * obj->update(index,val);
 * int param_2 = obj->sumRange(left,right);
 */