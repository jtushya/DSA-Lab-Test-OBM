#include <iostream>
using namespace std;

// Node structure for the binary tree
struct Node
{
    int data;
    Node *left, *right, *par;

    Node(int val) : data(val), left(NULL), right(NULL), par(NULL) {}
};

// BinaryTree class to manage tree operations
class BinaryTree
{
public:
    Node *createTree(int arr[], int size, Node *par, Node *root, int i)
    {
        if (i < size && arr[i] != -1)
        {
            root = new Node(arr[i]);
            root->par = par;

            root->left = createTree(arr, size, root, root->left, 2 * i + 1);
            root->right = createTree(arr, size, root, root->right, 2 * i + 2);
        }
        return root;
    }

    void inorder(Node *root)
    {
        if (root == NULL)
            return;
        inorder(root->left);
        cout << root->data << ' ';
        inorder(root->right);
    }

    void postorder(Node *root)
    {
        if (root == NULL)
            return;
        postorder(root->left);
        postorder(root->right);
        cout << root->data << ' ';
    }

    Node *getReferenceOf(Node *root, int val)
    {
        if (root == NULL)
            return NULL;
        if (root->data == val)
            return root;

        Node *leftSearch = getReferenceOf(root->left, val);
        if (leftSearch != NULL)
            return leftSearch;

        return getReferenceOf(root->right, val);
    }
};

// Appends the subtree rooted at [root] as the right-most child of the subtree rooted at [newRoot].
void append(Node *root, Node *newRoot)
{
    Node *rightMostChild = newRoot;
    while (rightMostChild->right != NULL)
        rightMostChild = rightMostChild->right;

    rightMostChild->right = root;
    root->par = rightMostChild;
}

// Detaches the subtree rooted at [newRoot] from the tree rooted at [root].
void fix(Node *root, Node *newRoot)
{
    if (root == NULL)
        return;

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

    fix(root->left, newRoot);
    fix(root->right, newRoot);
}

// Re-roots the tree by making [newRoot] the new root of the tree.
void reRoot(Node *root, Node *newRoot)
{
    if (root == newRoot)
        return;

    fix(root, newRoot);
    append(root, newRoot);
}

int main()
{
    BinaryTree tree;

    // Static array for tree creation
    int arr[] = {5, 7, 9, 3, -1, 11, 15, -1, -1, -1, -1, 12, 14};
    int size = sizeof(arr) / sizeof(arr[0]);

    Node *root = tree.createTree(arr, size, NULL, NULL, 0);

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

        newRoot = tree.getReferenceOf(root, n);

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
