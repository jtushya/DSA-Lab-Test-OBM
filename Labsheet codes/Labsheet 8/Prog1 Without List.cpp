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