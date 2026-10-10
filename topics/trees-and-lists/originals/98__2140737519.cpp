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
    bool isValidBST(TreeNode* root) {
        std::function<bool(TreeNode*, long long, long long)> traverse = [&](TreeNode* current, long long min, long long max) {
            if (current == nullptr) {
                return true;
            }

            if (current->val >= max || current->val <= min) {
                return false;
            }

            return traverse(current->left, min, current->val) 
                    && traverse(current->right, current->val, max);

            return true;
        };

        long long start = INT_MIN - 1LL;
        long long end = INT_MAX + 1LL;

        return traverse(root, start, end);
    }
};