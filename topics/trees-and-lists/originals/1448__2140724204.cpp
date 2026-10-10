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
    int goodNodes(TreeNode* root) {
        std::function<int(TreeNode*, int)> traverse = [&](TreeNode* current, int currentMax) {
            if (current == nullptr) {
                return 0;
            }

            auto result = current->val >= currentMax;
            currentMax = std::max(current->val, currentMax);
            return result
                + traverse(current->left, currentMax)
                + traverse(current->right, currentMax);
        };

        return traverse(root, INT_MIN);
    }
};