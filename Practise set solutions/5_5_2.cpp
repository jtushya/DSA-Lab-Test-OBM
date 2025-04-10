#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    char data;   // Operator (+, -, *, /)
    int value;   // Operand (for multi-digit numbers)
    Node *left, *right;

    Node() : data(0), value(0), left(nullptr), right(nullptr) {}
};

// Function to construct the binary tree from the string expression
void construct(string s, int* p, Node* node) {
    // Skip spaces if any (optional for cleaner input)
    while (s[*p] == ' ') (*p)++;

    // If the character is '(', it's a new subexpression
    if (s[*p] == '(') {
        (*p)++; // Skip '('

        // Left subexpression (recursive call)
        node->left = new Node();
        construct(s, p, node->left);

        // Operator
        node->data = s[*p];
        (*p)++; // Skip operator

        // Right subexpression (recursive call)
        node->right = new Node();
        construct(s, p, node->right);

        (*p)++; // Skip ')'
    } 
    else {
        // Read a multi-digit number
        node->value = 0;
        while (s[*p] >= '0' && s[*p] <= '9') {
            node->value = node->value * 10 + (s[*p] - '0');
            (*p)++;
        }
    }
}

// Function to evaluate the expression in the binary tree
int evaluate(Node* node) {
    // If it's a leaf node, return the value (operand)
    if (node->left == nullptr && node->right == nullptr) {
        return node->value;
    }

    // Otherwise, evaluate the left and right subtrees first
    int leftValue = evaluate(node->left);
    int rightValue = evaluate(node->right);

    // Apply the operation based on the operator at the current node
    switch (node->data) {
        case '+': return leftValue + rightValue;
        case '-': return leftValue - rightValue;
        case '*': return leftValue * rightValue;
        case '/': return leftValue / rightValue;  // Assume valid division (no zero division)
        default: return 0;  // Should never happen if input is valid
    }
}

int main() {
    string s;
    cin >> s;

    int idx = 0;
    int* p = &idx;
    Node* root = new Node();
    construct(s, p, root);

    cout << evaluate(root) << '\n';
    return 0;
}
