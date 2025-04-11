#include <iostream>
#include <vector>
using namespace std;

// Structure to represent a node in the binary tree
struct Node {
    int value;      // value of the node
    Node* left;     // pointer to left child
    Node* right;    // pointer to right child

    // Constructor
    Node(int val) {
        value = val;
        left = nullptr;
        right = nullptr;
    }
};

int maxScore = 0;  // Global variable to store the maximum triangle score

// Recursive DFS function to explore the tree and calculate max score
int dfs(Node* node) {
    if (!node) return 0;  // If the node is null, return 0

    // Recursively compute the best score from left and right subtrees
    int leftScore = dfs(node->left);
    int rightScore = dfs(node->right);

    // If current node has both children, try forming a triangle here
    if (node->left && node->right) {
        int triangleScore = node->value * (node->left->value + node->right->value);

        // Add scores from grandchildren (since children are now used)
        int skipChildrenScore = dfs(node->left->left) + dfs(node->left->right)
                              + dfs(node->right->left) + dfs(node->right->right);

        int totalScore = triangleScore + skipChildrenScore;

        // Update the global max score if this is better
        if (totalScore > maxScore) {
            maxScore = totalScore;
        }
    }

    // Also consider the case where we don't form a triangle here
    int combinedChildScore = leftScore + rightScore;
    if (combinedChildScore > maxScore) {
        maxScore = combinedChildScore;
    }

    // Return the best single branch score for parent use
    return (leftScore > rightScore ? leftScore : rightScore);
}

int main() {
    int n;
    cin >> n;

    vector<Node*> nodes(n);  // List of all nodes

    // Create empty nodes first
    for (int i = 0; i < n; i++) {
        nodes[i] = new Node(0);
    }

    // Read the parent array and construct the binary tree
    for (int i = 1; i < n; i++) {
        int parent;
        cin >> parent;
        if (!nodes[parent - 1]->left) {
            nodes[parent - 1]->left = nodes[i];
        } else {
            nodes[parent - 1]->right = nodes[i];
        }
    }

    // Read the values of the nodes
    for (int i = 0; i < n; i++) {
        cin >> nodes[i]->value;
    }

    // Start DFS from the root (node 0)
    dfs(nodes[0]);

    // Output the maximum score
    cout << maxScore << endl;

    return 0;
}
