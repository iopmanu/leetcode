#include "templates.hpp"

#include <algorithm>
#include <bit>
#include <functional>
#include <iostream>
#include <limits>
#include <random>
#include <stdexcept>
#include <string>

namespace {
void check(bool condition, const std::string& message) {
    if (!condition) throw std::runtime_error(message);
}

void testDsu() {
    patterns::DSU dsu(6);
    check(dsu.uni(1, 2), "first union must merge");
    check(!dsu.uni(2, 1), "repeated union must not merge");
    check(dsu.componentSize(1) == 2, "root component size");
    check(dsu.find(1) == dsu.find(2), "merged nodes share root");
    check(dsu.find(0) != dsu.find(1), "separate components");
    check(dsu.componentCount() == 5, "component count");
    patterns::DSU empty(0);
    check(empty.componentCount() == 0, "empty DSU");
    bool rejected = false;
    try { patterns::DSU invalid(-1); } catch (const std::invalid_argument&) { rejected = true; }
    check(rejected, "negative vertex count rejected");

    std::mt19937 random(1970);
    for (int trial = 0; trial < 100; ++trial) {
        int n = 1 + static_cast<int>(random() % 25);
        patterns::DSU actual(n);
        std::vector<int> label(n);
        for (int i = 0; i < n; ++i) label[i] = i;
        for (int step = 0; step < 100; ++step) {
            int a = static_cast<int>(random() % n);
            int b = static_cast<int>(random() % n);
            bool merged = label[a] != label[b];
            int oldLabel = label[b];
            int newLabel = label[a];
            check(actual.uni(a, b) == merged, "union versus relabel oracle");
            for (int& value : label) if (value == oldLabel) value = newLabel;
            for (int i = 0; i < n; ++i) {
                int size = static_cast<int>(std::count(label.begin(), label.end(), label[i]));
                check(actual.componentSize(i) == size, "random component size");
                check((actual.find(i) == actual.find(a)) == (label[i] == label[a]), "random connectivity");
            }
        }
    }
}

std::optional<long long> bruteMst(int n, const std::vector<patterns::WeightedEdge>& edges) {
    if (n <= 1) return 0;
    std::optional<long long> best;
    for (unsigned mask = 0; mask < (1U << edges.size()); ++mask) {
        if (std::popcount(mask) != n - 1) continue;
        std::vector<std::vector<bool>> reach(n, std::vector<bool>(n, false));
        for (int i = 0; i < n; ++i) reach[i][i] = true;
        long long cost = 0;
        for (std::size_t i = 0; i < edges.size(); ++i) {
            if ((mask & (1U << i)) == 0) continue;
            const auto& edge = edges[i];
            reach[edge.from][edge.to] = reach[edge.to][edge.from] = true;
            cost += edge.weight;
        }
        for (int k = 0; k < n; ++k)
            for (int i = 0; i < n; ++i)
                for (int j = 0; j < n; ++j)
                    reach[i][j] = reach[i][j] || (reach[i][k] && reach[k][j]);
        if (std::all_of(reach[0].begin(), reach[0].end(), [](bool value) { return value; })) {
            if (!best || cost < *best) best = cost;
        }
    }
    return best;
}

void testKruskal() {
    std::vector<patterns::WeightedEdge> edges{{0, 1, 4}, {1, 2, -1}, {0, 2, 2}};
    auto result = patterns::kruskal(3, edges);
    check(result.connected && result.cost == 1 && result.edgeIndices.size() == 2, "Kruskal triangle");
    auto disconnected = patterns::kruskal(3, {{0, 1, 5}});
    check(!disconnected.connected && disconnected.cost == 5, "explicit partial forest");
    check(patterns::kruskal(0, {}).connected, "empty forest is connected by convention");
    check(patterns::kruskal(1, {{0, 0, -100}}).cost == 0, "self loop cannot enter tree");
    check(patterns::kruskal(3, {{0, 1, 3000000000LL}, {1, 2, 3000000000LL}}).cost == 6000000000LL,
          "64-bit cost");
    std::mt19937 random(1489);
    for (int trial = 0; trial < 800; ++trial) {
        int n = 1 + static_cast<int>(random() % 5);
        int m = static_cast<int>(random() % 9);
        std::vector<patterns::WeightedEdge> graph;
        for (int i = 0; i < m; ++i) {
            graph.push_back({static_cast<int>(random() % n), static_cast<int>(random() % n),
                             static_cast<int>(random() % 11) - 5});
        }
        auto expected = bruteMst(n, graph);
        auto actual = patterns::kruskal(n, graph);
        check(actual.connected == expected.has_value(), "random MST connectivity");
        if (expected) {
            check(actual.cost == *expected, "random MST versus subset enumeration");
            check(actual.edgeIndices.size() == static_cast<std::size_t>(n - 1), "MST edge count");
        }
        long long sum = 0;
        std::vector<bool> seen(graph.size(), false);
        for (std::size_t index : actual.edgeIndices) {
            check(index < graph.size() && !seen[index], "returned original edge indices");
            seen[index] = true;
            sum += graph[index].weight;
        }
        check(sum == actual.cost, "chosen edge costs agree");
    }
}

void testBfs() {
    std::vector<std::vector<int>> graph{{1}, {2}, {}, {2}, {}};
    check(patterns::multiSourceBfs(graph, {0, 3, 0}) == std::vector<int>({0, 1, 1, 0, -1}), "multi-source BFS");
    check(patterns::multiSourceBfs({}, {}).empty(), "empty graph BFS");
    check(patterns::multiSourceBfs(graph, {}) == std::vector<int>(5, -1), "no sources");
    std::mt19937 random(994);
    for (int trial = 0; trial < 500; ++trial) {
        int n = 1 + static_cast<int>(random() % 12);
        std::vector<std::vector<int>> adj(n);
        std::vector<std::vector<int>> dist(n, std::vector<int>(n, 10000));
        std::vector<int> sources;
        for (int i = 0; i < n; ++i) {
            dist[i][i] = 0;
            if (random() % 3 == 0) sources.push_back(i);
            for (int j = 0; j < n; ++j) if (i != j && random() % 4 == 0) {
                adj[i].push_back(j);
                dist[i][j] = 1;
            }
        }
        for (int k = 0; k < n; ++k)
            for (int i = 0; i < n; ++i)
                for (int j = 0; j < n; ++j)
                    dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
        auto actual = patterns::multiSourceBfs(adj, sources);
        for (int node = 0; node < n; ++node) {
            int expected = 10000;
            for (int source : sources) expected = std::min(expected, dist[source][node]);
            check(actual[node] == (expected == 10000 ? -1 : expected), "BFS versus Floyd-Warshall");
        }
    }
}

void testTopological() {
    auto chain = patterns::topologicalOrder({{1}, {2}, {}});
    check(chain && *chain == std::vector<int>({0, 1, 2}), "chain order");
    check(!patterns::topologicalOrder({{1}, {0}}), "cycle rejected");
    check(!patterns::topologicalOrder({{0}}), "self-loop cycle");
    check(patterns::topologicalOrder({}).value().empty(), "empty DAG is valid");
    check(patterns::topologicalOrder({{1, 1}, {}}).has_value(), "parallel edges counted consistently");
    std::mt19937 random(207);
    for (int trial = 0; trial < 500; ++trial) {
        int n = 1 + static_cast<int>(random() % 12);
        std::vector<std::vector<int>> adj(n);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if (random() % 7 == 0) adj[i].push_back(j);
        std::vector<int> color(n, 0);
        std::function<bool(int)> visit = [&](int node) {
            if (color[node] == 1) return false;
            if (color[node] == 2) return true;
            color[node] = 1;
            for (int next : adj[node]) if (!visit(next)) return false;
            color[node] = 2;
            return true;
        };
        bool acyclic = true;
        for (int i = 0; i < n; ++i) if (!visit(i)) { acyclic = false; break; }
        auto actual = patterns::topologicalOrder(adj);
        check(actual.has_value() == acyclic, "Kahn versus three-color DFS");
        if (actual) {
            check(actual->size() == static_cast<std::size_t>(n), "all DAG nodes emitted");
            std::vector<int> position(n, -1);
            for (int i = 0; i < n; ++i) {
                check(position[(*actual)[i]] == -1, "no duplicate output vertex");
                position[(*actual)[i]] = i;
            }
            for (int i = 0; i < n; ++i)
                for (int j : adj[i]) check(position[i] < position[j], "every edge points forward");
        }
    }
}

void testIslandArea() {
    std::vector<std::vector<int>> grid{{1, 1, 0}, {0, 1, 0}, {1, 0, 1}};
    check(patterns::consumeIsland(grid, 0, 0) == 3, "connected land area");
    check(patterns::consumeIsland(grid, 0, 0) == 0, "land consumed once");
    check(grid[2][0] == 1 && grid[2][2] == 1, "diagonals stay separate");
    std::vector<std::vector<int>> empty;
    check(patterns::consumeIsland(empty, 0, 0) == 0, "empty grid");
    check(patterns::consumeIsland(grid, -1, 0) == 0, "outside start");
    std::mt19937 random(695);
    for (int trial = 0; trial < 400; ++trial) {
        int rows = 1 + static_cast<int>(random() % 10);
        int cols = 1 + static_cast<int>(random() % 10);
        std::vector<std::vector<int>> input(rows, std::vector<int>(cols));
        for (auto& row : input) for (int& cell : row) cell = static_cast<int>(random() % 2);
        auto original = input;
        int row = static_cast<int>(random() % rows);
        int col = static_cast<int>(random() % cols);
        // Independent fixed-point reachability, no DFS/BFS queue.
        std::vector<std::vector<bool>> seen(rows, std::vector<bool>(cols, false));
        seen[row][col] = input[row][col] == 1;
        bool changed = true;
        while (changed) {
            changed = false;
            for (int i = 0; i < rows; ++i) for (int j = 0; j < cols; ++j) {
                if (input[i][j] == 0 || seen[i][j]) continue;
                bool neighbor = (i > 0 && seen[i - 1][j]) || (i + 1 < rows && seen[i + 1][j]) ||
                                (j > 0 && seen[i][j - 1]) || (j + 1 < cols && seen[i][j + 1]);
                if (neighbor) { seen[i][j] = true; changed = true; }
            }
        }
        int expected = 0;
        for (auto& current : seen) expected += static_cast<int>(std::count(current.begin(), current.end(), true));
        check(patterns::consumeIsland(input, row, col) == expected, "island versus fixed-point reachability");
        for (int i = 0; i < rows; ++i) for (int j = 0; j < cols; ++j)
            check(input[i][j] == (seen[i][j] ? 0 : original[i][j]), "exact mutation footprint");
    }
}
} // namespace

int main(int argc, char** argv) {
    try {
        std::string group = argc > 1 ? argv[1] : "all";
        if (group == "all" || group == "dsu") testDsu();
        if (group == "all" || group == "kruskal") testKruskal();
        if (group == "all" || group == "bfs") testBfs();
        if (group == "all" || group == "topological") testTopological();
        if (group == "all" || group == "island") testIslandArea();
        std::cout << "dsu-and-graphs: " << group << " passed\n";
    } catch (const std::exception& error) {
        std::cerr << "FAIL: " << error.what() << '\n';
        return 1;
    }
}
