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

        std::vector<int> buffer(10, -1);

        std::function<void(TreeNode*, int)> recursion = [&](TreeNode* current, int height) {
            if (current == nullptr) {
                return;
            }

            buffer[height] = current->val;

            if (current->left == nullptr && current->right == nullptr) {
                int value = 0;
                for (int i = 0; i <= height; i++) {
                    value += std::pow(10, (height - i))  * buffer[i];
                }

                result += value;
                return;
            }

            recursion(current->left, height + 1);
            recursion(current->right, height + 1);
            buffer[height] = -1;
        };

        recursion(root, 0);

        return result;
    }
};