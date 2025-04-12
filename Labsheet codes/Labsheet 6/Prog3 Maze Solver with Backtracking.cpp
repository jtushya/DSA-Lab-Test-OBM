/*
Logic and Intuition:
1. **Problem Description**:
   - A mouse is trapped in a maze and needs to find its way from the entry point (`m`) to the exit point (`e`).
   - The maze consists of walls (`1`), passages (`0`), an entry point (`m`), and an exit point (`e`).

2. **Approach**:
   - The program uses **backtracking** to explore all possible paths in the maze.
   - If the mouse reaches a dead end, it retraces its steps to the last position with untried paths and continues exploring.

3. **Key Features**:
   - **Borderline Protection**: A frame of `1`s is added around the maze to prevent the mouse from falling out of bounds.
   - **Visited Marking**: Each visited position is marked with a period (`.`) to avoid revisiting.
   - **Stack Usage**:
     - `mazeRows`: Temporarily stores rows of the maze as they are entered by the user.
     - `mazeStack`: Stores untried neighboring positions for backtracking.

4. **Steps**:
   - The user enters the maze row by row.
   - The program adds a frame of `1`s around the maze.
   - The program uses a stack (`mazeStack`) to explore the maze:
     - Pushes unvisited neighbors (up, down, left, right) onto the stack.
     - Pops the stack to backtrack when a dead end is reached.
   - If the mouse reaches the exit, the program prints "Success".
   - If no path to the exit exists, the program prints "Failure".

5. **Example**:
   Input Maze:
   ```
   m001
   0110
   000e
   ```
   Output:
   ```
   m111
   10110
   1000e
   Success
   ```
*/

#include <bits/stdc++.h>
using namespace std;

// Custom Stack class that extends the STL stack to add a `pop` method that returns the top element
template <class T>
class Stack : public stack<T>
{
public:
    T pop()
    {
        T tmp = stack<T>::top();
        stack<T>::pop();
        return tmp;
    }
};

// Represents a cell in the maze
class Cell
{
public:
    Cell(int i = 0, int j = 0) : x(i), y(j) {} // Constructor to initialize cell coordinates
    bool operator==(const Cell &c) const { return x == c.x && y == c.y; } // Equality operator to compare cells

private:
    int x, y; // Coordinates of the cell
    friend class Maze; // Allow Maze class to access private members
};

// Represents the maze and implements the pathfinding logic
class Maze
{
public:
    Maze();         // Constructor to initialize the maze
    void exitMaze(); // Finds the path from entry to exit

private:
    Cell currentCell, exitCell, entryCell; // Current, exit, and entry cells
    const char exitMarker, entryMarker, visited, passage, wall; // Maze markers
    Stack<Cell> mazeStack; // Stack to store untried neighbors
    char **store;          // 2D array to store the maze
    void pushUnvisited(int, int); // Push unvisited neighbors onto the stack
    friend ostream &operator<<(ostream &, const Maze &); // Overload << to print the maze
    int rows, cols; // Dimensions of the maze
};

// Constructor to initialize the maze
Maze::Maze() : exitMarker('e'), entryMarker('m'), visited('.'), passage('0'), wall('1')
{
    Stack<char *> mazeRows; // Temporary stack to store maze rows
    char str[80], *s;
    int col, row = 0;

    cout << "Enter a rectangular maze using the following characters:\n"
         << "m - entry\n"
         << "e - exit\n"
         << "1 - wall\n"
         << "0 - passage\n"
         << "Enter one line at a time; end with Ctrl-z:\n";

    // Read maze rows from the user
    while (cin >> str)
    {
        row++;
        cols = strlen(str);
        s = new char[cols + 3]; // Allocate space for the row with border columns
        mazeRows.push(s);       // Push the row onto the stack
        strcpy(s + 1, str);     // Copy the row into the array, leaving space for borders
        s[0] = s[cols + 1] = wall; // Add border columns (walls)
        s[cols + 2] = '\0';

        // Identify the entry and exit cells
        if (strchr(s, exitMarker) != 0)
        {
            exitCell.x = row;
            exitCell.y = strchr(s, exitMarker) - s;
        }
        if (strchr(s, entryMarker) != 0)
        {
            entryCell.x = row;
            entryCell.y = strchr(s, entryMarker) - s;
        }
    }

    rows = row; // Set the number of rows
    store = new char *[rows + 2]; // Allocate space for the maze with border rows
    store[0] = new char[cols + 3]; // Top border row

    // Transfer rows from the stack to the maze array
    for (; !mazeRows.empty(); row--)
    {
        store[row] = mazeRows.pop();
    }

    store[rows + 1] = new char[cols + 3]; // Bottom border row
    store[0][cols + 2] = store[rows + 1][cols + 2] = '\0';

    // Fill the border rows with walls
    for (col = 0; col <= cols + 1; col++)
    {
        store[0][col] = wall;
        store[rows + 1][col] = wall;
    }
}

// Push unvisited neighbors onto the stack
void Maze::pushUnvisited(int row, int col)
{
    if (store[row][col] == passage || store[row][col] == exitMarker)
    {
        mazeStack.push(Cell(row, col));
    }
}

// Finds the path from entry to exit
void Maze::exitMaze()
{
    int row, col;
    currentCell = entryCell; // Start from the entry cell

    while (!(currentCell == exitCell)) // Continue until the exit is reached
    {
        row = currentCell.x;
        col = currentCell.y;
        cout << *this; // Print the current state of the maze

        if (!(currentCell == entryCell))
            store[row][col] = visited; // Mark the current cell as visited

        // Push unvisited neighbors onto the stack
        pushUnvisited(row - 1, col); // Upper neighbor
        pushUnvisited(row + 1, col); // Lower neighbor
        pushUnvisited(row, col - 1); // Left neighbor
        pushUnvisited(row, col + 1); // Right neighbor

        if (mazeStack.empty()) // If no unvisited neighbors remain, the maze is unsolvable
        {
            cout << *this;
            cout << "Failure" << endl;
            return;
        }
        else
            currentCell = mazeStack.pop(); // Backtrack to the last untried position
    }

    cout << *this;
    cout << "Success\n"; // Exit found
}

// Overload << to print the maze
ostream &operator<<(ostream &out, const Maze &maze)
{
    for (int row = 0; row <= maze.rows + 1; row++)
        out << maze.store[row] << endl;
    out << endl;
    return out;
}

int main()
{
    Maze().exitMaze(); // Create a maze and find the path
    return 0;
}