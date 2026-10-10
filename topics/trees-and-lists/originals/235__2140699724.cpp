/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (p->val > q->val) {
            return lowestCommonAncestor(root, q, p);
        }

        std::function<TreeNode*(TreeNode*)> traverse = [&](TreeNode* current) -> TreeNode* 
        {
            if (current == nullptr) {
                return nullptr;
            }

            if (p->val <= current->val && q->val >= current->val) {
                return current;
            }

            if (p->val <= current->val && q->val <= current->val) {
                return traverse(current->left);
            }

            return traverse(current->right);
        };

        return traverse(root);
    }
};