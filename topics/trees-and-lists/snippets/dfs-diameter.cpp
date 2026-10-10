    int diameterOfBinaryTree(TreeNode* root) {
        int result = 0;
        std::function<int(TreeNode*)> dfs = [&](TreeNode* current) {
            if (current == nullptr) {
                return 0;
            }

            int left = dfs(current->left);
            int right = dfs(current->right);

            result = std::max(result, left + right);

            return 1 + std::max(left, right);
        };

        dfs(root);
        return result;
    }
