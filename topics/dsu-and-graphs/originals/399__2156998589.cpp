class Solution {
public:
    vector<double> calcEquation(
        vector<vector<string>>& equations,
        vector<double>& values, 
        vector<vector<string>>& queries
    ) {
        std::unordered_map<std::string, std::unordered_map<std::string, double>> edges{};
        for (int i = 0; i < equations.size(); i++) {
            auto l = equations[i][0]; auto r = equations[i][1];
            auto division = values[i];

            edges[l][r] = division;
            edges[r][l] = 1 / division;
        }

        std::function<double(const std::string&, const std::string&, std::unordered_set<std::string>&)> traverse = [&](
            const auto& start, const auto& end, std::unordered_set<std::string>& visited
        ) {
            if (!edges.contains(start)) {
                return -1.0;
            }

            if (edges[start].contains(end)) {
                return edges[start][end];
            }

            visited.insert(start);

            for (auto&& [neighbor, value] : edges[start]) {
                if (!visited.contains(neighbor)) {
                    double product = traverse(neighbor, end, visited);
                    if (product != -1.0) {
                        return value * product;
                    }
                }
            }

            return -1.0;
        };

        std::vector<double> result(queries.size(), -1.0);
        for (int i = 0; i < queries.size(); i++) {
            auto lq = queries[i][0]; auto rq = queries[i][1];
            std::unordered_set<std::string> visited{};
            result[i] = traverse(lq, rq, visited);
        }

        return result;
    }
};