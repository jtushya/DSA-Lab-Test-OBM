/*
Logic and Intuition:
1. **Euler Tour**:
   - Euler Tour is a traversal technique that records the sequence of nodes visited during a Depth First Search (DFS).
   - Each node is visited twice (once when entering and once when exiting), except the root, which is visited once.
   - This traversal helps in efficiently solving problems like Lowest Common Ancestor (LCA) and subtree size.

2. **Lowest Common Ancestor (LCA)**:
   - The LCA of two nodes `u` and `v` is the deepest node that is an ancestor of both `u` and `v`.
   - Using Euler Tour, the LCA can be found by identifying the range of indices in the Euler Tour corresponding to the first occurrences of `u` and `v`.
   - The node with the minimum depth (level) in this range is the LCA.

3. **Subtree Size (Dependents)**:
   - The size of the subtree rooted at a node `x` can be determined by counting the occurrences of `x` in the Euler Tour.
   - Each node in the subtree contributes two occurrences in the Euler Tour (entering and exiting), except the root of the subtree, which contributes one.

4. **Efficient Querying**:
   - The `firstOccurrence` array allows quick access to the first index of any node in the Euler Tour.
   - The `level` array stores the depth of each node in the Euler Tour, enabling efficient computation of the LCA.

Tasks:
- Implement `findLCA` to compute the LCA of two nodes using the `firstOccurrence` and `level` arrays.
- Implement `findDependents` to compute the subtree size of a node using the Euler Tour.
*/

#include <iostream>
#include <vector>
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
    vector<int> euler; // Stores the Euler Tour sequence
    vector<int> level; // Stores the level of each node in the Euler Tour
    vector<int> firstOccurrence; // Stores the first occurrence of each node in the Euler Tour

    // Helper function to perform Euler Tour
    void tour(TreeNode* node, int depth, int& index) {
        if (!node) return;

        // Record first occurrence of the node
        if (firstOccurrence[node->val] == -1) {
            firstOccurrence[node->val] = index;
        }

        // Add node to Euler and Level arrays
        euler.push_back(node->val);
        level.push_back(depth);
        index++;

        // Recur for left subtree
        tour(node->left, depth + 1, index);
        if (node->left) {
            euler.push_back(node->val);
            level.push_back(depth);
            index++;
        }

        // Recur for right subtree
        tour(node->right, depth + 1, index);
        if (node->right) {
            euler.push_back(node->val);
            level.push_back(depth);
            index++;
        }
    }

public:
    // Constructor to initialize Euler Tour
    EulerTour(TreeNode* root, int maxNodeValue) {
        // Initialize firstOccurrence with -1 (indicating no occurrence yet)
        firstOccurrence.resize(maxNodeValue + 1, -1);
        int index = 0;
        tour(root, 0, index);
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
        for (int val : euler) {
            if (val == x) count++;
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
