#include <iostream>
using namespace std;

/*
============================================
📘 PRACTICE SET 6 — PROBLEM 4
============================================

🔹 PROBLEM STATEMENT
---------------------
You are given k sorted arrays.
Merge them into a single sorted array using a min-heap (priority queue).
Arrays are statically allocated (not vectors).
============================================
*/

struct HeapNode {
    int value;  // the actual number
    int row;    // which array it came from
    int index;  // index in that array

    HeapNode(int v, int r, int i) : value(v), row(r), index(i) {}
};

class MinHeap {
    HeapNode** heap;
    int capacity, size;

    void heapify(int i) {
        int smallest = i;
        int left = 2*i + 1;
        int right = 2*i + 2;

        if (left < size && heap[left]->value < heap[smallest]->value)
            smallest = left;
        if (right < size && heap[right]->value < heap[smallest]->value)
            smallest = right;

        if (smallest != i) {
            swap(heap[i], heap[smallest]);
            heapify(smallest);
        }
    }

public:
    MinHeap(int cap) : capacity(cap), size(0) {
        heap = new HeapNode*[cap];
    }

    void insert(HeapNode* node) {
        int i = size++;
        heap[i] = node;
        while (i && heap[(i - 1) / 2]->value > heap[i]->value) {
            swap(heap[i], heap[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }

    HeapNode* extractMin() {
        if (size == 0) return nullptr;
        HeapNode* root = heap[0];
        heap[0] = heap[--size];
        heapify(0);
        return root;
    }

    bool isEmpty() { return size == 0; }
};

int* mergeKSortedArrays(int arr[][100], int sizes[], int k, int &resultSize) {
    MinHeap minHeap(k);
    int totalSize = 0;

    // Step 1: insert first elements from each array
    for (int i = 0; i < k; i++) {
        totalSize += sizes[i];
        if (sizes[i] > 0) {
            minHeap.insert(new HeapNode(arr[i][0], i, 0));
        }
    }

    int* result = new int[totalSize];
    int idx = 0;

    // Step 2: build result
    while (!minHeap.isEmpty()) {
        HeapNode* minNode = minHeap.extractMin();
        result[idx++] = minNode->value;

        int r = minNode->row;
        int i = minNode->index;
        if (i + 1 < sizes[r]) {
            minHeap.insert(new HeapNode(arr[r][i + 1], r, i + 1));
        }
    }

    resultSize = totalSize;
    return result;
}

int main() {
    int k;
    cin >> k;

    int arr[10][100];      // Supports up to 10 arrays with 100 elements each
    int sizes[10];         // Size of each array

    for (int i = 0; i < k; i++) {
        cin >> sizes[i];
        for (int j = 0; j < sizes[i]; j++) {
            cin >> arr[i][j];
        }
    }

    int resultSize;
    int* result = mergeKSortedArrays(arr, sizes, k, resultSize);

    for (int i = 0; i < resultSize; i++) {
        cout << result[i] << " \n"[i == resultSize - 1];
    }

    delete[] result;
    return 0;
}
