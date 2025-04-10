#include <iostream>
using namespace std;

class Node {
public:
    char data;            // Operator or operand as character
    int value;            // Final evaluated value (used later)
    Node* left, *right;

    Node() : data(0), value(0), left(nullptr), right(nullptr) {}
};

// Recursive function to construct the parse tree
void construct(string s, int* p, Node* node) {
    // Skip whitespaces
    while (*p < s.length() && s[*p] == ' ') (*p)++;

    if (isdigit(s[*p])) {
        // It's a digit → Leaf node
        node->data = s[*p];
        node->left = node->right = nullptr;
        (*p)++;
        return;
    }

    if (s[*p] == '(') {
        (*p)++;  // Skip '('

        // Build left subtree
        node->left = new Node();
        construct(s, p, node->left);

        // Current node's data is the operator
        node->data = s[*p];
        (*p)++;

        // Build right subtree
        node->right = new Node();
        construct(s, p, node->right);

        (*p)++;  // Skip ')'
    }
}

// Evaluate the parse tree
int evaluate(Node* node) {
    // If it's a digit/leaf node
    if (node->left == nullptr && node->right == nullptr)
        return node->data - '0';  // Convert char to int

    int leftVal = evaluate(node->left);
    int rightVal = evaluate(node->right);

    switch (node->data) {
        case '+': return leftVal + rightVal;
        case '-': return leftVal - rightVal;
        case '*': return leftVal * rightVal;
        case '/': return leftVal / rightVal;  // Assume no divide-by-zero
        default: return 0;
    }
}

int main() {
    string s;
    cin >> s;
    
    // Wrap the entire expression in parentheses
    s = "(" + s + ")";

    int idx = 0;
    int* p = &idx;
    Node* node = new Node();

    construct(s, p, node);
    cout << evaluate(node) << '\n';

    return 0;
}
