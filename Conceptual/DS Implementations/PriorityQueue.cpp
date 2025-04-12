#include <iostream>
#include <queue>
using namespace std;

class PriorityQueue {
private:
    priority_queue<int> pq;

public:
    void push(int data) {
        pq.push(data);
    }

    void pop() {
        if (!pq.empty()) {
            pq.pop();
        } else {
            cout << "Priority Queue is empty\n";
        }
    }

    int top() {
        if (!pq.empty()) {
            return pq.top();
        }
        cout << "Priority Queue is empty\n";
        return -1;
    }

    bool isEmpty() {
        return pq.empty();
    }
};

int main() {
    PriorityQueue pq;

    pq.push(10);
    pq.push(20);
    pq.push(15);

    cout << "Top element: " << pq.top() << endl;

    pq.pop();
    cout << "Top element after pop: " << pq.top() << endl;

    return 0;
}