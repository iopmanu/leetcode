    TreeNode* deleteNode(TreeNode* root, int key) {
        if (!root) return nullptr;

        if (key < root->val) {
            root->left = deleteNode(root->left, key);
        } else if (key > root->val) {
            root->right = deleteNode(root->right, key);
        } else {
            if (!root->left) {
                TreeNode* temp = root->right;
                delete root;
                return temp;
            } else if (!root->right) {
                TreeNode* temp = root->left;
                delete root;
                return temp;
            }

            TreeNode* tmp = root->left;
            while (tmp->right != nullptr) {
                tmp = tmp->right;
            }

            root->val = tmp->val;
            root->left = deleteNode(root->left, tmp->val);
        }
        return root;
    }
