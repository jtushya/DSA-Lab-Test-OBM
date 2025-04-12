/*
Intuition and Logic:
1. The Stock Span Problem:
   - Given the price of a stock for `n` days, the stock span for a day is defined as the maximum number of consecutive days (up to the current day) the stock price was less than or equal to the price on the current day.

2. Approach:
   - Use a stack to efficiently calculate the span for each day.
   - The stack stores indices of the days in decreasing order of their stock prices.
   - For each day `i`:
     - Pop elements from the stack until the stack is empty or the price at the top of the stack is greater than the price on day `i`.
     - If the stack is empty, the span is `i + 1` (all previous days have prices less than or equal to the current price).
     - Otherwise, the span is `i - stack.top()` (difference between the current day and the last day with a higher price).

3. Example:
   Input: Prices = [100, 80, 60, 70, 60, 75, 85]
   Output: Spans = [1, 1, 1, 2, 1, 4, 6]
   Explanation:
   - Day 0: Price = 100, Span = 1 (no previous days)
   - Day 1: Price = 80, Span = 1 (no previous days with price <= 80)
   - Day 2: Price = 60, Span = 1 (no previous days with price <= 60)
   - Day 3: Price = 70, Span = 2 (Day 2 has price <= 70)
   - Day 4: Price = 60, Span = 1 (no previous days with price <= 60)
   - Day 5: Price = 75, Span = 4 (Days 4, 3, 2, and 1 have prices <= 75)
   - Day 6: Price = 85, Span = 6 (Days 5, 4, 3, 2, 1, and 0 have prices <= 85)
*/

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

int main()
{
    int n;
    cout << "Enter the number of days: ";
    cin >> n;

    int prices[n];
    cout << "Enter the stock prices for " << n << " days: ";
    for (int i = 0; i < n; i++)
        cin >> prices[i];

    int spans[n];
    ArrayStack<int> stack;

    for (int i = 0; i < n; i++)
    {
        // Pop elements from the stack while the stack is not empty and the price at the top of the stack is less than or equal to the current price
        while (!stack.empty() && prices[stack.top()] <= prices[i])
            stack.pop();

        // Calculate the span
        spans[i] = stack.empty() ? (i + 1) : (i - stack.top());

        // Push the current index onto the stack
        stack.push(i);
    }

    cout << "Stock spans for each day: ";
    for (int i = 0; i < n; i++)
        cout << spans[i] << " ";
    cout << endl;

    return 0;
}