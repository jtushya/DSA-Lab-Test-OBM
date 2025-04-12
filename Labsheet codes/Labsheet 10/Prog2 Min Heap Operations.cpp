#include <iostream>
#include <vector>
using namespace std;

// Dynamic Array / Vector based Min Heap implementation
class MinHeap
{
private:
    vector<int> heap;
    int heapSize;
    int heapCapacity;
    void buildMinHeap();
    void bubbleDown(int index);
    void bubbleUp(int index);
    void swap(int i, int j);

public:
    // initializes an empty heap
    MinHeap()
    {
        heapSize = heapCapacity = 0;
    }
    // initializes the heap with the given elements.
    // This runs BUILD_MIN_HEAP operation internally.
    MinHeap(vector<int> elems)
    {
        heapSize = heapCapacity = elems.size();

        // hard-copy of elements into the heap
        for (int elem : elems)
        {
            heap.push_back(elem);
        }

        buildMinHeap();
    }
    void insert(int elem);
    int getMin() const;
    int extractMin();
    vector<int> sort();
    void display();
    bool empty() const;
    int size() const;
};

// BUILD_MIN_HEAP operation.
// Time Complexity = O(n)
void MinHeap::buildMinHeap()
{
    // Run from last internal node upto the root node.
    for (int i = (heapSize >> 1) - 1; i >= 0; i--)
    {
        // Heapify this entry
        bubbleDown(i);
    }
}

// Inserts the given element to the Heap
// Time Complexity = O(log n)
void MinHeap::insert(int elem)
{
    if (heapSize < heapCapacity)
    {
        // update the index with the new element
        heap.at(heapSize) = elem;
    }
    else
    {
        // append at the back
        heap.push_back(elem);
        ++heapCapacity;
    }

    // heapify this new entry
    bubbleUp(heapSize);

    // increment heap size
    ++heapSize;
}

// Returns the minimum item in the Heap
// Time Complexity = O(1)
int MinHeap::getMin() const
{
    return heap.at(0);
}

// Task 1: Complete extractMin() method
// Extracts and returns the minimum item from the heap.
// Time Complexity = O(log n)
int MinHeap::extractMin()
{
    if (empty())
        throw "Heap is Empty!";

    // Grab the minimum item at the root
    int item = heap.at(0);

    // Move the last element to the root
    heap.at(0) = heap.at(heapSize - 1);

    // Remove the last element (as it's now duplicated at root)
    heap.pop_back();

    // Decrease the heap size
    --heapSize;

    // Perform heapify (bubble down) to restore heap property
    bubbleDown(0);

    return item;
}

// Heap Sort Algorithm.
// Returns the sorted list of elements in the Min Heap.
// Time Complexity = O(n * log n)
vector<int> MinHeap::sort()
{
    vector<int> sortedList;

    // STEP 1: Apply BUILD_MIN_HEAP operation
    buildMinHeap();

    // STEP 2: Use extractMin() to populate sortedList
    while (!empty()) // O(n)
    {
        // extract minimum element
        int minElem = extractMin(); // O(log n)

        // insert minElem into sortedList
        sortedList.push_back(minElem); // O(1)
    }

    // Populate heap
    for (int elem : sortedList)
        insert(elem);

    return sortedList;
}

// Bubble-Up operation
// Move a node upwards until the heap invariant is satisfied.
// Time Complexity = O(log n)
void MinHeap::bubbleUp(int index)
{
    if (index < 0 || index > heapSize)
        throw "Invalid index.";
    if (index == 0)
        return;

    // Grab the index of the next parent node w.r.t. index
    int parent = (index - 1) >> 1;

    // Keep bubbling up, until we reach the root
    // or the heap property is satisfied.
    while (index > 0 && heap.at(index) < heap.at(parent))
    {
        // Exchange index with parent
        swap(index, parent);

        // update indices.
        index = parent;
        parent = (index - 1) >> 1;
    }
}

// Task 2: Implement bubbleDown() method
// Bubble-Down operation
// Move a node downwards until the heap invariant is satisfied.
// Time Complexity = O(log n)
void MinHeap::bubbleDown(int index)
{
    if (index < 0 || index >= heapSize)
        throw "Invalid index.";

    while (true)
    {
        // Calculate indices of left and right children
        int left = (index << 1) + 1;
        int right = (index << 1) + 2;
        int smallest = index;

        // If left child exists and is smaller than current smallest
        if (left < heapSize && heap[left] < heap[smallest])
            smallest = left;

        // If right child exists and is smaller than current smallest
        if (right < heapSize && heap[right] < heap[smallest])
            smallest = right;

        // If the current index holds the smallest value, stop
        if (smallest == index)
            break;

        // Otherwise, swap and continue bubbling down
        swap(index, smallest);
        index = smallest;
    }
}

// Utility method to swap elements at given indices.
void MinHeap::swap(int i, int j)
{
    int elem = heap.at(i);
    heap.at(i) = heap.at(j);
    heap.at(j) = elem;
}

// Utility method to print the heap items
void MinHeap::display()
{
    cout << '[';
    for (int i = 0; i < size() - 1; i++)
        cout << heap.at(i) << ", ";
    if (!empty())
        cout << heap.at(size() - 1);
    cout << "]\n";
}

// Utility method to check if the heap is empty
bool MinHeap::empty() const
{
    return size() == 0;
}

// Utility method to get the size of the heap
int MinHeap::size() const
{
    return heapSize;
}

int main()
{
    MinHeap minHeap;

    minHeap.insert(6);
    minHeap.insert(3);
    minHeap.insert(4);
    minHeap.insert(7);

    cout << "Heap Elems: ";
    minHeap.display();

    cout << "Min Elem = " << minHeap.getMin() << '\n';

    cout << minHeap.extractMin() << " removed!\n";

    cout << "Heap Elems: ";
    minHeap.display();

    cout << "Min Elem = " << minHeap.getMin() << '\n';

    cout << minHeap.extractMin() << " removed!\n";

    cout << "Heap Elems: ";
    minHeap.display();

    minHeap.insert(8);
    minHeap.insert(1);

    cout << "Heap Elems: ";
    minHeap.display();

    cout << "Min Elem = " << minHeap.getMin() << '\n';

    cout << '\n';

    vector<int> inputList = {7, 4, -2, 15, 9, 11};

    cout << "Input List:-\n";
    for (int elem : inputList)
        cout << elem << ' ';
    cout << endl;

    MinHeap minHeap2(inputList);

    vector<int> sortedList = minHeap2.sort();

    cout << "Sorted List:-\n";
    for (int elem : sortedList)
        cout << elem << ' ';
    cout << endl;

    return 0;
}