#include <algorithm>
#include <functional>
#include <queue>
#include <utility>
#include <vector>

int findMaximumDistance(const std::vector<std::vector<int>>& arrays) {
    using Candidate = std::pair<int, std::size_t>;

    // A min-heap trimmed to two elements keeps the two largest maxima.
    std::priority_queue<Candidate, std::vector<Candidate>, std::greater<Candidate>> largest;
    // A max-heap trimmed to two elements keeps the two smallest minima.
    std::priority_queue<Candidate> smallest;

    for (std::size_t i = 0; i < arrays.size(); ++i) {
        largest.emplace(arrays[i].back(), i);
        if (largest.size() > 2) {
            largest.pop();
        }

        smallest.emplace(arrays[i].front(), i);
        if (smallest.size() > 2) {
            smallest.pop();
        }
    }

    const Candidate secondLargest = largest.top();
    largest.pop();
    const Candidate globalLargest = largest.top();

    const Candidate secondSmallest = smallest.top();
    smallest.pop();
    const Candidate globalSmallest = smallest.top();

    if (globalLargest.second != globalSmallest.second) {
        return globalLargest.first - globalSmallest.first;
    }

    return std::max(
            globalLargest.first - secondSmallest.first,
            secondLargest.first - globalSmallest.first);
}
