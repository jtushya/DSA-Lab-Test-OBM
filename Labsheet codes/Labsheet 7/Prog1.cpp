#include <iostream>
using namespace std;

struct Node {
    char data;
    Node* next;
    Node* prev;
    Node(char val) : data(val), next(nullptr), prev(nullptr) {}
};

class Deque {
private:
    Node* front;
    Node* rear;
public:
    Deque() : front(nullptr), rear(nullptr) {}
    ~Deque() {
        while (!isEmpty()) popFront();
    }
    void pushFront(char x) {
        /* ??? */
    }
    void pushBack(char x) {
        Node* newNode = new Node(x);
        if (isEmpty()) front = rear = newNode;
        else {
            rear->next = newNode;
            newNode->prev = rear;
            rear = newNode;
        }
    }
    char popFront() {
        if (isEmpty()) return '\0';
        char val = front->data;
        Node* temp = front;
        front = front->next;
        if (front) front->prev = nullptr;
        else rear = nullptr;
        delete temp;
        return val;
    }
    char popBack() {
        /* ??? */
    }
    bool isEmpty() { return front == nullptr; }
};

bool isPalindrome(string s) {
    /* ??? */
}

bool canFormPalindrome(Deque& dq, string s = "") {
    /* ??? */
}

int main() {
    Deque dq;
    string input = "rearcca";
    for (char c : input) dq.pushBack(c);
    cout << (canFormPalindrome(dq) ? "YES" : "NO") << endl;
    return 0;
}