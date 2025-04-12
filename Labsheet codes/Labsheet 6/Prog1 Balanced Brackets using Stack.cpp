#include <iostream>
using namespace std;
template <typename E>
class ArrayStack
{
    enum
    {
        DEF_CAPACITY = 100
    }; // default stack capacity
public:
    ArrayStack(int cap = DEF_CAPACITY); // constructor from capacity
    int size() const;                   // number of items in the stack
    bool empty() const;                 // is the stack empty?
    const E &top();                     // get the top element
    void push(const E &e);              // push element onto stack
    void pop();                         // pop the stack
                                        // ...housekeeping functions omitted
private:                                // member data
    E *S;                               // array of stack elements
    int capacity;                       // stack capacity
    int t;                              // index of the top of the stack
};
template <typename E> // push element onto the stack
void ArrayStack<E>::push(const E &e)
{
    if (size() == capacity)
        cout << "Push to full stack\n";
    S[++t] = e;
}
template <typename E> // pop the stack
void ArrayStack<E>::pop()
{
    if (empty())
        cout << "Pop from empty stack\n";
    --t;
}
template <typename E>
ArrayStack<E>::ArrayStack(int cap)
    : S(new E[cap]), capacity(cap), t(-1) {} // constructor from capacity
template <typename E>
int ArrayStack<E>::size() const
{
    return (t + 1);
} // number of items in the stack

template <typename E>
bool ArrayStack<E>::empty() const
{
    return (t < 0);
} // is the stack empty?

template <typename E> // return top of stack
const E &ArrayStack<E>::top()
{
    if (empty())
        cout << "Top of empty stack\n";
    return S[t];
}
// returns true if the given character is a bracket, false o.w.
bool isBracket(char c)
{
    return c == '(' || c == ')' || c == '{' || c == '}' || c == '[' || c == ']'; // Added support for {} and []
}

// returns true if the brackets match, false o.w.
bool isMatchingPair(char open, char close)
{
    return (open == '(' && close == ')') ||
           (open == '{' && close == '}') ||
           (open == '[' && close == ']'); // Added matching logic for {} and []
}

bool isBalanced(const string &expression)
{
    ArrayStack<char> stack;

    for (char c : expression)
    {
        if (c == '(' || c == '{' || c == '[') // Push opening brackets onto the stack
        {
            stack.push(c);
        }
        else if (c == ')' || c == '}' || c == ']') // Check closing brackets
        {
            if (stack.empty() || !isMatchingPair(stack.top(), c))
                return false; // Unmatched closing bracket or mismatched pair
            stack.pop();
        }
    }

    return stack.empty(); // If stack is empty, all brackets are balanced
}

int main()
{
    string expression;
    cout << "Enter an expression: ";
    cin >> expression;

    if (isBalanced(expression))
        cout << "The expression has balanced brackets.\n";
    else
        cout << "The expression does not have balanced brackets.\n";

    return 0;
}