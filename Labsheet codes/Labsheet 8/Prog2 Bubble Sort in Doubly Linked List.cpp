/*
Problem:
This program implements the Bubble Sort algorithm on a doubly linked list. Bubble Sort is a simple sorting algorithm that repeatedly compares adjacent elements and swaps them if they are in the wrong order. The program sorts the elements of the list in ascending order.

Intuition and Logic:
1. **Doubly Linked List**:
   - A doubly linked list allows traversal in both directions, making it suitable for implementing sorting algorithms.
   - The program uses a doubly linked list to store the elements and provides methods for appending, displaying, and sorting the list.

2. **Bubble Sort**:
   - Bubble Sort works by repeatedly iterating through the list and swapping adjacent elements if they are in the wrong order.
   - The algorithm continues until no swaps are needed, indicating that the list is sorted.

3. **Implementation**:
   - The program uses a `bubbleSort` function to iterate through the list and perform swaps as needed.
   - It tracks the last sorted node to optimize the sorting process and reduce unnecessary comparisons.

4. **Efficiency**:
   - Bubble Sort has a time complexity of O(n^2) in the worst case, making it suitable for small datasets.
   - The use of a doubly linked list provides flexibility and dynamic memory management.

5. **Example**:
   - Input: List = [30, 20, 10].
   - Output: Sorted List = [10, 20, 30].

6. **Applications**:
   - Bubble Sort is often used as an educational tool to introduce sorting algorithms and their concepts.

This program demonstrates the use of doubly linked lists for implementing sorting algorithms and highlights the trade-offs between simplicity and efficiency.
*/

/* Bubble Sort in a Doubly Linked List */

#include <iostream>

using namespace std;

// basic structure of a doubly linked list node
class doubly_linked_list_node
{
private:
    int data;
    doubly_linked_list_node *nextPtr;
    doubly_linked_list_node *prevPtr;

public:
    doubly_linked_list_node(int item)
    {
        // call to designated constructor
        doubly_linked_list_node(item, NULL, NULL);
    }
    // designated constructor
    doubly_linked_list_node(int item, doubly_linked_list_node *prev, doubly_linked_list_node *next)
    {
        data = item;
        prevPtr = prev;
        nextPtr = next;
    }
    int getData();
    doubly_linked_list_node *getNext();
    doubly_linked_list_node *getPrev();
    void setNext(doubly_linked_list_node *newNext);
    void setPrev(doubly_linked_list_node *newPrev);
};

typedef doubly_linked_list_node node;

int node::getData()
{
    return data;
}

node *node::getNext()
{
    return nextPtr;
}

node *node::getPrev()
{
    return prevPtr;
}

void node::setNext(node *newNext)
{
    nextPtr = newNext;
}

void node::setPrev(node *newPrev)
{
    prevPtr = newPrev;
}

// basic functionalities in a doubly linked list data structure.
class doubly_linked_list
{
private:
    node *head, *tail;
    void bubbleSort();
    void swap(node *, node *);

public:
    doubly_linked_list()
    {
        head = tail = NULL;
    }
    void append(int item);
    bool isEmpty();
    void sort();
    void display();
};

typedef doubly_linked_list list;

// appends the given item at the end of the list
void list::append(int item)
{
    if (isEmpty())
    {
        head = tail = new node(item, NULL, NULL);
    }
    else
    {
        tail->setNext(new node(item, tail, NULL));
        tail = tail->getNext();
    }
}

// utility method to check if the list is empty
bool list::isEmpty()
{
    return head == NULL;
}

// sorts the given list
void list::sort()
{
    if (isEmpty())
    {
        return;
    }
    bubbleSort();
}

// Implementing bubble sort algorithm in a Doubly Linked List
// Time Complexity:
// Best Case = Omega(n)
// Worst Case = Big-Oh(n^2)
void list::bubbleSort()
{
    if (isEmpty())
        return;

    bool swapped = true;
    node *lastSorted = NULL; // Tracks the last sorted node

    while (swapped) // Continue until no swaps are made
    {
        swapped = false;
        node *current = head;

        while (current->getNext() != lastSorted)
        {
            if (current->getData() > current->getNext()->getData())
            {
                // Swap the two adjacent nodes
                swap(current, current->getNext());
                swapped = true;
            }
            else
            {
                current = current->getNext(); // Move to the next node
            }
        }

        // Update the last sorted node
        lastSorted = current;
    }
}

// utility method to swap the two adjacent nodes of the list
void list::swap(node *a, node *b)
{
    if (a->getNext() != b)
    {
        // Ensure a and b are adjacent; if not, return
        return;
    }

    // Fix the head pointer
    if (head == a)
    {
        head = b;
    }

    // Fix the tail pointer
    if (tail == b)
    {
        tail = a;
    }

    // Update pointers for swapping
    a->setNext(b->getNext());
    b->setPrev(a->getPrev());

    if (a->getNext() != NULL)
    {
        a->getNext()->setPrev(a);
    }

    if (b->getPrev() != NULL)
    {
        b->getPrev()->setNext(b);
    }

    b->setNext(a);
    a->setPrev(b);
}

// utility method to display the list contents
void list::display()
{
    if (isEmpty())
    {
        cout << "Empty List!\n";
        return;
    }
    node *ptr;
    cout << "NULL";
    for (ptr = head; ptr != tail; ptr = ptr->getNext())
    {
        cout << " <- " << ptr->getData() << " -> ";
    }
    cout << " <- " << tail->getData() << " -> "
         << "NULL" << endl;
}

int main()
{
    list li;
    li.append(20);
    li.append(30);
    li.append(15);
    cout << "Before Sorting:\n";
    li.display();
    li.sort();
    cout << "After Sorting:\n";
    li.display();
    li.sort();
    li.append(10);
    li.append(25);
    li.append(35);
    cout << "Before Sorting:\n";
    li.display();
    li.sort();
    cout << "After Sorting:\n";
    li.display();
    return 0;
}