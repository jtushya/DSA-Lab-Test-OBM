#include <iostream>

using namespace std;

// Node structure for the Expression Tree
class ExpressionTreeNode
{
public:
    double operand;          // Stores the operand value for leaf nodes
    char _operator;          // Stores the operator for internal nodes
    ExpressionTreeNode *left, *right; // Pointers to left and right child nodes

    ExpressionTreeNode()
    {
        operand = 0;
        _operator = '\0';
        left = right = NULL;
    }
};

typedef ExpressionTreeNode Node;

// ExpressionTree class to manage the Expression Tree
class ExpressionTree
{
private:
    int idx;                 // Index to traverse the input expression string
    bool isEvaluated;        // Flag to check if the expression is already evaluated
    Node *root;              // Root of the Expression Tree
    Node *buildExpressionTree(const string); // Builds the Expression Tree recursively
    void inorder(Node *ptr); // Performs an inorder traversal
    void postorder(Node *ptr); // Performs a postorder traversal

public:
    ExpressionTree(const string expr)
    {
        idx = 0;
        isEvaluated = false;
        root = buildExpressionTree(expr); // Build the tree from the input expression
    }
    void showExpression(); // Displays the expression in infix notation
    void evaluateExpression(); // Evaluates the expression
    double eval(const char opr, const double leftOperand, const double rightOperand); // Evaluates a sub-expression
    double getResult(); // Returns the result of the expression
    bool isLeaf(Node *ptr); // Checks if a node is a leaf node
};

typedef ExpressionTree Tree;

// Builds the Expression Tree from a valid parenthesized expression
Node *Tree::buildExpressionTree(const string expr)
{
    if (idx == expr.length())
        return NULL;

    Node *root = new Node();

    // If the current character is '(', process the left subtree
    if (expr[idx] == '(')
    {
        ++idx;
        root->left = buildExpressionTree(expr);
    }
    else
    {
        // If it's a number, create a leaf node
        root->operand = expr[idx] - '0';
        return root;
    }

    ++idx;

    // Skip over closing parenthesis ')' (if any)
    while (idx < expr.length() && expr[idx] == ')')
        ++idx;

    if (idx == expr.length())
        return root;

    // Set the operator for the current node
    root->_operator = expr[idx];
    ++idx;

    // Process the right subtree
    root->right = buildExpressionTree(expr);

    return root;
}

// Displays the expression in infix notation
void Tree::showExpression()
{
    inorder(root);
    cout << endl;
}

// Performs an inorder traversal of the Expression Tree
void Tree::inorder(Node *root)
{
    if (isLeaf(root))
    {
        cout << root->operand;
        return;
    }

    cout << "(";
    inorder(root->left);
    cout << root->_operator;
    inorder(root->right);
    cout << ")";
}

// Evaluates the expression in the Expression Tree
void Tree::evaluateExpression()
{
    if (isEvaluated)
        return;

    postorder(root); // Perform a postorder traversal to evaluate the tree
    isEvaluated = true;
}

// Performs a postorder traversal to evaluate the Expression Tree
void Tree::postorder(Node *root)
{
    if (isLeaf(root))
        return;

    // Evaluate the left and right subtrees
    postorder(root->left);
    postorder(root->right);

    // Evaluate the current sub-expression
    double result = eval(root->_operator, root->left->operand, root->right->operand);

    // Store the result in the current node
    root->operand = result;
}

// Evaluates a sub-expression given an operator and two operands
double Tree::eval(const char opr, const double leftOperand, const double rightOperand)
{
    switch (opr)
    {
    case '+':
        return leftOperand + rightOperand;
    case '-':
        return leftOperand - rightOperand;
    case '*':
        return leftOperand * rightOperand;
    case '/':
        if ((int)rightOperand == 0)
            throw "Division by 0";
        return leftOperand / rightOperand;
    }
    return 0; // Default return value (should not reach here)
}

// Returns the result of the expression
double Tree::getResult()
{
    if (!isEvaluated)
        evaluateExpression();

    return root->operand;
}

// Checks if a node is a leaf node
bool Tree::isLeaf(Node *ptr)
{
    return ptr->left == NULL && ptr->right == NULL;
}

int main(int argc, char **argv)
{
    // Example expressions
    const string expr1 = "((5+2)*(3-1))";
    const string expr2 = "(5+((3-4)*2))";
    const string expr3 = "(8*((5+(3-(4/(3/2))))-1))";

    // Create Expression Trees for the given expressions
    ExpressionTree exprTree1(expr1);
    ExpressionTree exprTree2(expr2);
    ExpressionTree exprTree3(expr3);

    // Display the expressions in infix notation
    cout << "Expr Tree 1 = ";
    exprTree1.showExpression();
    cout << "Expr Tree 2 = ";
    exprTree2.showExpression();
    cout << "Expr Tree 3 = ";
    exprTree3.showExpression();

    cout << "Evaluating...\n";

    // Evaluate the expressions
    exprTree1.evaluateExpression();
    exprTree2.evaluateExpression();
    exprTree3.evaluateExpression();

    // Display the results of the evaluations
    cout << "Expr Tree 1 Result = " << exprTree1.getResult() << "\n";
    cout << "Expr Tree 2 Result = " << exprTree2.getResult() << "\n";
    cout << "Expr Tree 3 Result = " << exprTree3.getResult() << "\n";

    return 0;
}