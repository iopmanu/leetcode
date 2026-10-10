/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        std::ostringstream os{};
        std::function<void(TreeNode*)> traverse = [&](TreeNode* current) {
            if (!current) {
                os << "# ";
                return;
            }

            os << std::to_string(current->val) << ' ';
            traverse(current->left);
            traverse(current->right);
        };

        traverse(root);
        return os.str();
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        std::istringstream in(data);
        std::function<TreeNode*()> traverse = [&]() -> TreeNode* {
            std::string val;
            in >> val;
            if (val == "#") {
                return nullptr;
            }

            TreeNode* root = new TreeNode(std::stoi(val));
            root->left = traverse();
            root->right = traverse();

            return root;
        };

        return traverse();
    }
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));