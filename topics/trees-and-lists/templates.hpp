#pragma once

#include <algorithm>
#include <charconv>
#include <climits>
#include <cstdlib>
#include <memory>
#include <optional>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

namespace patterns {

// All raw node pointers are non-owning links. Returned new trees/lists belong to
// the caller; destroyTree/destroyList/destroyRandomList release their nodes.
struct ListNode {
    int val;
    ListNode* next;
    explicit ListNode(int value = 0, ListNode* nextNode = nullptr)
        : val(value), next(nextNode) {}
};
struct RandomNode {
    int val;
    RandomNode* next = nullptr;
    RandomNode* random = nullptr;
    explicit RandomNode(int value) : val(value) {}
};
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    explicit TreeNode(int value, TreeNode* leftNode = nullptr, TreeNode* rightNode = nullptr)
        : val(value), left(leftNode), right(rightNode) {}
};

// Preconditions: an acyclic next chain / a proper tree, with uniquely owned nodes.
inline void destroyList(ListNode* head) {
    while (head) { auto* next = head->next; delete head; head = next; }
}
inline void destroyRandomList(RandomNode* head) {
    // Random edges are aliases, never separate ownership edges.
    while (head) { auto* next = head->next; delete head; head = next; }
}
inline void destroyTree(TreeNode* root) {
    if (!root) { return; }
    destroyTree(root->left); destroyTree(root->right); delete root;
}
using TreeOwner = std::unique_ptr<TreeNode, decltype(&destroyTree)>;

// 206: current begins the untouched suffix; prev heads the reversed prefix.
inline ListNode* reverseList(ListNode* head) {
    ListNode* prev = nullptr;
    while (head) {
        auto* next = head->next;
        head->next = prev;
        prev = head;
        head = next;
    }
    return prev;
}

// 143: split, reverse the second half, then weave. Reuses every input node.
inline void reorderList(ListNode* head) {
    if (!head || !head->next) { return; }
    auto* slow = head; auto* fast = head;
    while (fast->next && fast->next->next) {
        slow = slow->next; fast = fast->next->next;
    }
    auto* second = slow->next;
    slow->next = nullptr;
    second = reverseList(second);
    auto* first = head;
    while (second) {
        auto* nextFirst = first->next;
        auto* nextSecond = second->next;
        first->next = second; second->next = nextFirst;
        first = nextFirst; second = nextSecond;
    }
}

// 21: disjoint sorted input chains; ownership transfers into the returned chain.
inline ListNode* mergeSortedLists(ListNode* left, ListNode* right) {
    ListNode dummy;
    auto* tail = &dummy;
    while (left && right) {
        auto*& chosen = left->val <= right->val ? left : right;
        tail->next = chosen; chosen = chosen->next; tail = tail->next;
    }
    tail->next = left ? left : right;
    return dummy.next;
}

// 25: probe a complete block before changing any link. Short tail stays intact.
inline ListNode* reverseKGroup(ListNode* head, int k) {
    if (k <= 0) { throw std::invalid_argument("k must be positive"); }
    if (k == 1) { return head; }
    auto* current = head;
    for (int i = 0; i < k; ++i) {
        if (!current) { return head; }
        current = current->next;
    }
    current = head;
    ListNode* prev = nullptr;
    for (int i = 0; i < k; ++i) {
        auto* next = current->next;
        current->next = prev; prev = current; current = next;
    }
    head->next = reverseKGroup(current, k);
    return prev;
}

// 19: preserve the source's length-first approach; a stack sentinel removes the
// head special case. This owning-list version deletes the removed node.
inline ListNode* removeNthFromEnd(ListNode* head, int n) {
    int length = 0;
    for (auto* current = head; current; current = current->next) { ++length; }
    if (n <= 0 || n > length) { throw std::invalid_argument("n outside list"); }
    ListNode dummy(0, head);
    auto* prev = &dummy;
    for (int i = 0; i < length - n; ++i) { prev = prev->next; }
    auto* removed = prev->next;
    prev->next = removed->next; delete removed;
    return dummy.next;
}

// 138: next must be acyclic; every random target must be null or in that chain.
inline RandomNode* copyRandomList(const RandomNode* head) {
    std::unordered_map<const RandomNode*, RandomNode*> mapping;
    mapping.emplace(nullptr, nullptr);
    std::vector<std::unique_ptr<RandomNode>> owned;
    for (auto* current = head; current; current = current->next) {
        owned.push_back(std::make_unique<RandomNode>(current->val));
        mapping.emplace(current, owned.back().get());
    }
    for (auto* current = head; current; current = current->next) {
        auto* copy = mapping.at(current);
        copy->next = mapping.at(current->next);
        copy->random = mapping.at(current->random);
    }
    auto* result = mapping.at(head);
    for (auto& node : owned) { static_cast<void>(node.release()); }
    return result;
}

struct TreeStats {
    int height = 0;               // Nodes on the longest downward path.
    int diameter = 0;             // Edges on the longest arbitrary path.
    bool balanced = true;
    long long sum = 0;
    int count = 0;
    std::optional<long long> maxPathSum; // Empty only for an empty tree.
};

