#include <iostream>
#include <queue>
#include <list>
#include <vector>

using namespace std;

/**
 * Comparator class for Min Priority Queue
 * This comparator makes a min-heap by defining operator()
 * such that it returns true if `a` should come *after* `b` in the heap.
 */
class C
{
public:
    // This should be public for the compiler to access this function during sorting
    int operator()(const int a, const int b)
    {
        // Min-Priority Queue: we want smaller elements to come first
        return a > b; // if a > b, then a has lower priority than b
    }
};

/**
 * Comparator class for Max Priority Queue
 */
class D
{
public:
    // Again, must be public or the priority queue cannot access this method
    int operator()(const int a, const int b)
    {
        // Max-Priority Queue: we want larger elements to come first
        return a < b; // if a < b, then a has lower priority than b
    }
};

// Sorts list in ascending order using Min-Priority Queue
list<int> sortAscending(list<int> S)
{
    // Declare a min-priority queue using comparator C
    priority_queue<int, vector<int>, C> P;

    // Transfer elements from list to priority queue
    while (!S.empty())
    {
        int e = S.front();
        S.pop_front();
        P.push(e); // insert into min-priority queue
    }

    // Clear list and refill with sorted elements from the queue
    while (!P.empty())
    {
        int e = P.top(); // smallest element
        S.push_back(e);
        P.pop();
    }

    return S;
}

// Sorts list in descending order using Max-Priority Queue
list<int> sortDescending(list<int> S)
{
    // Declare a max-priority queue using comparator D
    priority_queue<int, vector<int>, D> P;

    // Move all elements into the priority queue
    while (!S.empty())
    {
        int e = S.front();
        S.pop_front();
        P.push(e); // insert into max-priority queue
    }

    // Refill the list in descending order
    while (!P.empty())
    {
        int e = P.top(); // largest element
        S.push_back(e);
        P.pop();
    }

    return S;
}

// Utility function to print list of integers
void display(list<int> S)
{
    for (int e : S)
        cout << e << ' ';
    cout << '\n';
}

/**
 * Class to store a 2D point
 */
class Point
{
public:
    int x;
    int y;

    // Constructor
    Point(int X, int Y)
    {
        x = X;
        y = Y;
    }
};

/**
 * Custom comparator class to compare two Point objects
 * based on their y-coordinates in ascending order
 */
class CompareY
{
public:
    // Must be public for the priority queue to use
    bool operator()(const Point &a, const Point &b)
    {
        // For a min-priority queue of Points based on y-coordinate
        return a.y > b.y;
    }
};

// Sorts a list of Points by increasing order of Y coordinate
list<Point> sortByYCoordinate(list<Point> points)
{
    // Priority queue of Point objects with custom comparator
    priority_queue<Point, vector<Point>, CompareY> pq;

    // Transfer elements into priority queue
    while (!points.empty())
    {
        pq.push(points.front());
        points.pop_front();
    }

    // Refill the list from the priority queue (sorted by y)
    while (!pq.empty())
    {
        points.push_back(pq.top());
        pq.pop();
    }

    return points;
}

// Display list of Points
void display(list<Point> points)
{
    cout << "[ ";
    for (Point point : points)
        cout << '(' << point.x << ", " << point.y << ") ";
    cout << "]\n";
}

int main()
{
    // Example input lists
    list<int> S = {10, 5, 7, 14, 2, 6};
    list<int> S2 = {10, 5, 7, 14, 2, 6};

    cout << "Input List:-\n";
    display(S);

    // Sort both lists using min and max priority queues
    S = sortAscending(S);
    S2 = sortDescending(S2);

    cout << "List sorted in Ascending Order:-\n";
    display(S);
    cout << "List sorted in Descending Order:-\n";
    display(S2);

    cout << endl;

    // Input list of Points
    list<Point> points;

    points.push_back(Point(2, 7));
    points.push_back(Point(7, 4));
    points.push_back(Point(11, 2));
    points.push_back(Point(15, 9));

    cout << "Input Points:-\n";
    display(points);

    // Sort the points by their y-coordinates
    points = sortByYCoordinate(points);

    cout << "Points sorted in increasing order of Y coordinates:-\n";
    display(points);

    return 0;
}
