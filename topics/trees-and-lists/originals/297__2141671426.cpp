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
        if (!root) {
            return "";
        }

        std::unordered_map<TreeNode*, int> ids{};
        int nextId = 0;

        std::function<void(TreeNode*)> assignIds = [&](TreeNode* current) {
            if (!current) {
                return;
            }

            ids[current] = nextId++;

            assignIds(current->left);
            assignIds(current->right);
        };

        assignIds(root);

        std::string buffer;

        std::function<void(TreeNode*)> in = [&](TreeNode* current) {
            if (!current) {
                return;
            }

            in(current->left);

            buffer.append(std::to_string(ids[current]));
            buffer.push_back(':');
            buffer.append(std::to_string(current->val));
            buffer.push_back(',');

            in(current->right);
        };

        in(root);

        if (!buffer.empty() && buffer.back() == ',') {
            buffer.pop_back();
        }

        buffer.push_back('|');

        std::function<void(TreeNode*)> pre = [&](TreeNode* current) {
            if (!current) {
                return;
            }

            buffer.append(std::to_string(ids[current]));
            buffer.push_back(':');
            buffer.append(std::to_string(current->val));
            buffer.push_back(',');

            pre(current->left);
            pre(current->right);
        };

        pre(root);

        if (!buffer.empty() && buffer.back() == ',') {
            buffer.pop_back();
        }

        return buffer;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        if (data.empty()) {
            return nullptr;
        }

        auto separator = data.find('|');

        std::string inorderData = data.substr(0, separator);
        std::string preorderData = data.substr(separator + 1);

        std::vector<std::pair<int, int>> inorder{};
        std::vector<std::pair<int, int>> preorder{};

        auto parse = [](const std::string& input) {
            std::vector<std::pair<int, int>> result{};

            int start = 0;
            while (start < input.size()) {
                int end = input.find(',', start);
                if (end == std::string::npos) {
                    end = input.size();
                }

                int colon = input.find(':', start);

                int id = std::stoi(
                    input.substr(start, colon - start)
                );

                int value = std::stoi(
                    input.substr(colon + 1, end - colon - 1)
                );

                result.push_back({id, value});

                start = end + 1;
            }

            return result;
        };

        inorder = parse(inorderData);
        preorder = parse(preorderData);

        std::unordered_map<int, int> mapping{};
        for (int i = 0; i < inorder.size(); ++i) {
            mapping[inorder[i].first] = i;
        }

        int preorderIdx = 0;

        std::function<TreeNode*(int, int)> build =
            [&](int start, int end) -> TreeNode* {
                if (start > end) {
                    return nullptr;
                }

                auto [rootId, rootVal] = preorder[preorderIdx++];

                TreeNode* root = new TreeNode(rootVal);
                int pivot = mapping[rootId];

                root->left = build(start, pivot - 1);
                root->right = build(pivot + 1, end);

                return root;
            };

        return build(0, inorder.size() - 1);
    }
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));