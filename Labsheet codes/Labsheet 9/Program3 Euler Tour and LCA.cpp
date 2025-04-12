#include <iostream>
#include <climits>
using namespace std;

// TreeNode structure
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// EulerTour class to perform Euler Tour and answer queries
class EulerTour {
private:
    int* euler; // Stores the Euler Tour sequence
    int* level; // Stores the level of each node in the Euler Tour
    int* firstOccurrence; // Stores the first occurrence of each node in the Euler Tour
    int eulerSize; // Size of the euler array
    int capacity; // Capacity of the dynamic arrays

    // Helper function to resize dynamic arrays
    void resizeArrays() {
        capacity *= 2;
        int* newEuler = new int[capacity];
        int* newLevel = new int[capacity];
        for (int i = 0; i < eulerSize; i++) {
            newEuler[i] = euler[i];
            newLevel[i] = level[i];
        }
        delete[] euler;
        delete[] level;
        euler = newEuler;
        level = newLevel;
    }

    // This function performs an Euler Tour traversal of the binary tree.
    // It populates the euler, level, and firstOccurrence arrays.
    // Parameters:
    // - node: The current node being visited.
    // - depth: The depth of the current node in the tree.
    // - index: The current index in the Euler Tour sequence.
    void tour(TreeNode* node, int depth, int& index) {
        if (!node) return; // Base case: If the node is null, return.

        // Record the first occurrence of the node in the Euler Tour.
        if (firstOccurrence[node->val] == -1) {
            firstOccurrence[node->val] = index;
        }

        // Add the current node to the Euler and Level arrays.
        if (eulerSize == capacity) resizeArrays(); // Resize arrays if full.
        euler[eulerSize] = node->val;
        level[eulerSize] = depth;
        eulerSize++;
        index++;

        // Recur for the left subtree.
        tour(node->left, depth + 1, index);
        if (node->left) {
            // Add the current node again after visiting the left subtree.
            if (eulerSize == capacity) resizeArrays();
            euler[eulerSize] = node->val;
            level[eulerSize] = depth;
            eulerSize++;
            index++;
        }

        // Recur for the right subtree.
        tour(node->right, depth + 1, index);
        if (node->right) {
            // Add the current node again after visiting the right subtree.
            if (eulerSize == capacity) resizeArrays();
            euler[eulerSize] = node->val;
            level[eulerSize] = depth;
            eulerSize++;
            index++;
        }
    }

public:
    // Constructor to initialize Euler Tour
    EulerTour(TreeNode* root, int maxNodeValue) {
        capacity = 100; // Initial capacity
        euler = new int[capacity];
        level = new int[capacity];
        firstOccurrence = new int[maxNodeValue + 1];
        for (int i = 0; i <= maxNodeValue; i++) {
            firstOccurrence[i] = -1;
        }
        // eulerSize = 0;
        int index = 0;
        tour(root, 0, index);
    }

    // Destructor to free memory
    ~EulerTour() {
        delete[] euler;
        delete[] level;
        delete[] firstOccurrence;
    }

    // Function to find LCA of two nodes
    int findLCA(int u, int v) {
        // Get the first occurrences of u and v
        int uIdx = firstOccurrence[u];
        int vIdx = firstOccurrence[v];

        // Ensure uIdx is less than vIdx
        if (uIdx > vIdx) swap(uIdx, vIdx);

        // Find the node with the minimum level in the range [uIdx, vIdx]
        int minLevel = INT_MAX;
        int lca = -1;
        for (int i = uIdx; i <= vIdx; i++) {
            if (level[i] < minLevel) {
                minLevel = level[i];
                lca = euler[i];
            }
        }

        return lca;
    }

    // Function to find the number of dependents (subtree size) of a node
    int findDependents(int x) {
        // Count the number of occurrences of x in the Euler array
        int count = 0;
        for (int i = 0; i < eulerSize; i++) {
            if (euler[i] == x) count++;
        }

        // Subtree size = (number of occurrences + 1) / 2
        // Note: This formula works because each node appears twice in the Euler Tour
        // except for the root of the subtree.
        return (count + 1) / 2;
    }
};

// Main function
int main() {
    // Build the binary tree using linked structure
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->right = new TreeNode(6);

    // Perform Euler Tour
    // Pass the maximum node value in the tree (6 in this case)
    EulerTour eulerTour(root, 6);

    // Find LCA of 4 and 5
    int lca = eulerTour.findLCA(4, 5);
    cout << "LCA of 4 and 5 is: " << lca << endl; // Expected: 2

    // Find dependents of 2
    int dependents = eulerTour.findDependents(2);
    cout << "Dependents of 2 is: " << dependents << endl; // Expected: 3

    // Additional test cases
    cout << "LCA of 3 and 6 is: " << eulerTour.findLCA(3, 6) << endl; // Expected: 3
    cout << "LCA of 4 and 6 is: " << eulerTour.findLCA(4, 6) << endl; // Expected: 1

    return 0;
}
