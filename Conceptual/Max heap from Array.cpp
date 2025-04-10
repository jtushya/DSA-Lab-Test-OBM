#include <iostream>
using namespace std;

// Heapify a subtree rooted with node i, which is an index in arr[], n is size of heap
void heapify(int arr[], int n, int i) {
    int largest = i;          // Initialize largest as root
    int left = 2 * i + 1;     // Left child index
    int right = 2 * i + 2;    // Right child index

    // If left child is larger than root
    if (left < n && arr[left] > arr[largest])
        largest = left;

    // If right child is larger than the current largest
    if (right < n && arr[right] > arr[largest])
        largest = right;

    // If largest is not root
    if (largest != i) {
        swap(arr[i], arr[largest]);    // Swap with larger child
        heapify(arr, n, largest);      // Recursively heapify the affected subtree
    }
}

// Function to build a Max-Heap from the given array
void buildMaxHeap(int arr[], int n) {
    // Start from the last internal node and heapify each
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
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
    int arr[] = {4, 10, 3, 5, 1, 8, 7};
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "Original array:\n";
    printArray(arr, n);

    buildMaxHeap(arr, n);

    cout << "Max-Heap array:\n";
    printArray(arr, n);

    return 0;
}
