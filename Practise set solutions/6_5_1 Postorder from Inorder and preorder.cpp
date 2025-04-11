#include <iostream>
#include <vector>
using namespace std;

/*
============================================
📘 PRACTICE SET 6 — PROBLEM 5, PART 1 
Post order from preorder and inorder traversal arrays
============================================

🔹 PROBLEM STATEMENT
---------------------
You are given the preorder and inorder traversals of a binary tree.
Your task is to:
1. Reconstruct the binary tree using these traversals.
2. Print the postorder traversal of the constructed tree.

Constraints:
- The function must be recursive.
- Assume all elements are unique and the tree is binary.

🔹 SAMPLE INPUT
---------------
n = 7  
preorder = [1, 2, 4, 5, 3, 6, 7]  
inorder  = [4, 2, 5, 1, 6, 3, 7]

🔹 EXPECTED OUTPUT
------------------
4 5 2 6 7 3 1  ← postorder traversal

============================================
🧠 INTUITION + DEMO EXAMPLE
============================================

We are given:
    Preorder: [1, 2, 4, 5, 3, 6, 7]
    Inorder : [4, 2, 5, 1, 6, 3, 7]

Step-by-step idea:
- Preorder tells us the root first. So, preorder[0] = 1 → root.
- Inorder tells us what is in the left and right subtree.
  In inorder, 1 splits the array:
      Left part [4,2,5] → left subtree
      Right part [6,3,7] → right subtree

We recursively:
- Pick next root from preorder
- Use inorder to divide left and right subtree
- Recurse and build the entire tree

The tree built will look like this:

            1
          /   \
         2     3
        / \   / \
       4   5 6   7

Postorder (Left, Right, Root): 4 5 2 6 7 3 1 ✅

*/

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int d) : data(d), left(nullptr), right(nullptr) {}
};

Node* buildTree(vector<int>& preorder, vector<int>& inorder, int inStart, int inEnd, int &preIndex) {
    if (inStart > inEnd) return nullptr;

    // Get current root from preorder
    int rootVal = preorder[preIndex++];
    Node* root = new Node(rootVal);

    // If it's a leaf node (no children)
    if (inStart == inEnd) return root;

    // Find index of root in inorder
    int inIndex;
    for (inIndex = inStart; inIndex <= inEnd; inIndex++) {
        if (inorder[inIndex] == rootVal) break;
    }

    // Build left and right subtrees recursively
    root->left = buildTree(preorder, inorder, inStart, inIndex - 1, preIndex);
    root->right = buildTree(preorder, inorder, inIndex + 1, inEnd, preIndex);

    return root;
}

// Print postorder traversal: Left, Right, Root
void postorder(Node* root) {
    if (!root) return;
    postorder(root->left);
    postorder(root->right);
    cout << root->data << " ";
}

int main() {
    int n;
    cin >> n;

    vector<int> preorder(n), inorder(n);
    for (int i = 0; i < n; i++) cin >> preorder[i];
    for (int i = 0; i < n; i++) cin >> inorder[i];

    int preIndex = 0;
    Node* root = buildTree(preorder, inorder, 0, n - 1, preIndex);

    postorder(root);
    cout << '\n';

    return 0;
}
