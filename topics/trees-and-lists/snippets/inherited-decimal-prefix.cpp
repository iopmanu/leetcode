    int sumNumbers(TreeNode* root) {
        int result = 0;
        int current = 0;

        std::function<int(TreeNode*, int)> recursion = [&](TreeNode* current, int sum) {
            if (current == nullptr) {
                return 0;
            }

            sum = sum * 10 + current->val;

            if (current->left == nullptr && current->right == nullptr) {
                return sum;
            }

            return recursion(current->left, sum) + recursion(current->right, sum);
        };

        return recursion(root, 0);
    }
