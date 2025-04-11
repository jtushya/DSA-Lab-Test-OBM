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
    MinHeap()
    {
        heapCapacity = 100;
        heap = new int[heapCapacity];
        heapSize = 0;
    }

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

int max(int a, int b) {
    return (a > b) ? a : b;
}

int longestJobFirst(int M, int N, int jobs[])
{
    // Simple selection sort in descending order
    for (int i = 0; i < N - 1; i++) {
        for (int j = i + 1; j < N; j++) {
            if (jobs[i] < jobs[j]) {
                int temp = jobs[i];
                jobs[i] = jobs[j];
                jobs[j] = temp;
            }
        }
    }

    int* cpu = new int[M];
    for (int i = 0; i < M; i++) cpu[i] = 0;

    for (int i = 0; i < N; i++) {
        int minIdx = 0;
        for (int j = 1; j < M; j++) {
            if (cpu[j] < cpu[minIdx])
                minIdx = j;
        }
        cpu[minIdx] += jobs[i];
    }

    int maxTime = cpu[0];
    for (int i = 1; i < M; i++)
        maxTime = max(maxTime, cpu[i]);

    delete[] cpu;
    return maxTime;
}

int main()
{
    int M, N;
    cout << "M = "; cin >> M;
    cout << "N = "; cin >> N;

    int* arr = new int[N];
    cout << "Enter CPU times of " << N << " jobs:\n";
    for (int i = 0; i < N; i++)
        cin >> arr[i];

    int ljf = longestJobFirst(M, N, arr);
    MinHeap minHeap(arr, N);

    int* cpu = new int[M]{0};
    for (int i = 0; i < M && !minHeap.empty(); i++)
        cpu[i] = minHeap.extractMin();

    int t = 0;
    while (!minHeap.empty()) {
        int minJobTime = cpu[0];
        for (int i = 1; i < M; i++)
            if (cpu[i] < minJobTime)
                minJobTime = cpu[i];

        for (int i = 0; i < M; i++) {
            cpu[i] -= minJobTime;
            if (cpu[i] == 0 && !minHeap.empty())
                cpu[i] = minHeap.extractMin();
        }
        t += minJobTime;
    }

    int sjf = t;
    for (int i = 0; i < M; i++)
        sjf = max(sjf, t + cpu[i]);

    cout << "Time taken by Longest Job First = " << ljf << endl;
    cout << "Time taken by Shortest Job First = " << sjf << endl;

    delete[] arr;
    delete[] cpu;
    return 0;
}
