class Solution {
public:
    string evaluate(string s, vector<vector<string>>& knowledge) {
        std::unordered_map<std::string_view, std::string_view> mapping{};
        for (int i = 0; i < knowledge.size(); i++) {
            mapping[knowledge[i][0]] = std::string_view(knowledge[i][1]);
        }

        std::ostringstream os{};
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '(') {
                int start = i + 1;

                while (i < s.size() && s[i] != ')') {
                    i++;
                }

                std::string_view substr(s.data() + start, i - start);
                if (!mapping.contains(substr)) {
                    os << '?';
                } else {
                    os << mapping[substr];
                }
            } else {
                os << s[i];
            }
        }

        return os.str();
    }
};