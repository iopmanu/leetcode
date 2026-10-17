    vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
        std::vector<std::vector<int>> result{};
        std::vector<int> buffer{};

        std::function<void(TreeNode* current, std::vector<int>&, int)> recursive = [&](
            TreeNode* current, std::vector<int>& buffer, int sum 
        ) {
            if (current == nullptr) {
                return;
            }

            buffer.push_back(current->val);
            int currentSum = sum + current->val;

            if (current->left == nullptr && current->right == nullptr) {
                if (currentSum == targetSum) {
                    result.push_back(buffer);
                }
            }

            recursive(current->left, buffer, currentSum);
            recursive(current->right, buffer, currentSum);
            buffer.pop_back();
        };

        recursive(root, buffer, 0);
        return result;
    }