// 104/110/543/124/2265: combine child summaries once, in postorder.
inline TreeStats measureTree(const TreeNode* root) {
    struct State { TreeStats stats; long long downwardGain = 0; };
    auto dfs = [&](auto&& self, const TreeNode* node) -> State {
        if (!node) { return {}; }
        auto left = self(self, node->left);
        auto right = self(self, node->right);
        TreeStats result;
        result.height = 1 + std::max(left.stats.height, right.stats.height);
        result.diameter = std::max({left.stats.diameter, right.stats.diameter,
                                   left.stats.height + right.stats.height});
        result.balanced = left.stats.balanced && right.stats.balanced &&
                          std::abs(left.stats.height - right.stats.height) <= 1;
        result.sum = left.stats.sum + right.stats.sum + node->val;
        result.count = left.stats.count + right.stats.count + 1;
        long long leftGain = std::max(0LL, left.downwardGain);
        long long rightGain = std::max(0LL, right.downwardGain);
        long long best = node->val + leftGain + rightGain;
        if (left.stats.maxPathSum) { best = std::max(best, *left.stats.maxPathSum); }
        if (right.stats.maxPathSum) { best = std::max(best, *right.stats.maxPathSum); }
        result.maxPathSum = best;
        return {result, node->val + std::max(leftGain, rightGain)};
    };
    return dfs(dfs, root).stats;
}

// 98: every ancestor contributes an exclusive bound, not just the parent.
inline bool isValidBst(const TreeNode* root) {
    auto dfs = [&](auto&& self, const TreeNode* node, long long low, long long high) -> bool {
        if (!node) { return true; }
        return low < node->val && node->val < high &&
               self(self, node->left, low, node->val) &&
               self(self, node->right, node->val, high);
    };
    return dfs(dfs, root, static_cast<long long>(INT_MIN) - 1,
               static_cast<long long>(INT_MAX) + 1);
}

// 105: unique values are required. Throws before returning an inconsistent tree.
inline TreeNode* buildTree(const std::vector<int>& preorder, const std::vector<int>& inorder) {
    if (preorder.size() != inorder.size()) { throw std::invalid_argument("traversal sizes differ"); }
    std::unordered_map<int, int> position;
    const int n = static_cast<int>(inorder.size());
    for (int i = 0; i < n; ++i) {
        if (!position.emplace(inorder[i], i).second) { throw std::invalid_argument("duplicate value"); }
    }
    int next = 0;
    auto build = [&](auto&& self, int start, int end) -> TreeNode* {
        if (start >= end) { return nullptr; }
        if (next == n) { throw std::invalid_argument("short preorder"); }
        int value = preorder[next++];
        auto it = position.find(value);
        if (it == position.end() || it->second < start || it->second >= end) {
            throw std::invalid_argument("inconsistent traversals");
        }
        TreeOwner root(new TreeNode(value), destroyTree);
        root->left = self(self, start, it->second);
        root->right = self(self, it->second + 1, end);
        return root.release();
    };
    return build(build, 0, n);
}

// 297: null markers make preorder sufficient even when values repeat.
inline std::string serializeTree(const TreeNode* root) {
    std::ostringstream out;
    auto visit = [&](auto&& self, const TreeNode* node) -> void {
        if (!node) { out << "# "; return; }
        out << node->val << ' '; self(self, node->left); self(self, node->right);
    };
    visit(visit, root); return out.str();
}
inline TreeNode* deserializeTree(const std::string& data) {
    std::istringstream in(data);
    auto build = [&](auto&& self) -> TreeNode* {
        std::string token;
        if (!(in >> token)) { throw std::invalid_argument("missing tree token"); }
        if (token == "#") { return nullptr; }
        int value = 0;
        auto [end, error] = std::from_chars(token.data(), token.data() + token.size(), value);
        if (error != std::errc{} || end != token.data() + token.size()) {
            throw std::invalid_argument("invalid integer token");
        }
        TreeOwner root(new TreeNode(value), destroyTree);
        root->left = self(self); root->right = self(self);
        return root.release();
    };
    TreeOwner root(build(build), destroyTree);
    std::string extra;
    if (in >> extra) { throw std::invalid_argument("extra tree token"); }
    return root.release();
}

// 968: a three-state compression of the source's postorder covered-node set.
inline int minimumCameras(const TreeNode* root) {
    enum class Coverage { needsCamera, covered, hasCamera };
    int cameras = 0;
    auto dfs = [&](auto&& self, const TreeNode* node) -> Coverage {
        if (!node) { return Coverage::covered; }
        auto left = self(self, node->left); auto right = self(self, node->right);
        if (left == Coverage::needsCamera || right == Coverage::needsCamera) {
            ++cameras; return Coverage::hasCamera;
        }
        if (left == Coverage::hasCamera || right == Coverage::hasCamera) { return Coverage::covered; }
        return Coverage::needsCamera;
    };
    if (dfs(dfs, root) == Coverage::needsCamera) { ++cameras; }
    return cameras;
}

} // namespace patterns
