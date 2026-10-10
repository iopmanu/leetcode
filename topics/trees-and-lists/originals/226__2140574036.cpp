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
    TreeNode* invertTree(TreeNode* root) {
        dfs(root);

        return root;
    }

    void dfs(TreeNode* current) {
        if (current == nullptr) {
            return;
        }

        TreeNode* tmp = current->left;
        current->left = current->right;
        current->right = tmp;

        dfs(current->left);
        dfs(current->right);
    }
};