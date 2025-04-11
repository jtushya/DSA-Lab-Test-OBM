#include <iostream>
#include <vector>
using namespace std;

// Heapify a subtree rooted at index i in array of size n (Max-Heap)
void heapify(vector<int>& arr, int n, int i) {
    int largest = i;          // Assume root is largest
    int left = 2 * i + 1;     // Left child index
    int right = 2 * i + 2;    // Right child index

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    // If largest is not the root
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest); // Recursively heapify the affected subtree
    }
}

// Heap Sort function using Max-Heap
void heapSort(vector<int>& arr) {
    int n = arr.size();

    // Build Max-Heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // One by one extract elements from the heap
    for (int i = n - 1; i > 0; i--) {
        // Move current root to the end
        swap(arr[0], arr[i]);

        // Call max heapify on the reduced heap
        heapify(arr, i, 0);
    }
}

// Utility function to print array
void printArray(const vector<int>& arr) {
    for (int num : arr)
        cout << num << " ";
    cout << endl;
}

// Driver code
int main() {
    vector<int> arr = {4, 10, 3, 5, 1};

    cout << "Original array:\n";
    printArray(arr);

    heapSort(arr);

    cout << "Sorted array:\n";
    printArray(arr);

    return 0;
}
