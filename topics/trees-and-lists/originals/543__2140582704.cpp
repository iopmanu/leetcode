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
};