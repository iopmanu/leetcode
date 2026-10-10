#include "templates.hpp"
#include <algorithm>
#include <climits>
#include <iostream>
#include <numeric>
#include <random>
#include <set>
#include <stdexcept>
#include <vector>

namespace {
int failures = 0;
void check(bool condition, const char* name) {
    if (!condition) { std::cerr << "FAIL: " << name << '\n'; ++failures; }
}
patterns::ListNode* makeList(const std::vector<int>& values) {
    patterns::ListNode dummy; auto* tail = &dummy;
    for (int value : values) { tail->next = new patterns::ListNode(value); tail = tail->next; }
    return dummy.next;
}
std::vector<int> listValues(patterns::ListNode* head) {
    std::vector<int> result; std::set<patterns::ListNode*> seen;
    while (head && seen.insert(head).second) { result.push_back(head->val); head = head->next; }
    check(head == nullptr, "list remains acyclic");
    return result;
}
void traversals(const patterns::TreeNode* node, std::vector<int>& pre, std::vector<int>& in) {
    if (!node) { return; }
    pre.push_back(node->val); traversals(node->left, pre, in); in.push_back(node->val);
    traversals(node->right, pre, in);
}
int bruteCameras(const std::vector<patterns::TreeNode*>& nodes) {
    const int n = static_cast<int>(nodes.size()); int best = n;
    for (unsigned mask = 0; mask < (1U << n); ++mask) {
        std::set<const patterns::TreeNode*> covered; int count = 0;
        for (int i = 0; i < n; ++i) {
            if ((mask & (1U << i)) == 0) { continue; }
            ++count; covered.insert(nodes[i]); covered.insert(nodes[i]->left); covered.insert(nodes[i]->right);
            for (auto* parent : nodes) {
                if (parent->left == nodes[i] || parent->right == nodes[i]) { covered.insert(parent); }
            }
        }
        if (std::all_of(nodes.begin(), nodes.end(), [&](auto* p) { return covered.contains(p); })) {
            best = std::min(best, count);
        }
    }
    return best;
}
long long brutePathSum(const std::vector<patterns::TreeNode*>& nodes) {
    long long best = LLONG_MIN;
    for (auto* start : nodes) {
        auto visit = [&](auto&& self, const patterns::TreeNode* node,
                         const patterns::TreeNode* prev, long long sum) -> void {
            sum += node->val; best = std::max(best, sum);
            for (auto* other : nodes) {
                if (other != prev && (node->left == other || node->right == other ||
                    other->left == node || other->right == node)) { self(self, other, node, sum); }
            }
        };
        visit(visit, start, nullptr, 0);
    }
    return best;
}
}

