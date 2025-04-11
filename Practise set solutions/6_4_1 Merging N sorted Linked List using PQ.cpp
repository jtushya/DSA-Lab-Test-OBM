// Practice Set 6, Problem 4 – Linked List Version
// Merge k sorted linked lists into a single sorted linked list using a priority queue

#include <iostream>
using namespace std;

struct ListNode {
    int value;
    ListNode* next;
    ListNode(int v) : value(v), next(nullptr) {}
};

struct HeapNode {
    ListNode* node;
    int listIndex;
    HeapNode(ListNode* n, int idx) : node(n), listIndex(idx) {}
};

class MinHeap {
    HeapNode** heap;
    int capacity, size;

    void heapify(int i) {
        int smallest = i;
        int left = 2 * i + 1, right = 2 * i + 2;

        if (left < size && heap[left]->node->value < heap[smallest]->node->value)
            smallest = left;
        if (right < size && heap[right]->node->value < heap[smallest]->node->value)
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

        while (i && heap[(i - 1) / 2]->node->value > heap[i]->node->value) {
            swap(heap[i], heap[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }

    HeapNode* extractMin() {
        if (size == 0) return nullptr;

        HeapNode* root = heap[0];
        size--;
        heap[0] = heap[size];
        heapify(0);
        return root;
    }

    bool isEmpty() { return size == 0; }
};

ListNode* mergeKLists(ListNode* lists[], int k) {
    MinHeap heap(k);

    // Insert head nodes of each list
    for (int i = 0; i < k; ++i)
        if (lists[i]) heap.insert(new HeapNode(lists[i], i));

    ListNode* dummy = new ListNode(-1);
    ListNode* tail = dummy;

    while (!heap.isEmpty()) {
        HeapNode* minNode = heap.extractMin();
        tail->next = minNode->node;
        tail = tail->next;

        if (minNode->node->next)
            heap.insert(new HeapNode(minNode->node->next, minNode->listIndex));
    }

    return dummy->next;
}

// --- Helper functions for input/output ---
ListNode* createList(int arr[], int size) {
    if (size == 0) return nullptr;
    ListNode* head = new ListNode(arr[0]);
    ListNode* tail = head;
    for (int i = 1; i < size; ++i) {
        tail->next = new ListNode(arr[i]);
        tail = tail->next;
    }
    return head;
}

void printList(ListNode* head) {
    while (head) {
        cout << head->value << " ";
        head = head->next;
    }
    cout << "\n";
}

// --- Main function for testing ---
int main() {
    int k;
    cin >> k;

    ListNode* lists[100]; // Assume max 100 lists

    for (int i = 0; i < k; ++i) {
        int size;
        cin >> size;
        int arr[100]; // Assume max 100 elements per list
        for (int j = 0; j < size; ++j) cin >> arr[j];
        lists[i] = createList(arr, size);
    }

    ListNode* result = mergeKLists(lists, k);
    printList(result);

    return 0;
}
