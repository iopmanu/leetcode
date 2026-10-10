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

 /*
    inorder:
    left -> self -> right

    preorder:
    self -> left -> right

 */
class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        std::unordered_map<int, int> mapping{};
        for (int i = 0; i < inorder.size(); i++) {
            mapping[inorder[i]] = i;
        }

        TreeNode* root = new TreeNode(preorder[0], nullptr, nullptr);
        int preorderIdx = 0;

        std::function<TreeNode*(int, int)> traverse = [&](int start, int end) -> TreeNode* {
            if (start > end) {
                return nullptr;
            }

            int rootVal = preorder[preorderIdx++];
            TreeNode* root = new TreeNode(rootVal);
            int pivot = mapping[rootVal];

            root->left = traverse(start, pivot - 1);
            root->right = traverse(pivot + 1, end);

            return root;
        };

        return traverse(0, inorder.size() - 1);
    }
};