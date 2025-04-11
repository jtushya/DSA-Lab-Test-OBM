#include <iostream>
#include "linked_binary_tree.h"

using namespace std;

// appends the [root]ed sub-tree
// as the right-most-child of [newRoot]ed sub-tree
void append(Node *root, Node *newRoot)
{
    // find the right-most leaf of the sub-tree
    // rooted at [newRoot]
    Node *rightMostChild = newRoot;

    while (rightMostChild->right != NULL)
        rightMostChild = rightMostChild->right;

    // append the sub-tree (update pointers)
    rightMostChild->right = root;
    root->par = rightMostChild;
}

// Extracts the subtree rooted at [newRoot] node
// from the tree rooted at [root]
void fix(Node *root, Node *newRoot)
{
    // base case
    if (root == NULL)
        return;

    // update the child pointer (either left/right)
    // of the parent node of [newRoot] in the binary tree.
    // and
    // update the parent pointer of [newRoot] node
    if (root->left == newRoot)
    {
        root->left = NULL;
        newRoot->par = NULL;
        return;
    }
    if (root->right == newRoot)
    {
        root->right = NULL;
        newRoot->par = NULL;
        return;
    }
    fix(root->left, newRoot);  // go to left sub tree
    fix(root->right, newRoot); // go to right sub tree
}

void reRoot(Node *root, Node *newRoot)
{
    if (root == newRoot)
        return; // nothing to do

    // STEP 1
    fix(root, newRoot);

    // STEP 2
    append(root, newRoot);
}

int main()
{
    BinaryTree tree;

    vector<int> v = {5, 7, 9, 3, -1, 11, 15, -1, -1, -1, -1, 12, 14};

    Node *root = tree.createTree(v, NULL, NULL, 0);

    cout << "Initial Tree:-" << endl;

    cout << "Inorder:";
    tree.inorder(root);
    cout << '\n';
    cout << "Postorder:";
    tree.postorder(root);
    cout << '\n';

    Node *newRoot = NULL;
    int n;

    while (true)
    {
        cout << "\nEnter the new root of the tree: ";
        cin >> n;

        newRoot = tree.getReferenceOf(n);

        if (newRoot != NULL)
            break;

        cout << "Enter valid input.\n";
    }

    reRoot(root, newRoot);

    cout << "\nAfter Re-Root operation:-" << endl;

    cout << "Inorder:";
    tree.inorder(newRoot);
    cout << '\n';
    cout << "Postorder:";
    tree.postorder(newRoot);
    cout << '\n';

    return 0;
}