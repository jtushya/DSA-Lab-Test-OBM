#include <iostream>
using namespace std;

struct TreeNode {
    int data;
    TreeNode* right;

    TreeNode(int val) : data(val), right(nullptr) {}
};

class RightChildTree {
private:
    TreeNode* root;

    void inorder(TreeNode* node) {
        if (node == nullptr) return;
        cout << node->data << " ";
        inorder(node->right);
    }

public:
    RightChildTree() : root(nullptr) {}

    void insert(int data) {
        if (root == nullptr) {
            root = new TreeNode(data);
            return;
        }
        TreeNode* temp = root;
        while (temp->right != nullptr) {
            temp = temp->right;
        }
        temp->right = new TreeNode(data);
    }

    void inorder() {
        inorder(root);
        cout << endl;
    }
};

int main() {
    RightChildTree tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);

    cout << "Inorder Traversal: ";
    tree.inorder();

    return 0;
}