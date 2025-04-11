#include <bits/stdc++.h>
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

int giveScore(string ops){
    ArrayStack<char> charStack;
    int sum = 0;

    for (int i=0; i < ops.length(); i++) {
        cout << ops[i] << endl;
        if (ops[i] == '+'){
                int first = charStack.top();
                charStack.pop();
                int second = charStack.top();
                charStack.push(first);
                charStack.push(first + second);
                sum += first + second;
        } else if (ops[i] == 'D'){
                sum += 2 * charStack.top();
                charStack.push(2 * charStack.top());
        } else if (//fill code here){
                //fill code here
        } else {
                sum += int(ops[i])-48;
                charStack.push(int(ops[i])-48);
        }
    }
    return sum;
}

int main()
{
    //given the string operations
    string ops = "524CD9++";
    cout << giveScore(ops);

    return 0;

}