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
    bool isSameTree(TreeNode* p, TreeNode* q) {
        bool result = true;
        std::function<void(TreeNode*, TreeNode*)> dfs = [&](TreeNode* l, TreeNode* r) {
            result &= !(l == nullptr ^ r == nullptr);
            if (!result || l == nullptr || r == nullptr) {
                return;
            }

            result &= (l->val == r->val);
            dfs(l->left, r->left);
            dfs(l->right, r->right);
        };

        dfs(p, q);
        return result;
    }
};