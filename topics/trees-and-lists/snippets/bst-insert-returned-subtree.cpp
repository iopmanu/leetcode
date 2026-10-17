    TreeNode* insertIntoBST(TreeNode* root, int val) {
        std::function<TreeNode*(TreeNode*)> recursive = [&](TreeNode* current) {
            if (current == nullptr) {
                return new TreeNode(val);
            }

            if (current->val < val) {
                current->right = recursive(current->right);
            } else {
                current->left = recursive(current->left);
            }

            return current;
        };

        return recursive(root);
    }
