#include <iostream>
using namespace std;

// Array based Min Heap implementation without using STL vector
class MinHeap
{
private:
    int* heap; // dynamic array
    int heapSize;
    int heapCapacity;
    void buildMinHeap();
    void bubbleDown(int index);
    void bubbleUp(int index);
    void swap(int i, int j);
    void resize();

public:
    // initializes an empty heap
    MinHeap()
    {
        heapCapacity = 100; // initial capacity
        heap = new int[heapCapacity];
        heapSize = 0;
    }

    // initializes the heap with the given elements.
    MinHeap(int arr[], int size)
    {
        heapCapacity = size;
        heapSize = size;
        heap = new int[heapCapacity];
        for (int i = 0; i < size; i++)
            heap[i] = arr[i];
        buildMinHeap();
    }

    ~MinHeap()
    {
        delete[] heap;
    }

    void insert(int elem);
    int getMin() const;
    int extractMin();
    void sort(int sorted[]);
    void display();
    bool empty() const;
    int size() const;
};

void MinHeap::buildMinHeap()
{
    for (int i = (heapSize >> 1) - 1; i >= 0; i--)
        bubbleDown(i);
}

void MinHeap::resize()
{
    heapCapacity *= 2;
    int* newHeap = new int[heapCapacity];
    for (int i = 0; i < heapSize; i++)
        newHeap[i] = heap[i];
    delete[] heap;
    heap = newHeap;
}

void MinHeap::insert(int elem)
{
    if (heapSize == heapCapacity)
        resize();

    heap[heapSize] = elem;
    bubbleUp(heapSize);
    heapSize++;
}

int MinHeap::getMin() const
{
    if (empty()) throw "Heap is Empty!";
    return heap[0];
}

int MinHeap::extractMin()
{
    if (empty()) throw "Heap is Empty!";
    int item = heap[0];
    heap[0] = heap[heapSize - 1];
    heapSize--;
    bubbleDown(0);
    return item;
}

void MinHeap::sort(int sorted[])
{
    int originalSize = heapSize;
    for (int i = 0; i < originalSize; i++)
        sorted[i] = extractMin();

    // Rebuild original heap from sorted for reusability
    for (int i = 0; i < originalSize; i++)
        insert(sorted[i]);
}

void MinHeap::bubbleUp(int index)
{
    while (index > 0)
    {
        int parent = (index - 1) >> 1;
        if (heap[index] < heap[parent])
        {
            swap(index, parent);
            index = parent;
        }
        else break;
    }
}

void MinHeap::bubbleDown(int index)
{
    while (true)
    {
        int left = (index << 1) + 1;
        int right = (index << 1) + 2;
        int smallest = index;

        if (left < heapSize && heap[left] < heap[smallest])
            smallest = left;
        if (right < heapSize && heap[right] < heap[smallest])
            smallest = right;

        if (smallest == index) break;

        swap(index, smallest);
        index = smallest;
    }
}

void MinHeap::swap(int i, int j)
{
    int temp = heap[i];
    heap[i] = heap[j];
    heap[j] = temp;
}

void MinHeap::display()
{
    cout << '[';
    for (int i = 0; i < heapSize - 1; i++)
        cout << heap[i] << ", ";
    if (!empty())
        cout << heap[heapSize - 1];
    cout << "]\n";
}

bool MinHeap::empty() const
{
    return heapSize == 0;
}

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

    int inputList[] = {7, 4, -2, 15, 9, 11};
    int size = sizeof(inputList) / sizeof(inputList[0]);

    cout << "Input List:-\n";
    for (int i = 0; i < size; i++)
        cout << inputList[i] << ' ';
    cout << endl;

    MinHeap minHeap2(inputList, size);
    int* sortedList = new int[size];
    minHeap2.sort(sortedList);

    cout << "Sorted List:-\n";
    for (int i = 0; i < size; i++)
        cout << sortedList[i] << ' ';
    cout << endl;

    delete[] sortedList;

    return 0;
}