int main() {
    using namespace patterns;
    auto* head = makeList({1, 2, 3}); head = reverseList(head);
    check(listValues(head) == std::vector<int>({3, 2, 1}), "reverse links"); destroyList(head);
    head = makeList({1, 2, 3, 4, 5}); reorderList(head);
    check(listValues(head) == std::vector<int>({1, 5, 2, 4, 3}), "odd reorder"); destroyList(head);
    head = mergeSortedLists(makeList({1, 3, 5}), makeList({2, 4}));
    check(listValues(head) == std::vector<int>({1, 2, 3, 4, 5}), "dummy merge"); destroyList(head);
    head = reverseKGroup(makeList({1, 2, 3, 4, 5}), 2);
    check(listValues(head) == std::vector<int>({2, 1, 4, 3, 5}), "whole groups only");
    head = removeNthFromEnd(head, 5);
    check(listValues(head) == std::vector<int>({1, 4, 3, 5}), "remove head"); destroyList(head);
    bool rejected = false;
    try { static_cast<void>(removeNthFromEnd(nullptr, 1)); } catch (const std::invalid_argument&) { rejected = true; }
    check(rejected, "reject invalid n");

    head = removeNthFromEnd(makeList({9}), 1);
    check(head == nullptr, "remove sole node"); destroyList(head);
    check(reverseList(nullptr) == nullptr && mergeSortedLists(nullptr, nullptr) == nullptr,
          "empty pointer helpers");
    rejected = false;
    try { static_cast<void>(reverseKGroup(nullptr, 0)); } catch (const std::invalid_argument&) { rejected = true; }
    check(rejected, "reject nonpositive group size");

    auto* first = new RandomNode(7); auto* second = new RandomNode(13);
    first->next = second; first->random = second; second->random = second;
    auto* copy = copyRandomList(first);
    check(copy && copy != first && copy->next != second && copy->val == 7 && copy->next &&
          copy->next->val == 13 && copy->random == copy->next && copy->next->random == copy->next,
          "clone preserves identities and random edges");
    destroyRandomList(first); destroyRandomList(copy);
    check(copyRandomList(nullptr) == nullptr, "clone empty");

    auto* tree = new TreeNode(2, new TreeNode(1), new TreeNode(3));
    auto stats = measureTree(tree);
    check(stats.height == 2 && stats.diameter == 2 && stats.balanced && stats.count == 3 &&
          stats.sum == 6 && stats.maxPathSum == 6, "postorder aggregates");
    check(isValidBst(tree), "valid strict BST"); tree->right->val = 2;
    check(!isValidBst(tree), "reject duplicate BST key"); tree->right->val = 3;
    check(serializeTree(tree) == "2 1 # # 3 # # ", "preorder null encoding");
    auto* restored = deserializeTree("2 1 # # 3 # # ");
    check(serializeTree(restored) == serializeTree(tree), "codec round trip");
    destroyTree(restored); destroyTree(tree);
    tree = new TreeNode(10, new TreeNode(5), new TreeNode(15, new TreeNode(6), nullptr));
    check(!isValidBst(tree), "BST ancestor bound violation"); destroyTree(tree);
    tree = new TreeNode(INT_MIN, nullptr, new TreeNode(INT_MAX));
    check(isValidBst(tree), "BST int extremes"); destroyTree(tree);
    tree = buildTree({3, 9, 20, 15, 7}, {9, 3, 15, 20, 7});
    check(serializeTree(tree) == "3 9 # # 20 15 # # 7 # # ", "traversal reconstruction"); destroyTree(tree);
    for (const auto& text : {"", "1 #", "# #", "1x # #"}) {
        rejected = false;
        try { auto* bad = deserializeTree(text); destroyTree(bad); }
        catch (const std::invalid_argument&) { rejected = true; }
        check(rejected, "malformed codec rejected");
    }
    rejected = false;
    try { auto* bad = buildTree({1, 2, 3}, {3, 1, 2}); destroyTree(bad); }
    catch (const std::invalid_argument&) { rejected = true; }
    check(rejected, "inconsistent traversals rejected");
    check(minimumCameras(nullptr) == 0 && measureTree(nullptr).count == 0, "empty tree");

    std::mt19937 rng(0x7ee123U);
    for (int trial = 0; trial < 300; ++trial) {
        int n = static_cast<int>(rng() % 25); std::vector<int> values(n);
        std::iota(values.begin(), values.end(), 0); head = makeList(values); reorderList(head);
        std::vector<int> expected;
        for (int l = 0, r = n - 1; l <= r; ++l, --r) {
            expected.push_back(l); if (l < r) { expected.push_back(r); }
        }
        check(listValues(head) == expected, "seeded reorder versus index model"); destroyList(head);
        int k = 1 + static_cast<int>(rng() % 7); head = reverseKGroup(makeList(values), k);
        for (int i = 0; i + k <= n; i += k) { std::reverse(values.begin() + i, values.begin() + i + k); }
        check(listValues(head) == values, "seeded groups versus vector model"); destroyList(head);
    }
    for (int trial = 0; trial < 140; ++trial) {
        int n = 1 + static_cast<int>(rng() % 9); std::vector<TreeNode*> nodes;
        for (int i = 0; i < n; ++i) {
            nodes.push_back(new TreeNode(i - 5));
            if (i > 0) {
                while (true) {
                    auto* parent = nodes[rng() % i]; auto*& slot = (rng() % 2) ? parent->left : parent->right;
                    if (!slot) { slot = nodes.back(); break; }
                }
            }
        }
        check(minimumCameras(nodes[0]) == bruteCameras(nodes), "seeded cameras versus exhaustive subsets");
        check(measureTree(nodes[0]).maxPathSum == brutePathSum(nodes), "seeded gain versus all paths");
        std::vector<int> pre, in; traversals(nodes[0], pre, in);
        auto* rebuilt = buildTree(pre, in);
        check(serializeTree(rebuilt) == serializeTree(nodes[0]), "seeded traversal reconstruction");
        check(isValidBst(nodes[0]) == std::is_sorted(in.begin(), in.end()), "seeded BST versus inorder");
        auto* decoded = deserializeTree(serializeTree(nodes[0]));
        check(serializeTree(decoded) == serializeTree(nodes[0]), "seeded codec round trip");
        destroyTree(rebuilt); destroyTree(decoded); destroyTree(nodes[0]);
    }
    if (failures) { std::cerr << failures << " failures\n"; return 1; }
    std::cout << "trees-and-lists: deterministic + 300 list + 140 exhaustive tree trials passed\n";
}
