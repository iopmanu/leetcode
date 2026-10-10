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
    int result = 0;

public:
    int averageOfSubtree(TreeNode* root) {
        recursive(root);
        return result;
    }

    std::pair<int, int> recursive(TreeNode* current) {
        if (current == nullptr) {
            return std::make_pair<int, int>(0, 0);
        }

        auto l = recursive(current->left);
        auto r = recursive(current->right);

        int newSum = l.first + r.first + current->val;
        auto newCount = l.second + r.second + 1;

        result += (newSum / newCount == current->val);

        return std::make_pair(newSum, l.second + r.second + 1);
    }
};