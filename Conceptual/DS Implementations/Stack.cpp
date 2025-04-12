#include <iostream>
#include <stack>
using namespace std;

class Stack {
private:
    int* arr;
    int top;
    int capacity;

public:
    Stack(int size) {
        arr = new int[size];
        capacity = size;
        top = -1;
    }

    ~Stack() {
        delete[] arr;
    }

    void push(int x) {
        if (isFull()) {
            cout << "Stack Overflow\n";
            return;
        }
        arr[++top] = x;
    }

    int pop() {
        if (isEmpty()) {
            cout << "Stack Underflow\n";
            return -1;
        }
        return arr[top--];
    }

    int peek() {
        if (!isEmpty()) {
            return arr[top];
        }
        return -1;
    }

    bool isEmpty() {
        return top == -1;
    }

    bool isFull() {
        return top == capacity - 1;
    }
};

int main() {
    Stack s(5);

    s.push(1);
    s.push(2);
    s.push(3);

    cout << "Top element is: " << s.peek() << endl;

    cout << "Stack elements: ";
    while (!s.isEmpty()) {
        cout << s.pop() << " ";
    }
    cout << endl;

    return 0;
}