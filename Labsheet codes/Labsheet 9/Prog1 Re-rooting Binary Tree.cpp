/*
Problem:
This program implements a re-rooting operation on a binary tree. It allows the user to select a new root for the tree and rearranges the tree structure accordingly.

Intuition and Logic:
1. The re-rooting operation involves detaching the subtree rooted at the new root and appending the original tree as a child of the new root.
2. The program uses recursive functions to detach the subtree and append the original tree.
3. The tree is displayed in inorder and postorder traversals before and after the re-rooting operation.
4. This demonstrates the flexibility of tree structures and the use of recursion for tree manipulations.
*/

#include <iostream>
#include "linked_binary_tree.h"

using namespace std;

// Appends the subtree rooted at [root] as the right-most child of the subtree rooted at [newRoot].
void append(Node *root, Node *newRoot)
{
    // Find the right-most child of the subtree rooted at [newRoot].
    Node *rightMostChild = newRoot;

    while (rightMostChild->right != NULL)
        rightMostChild = rightMostChild->right;

    // Update pointers to append the subtree.
    rightMostChild->right = root;
    root->par = rightMostChild;
}

// Detaches the subtree rooted at [newRoot] from the tree rooted at [root].
void fix(Node *root, Node *newRoot)
{
    // Base case: If the root is NULL, do nothing.
    if (root == NULL)
        return;

    // If [newRoot] is the left child, detach it.
    if (root->left == newRoot)
    {
        root->left = NULL;
        newRoot->par = NULL;
        return;
    }

    // If [newRoot] is the right child, detach it.
    if (root->right == newRoot)
    {
        root->right = NULL;
        newRoot->par = NULL;
        return;
    }

    // Recursively search in the left and right subtrees.
    fix(root->left, newRoot);
    fix(root->right, newRoot);
}

// Re-roots the tree by making [newRoot] the new root of the tree.
void reRoot(Node *root, Node *newRoot)
{
    // If the current root is already the new root, do nothing.
    if (root == newRoot)
        return;

    // Step 1: Detach the subtree rooted at [newRoot].
    fix(root, newRoot);

    // Step 2: Append the original tree as the right-most child of [newRoot].
    append(root, newRoot);
}

int main()
{
    BinaryTree tree;

    // Create a binary tree from a vector of integers.
    vector<int> v = {5, 7, 9, 3, -1, 11, 15, -1, -1, -1, -1, 12, 14};
    Node *root = tree.createTree(v, NULL, NULL, 0);

    // Display the initial tree in inorder and postorder traversals.
    cout << "Initial Tree:-" << endl;
    cout << "Inorder:";
    tree.inorder(root);
    cout << '\n';
    cout << "Postorder:";
    tree.postorder(root);
    cout << '\n';

    Node *newRoot = NULL;
    int n;

    // Prompt the user to enter the value of the new root.
    while (true)
    {
        cout << "\nEnter the new root of the tree: ";
        cin >> n;

        // Get the reference to the node with the entered value.
        newRoot = tree.getReferenceOf(n);

        // If the node exists, break the loop.
        if (newRoot != NULL)
            break;

        // Otherwise, prompt the user to enter a valid value.
        cout << "Enter valid input.\n";
    }

    // Perform the re-root operation.
    reRoot(root, newRoot);

    // Display the tree after the re-root operation in inorder and postorder traversals.
    cout << "\nAfter Re-Root operation:-" << endl;
    cout << "Inorder:";
    tree.inorder(newRoot);
    cout << '\n';
    cout << "Postorder:";
    tree.postorder(newRoot);
    cout << '\n';

    return 0;
}