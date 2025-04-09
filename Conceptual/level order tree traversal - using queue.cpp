#include <iostream>
#include <queue>
using namespace std;

// Define the structure for the tree node
struct TreeNode {
    int value;
    TreeNode* left;
    TreeNode* right;

    // Constructor to initialize a new node
    TreeNode(int val) {
        value = val;
        left = right = nullptr;
    }
};

// Level Order Traversal Function
void LevelOrderTraversal(TreeNode* root) {
    if (root == nullptr) return;

    // Create an empty queue to store nodes
    queue<TreeNode*> Q;

    // Enqueue the root node
    Q.push(root);

    while (!Q.empty()) {
        // Dequeue the front node from the queue
        TreeNode* node = Q.front();
        Q.pop();

        // Print the current node's value
        cout << node->value << " ";

        // If the left child exists, enqueue it
        if (node->left != nullptr) {
            Q.push(node->left);
        }

        // If the right child exists, enqueue it
        if (node->right != nullptr) {
            Q.push(node->right);
        }
    }
}

// Function to construct a binary tree from an array using level-order
TreeNode* constructTree(int arr[], int n) {
    if (n == 0) return nullptr;

    // Create the root node
    TreeNode* root = new TreeNode(arr[0]);

    // Use a queue to construct the tree level by level
    queue<TreeNode*> Q;
    Q.push(root);

    int i = 1;
    while (i < n) {
        TreeNode* node = Q.front();
        Q.pop();

        // Add left child
        if (i < n) {
            node->left = new TreeNode(arr[i++]);
            Q.push(node->left);
        }

        // Add right child
        if (i < n) {
            node->right = new TreeNode(arr[i++]);
            Q.push(node->right);
        }
    }

    return root;
}

int main() {
    // Example array to construct the binary tree
    int arr[] = {1, 2, 3, 4, 5, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);

    // Construct the binary tree
    TreeNode* root = constructTree(arr, n);

    // Perform Level Order Traversal
    cout << "Level Order Traversal: ";
    LevelOrderTraversal(root);
    cout << endl;

    return 0;
}
