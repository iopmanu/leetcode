class Solution {
public:
    bool canReach(string s, int minJump, int maxJump) {
        std::deque<size_t> q;
        q.push_back(0);

        int farthest = 0;

        while (!q.empty()) {
            int i = q.front();
            q.pop_front();

            if (i == s.size() - 1) {
                return true;
            }

            int start = max(i + minJump, farthest + 1);
            int end = min(i + maxJump, (int)s.size() - 1);

            for (int j = start; j <= end; ++j) {
                if (s[j] == '0') {
                    q.push_back(j);
                }
            }

            farthest = max(farthest, end);
        }

        return false;
    }
};