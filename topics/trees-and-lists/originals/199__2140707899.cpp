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
    vector<int> rightSideView(TreeNode* root) {
        if (!root) {
            return {};
        }

        std::deque<TreeNode*> q{};
        q.push_back(root);

        std::vector<int> result{};
        while(!q.empty()) {
            int currentSize = q.size();
            result.push_back(q.back()->val);

            for (int i = 0; i < currentSize; ++i) {
                TreeNode* current = q.front();
                q.pop_front();

                if (current->left) {
                    q.push_back(current->left);
                }

                if (current->right) {
                    q.push_back(current->right);
                }
            }
        }

        return result;
    }
};