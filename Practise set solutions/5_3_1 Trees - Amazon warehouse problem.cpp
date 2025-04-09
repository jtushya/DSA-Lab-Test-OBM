#include <iostream>
using namespace std;

class Node {
public:
    int subtreeSize;
    Node *child, *sibling;

    Node() : subtreeSize(0), child(nullptr), sibling(nullptr) {}
};

void treeFromInput(Node **tree, int n) {
    for (int i = 0; i < n; i++) tree[i] = new Node();
    for (int i = 1; i < n; i++) {
        int parent;
        cin >> parent;
        parent--; // converting to 0-based
        if (tree[parent]->child != nullptr)
            tree[i]->sibling = tree[parent]->child;
        tree[parent]->child = tree[i];
    }
}

void calcSubtreeSizes(Node* node) {
    node->subtreeSize = 1;
    for (Node *c = node->child; c != nullptr; c = c->sibling) {
        calcSubtreeSizes(c);
        node->subtreeSize += c->subtreeSize;
    }
}

int calcTotalDist(Node* node, int depth = 0) {
    int total = depth;
    for (Node* c = node->child; c != nullptr; c = c->sibling) {
        total += calcTotalDist(c, depth + 1);
    }
    return total;
}

int main() {
    int n;
    cin >> n;
    Node** tree = (Node**)(malloc(sizeof(Node*) * n));
    treeFromInput(tree, n);
    calcSubtreeSizes(tree[0]);
    cout << calcTotalDist(tree[0]) << '\n';
    return 0;
}
