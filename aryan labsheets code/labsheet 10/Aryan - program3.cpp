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

//the minHeap class required to implement this job application code

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

// Extracts and returns the minimum item from the heap.
// Time Complexity = O(log n)
int MinHeap::extractMin()
{
    if (empty())
        throw "Heap is Empty!";

    // Grab the minimum item
    int item = heap.at(0);

    // add missing code...

    //now replace the root with the last element
    heap.at(0)=heap.at(heapSize-1);

    //Reduce the heap size
    heapSize--;

    //Remove the last element from the vector (to clean memory)
    heap.pop_back();
    heapCapacity--;

    //restore the heap property again
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

// Bubble-Down operation
// Move a node downwards until the heap invariant is satisfied.
// Time Complexity = O(log n)
void MinHeap::bubbleDown(int index)
{
    if (index < 0 || index > heapSize)
        throw "Invalid index.";

    // complete the code...
  while(true){
    int leftChild=2*index + 1;
    int rightChild=2*index + 2;
    int smallest= index;

    if(leftChild < heapSize && heap[leftChild] < heap[smallest]){
        smallest=leftChild;
    }

    if(rightChild < heapSize && heap[rightChild] < heap[smallest]){
        smallest=rightChild;
    }

    //if the smallest is not the current index, swap and continue
    if(smallest!=index){
        swap(index,smallest);
        index=smallest;
    }

    else{
        break; //i.e. the heap properties are satisfied
    }
    
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

//this is the maxHeap class to implement the code..
class MaxHeap {
    private:
        vector<int> heap;
        int heapSize;
    
        void bubbleUp(int index) {
            while (index > 0) {
                int parent = (index - 1) / 2;
                if (heap[index] > heap[parent]) {
                    swap(heap[index], heap[parent]);
                    index = parent;
                } else break;
            }
        }
    
        void bubbleDown(int index) {
            int left, right, largest;
    
            while (true) {
                left = 2 * index + 1;
                right = 2 * index + 2;
                largest = index;
    
                if (left < heapSize && heap[left] > heap[largest]) {
                    largest = left;
                }
    
                if (right < heapSize && heap[right] > heap[largest]) {
                    largest = right;
                }
    
                if (largest != index) {
                    swap(heap[index], heap[largest]);
                    index = largest;
                } else break;
            }
        }
    
    public:
        MaxHeap() {
            heapSize = 0;
        }
    
        MaxHeap(const vector<int>& elems) {
            heap = elems;
            heapSize = elems.size();
    
            // Build heap (heapify)
            for (int i = heapSize / 2 - 1; i >= 0; i--) {
                bubbleDown(i);
            }
        }
    
        void insert(int val) {
            heap.push_back(val);
            heapSize++;
            bubbleUp(heapSize - 1);
        }
    
        int extractMax() {
            if (heapSize == 0) throw runtime_error("Heap is empty");
    
            int maxElem = heap[0];
            heap[0] = heap[heapSize - 1];
            heap.pop_back();
            heapSize--;
            bubbleDown(0);
    
            return maxElem;
        }
    
        bool empty() const {
            return heapSize == 0;
        }
    
        int size() const {
            return heapSize;
        }
    };
    
//the code for the job question starts from here.....

//this is the code for the longest job time using a maxHeap...
int longestJobFirst(int M, int N, vector<int> jobs)
{
    // Code here ...
    // Initialize min-heap with jobs / tasks time
    MaxHeap maxHeap(jobs);

    // initialize 'M' machines / CPUs
    int *cpu = new int[M]{0};

    // initially allocate most timed jobs to all CPUs
    for (int i = 0; i < M; i++)
        cpu[i] = maxHeap.extractMax();

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
           cpu[i]-=minJobTime;

            // CPU is now idle
            if (cpu[i] == 0)
            {
                // first check if we still have jobs to allocate
                if (!maxHeap.empty())
                {
                    cpu[i] = maxHeap.extractMax();
                }
            }
        }

        // clock ticks
        t += minJobTime;

        // if all jobs are allocated, break
        if (maxHeap.empty())
            break;
    }

    // find the maximum of all time remaining.
    int maxRemTime = 0;

    for (int i = 0; i < M; i++)
        maxRemTime = max(maxRemTime, cpu[i]);

    // return the total time spent.
    return t + maxRemTime;

}

//this is the code for the shortest job time using a minHeap...
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