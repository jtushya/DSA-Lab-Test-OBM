#include <iostream>

using namespace std;

class ExpressionTreeNode
{
public:
    double operand;
    char _operator;
    ExpressionTreeNode *left, *right;
    ExpressionTreeNode()
    {
        operand = 0;
        _operator = '\0';
        left = right = NULL;
    }
};

typedef ExpressionTreeNode Node;

class ExpressionTree
{
private:
    int idx;
    bool isEvaluated;
    Node *root;
    Node *buildExpressionTree(const string);
    void inorder(Node *ptr);
    void postorder(Node *ptr);

public:
    ExpressionTree(const string expr)
    {
        idx = 0;
        isEvaluated = false;
        root = buildExpressionTree(expr);
    }
    void showExpression();
    void evaluateExpression();
    double eval(const char opr, const double leftOperand, const double rightOperand);
    double getResult();
    bool isLeaf(Node *ptr);
};

typedef ExpressionTree Tree;

// given a valid parenthesized expression
// convert it into a Expression Tree
// leaf nodes should contain the operand
// Internal nodes should contain the operator
Node *Tree::buildExpressionTree(const string expr)
{
    if (idx == expr.length())
        return NULL;

    Node *root = new Node();

    if (expr[idx] == '(')
    {
        ++idx;

        root->left = buildExpressionTree(expr);
    }
    else
    {
        root->operand = expr[idx] - '0'; // operand is always a leaf node
        return root;
    }

    ++idx;

    // skip over closing parenthesis ')' (if any)
    while (idx < expr.length() && expr[idx] == ')')
        ++idx;

    if (idx == expr.length())
        return root;

    root->_operator = expr[idx]; // operator is always an internal node

    ++idx;

    root->right = buildExpressionTree(expr);

    return root;
}

// Prints the expression contained in the expression tree
void Tree::showExpression()
{
    inorder(root);
    cout << endl;
}

// an inorder walk over the expression tree
void Tree::inorder(Node *root)
{
    // base case
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

// Evaluates the expression contained in the expression tree
// Each sub-tree root node will contain the result of
// the sub-expression that follows that root.
void Tree::evaluateExpression()
{
    if (isEvaluated)
        return;

    postorder(root);

    isEvaluated = true;
}

void Tree::postorder(Node *root)
{
    // base case
    if (isLeaf(root))
        return;

    // Solve left-sub-tree
    postorder(root->left);

    // Solve right-sub-tree
    postorder(root->right);

    // Evaluate this sub-expression
    double result = eval(root->_operator, root->left->operand, root->right->operand);

    // assigned result to the root node
    root->operand = result;
}

// Utility method to evaluate the sub-expression
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
            throw "Divison by 0";
        return leftOperand / rightOperand;
    }
}

// Returns the result of the expression
double Tree::getResult()
{
    if (!isEvaluated)
        evaluateExpression();

    return root->operand;
}

// Utility method to check whether the given node
// is a Leaf node or not
bool Tree::isLeaf(Node *ptr)
{
    return ptr->left == NULL && ptr->right == NULL;
}

int main(int argc, char **argv)
{
    const string expr1 = "((5+2)*(3-1))";
    const string expr2 = "(5+((3-4)*2)";
    const string expr3 = "(8*((5+(3-(4/(3/2))))-1))";

    ExpressionTree exprTree1(expr1);
    ExpressionTree exprTree2(expr2);
    ExpressionTree exprTree3(expr3);

    cout << "Expr Tree 1 = ";
    exprTree1.showExpression();
    cout << "Expr Tree 2 = ";
    exprTree2.showExpression();
    cout << "Expr Tree 3 = ";
    exprTree3.showExpression();

    cout << "Evaluating...\n";

    exprTree1.evaluateExpression();
    exprTree2.evaluateExpression();
    exprTree3.evaluateExpression();

    cout << "Expr Tree 1 Result = " << exprTree1.getResult() << "\n";
    cout << "Expr Tree 2 Result = " << exprTree2.getResult() << "\n";
    cout << "Expr Tree 3 Result = " << exprTree3.getResult() << "\n";

    return 0;
}