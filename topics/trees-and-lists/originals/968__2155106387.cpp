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
    int minCameraCover(TreeNode* root) {
        std::unordered_set<TreeNode*> covered{};
        covered.insert(nullptr);

        int result = 0;
        std::function<void(TreeNode*, TreeNode*)> traverse = [&](TreeNode* current, TreeNode* parent) {
            if (current == nullptr) {
                return;
            }

            traverse(current->left, current);
            traverse(current->right, current);

            if (parent == nullptr && !covered.contains(current) 
                || !covered.contains(current->left) || !covered.contains(current->right)) {
                
                ++result;
                covered.insert(current);
                covered.insert(parent);
                covered.insert(current->left);
                covered.insert(current->right);
            }
        };

        traverse(root, nullptr);
        return result;
    }
};