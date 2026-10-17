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
        std::vector<TreeNode*> pStack, qStack;

        std::function<bool(TreeNode*, std::vector<TreeNode*>&, TreeNode*)> fillTheStack = [&](
            TreeNode* current, std::vector<TreeNode*>& s, TreeNode* toFind
        ) {
            if (current == nullptr) {
                return false;
            }

            s.push_back(current);

            if (current == toFind) {
                return true;
            }

            if (fillTheStack(current->left, s, toFind) || fillTheStack(current->right, s, toFind)) {
                return true;
            }

            s.pop_back();
            return false;
        };

        fillTheStack(root, pStack, p);
        fillTheStack(root, qStack, q);

        TreeNode* lca = nullptr;
        for (int i = 0; i < std::min(pStack.size(), qStack.size()); ++i) {
            if (pStack[i] == qStack[i]) {
                lca = pStack[i];
            } else {
                break;
            }
        }

        return lca;
    }
};
