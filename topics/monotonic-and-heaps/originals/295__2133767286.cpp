class MedianFinder {
    std::priority_queue<int, std::vector<int>, std::greater<int>> rightHeap{};
    std::priority_queue<int, std::vector<int>, std::less<int>> leftHeap{};

public:
    MedianFinder() {}
    
    void addNum(int num) {
        if (leftHeap.empty() || num < leftHeap.top()) {
            leftHeap.push(num);
        } else {
            rightHeap.push(num);
        }

        if (leftHeap.size() > rightHeap.size() + 1) {
            rightHeap.push(leftHeap.top());
            leftHeap.pop();
        } else if (rightHeap.size() > leftHeap.size()) {
            leftHeap.push(rightHeap.top());
            rightHeap.pop();
        }
    }
    
    double findMedian() {
        if ((rightHeap.size() + leftHeap.size()) % 2 == 0) {
            return ((double) leftHeap.top() + (double) rightHeap.top()) / 2;
        }

        return (double) leftHeap.top();
    }
};

// baseline: sorted vector (o(N) push + O(1) scan)

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */