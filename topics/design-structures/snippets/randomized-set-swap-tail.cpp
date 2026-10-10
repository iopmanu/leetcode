class RandomizedSet {
   std::unordered_map<int, int> positions;
   std::vector<int> values;

public:
    RandomizedSet() {
    }
    
    bool insert(int val) {
        if (positions.contains(val)) {
            return false;
        }

        int pos = values.size();
        positions[val] = pos;
        values.emplace_back(val);
        return true;
    }
    
    bool remove(int val) {
        if (!positions.contains(val)) {
            return false;
        }

        int pos = positions[val];
        positions[values.back()] = pos;
        std::swap(values[pos], values.back());

        values.pop_back();
        positions.erase(val);

        return true;
    }
    
    int getRandom() {
        return values[std::rand() % values.size()];
    }
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */