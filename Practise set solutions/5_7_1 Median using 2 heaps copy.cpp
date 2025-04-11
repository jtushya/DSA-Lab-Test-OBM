#include <iostream>
using namespace std;

class MaxHeap {
public:
    int* arr;
    int size;
    int capacity;

    MaxHeap(int cap) {
        capacity = cap;
        arr = new int[cap];
        size = 0;
    }

    ~MaxHeap() {
        delete[] arr;
    }

    void push(int val) {
        if (size == capacity) return;
        int i = size++;
        arr[i] = val;
        while (i > 0 && arr[(i - 1) / 2] < arr[i]) {
            swap(arr[i], arr[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }

    int pop() {
        if (size == 0) return -1;
        int root = arr[0];
        arr[0] = arr[--size];
        heapify(0);
        return root;
    }

    int top() {
        return size > 0 ? arr[0] : -1;
    }

    int getSize() {
        return size;
    }

private:
    void heapify(int i) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        if (left < size && arr[left] > arr[largest]) largest = left;
        if (right < size && arr[right] > arr[largest]) largest = right;
        if (largest != i) {
            swap(arr[i], arr[largest]);
            heapify(largest);
        }
    }
};

void runningMedian(int n, int arr[]) {
    MaxHeap left(n), right(n); // right is simulated MinHeap using negative values

    for (int i = 0; i < n; i++) {
        int num = arr[i];

        if (left.getSize() == 0 || num <= left.top()) {
            left.push(num);
        } else {
            right.push(-num); // simulate min-heap
        }

        // Balance the heaps
        if (left.getSize() > right.getSize() + 1) {
            int temp = left.pop();
            right.push(-temp);
        } else if (right.getSize() > left.getSize()) {
            int temp = -right.pop();
            left.push(temp);
        }

        // Median is the top of the left heap
        cout << left.top() << " ";
    }

    cout << endl;
}

int main() {
    int n;
    cin >> n;
    int arr[n];
    for (int i = 0; i < n; i++) cin >> arr[i];
    runningMedian(n, arr);
    return 0;
}
