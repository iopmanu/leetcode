class Solution {
    using TCounts = std::unordered_map<char, int>;
public:
    string rankTeams(vector<string>& votes) {
        std::vector<TCounts> places(votes[0].size(), TCounts{});
        for (const auto& vote : votes) {
            for (int i = 0; i < vote.size(); ++i) {
                ++places[i][vote[i]];
            }
        }

        std::string teams = votes[0];
        std::sort(teams.begin(), teams.end(), [&](char a, char b) {
            for (int i = 0; i < places.size(); i++) {
                int sa = places[i][a];
                int sb = places[i][b];
                if (sa != sb) {
                    return sa > sb;
                }
            }

            return a < b;
        });

        return teams;
    }
};