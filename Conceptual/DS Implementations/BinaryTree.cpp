#include <iostream>
using namespace std;

struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

class BinaryTree {
private:
    TreeNode* root;

    void inorder(TreeNode* node) {
        if (node == nullptr) return;
        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }

public:
    BinaryTree() : root(nullptr) {}

    void insert(int data) {
        if (root == nullptr) {
            root = new TreeNode(data);
            return;
        }
        TreeNode* temp = root;
        while (true) {
            if (data < temp->data) {
                if (temp->left == nullptr) {
                    temp->left = new TreeNode(data);
                    break;
                }
                temp = temp->left;
            } else {
                if (temp->right == nullptr) {
                    temp->right = new TreeNode(data);
                    break;
                }
                temp = temp->right;
            }
        }
    }

    void inorder() {
        inorder(root);
        cout << endl;
    }
};

int main() {
    BinaryTree tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);

    cout << "Inorder Traversal: ";
    tree.inorder();

    return 0;
}