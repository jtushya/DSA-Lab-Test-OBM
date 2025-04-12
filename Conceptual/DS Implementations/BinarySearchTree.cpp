#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

class BinarySearchTree {
private:
    Node* root;

    Node* insert(Node* node, int data) {
        if (node == nullptr) {
            return new Node(data);
        }
        if (data < node->data) {
            node->left = insert(node->left, data);
        } else {
            node->right = insert(node->right, data);
        }
        return node;
    }

    void inorder(Node* node) {
        if (node == nullptr) return;
        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }

    Node* search(Node* node, int key) {
        if (node == nullptr || node->data == key) return node;
        if (key < node->data) return search(node->left, key);
        return search(node->right, key);
    }

public:
    BinarySearchTree() : root(nullptr) {}

    void insert(int data) {
        root = insert(root, data);
    }

    void inorder() {
        inorder(root);
        cout << endl;
    }

    bool search(int key) {
        return search(root, key) != nullptr;
    }
};

int main() {
    BinarySearchTree bst;

    bst.insert(5);
    bst.insert(3);
    bst.insert(7);
    bst.insert(2);
    bst.insert(4);

    cout << "Inorder Traversal: ";
    bst.inorder();

    cout << "Search for 4: " << (bst.search(4) ? "Found" : "Not Found") << endl;
    cout << "Search for 6: " << (bst.search(6) ? "Found" : "Not Found") << endl;

    return 0;
}