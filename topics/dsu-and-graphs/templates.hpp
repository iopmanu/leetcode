#pragma once

#include <algorithm>
#include <cstddef>
#include <deque>
#include <numeric>
#include <optional>
#include <stdexcept>
#include <utility>
#include <vector>

namespace patterns {

// Source: 1970/1489. Vertex ids are in [0, n); only roots have current size.
struct DSU {
    std::vector<int> parent;
    std::vector<int> size;

    explicit DSU(int n) {
        if (n < 0) throw std::invalid_argument("negative vertex count");
        parent.resize(n);
        size.assign(n, 1);
        std::iota(parent.begin(), parent.end(), 0);
        components = n;
    }

    int find(int i) {
        int root = i;
        while (parent[root] != root) root = parent[root];
        while (parent[i] != i) {
            int next = parent[i];
            parent[i] = root;
            i = next;
        }
        return root;
    }

    // Returns true exactly when two previously separate components merge.
    bool uni(int i, int j) {
        int rootI = find(i);
        int rootJ = find(j);
        if (rootI == rootJ) return false;
        if (size[rootI] < size[rootJ]) std::swap(rootI, rootJ);
        parent[rootJ] = rootI;
        size[rootI] += size[rootJ];
        --components;
        return true;
    }

    int componentSize(int i) { return size[find(i)]; }
    int componentCount() const { return components; }

private:
    int components = 0;
};

struct WeightedEdge {
    int from;
    int to;
    long long weight;
};

struct MstResult {
    long long cost = 0;
    std::vector<std::size_t> edgeIndices; // Positions in the original edge vector.
    bool connected = false;
};

// Undirected graph. Disconnected input returns its minimum spanning forest.
// Preconditions: valid endpoints; every intermediate cost fits long long.
inline MstResult kruskal(int n, const std::vector<WeightedEdge>& edges) {
    DSU dsu(n);
    std::vector<std::size_t> order(edges.size());
    std::iota(order.begin(), order.end(), 0);
    std::sort(order.begin(), order.end(), [&](std::size_t i, std::size_t j) {
        if (edges[i].weight != edges[j].weight) return edges[i].weight < edges[j].weight;
        return i < j;
    });

    MstResult result;
    for (std::size_t index : order) {
        const auto& edge = edges[index];
        if (!dsu.uni(edge.from, edge.to)) continue;
        result.cost += edge.weight;
        result.edgeIndices.push_back(index);
        if (dsu.componentCount() == 1) break;
    }
    result.connected = n == 0 || dsu.componentCount() == 1;
    return result;
}

// Source: 752/994. Unit-weight edges; mark distance when enqueuing.
// Valid graph/source ids required. Unreachable vertices have distance -1.
inline std::vector<int> multiSourceBfs(
    const std::vector<std::vector<int>>& graph, const std::vector<int>& sources
) {
    std::vector<int> distance(graph.size(), -1);
    std::deque<int> q;
    for (int source : sources) {
        if (distance[source] != -1) continue;
        distance[source] = 0;
        q.push_back(source);
    }
    while (!q.empty()) {
        int current = q.front();
        q.pop_front();
        for (int neighbor : graph[current]) {
            if (distance[neighbor] != -1) continue;
            distance[neighbor] = distance[current] + 1;
            q.push_back(neighbor);
        }
    }
    return distance;
}

// Source: 207. Edge u -> v means u must come before v.
// nullopt means a directed cycle; an empty vector means a valid empty DAG.
inline std::optional<std::vector<int>> topologicalOrder(
    const std::vector<std::vector<int>>& graph
) {
    std::vector<std::size_t> indegree(graph.size(), 0);
    for (const auto& neighbors : graph)
        for (int neighbor : neighbors) ++indegree[neighbor];

    std::deque<int> q;
    for (std::size_t i = 0; i < graph.size(); ++i)
        if (indegree[i] == 0) q.push_back(static_cast<int>(i));

    std::vector<int> order;
    order.reserve(graph.size());
    while (!q.empty()) {
        int current = q.front();
        q.pop_front();
        order.push_back(current);
        for (int neighbor : graph[current])
            if (--indegree[neighbor] == 0) q.push_back(neighbor);
    }
    if (order.size() != graph.size()) return std::nullopt;
    return order;
}

// Source: 695/200. Rectangular binary grid; consume one 4-connected island.
// Invalid start or water returns zero. Other components are unchanged.
inline int consumeIsland(std::vector<std::vector<int>>& grid, int row, int col) {
    if (grid.empty() || grid.front().empty()) return 0;
    int rows = static_cast<int>(grid.size());
    int cols = static_cast<int>(grid.front().size());
    if (row < 0 || row >= rows || col < 0 || col >= cols || grid[row][col] != 1) return 0;

    const std::pair<int, int> directions[]{{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    std::vector<std::pair<int, int>> stack{{row, col}};
    grid[row][col] = 0;
    int area = 0;
    while (!stack.empty()) {
        auto [i, j] = stack.back();
        stack.pop_back();
        ++area;
        for (auto [di, dj] : directions) {
            int nextI = i + di;
            int nextJ = j + dj;
            if (nextI < 0 || nextI >= rows || nextJ < 0 || nextJ >= cols) continue;
            if (grid[nextI][nextJ] != 1) continue;
            grid[nextI][nextJ] = 0;
            stack.push_back({nextI, nextJ});
        }
    }
    return area;
}

} // namespace patterns
