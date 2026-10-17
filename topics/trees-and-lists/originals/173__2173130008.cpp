class BSTIterator {
    std::stack<TreeNode*> stk;

    void pushAllLeft(TreeNode* node) {
        while (node != nullptr) {
            stk.push(node);
            node = node->left;
        }
    }

public:
    BSTIterator(TreeNode* root) {
        pushAllLeft(root);
    }
    
    int next() {
        TreeNode* currNode = stk.top();
        stk.pop();
        
        if (currNode->right != nullptr) {
            pushAllLeft(currNode->right);
        }
        
        return currNode->val;
    }
    
    bool hasNext() {
        return !stk.empty();
    }
};
