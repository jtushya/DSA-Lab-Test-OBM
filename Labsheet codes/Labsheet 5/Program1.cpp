#include <iostream>
#include "timer.h"

using namespace std;

template <typename DT>
class SinglyLinkedNode
{
public:
    // data items in the node
    DT dataItem;
    SinglyLinkedNode<DT> *next;

    // constructor
    SinglyLinkedNode(DT nodeValue, SinglyLinkedNode<DT> *nextPointer);
};

template <typename DT>
SinglyLinkedNode<DT>::SinglyLinkedNode(DT nodeValue, SinglyLinkedNode *nextPointer)
{
    dataItem = nodeValue;
    next = nextPointer;
}

template <typename DT>
class SinglyLinkedList
{
private:
    // Data Members
    SinglyLinkedNode<DT> *head, *tmp;
    int numberOfItems;
    int counter;

    // These are utility functions that the main functions will call
    void insertEndRecursive(const DT &newDataItem, SinglyLinkedNode<DT> *current);
    void deleteEndRecursive(SinglyLinkedNode<DT> *current);
    void printForwardRecursive(SinglyLinkedNode<DT> *current);
    void printBackwardRecursive(SinglyLinkedNode<DT> *current);
    void reverseRecursive(SinglyLinkedNode<DT> *prev, SinglyLinkedNode<DT> *curr);
    void nthNodeFromEndRecursive(SinglyLinkedNode<DT> *header, int n);

public:
    // Constructor
    SinglyLinkedList();

    void insertEnd(const DT &newDataItem);
    void deleteEnd();
    void printForward();
    void printBackward();
    void reverse();
    SinglyLinkedNode<DT> *nthNodeFromEnd(int n);
};

template <typename DT>
SinglyLinkedList<DT>::SinglyLinkedList()
{
    head = NULL;
    numberOfItems = 0;
}

// inserts a node at the end of the list
template <typename DT>
void SinglyLinkedList<DT>::insertEnd(const DT &newDataItem)
{
    insertEndRecursive(newDataItem, head);
    numberOfItems++;
}

template <typename DT>
void SinglyLinkedList<DT>::insertEndRecursive(const DT &newDataItem, SinglyLinkedNode<DT> *current)
{
    if (numberOfItems == 0)
    {
        head = new SinglyLinkedNode<DT>(newDataItem, NULL);
    }
    else if (current->next == NULL)
    {
        current->next = new SinglyLinkedNode<DT>(newDataItem, NULL);
    }
    else
    {
        insertEndRecursive(newDataItem, current->next);
    }
}

// deletes a node from the end of the list
template <typename DT>
void SinglyLinkedList<DT>::deleteEnd()
{
    deleteEndRecursive(head);
    numberOfItems--;
}

template <typename DT>
void SinglyLinkedList<DT>::deleteEndRecursive(SinglyLinkedNode<DT> *current)
{
    if (numberOfItems == 1)
    {
        delete head;
        head = NULL;
    }
    else if (current->next->next == NULL)
    {
        delete current->next;
        current->next = NULL;
    }
    else
    {
        deleteEndRecursive(current->next);
    }
}

// prints the list
template <typename DT>
void SinglyLinkedList<DT>::printForward()
{
    //missing code
}

template <typename DT>
void SinglyLinkedList<DT>::printForwardRecursive(SinglyLinkedNode<DT> *current)
{
    if (current == NULL)
        return;

    std::cout << current->dataItem << " ";
    printForwardRecursive(current->next);
    if (current == head)
        std::cout << std::endl;
}

// prints a list in reverse order.
template <typename DT>
void SinglyLinkedList<DT>::printBackward()
{
    //missing code
}

template <typename DT>
void SinglyLinkedList<DT>::printBackwardRecursive(SinglyLinkedNode<DT> *current)
{
    if (current == NULL)
        return;

    printBackwardRecursive(current->next);
    std::cout << current->dataItem << " ";
    if (current == head)
        std::cout << std::endl;
}

// reverse the list
template <typename DT>
void SinglyLinkedList<DT>::reverse()
{
    reverseRecursive(NULL, head);
}

template <typename DT>
void SinglyLinkedList<DT>::reverseRecursive(SinglyLinkedNode<DT> *prev, SinglyLinkedNode<DT> *curr)
{
    if (curr != NULL)
    {
        reverseRecursive(curr, curr->next);
        curr->next = prev;
    }
    else
    {
        head = prev;
    }
}

// finds and returns the n'th node from the end of the list.
template <typename DT>
SinglyLinkedNode<DT> *SinglyLinkedList<DT>::nthNodeFromEnd(int n)
{
    // code here
    counter = 0;
    tmp = NULL;
    nthNodeFromEndRecursive(head, n);
    return tmp; // return the n'th node from the end
}

// recursive solution to find out the n'th node from the end.
template <typename DT>
void SinglyLinkedList<DT>::nthNodeFromEndRecursive(SinglyLinkedNode<DT> *head, int n)
{
    if (head == NULL)
        return;

    nthNodeFromEndRecursive(head->next, n);
    counter++;
    if (counter == n)
    {
        tmp = head;
    }
}

void printChoices()
{
    cout << "+----------------------------------------+\n";
    cout << "Please enter one of the following choices:\n";
    cout << "1 : Insert at end\n";
    cout << "2 : Delete from end\n";
    cout << "3 : Print Forward\n";
    cout << "4 : Print Backward\n";
    cout << "5 : Reverse List\n";
    cout << "6 : Get N'th node from the end\n";
    cout << "7 : Exit\n";
}

int main()
{
    SinglyLinkedList<int> list;

    Timer timer; // initialize timer class object

    SinglyLinkedNode<int> *node;
    int a, b;
    char choice;

    while (1)
    {
        printChoices();
        cin >> choice;

        switch (choice)
        {
        case '1':
            cout << "Enter the item to insert: ";
            cin >> a;
            timer.start();
            list.insertEnd(a);
            timer.stop();
            cout << "Time spent: " << timer.getDurationInMilliSeconds() << " ms." << endl;
            break;
        case '2':
            timer.start();
            list.deleteEnd();
            timer.stop();
            cout << "Time spent: " << timer.getDurationInMilliSeconds() << " ms." << endl;
            break;
        case '3':
            timer.start();
            list.printForward();
            timer.stop();
            cout << "Time spent: " << timer.getDurationInMilliSeconds() << " ms." << endl;
            break;
        case '4':
            timer.start();
            list.printBackward();
            timer.stop();
            cout << "Time spent: " << timer.getDurationInMilliSeconds() << " ms." << endl;
            break;
        case '5':
            timer.start();
            list.reverse();
            timer.stop();
            cout << "Time spent: " << timer.getDurationInMilliSeconds() << " ms." << endl;
            break;
        case '6':
            cout << "Enter N: ";
            cin >> a;
            timer.start();
            node = list.nthNodeFromEnd(a);
            timer.stop();
            if (node == NULL)
                cout << "Such a node does not exist." << endl;
            else
                cout << "N'th node from the end: " << node->dataItem << endl;
            cout << "Time spent: " << timer.getDurationInMilliSeconds() << " ms." << endl;
            break;
        case '7':
            exit(1);
            break;
        default:
            cout << "Invalid choice." << endl;
        }
    }
}
