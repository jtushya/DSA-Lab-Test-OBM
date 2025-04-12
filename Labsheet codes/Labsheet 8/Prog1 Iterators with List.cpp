/*
Problem:
This program demonstrates the use of iterators with a list to perform various operations such as displaying elements, checking even/odd values, and updating elements. Iterators provide a way to traverse and manipulate elements in a container, making them a powerful tool in STL.

Intuition and Logic:
1. **Iterators**:
   - Iterators act as pointers to elements in a container, allowing traversal and modification of elements.
   - The program uses a list to store integers and iterators to access and modify the elements.

2. **Operations**:
   - **Display**: The program iterates through the list to display all elements.
   - **Check Even/Odd**: It checks whether each element is even or odd by dereferencing the iterator.
   - **Update**: The program updates each element by adding a fixed value and displays the updated list.

3. **Efficiency**:
   - Iterators provide a consistent and efficient way to traverse containers, regardless of their underlying implementation.
   - This makes them suitable for a wide range of applications, from simple traversals to complex algorithms.

4. **Example**:
   - Input: List = [10, 15, 20]; Update = +10.
   - Output: Updated List = [20, 25, 30].

5. **Applications**:
   - Iterators are widely used in STL algorithms, such as sorting, searching, and transforming containers.

This program highlights the power and flexibility of iterators in STL and demonstrates their use in list traversal and manipulation.
*/

/* Based on Iterators Concept */
#include <iostream>
#include <list>

using namespace std;

int main()
{
    // list specifying the marks
    list<int> marks;

    int N;
    cout << "Enter the number of subjects: ";
    cin >> N;

    cout << "Enter the marks in " << N << " subjects: ";
    for (int i = 0; i < N; i++)
    {
        int mark;
        cin >> mark;
        marks.push_back(mark); // Missing code A: Add mark to the list
    }

    // create an instance of list iterator
    list<int>::iterator itr;

    // Using Iterator, Display marks
    cout << "Input Marks: ";
    for (itr = marks.begin(); itr != marks.end(); itr++)
        cout << *itr << " "; // Missing code B: Dereference iterator to get value
    cout << endl;

    // Using Iterator, Check whether the mark is even or odd using iterator
    for (itr = marks.begin(); itr != marks.end(); itr++)
    {
        if (*itr % 2 == 0)
            cout << *itr << " = Even" << endl;
        else
            cout << *itr << " = Odd" << endl;
    }

    // Using Iterator, update the marks by 10
    for (itr = marks.begin(); itr != marks.end(); itr++) // Missing code D: Initialize iterator
        *itr = *itr + 10;

    cout << "Updated Marks: ";
    // Using Iterator, Display updated marks
    for (itr = marks.begin(); itr != marks.end(); itr++)
        cout << *itr << " "; // Missing code E: Dereference iterator to get value
    cout << endl;

    return 0;
}