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

int longestJobFirst(int M, int N, vector<int> jobs)
{
    // Code here ...
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