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
    int kthSmallest(TreeNode* root, int k) {
        int result = 0;
        int count = 0;

        std::function<void(TreeNode*)> traverse = [&](TreeNode* current) {
            if (current == nullptr) {
                return;
            }

            traverse(current->left);

            if (++count == k) {
                result = current->val;
            }

            traverse(current->right);
        };

        traverse(root);
        return result;
    }
};