    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        std::deque<TreeNode*> queue{};
        queue.push_back(root);

        std::vector<std::vector<int>> result{};

        while (!queue.empty()) {
            int size = queue.size();

            std::vector<int> level{};
            for (int i = 0; i < size; i++) {
                TreeNode* current = queue.front();
                queue.pop_front();

                if (current == nullptr) {
                    continue;
                }

                level.push_back(current->val);
                queue.push_back(current->left);
                queue.push_back(current->right);
            }

            if (level.empty()) {
                continue;
            }

            if (result.size() % 2) {
                std::reverse(level.begin(), level.end());
            }

            result.push_back(std::move(level));
        }

        return result;
    }
