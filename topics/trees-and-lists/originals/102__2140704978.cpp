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
    vector<vector<int>> levelOrder(TreeNode* root) {
        std::deque<TreeNode*> q{};
        q.push_back(root);

        if (!root) {
            return {};
        }

        std::vector<std::vector<int>> result{};
        while(!q.empty()) {
            int currentSize = q.size();

            std::vector<int> level{};
            for (int i = 0; i < currentSize; ++i) {
                TreeNode* current = q.front();
                q.pop_front();

                level.push_back(current->val);

                if (current->left != nullptr) {
                    q.push_back(current->left);
                }
                if (current->right) {
                    q.push_back(current->right);
                }
            }

            result.emplace_back(std::move(level));
        }

        return result;
    }
};