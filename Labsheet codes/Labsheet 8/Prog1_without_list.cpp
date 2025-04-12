#include <iostream>
using namespace std;

// Node structure for the linked list
struct Node {
    int data;
    Node* next;

    Node(int val) : data(val), next(nullptr) {}
};

// Custom LinkedList class
class LinkedList {
private:
    Node* head;
    Node* tail;

public:
    // Constructor
    LinkedList() : head(nullptr), tail(nullptr) {}

    // Add a new element to the end of the list
    void push_back(int val) {
        Node* newNode = new Node(val);
        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    // Iterator class for the linked list
    class Iterator {
    private:
        Node* current;

    public:
        Iterator(Node* node) : current(node) {}

        // Dereference operator
        int& operator*() {
            return current->data;
        }

        // Pre-increment operator
        Iterator& operator++() {
            current = current->next;
            return *this;
        }

        // Equality operator
        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }
    };

    // Begin iterator
    Iterator begin() {
        return Iterator(head);
    }

    // End iterator
    Iterator end() {
        return Iterator(nullptr);
    }
};

int main() {
    // Custom linked list specifying the marks
    LinkedList marks;

    int N;
    cout << "Enter the number of subjects: ";
    cin >> N;

    cout << "Enter the marks in " << N << " subjects: ";
    for (int i = 0; i < N; i++) {
        int mark;
        cin >> mark;
        marks.push_back(mark); // Add mark to the custom linked list
    }

    // Using Iterator, Display marks
    cout << "Input Marks: ";
    for (auto itr = marks.begin(); itr != marks.end(); ++itr)
        cout << *itr << " ";
    cout << endl;

    // Using Iterator, Check whether the mark is even or odd
    for (auto itr = marks.begin(); itr != marks.end(); ++itr) {
        if (*itr % 2 == 0)
            cout << *itr << " = Even" << endl;
        else
            cout << *itr << " = Odd" << endl;
    }

    // Using Iterator, update the marks by 10
    for (auto itr = marks.begin(); itr != marks.end(); ++itr)
        *itr = *itr + 10;

    cout << "Updated Marks: ";
    // Using Iterator, Display updated marks
    for (auto itr = marks.begin(); itr != marks.end(); ++itr)
        cout << *itr << " ";
    cout << endl;

    return 0;
}
