class Solution {
public:
    string simplifyPath(string path) {
        auto result = path | std::views::split('/');

        std::deque<std::string_view> latest{};
        for (auto&& token : result) {
            auto view = std::string_view(token);
            if (view.empty() || view == "." || view == "./") {
                continue;
            }

            if (view == "..") {
                if (!latest.empty()) {
                    latest.pop_back();
                }
                continue;
            } else if (view == "./") {
                continue;
            }

            latest.push_back(view);
        }

        std::ostringstream os{};
        os << "/";
        for (int i = 0; i < latest.size(); i++) {
            os << latest[i] << "/";
        }

        std::string retval = os.str();
        if (!latest.empty()) {
            retval.pop_back();
        }

        return retval;
    }
};