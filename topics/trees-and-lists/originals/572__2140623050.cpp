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
    bool isSubtree(TreeNode* root, TreeNode* subRoot) {
        bool result = false;

        std::function<bool(TreeNode*, TreeNode*)> isSame = [&](TreeNode* l, TreeNode* r) {
            if (r == nullptr && l == nullptr) {
                return true;
            }
            
            if (l == nullptr || r == nullptr) {
                return false;
            }

            return l->val == r->val && isSame(l->left, r->left) && isSame(l->right, r->right);
        };

        std::function<bool(TreeNode*, TreeNode*)> isSubtree = [&](TreeNode* l, TreeNode* r) {
            if (l == nullptr) {
                return false;
            }

            if (isSame(l, r)) {
                return true;
            }

            return isSubtree(l->left, r) || isSubtree(l->right, r);
        };

        return isSubtree(root, subRoot);
    }
};