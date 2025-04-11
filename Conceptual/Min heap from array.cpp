#include <iostream>
using namespace std;

// Heapify subtree rooted at index i for Min-Heap
void minHeapify(int arr[], int n, int i) {
    int smallest = i;         // Initialize smallest as root
    int left = 2 * i + 1;     // Left child index
    int right = 2 * i + 2;    // Right child index

    // If left child is smaller than root
    if (left < n && arr[left] < arr[smallest])
        smallest = left;

    // If right child is smaller than smallest so far
    if (right < n && arr[right] < arr[smallest])
        smallest = right;

    // If smallest is not root
    if (smallest != i) {
        swap(arr[i], arr[smallest]);
        minHeapify(arr, n, smallest);  // Recursively heapify the affected subtree
    }
}

// Function to build a Min-Heap
void buildMinHeap(int arr[], int n) {
    // Start from the last internal node and heapify each
    for (int i = n / 2 - 1; i >= 0; i--) {
        minHeapify(arr, n, i);
    }
}

// Utility function to print array
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}

// Driver code
int main() {
    int arr[] = {9, 4, 7, 1, 2, 6, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "Original array:\n";
    printArray(arr, n);

    buildMinHeap(arr, n);

    cout << "Min-Heap array:\n";
    printArray(arr, n);

    return 0;
}
