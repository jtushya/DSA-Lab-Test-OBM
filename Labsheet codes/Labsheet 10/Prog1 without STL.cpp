#include <iostream>
using namespace std;

// Function to display an array of integers
void displayIntArray(int arr[], int n)
{
    for (int i = 0; i < n; i++)
        cout << arr[i] << ' ';
    cout << endl;
}

// Selection Sort to sort in ascending order
void sortAscending(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int minIdx = i;
        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[minIdx])
                minIdx = j;
        }
        // Swap arr[i] and arr[minIdx]
        int temp = arr[i];
        arr[i] = arr[minIdx];
        arr[minIdx] = temp;
    }
}

// Selection Sort to sort in descending order
void sortDescending(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int maxIdx = i;
        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] > arr[maxIdx])
                maxIdx = j;
        }
        // Swap arr[i] and arr[maxIdx]
        int temp = arr[i];
        arr[i] = arr[maxIdx];
        arr[maxIdx] = temp;
    }
}

// Point class to store coordinates
class Point
{
public:
    int x, y;

    // Constructor
    Point() {} // Default constructor
    Point(int X, int Y)
    {
        x = X;
        y = Y;
    }
};

// Function to display an array of Point objects
void displayPoints(Point points[], int n)
{
    cout << "[ ";
    for (int i = 0; i < n; i++)
        cout << "(" << points[i].x << ", " << points[i].y << ") ";
    cout << "]" << endl;
}

// Sort array of Points by increasing Y coordinate (Selection Sort)
void sortByYCoordinate(Point points[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int minIdx = i;
        for (int j = i + 1; j < n; j++)
        {
            if (points[j].y < points[minIdx].y)
                minIdx = j;
        }
        // Swap points[i] and points[minIdx]
        Point temp = points[i];
        points[i] = points[minIdx];
        points[minIdx] = temp;
    }
}

int main()
{
    // Integer array input
    int S[] = {10, 5, 7, 14, 2, 6};
    int S2[] = {10, 5, 7, 14, 2, 6};
    int n = sizeof(S) / sizeof(S[0]);

    cout << "Input Array:\n";
    displayIntArray(S, n);

    sortAscending(S, n);
    sortDescending(S2, n);

    cout << "Array sorted in Ascending Order:\n";
    displayIntArray(S, n);

    cout << "Array sorted in Descending Order:\n";
    displayIntArray(S2, n);

    cout << endl;

    // Point array input
    Point points[4] = {
        Point(2, 7),
        Point(7, 4),
        Point(11, 2),
        Point(15, 9)
    };
    int m = 4;

    cout << "Input Points:\n";
    displayPoints(points, m);

    sortByYCoordinate(points, m);

    cout << "Points sorted in increasing order of Y coordinates:\n";
    displayPoints(points, m);

    return 0;
}
