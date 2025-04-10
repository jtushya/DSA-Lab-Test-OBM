#include <vector>
#include <stdexcept>
#include <iostream>

template <typename T>
class MinHeapPQ {
private:
    std::vector<T> heap;

    // Helper: Get parent, left, right indices
    int parent(int i) { return (i - 1) / 2; }
    int left(int i)   { return 2 * i + 1; }
    int right(int i)  { return 2 * i + 2; }

    // Heapify up (used during insert)
    void heapifyUp(int i) {
        while (i > 0 && heap[parent(i)] > heap[i]) {
            std::swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
    }

    // Heapify down (used during removeMin)
    void heapifyDown(int i) {
        int smallest = i;
        int l = left(i);
        int r = right(i);

        if (l < heap.size() && heap[l] < heap[smallest])
            smallest = l;
        if (r < heap.size() && heap[r] < heap[smallest])
            smallest = r;

        if (smallest != i) {
            std::swap(heap[i], heap[smallest]);
            heapifyDown(smallest);
        }
    }

public:
    // Insert into the heap
    void insert(T key) {
        heap.push_back(key);
        heapifyUp(heap.size() - 1);
    }

    // Return min (root of the heap)
    T getMin() {
        if (heap.empty()) throw std::runtime_error("Empty PQ");
        return heap[0];
    }

    // Remove the min element
    void removeMin() {
        if (heap.empty()) throw std::runtime_error("Empty PQ");

        heap[0] = heap.back();  // Move last to root
        heap.pop_back();
        heapifyDown(0);
    }

    // Utility
    bool isEmpty() const { return heap.empty(); }

    // Debugging helper
    void printHeap() {
        for (T x : heap)
            std::cout << x << " ";
        std::cout << "\n";
    }
};
