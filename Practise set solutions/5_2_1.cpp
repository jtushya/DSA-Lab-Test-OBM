#include <iostream>
#include <vector>
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

// Recursive function to calculate the probability that the sum is odd
double probabilityOdd(Node* node, bool currentSumOdd) {
    // If it's a leaf node
    if (node->child == nullptr) {
        // Check if current sum is odd
        return (currentSumOdd) ? 1.0 : 0.0;
    }

    // Otherwise, it's an internal node with children
    double probOdd = 0.0;
    double numChildren = 0.0;

    // Traverse all the children
    Node* child = node->child;
    while (child != nullptr) {
        numChildren++;
        probOdd += probabilityOdd(child, currentSumOdd ^ (child->value == 1));
        child = child->sibling;
    }

    // The probability of reaching an odd sum
    return probOdd / numChildren;
}

int main() {
    int n;
    cin >> n;
    Node** tree = new Node*[n];
    treeFromInput(tree, n);

    // Call the recursive function starting at the root node (node 0)
    cout.precision(6);
    cout << fixed << probabilityOdd(tree[0], tree[0]->value == 1) << endl;

    // Cleanup
    for (int i = 0; i < n; i++) {
        delete tree[i];
    }
    delete[] tree;
    return 0;
}
