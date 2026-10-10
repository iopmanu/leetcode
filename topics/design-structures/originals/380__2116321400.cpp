class RandomizedSet {
    std::unordered_map<int, int> s;
    std::vector<int> a;

public:
    RandomizedSet() {
        
    }
    
    bool insert(int val) {
        if (s.contains(val)) {
            return false;
        }

        a.push_back(val);
        s[val] = a.size() - 1;

        return true;
    }
    
    bool remove(int val) {
        if (!s.contains(val)) {
            return false;
        }
        
        int back = a.back();
        a[s[val]] = back;
        s[back] = s[val];
        s.erase(val);
        a.pop_back();

        return true;
    }
    
    int getRandom() {
        return a[std::rand() % a.size()];
    }
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */