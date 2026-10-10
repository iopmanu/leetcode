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
    int maxPathSum(TreeNode* root) {
        int result = INT_MIN;
        
        std::function<int(TreeNode*)> traverse = [&](TreeNode* current) {
            if (current == nullptr) {
                return 0;
            }

            auto leftGain = std::max(traverse(current->left), 0);
            auto rightGain = std::max(traverse(current->right), 0);

            result = std::max(leftGain + rightGain + current->val, result);

            return current->val + std::max(leftGain, rightGain);
        };

        traverse(root);
        return result;
    }
};