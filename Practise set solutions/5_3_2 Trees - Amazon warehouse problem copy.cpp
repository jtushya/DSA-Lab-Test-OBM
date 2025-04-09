#include <iostream>
#include <climits> // For INT_MAX
using namespace std;

class Node {
public:
    int subtreeSize;
    Node* child, *sibling;
    Node() : subtreeSize(0), child(nullptr), sibling(nullptr) {}
};

int N;
int minTotalDist = INT_MAX;
int bestCity = -1;  // stores the city (0-indexed) with minimum cost
Node** tree; // Global tree pointer, so it's accessible to all functions

// Build the tree from the input
void treeFromInput(Node** tree, int n) {
    for (int i = 0; i < n; i++) tree[i] = new Node();
    for (int i = 1; i < n; i++) {
        int parent;
        cin >> parent;
        parent--; // Zero-based index for tree structure
        if (tree[parent]->child != nullptr)
            tree[i]->sibling = tree[parent]->child; // Add new child as sibling
        tree[parent]->child = tree[i]; // Set new child
    }
}

// codefill1: Calculate subtree sizes for all nodes recursively
void calcSubtreeSizes(Node* node) {
    node->subtreeSize = 1; // The node itself counts as size 1
    for (Node* c = node->child; c != nullptr; c = c->sibling) {
        calcSubtreeSizes(c); // Recursive call for children
        node->subtreeSize += c->subtreeSize; // Accumulate sizes of all subtrees
    }
}

// codefill2: Calculate total delivery cost from the root node
int calcTotalDist(Node* node, int depth = 0) {
    int total = depth; // Add depth (distance) for this node
    for (Node* c = node->child; c != nullptr; c = c->sibling) {
        total += calcTotalDist(c, depth + 1); // Recursively calculate for children
    }
    return total; // Return the sum of all distances
}

// Identify the index of the node for rerooting (helper function)
int getNodeIndex(Node* ptr) {
    for (int i = 0; i < N; ++i) {
        if (tree[i] == ptr) return i; // Find and return index of node in the tree array
    }
    return -1; // shouldn't happen
}

// Function to perform rerooting, recalculating total distance for each node
void reroot(Node* node, int totalDist) {
    if (totalDist < minTotalDist) {
        minTotalDist = totalDist; // Update the minimum total distance
        bestCity = getNodeIndex(node); // Update the best city (node index)
    }

    for (Node* c = node->child; c != nullptr; c = c->sibling) {
        // Calculate the total delivery cost when rerooting to the child node
        int distFromChild = totalDist - c->subtreeSize + (N - c->subtreeSize);
        reroot(c, distFromChild); // Recursively reroot to the child node
    }
}

int main() {
    cin >> N; // Read the number of nodes (cities)
    tree = new Node*[N]; // Dynamically allocate memory for tree
    treeFromInput(tree, N); // Build the tree from input

    calcSubtreeSizes(tree[0]); // Calculate the subtree sizes from the root node
    int baseTotalDist = calcTotalDist(tree[0]); // Calculate the base total distance for the root
    reroot(tree[0], baseTotalDist); // Perform rerooting from the root to all other cities

    // Output the minimum total delivery cost and the best city for the warehouse
    cout << "Minimum total delivery cost: " << minTotalDist << '\n';
    cout << "Best city to place the warehouse: " << (bestCity + 1) << '\n'; // Convert to 1-based indexing

    delete[] tree; // Clean up memory
    return 0;
}
