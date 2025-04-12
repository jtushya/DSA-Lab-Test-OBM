#include <iostream>
#include <vector>
using namespace std;

struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

/*
    Sample Input Tree:
           1
          / \
         2   3
        / \
       4   5

    === Final Euler Paths ===

    1. Detailed Euler Path (preorder, inorder, postorder recorded):
       detailedEulerPath = [1, 2, 4, 4, 4, 2, 5, 5, 5, 2, 1, 3, 3, 3, 1]

    2. Single Euler Path (each node appears 3 times):
       singleEulerPath = [1, 2, 4, 4, 2, 5, 5, 2, 1, 3, 3, 1]

    3. In/Out Euler Path (entry/exit times of each node during DFS):
       inOutEulerPath = [1, 2, 4, 4, 5, 5, 2, 3, 3, 1]

    === In/Out Times ===
       inTime[1] = 1,  outTime[1] = 10
       inTime[2] = 2,  outTime[2] = 7
       inTime[3] = 8,  outTime[3] = 9
       inTime[4] = 3,  outTime[4] = 4
       inTime[5] = 5,  outTime[5] = 6
*/

const int MAX_NODES = 100;
int inTime[MAX_NODES], outTime[MAX_NODES];
int timer = 0;

// Euler paths
vector<int> detailedEulerPath;
vector<int> singleEulerPath;
vector<int> inOutEulerPath;

// Detailed Euler Tour (preorder, inorder, postorder)
void eulerTour(TreeNode* node) {
    if (node == nullptr) return;

    // Preorder
    detailedEulerPath.push_back(node->data);
    cout << "Preorder: " << node->data << endl;

    if (node->left) eulerTour(node->left);

    // Inorder
    detailedEulerPath.push_back(node->data);
    cout << "Inorder: " << node->data << endl;

    if (node->right) eulerTour(node->right);

    // Postorder
    detailedEulerPath.push_back(node->data);
    cout << "Postorder: " << node->data << endl;
}

// Single Euler Tour (each node visited 3 times)
void eulerTourSingle(TreeNode* node) {
    if (node == nullptr) return;

    singleEulerPath.push_back(node->data);  // Visit 1

    if (node->left) eulerTourSingle(node->left);

    singleEulerPath.push_back(node->data);  // Visit 2

    if (node->right) eulerTourSingle(node->right);

    singleEulerPath.push_back(node->data);  // Visit 3
}

// Euler Tour with In and Out Times + Euler Path
void eulerTourInOut(TreeNode* node) {
    if (node == nullptr) return;

    inTime[node->data] = ++timer;
    inOutEulerPath.push_back(node->data);
    cout << "Entering node " << node->data << " at time " << inTime[node->data] << endl;

    if (node->left) eulerTourInOut(node->left);
    if (node->right) eulerTourInOut(node->right);

    outTime[node->data] = ++timer;
    inOutEulerPath.push_back(node->data);
    cout << "Exiting node " << node->data << " at time " << outTime[node->data] << endl;
}

// Helper to print vector
void printPath(const vector<int>& path, const string& label) {
    cout << "\n" << label << ": ";
    for (int x : path) cout << x << " ";
    cout << endl;
}

int main() {
    // Construct the tree:
    //       1
    //      / \
    //     2   3
    //    / \
    //   4   5

    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);

    cout << "Euler Tour Traversal (Detailed):\n";
    eulerTour(root);
    printPath(detailedEulerPath, "Detailed Euler Path");

    cout << "\nEuler Tour Traversal (Single):\n";
    eulerTourSingle(root);
    printPath(singleEulerPath, "Single Euler Path");

    cout << "\nEuler Tour Traversal (In and Out Times):\n";
    eulerTourInOut(root);
    printPath(inOutEulerPath, "In/Out Euler Path");

    // Example ancestor query
    if (inTime[2] <= inTime[4] && outTime[4] <= outTime[2])
        cout << "\nNode 2 is an ancestor of node 4.\n";
    else
        cout << "\nNode 2 is NOT an ancestor of node 4.\n";

    return 0
