//can create an alternate version where I can have machines as nodes in the heap and jobs in array

// Note: An alternate implementation can be created where machines are nodes in the heap
// and jobs are stored in an array. This would allow dynamic allocation of jobs to machines
// based on their current load.

// Shortest Job First using Min Heap

// This problem is a better problem to Program 3 from Lab 7.
// Given there are are 'M' machines / CPUs and 'N' jobs.
// Each i'th job has an associated CPU time with them.
// Implement Longest Job First scheduling algorithm
// and the Shortest Job First scheduling algorithm.
// Compare the completion time of all 'N' jobs
// w.r.t. the above algorithms.
// Why do you think there is such difference?

#include <iostream>
#include <vector>
using namespace std;

/********************************************************************
 * Copy-paste your complete solution of MinHeap class from Program 1.
 ********************************************************************/
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
    MinHeap()
    {
        heapSize = heapCapacity = 0;
    }
    MinHeap(vector<int> elems)
    {
        heapSize = heapCapacity = elems.size();
        for (int elem : elems)
            heap.push_back(elem);
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

void MinHeap::buildMinHeap()
{
    for (int i = (heapSize / 2) - 1; i >= 0; i--)
        bubbleDown(i);
}

void MinHeap::insert(int elem)
{
    if (heapSize < heapCapacity)
        heap.at(heapSize) = elem;
    else
    {
        heap.push_back(elem);
        ++heapCapacity;
    }
    bubbleUp(heapSize);
    ++heapSize;
}

int MinHeap::getMin() const
{
    return heap.at(0);
}

int MinHeap::extractMin()
{
    if (empty())
        throw "Heap is Empty!";
    int item = heap.at(0);
    heap.at(0) = heap.at(heapSize - 1);
    heap.pop_back();
    --heapSize;
    bubbleDown(0);
    return item;
}

vector<int> MinHeap::sort()
{
    vector<int> sortedList;
    buildMinHeap();
    while (!empty())
        sortedList.push_back(extractMin());
    for (int elem : sortedList)
        insert(elem);
    return sortedList;
}

void MinHeap::bubbleUp(int index)
{
    if (index < 0 || index > heapSize)
        throw "Invalid index.";
    if (index == 0)
        return;
    int parent = (index - 1) / 2;
    while (index > 0 && heap.at(index) < heap.at(parent))
    {
        swap(index, parent);
        index = parent;
        parent = (index - 1) / 2;
    }
}

void MinHeap::bubbleDown(int index)
{
    if (index < 0 || index >= heapSize)
        throw "Invalid index.";
    while (true)
    {
        int left = (index * 2) + 1;
        int right = (index * 2) + 2;
        int smallest = index;
        if (left < heapSize && heap[left] < heap[smallest])
            smallest = left;
        if (right < heapSize && heap[right] < heap[smallest])
            smallest = right;
        if (smallest == index)
            break;
        swap(index, smallest);
        index = smallest;
    }
}

void MinHeap::swap(int i, int j)
{
    int temp = heap.at(i);
    heap.at(i) = heap.at(j);
    heap.at(j) = temp;
}

void MinHeap::display()
{
    cout << '[';
    for (int i = 0; i < size() - 1; i++)
        cout << heap.at(i) << ", ";
    if (!empty())
        cout << heap.at(size() - 1);
    cout << "]\n";
}

bool MinHeap::empty() const
{
    return size() == 0;
}

int MinHeap::size() const
{
    return heapSize;
}

int longestJobFirst(int M, int N, vector<int> jobs)
{
    // Initialize max-heap with jobs by negating job times
    MinHeap maxHeap;
    for (int job : jobs)
        maxHeap.insert(-job); // Negate to simulate max-heap behavior

    // Initialize 'M' machines / CPUs
    int *cpu = new int[M]{0};

    // Initially allocate longest jobs to all CPUs
    for (int i = 0; i < M && !maxHeap.empty(); i++)
        cpu[i] = -maxHeap.extractMin(); // Negate back to get original value

    // Initial time instant
    int t = 0;

    // While we still have jobs to schedule
    while (true)
    {
        // Find the minimum job time among CPUs
        int minJobTime = 9999;

        for (int i = 0; i < M; i++)
            minJobTime = min(minJobTime, cpu[i]);

        // Deduct minJobTime from all jobs and allocate next longest job to idle CPUs
        for (int i = 0; i < M; i++)
        {
            cpu[i] -= minJobTime;

            // CPU is now idle
            if (cpu[i] == 0)
            {
                // Check if we still have jobs to allocate
                if (!maxHeap.empty())
                {
                    cpu[i] = -maxHeap.extractMin(); // Negate back to get original value
                }
            }
        }

        // Clock ticks
        t += minJobTime;

        // If all jobs are allocated, break
        if (maxHeap.empty())
            break;
    }

    // Find the maximum of all time remaining
    int maxRemTime = 0;

    for (int i = 0; i < M; i++)
        maxRemTime = max(maxRemTime, cpu[i]);

    // Clean up dynamically allocated memory
    delete[] cpu;

    // Return the total time spent
    return t + maxRemTime;
}

int shortestJobFirst(int M, int N, vector<int> jobs)
{
    // Initialize min-heap with jobs / tasks time
    MinHeap minHeap(jobs);

    // initialize 'M' machines / CPUs
    int *cpu = new int[M]{0};

    // initially allocate least timed jobs to all CPUs
    for (int i = 0; i < M; i++)
        cpu[i] = minHeap.extractMin();

    // initial time instant
    int t = 0;

    // while we still have jobs to schedule
    while (true)
    {
        // the next job will be allocated to the CPU
        // with the least job time.

        // find the minimum job time
        int minJobTime = 9999;

        for (int i = 0; i < M; i++)
            minJobTime = min(minJobTime, cpu[i]);

        // deduct minJobTime from all jobs.
        // and allocate next minimum job to idle CPUs.
        for (int i = 0; i < M; i++)
        {
            cpu[i] -= minJobTime;

            // CPU is now idle
            if (cpu[i] == 0)
            {
                // first check if we still have jobs to allocate
                if (!minHeap.empty())
                {
                    cpu[i] = minHeap.extractMin();
                }
            }
        }

        // clock ticks
        t += minJobTime;

        // if all jobs are allocated, break
        if (minHeap.empty())
            break;
    }

    // find the maximum of all time remaining.
    int maxRemTime = 0;

    for (int i = 0; i < M; i++)
        maxRemTime = max(maxRemTime, cpu[i]);

    // return the total time spent.
    return t + maxRemTime;
}

// Utility method to return the minimum of two given integers.
int min(int a, int b)
{
    return a < b ? a : b;
}

// Utility method to return the maximum of two given integers.
int max(int a, int b)
{
    return a > b ? a : b;
}

int main()
{
    int M; // number of CPUs
    int N; // number of jobs / tasks

    cout << "M = ";
    cin >> M;

    cout << "N = ";
    cin >> N;

    cout << "Enter CPU times of " << N << " jobs:\n";
    vector<int> arr;
    for (int i = 0; i < N; i++)
    {
        int t;
        cin >> t;
        arr.push_back(t);
    }

    int LJF_time = longestJobFirst(M, N, arr);

    int SJF_time = shortestJobFirst(M, N, arr);

    cout << "Time taken by Longest Job First = " << LJF_time << endl;

    cout << "Time taken by Shortest Job First = " << SJF_time << endl;

    return 0;
}