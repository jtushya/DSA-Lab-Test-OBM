#include <iostream>
using namespace std;

class Node {
public:
    int value;
    Node *child, *sibling;
    Node() : value(0), child(nullptr), sibling(nullptr) {}
};

// Function to build the tree from input
void treeFromInput(Node** tree, int n) {
    for (int i = 0; i < n; i++) {
        int value;
        cin >> value;
        tree[i] = new Node();
        tree[i]->value = value;
    }

    for (int i = 1; i < n; i++) {
        int parent;
        cin >> parent;
        parent--;  // Convert to 0-indexed
        if (tree[parent]->child != nullptr)
            tree[i]->sibling = tree[parent]->child;
        tree[parent]->child = tree[i];
    }
}

// Recursive function to calculate expected sum at leaf
double expectedSum(Node* node, int currentSum) {
    currentSum += node->value;

    // If it's a leaf node
    if (node->child == nullptr) {
        return currentSum * 1.0; // Return the sum as a double
    }

    // Otherwise, it's an internal node with children
    double expected = 0.0;
    int numChildren = 0;

    for (Node* c = node->child; c != nullptr; c = c->sibling) {
        expected += expectedSum(c, currentSum);
        numChildren++;
    }

    return expected / numChildren; // Average of expected values from all children
}

int main() {
    int n;
    cin >> n;
    Node** tree = new Node*[n];
    treeFromInput(tree, n);

    // Call the recursive function starting at the root node (node 0)
    cout.precision(2);
    cout << fixed << expectedSum(tree[0], 0) << endl;

    // Cleanup
    for (int i = 0; i < n; i++) {
        delete tree[i];
    }
    delete[] tree;
    return 0;
}
