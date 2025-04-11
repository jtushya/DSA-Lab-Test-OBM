#include <iostream>
#include <vector>
using namespace std;

/*
============================================
📘 PRACTICE SET 6 — PROBLEM 5, PART 2
============================================

🔹 PROBLEM STATEMENT
---------------------
You are given the postorder and inorder traversals of a binary tree.
Your task is to:
1. Reconstruct the binary tree using these traversals.
2. Print the postorder traversal of the constructed tree to verify.

Constraints:
- The function must be recursive.
- Assume all elements are unique and the tree is binary.

🔹 SAMPLE INPUT
---------------
n = 7  
postorder = [4, 5, 2, 6, 7, 3, 1]  
inorder   = [4, 2, 5, 1, 6, 3, 7]

🔹 EXPECTED OUTPUT
------------------
4 5 2 6 7 3 1  ← postorder traversal

============================================
🧠 INTUITION + DEMO EXAMPLE
============================================

We are given:
    Postorder: [4, 5, 2, 6, 7, 3, 1]
    Inorder  : [4, 2, 5, 1, 6, 3, 7]

Step-by-step idea:
- Postorder gives us the root **at the end**. So, postorder[n-1] = 1 → root.
- In inorder, 1 splits the array:
      Left part  [4,2,5] → left subtree
      Right part [6,3,7] → right subtree

We recursively:
- Pick the current root from the **end** of postorder (going backwards)
- Use inorder to divide into left and right subtree
- ⚠️ Important: Build the **right subtree first**, because we are going backward in postorder

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

Node* buildTree(vector<int>& postorder, vector<int>& inorder, int inStart, int inEnd, int &postIndex) {
    if (inStart > inEnd) return nullptr;

    // Get current root from postorder
    int rootVal = postorder[postIndex--];
    Node* root = new Node(rootVal);

    // If it's a leaf node
    if (inStart == inEnd) return root;

    // Find index of root in inorder
    int inIndex;
    for (inIndex = inStart; inIndex <= inEnd; inIndex++) {
        if (inorder[inIndex] == rootVal) break;
    }

    // ⚠️ Build right subtree first, then left (because we are going backward in postorder)
    root->right = buildTree(postorder, inorder, inIndex + 1, inEnd, postIndex);
    root->left = buildTree(postorder, inorder, inStart, inIndex - 1, postIndex);

    return root;
}

// Print postorder traversal: Left, Right, Root
void postorderPrint(Node* root) {
    if (!root) return;
    postorderPrint(root->left);
    postorderPrint(root->right);
    cout << root->data << " ";
}

void preorderPrint(Node* root) {
    if (!root) return;
    cout << root->data << " ";
    preorderPrint(root->left);
    preorderPrint(root->right);
}


int main() {
    int n;
    cin >> n;

    vector<int> postorder(n), inorder(n);
    for (int i = 0; i < n; i++) cin >> postorder[i];
    for (int i = 0; i < n; i++) cin >> inorder[i];

    int postIndex = n - 1;
    Node* root = buildTree(postorder, inorder, 0, n - 1, postIndex);

    postorderPrint(root);  // This should match original postorder input
    cout << '\n';

    return 0;
}
