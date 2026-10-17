/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
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
};