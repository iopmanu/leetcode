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
    int sumNumbers(TreeNode* root) {
        int result = 0;
        int current = 0;

        std::function<int(TreeNode*, int)> recursion = [&](TreeNode* current, int sum) {
            if (current == nullptr) {
                return 0;
            }

            sum = sum * 10 + current->val;

            if (current->left == nullptr && current->right == nullptr) {
                return sum;
            }

            return recursion(current->left, sum) + recursion(current->right, sum);
        };

        return recursion(root, 0);
    }
};