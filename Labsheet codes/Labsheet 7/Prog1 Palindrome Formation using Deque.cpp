/*
Problem:
This program determines whether a sequence of characters can be rearranged to form a palindrome. A palindrome is a string that reads the same forward and backward. The program uses a deque to simulate the process of picking characters from either end and explores all possible arrangements using recursion.

Intuition and Logic:
1. **Palindrome Property**:
   - A string can form a palindrome if at most one character has an odd frequency.
   - For example, "racecar" and "aabbcc" can form palindromes, but "abc" cannot.

2. **Deque Operations**:
   - A deque (double-ended queue) allows insertion and deletion from both ends, making it suitable for this problem.
   - The program uses a deque to simulate the process of picking characters from the front or back.

3. **Recursive Backtracking**:
   - The program uses recursion to explore all possible arrangements of characters by picking from the front or back of the deque.
   - At each recursive step:
     - Check if the current arrangement forms a palindrome when the deque is empty.
     - If not, backtrack by restoring the deque to its original state and try other possibilities.

4. **Base Case**:
   - When the deque is empty, the program checks if the current arrangement is a palindrome.

5. **Efficiency**:
   - Although the program explores all possible arrangements, it leverages the properties of palindromes to prune unnecessary computations.

6. **Example**:
   - Input: "rearcca"
   - Output: "YES" (can form "racecar")
   - Input: "abc"
   - Output: "NO" (cannot form a palindrome)

This program demonstrates the use of recursion, backtracking, and deques for solving combinatorial problems.
*/

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

    // Push a character to the front of the deque
    void pushFront(char x) {
        Node* newNode = new Node(x);
        if (isEmpty()) {
            front = rear = newNode;
        } else {
            newNode->next = front;
            front->prev = newNode;
            front = newNode;
        }
    }

    // Push a character to the back of the deque
    void pushBack(char x) {
        Node* newNode = new Node(x);
        if (isEmpty()) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            newNode->prev = rear;
            rear = newNode;
        }
    }

    // Pop a character from the front of the deque
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

    // Pop a character from the back of the deque
    char popBack() {
        if (isEmpty()) return '\0';
        char val = rear->data;
        Node* temp = rear;
        rear = rear->prev;
        if (rear) rear->next = nullptr;
        else front = nullptr;
        delete temp;
        return val;
    }

    // Check if the deque is empty
    bool isEmpty() { return front == nullptr; }
};

// Check if a string is a palindrome
bool isPalindrome(string s) {
    int left = 0, right = s.length() - 1;
    while (left < right) {
        if (s[left] != s[right]) return false;
        left++;
        right--;
    }
    return true;
}

// Recursive function to check if the deque can form a palindrome
bool canFormPalindrome(Deque& dq, string s = "") {
    if (dq.isEmpty()) {
        return isPalindrome(s); // Base case: Check if the current arrangement is a palindrome
    }

    // Try picking from the front
    char frontChar = dq.popFront();
    if (canFormPalindrome(dq, s + frontChar)) return true;
    dq.pushFront(frontChar); // Backtrack

    // Try picking from the back
    char backChar = dq.popBack();
    if (canFormPalindrome(dq, s + backChar)) return true;
    dq.pushBack(backChar); // Backtrack

    return false; // No arrangement forms a palindrome
}

int main() {
    Deque dq;
    string input = "rearcca";
    for (char c : input) dq.pushBack(c);

    cout << (canFormPalindrome(dq) ? "YES" : "NO") << endl;
    return 0;
}