#include <iostream>
using namespace std;

class CircleList;

typedef string Elem; // element type
class CNode
{ // circularly linked list node
private:
    Elem elem;               // linked list element value
    CNode *next;             // next item in the list
    friend class CircleList; // provide CircleList access
};

class CircleList
{ // a circularly linked list
public:
    CircleList();              // constructor
    ~CircleList();             // destructor
    bool empty() const;        // is list empty?
    const Elem &front() const; // element at cursor
    const Elem &back() const;  // element following cursor
    void advance();            // advance cursor
    void add(const Elem &e);   // add after cursor
    void remove();             // remove node after cursor
    void traverse();           // traverse the list
private:
    CNode *cursor; // the cursor
};

CircleList::CircleList() // constructor
    : cursor(NULL)
{
}
CircleList::~CircleList() // destructor
{
    while (!empty())
        remove();
}

bool CircleList::empty() const // is list empty?
{
    return cursor == NULL;
}
const Elem &CircleList::back() const // element at cursor
{
    return cursor->elem;
}
const Elem &CircleList::front() const // element following cursor
{
    return cursor->next->elem;
}
void CircleList::advance() // advance cursor
{
    cursor = cursor->next;
}

void CircleList::add(const Elem &e)
{                         // add after cursor
    CNode *v = new CNode; // create a new node
    v->elem = e;
    if (cursor == NULL)
    {                // list is empty?
        v->next = v; // v points to itself
        cursor = v;  // cursor points to v
    }
    else
    {                           // list is nonempty?
        v->next = cursor->next; // link in v after cursor
        cursor->next = v;
    }
}

void CircleList::remove()
{                              // remove node after cursor
    CNode *old = cursor->next; // the node being removed
    if (old == cursor)         // removing the only node?
        cursor = NULL;         // list is now empty
    else
        cursor->next = old->next; // link out the old node
    delete old;                   // delete the old node
}

void CircleList::traverse()
{
    CNode *temp = cursor->next;
    while (temp != cursor)
    {
        cout << temp->elem << " ";
        temp = temp->next;
    }
    cout << temp->elem;
    cout << endl;
}

typedef string Elem; // queue element type

class LinkedQueue
{ // queue as doubly linked list
public:
    LinkedQueue();               // constructor
    int size() const;            // number of items in the queue
    bool empty() const;          // is the queue empty?
    const Elem &front();         // the front element
    void enqueue(const Elem &e); // enqueue element at rear
    void dequeue();              // dequeue element at front
    void display();              // display the items in the queue
private:                         // member data
    CircleList C;                // circular list of elements
    int n;                       // number of elements
};

LinkedQueue::LinkedQueue() // constructor
    : C(), n(0)
{
}

int LinkedQueue::size() const // number of items in the queue
{
    return n;
}

bool LinkedQueue::empty() const // is the queue empty?
{
    return n == 0;
}

const Elem &LinkedQueue::front()
{                     // get the front element
    return C.front(); // list front is queue front
}

void LinkedQueue::enqueue(const Elem &e)
{                // enqueue element at rear
    C.add(e);    // insert after cursor
    C.advance(); // ...and advance
    n++;
}

void LinkedQueue::dequeue()
{               // dequeue element at front
    C.remove(); // remove from list front
    n--;
}

void LinkedQueue::display()
{
    C.traverse();
}

void printOptions()
{
    cout << "1 : Enqueue\n";
    cout << "2 : Dequeue\n";
    cout << "3 : Get front element\n";
    cout << "4 : Get size\n";
    cout << "5 : Check if queue is empty\n";
    cout << "6 : Display Queue items\n";
    cout << "7 : Exit\n";
}

int main()
{
    LinkedQueue lq = LinkedQueue();
    char opt;

    printOptions();

    while (1)
    {
        cout << "+--------------------------+\n";
        cout << "Enter your choice: ";
        cin >> opt;
        switch (opt)
        {
        case '1':
        {
            string aux;
            cout << "Enter an item: ";
            cin >> aux;
            lq.enqueue(aux);
            cout << aux << " enqueued into the Queue." << endl;
            break;
        }
        case '2':
        {
            if (lq.empty())
                cout << "Queue Underflows!" << endl;
            else
            {
                string frontElem = lq.front();
                lq.dequeue();
                cout << frontElem << " dequeued from the Queue." << endl;
            }
            break;
        }
        case '3':
        {
            if (lq.empty())
                cout << "Queue is Empty!" << endl;
            else
                cout << "Elem at the FRONT = " << lq.front() << "." << endl;
            break;
        }
        case '4':
        {
            cout << "Size of the Queue = " << lq.size() << "." << endl;
            break;
        }
        case '5':
        {
            cout << "Queue is" << (lq.empty() ? "" : " NOT") << " Empty.\n";
            break;
        }
        case '6':
        {
            if (lq.empty())
                cout << "Queue is Empty!" << endl;
            else
            {
                cout << "FRONT -> ";
                lq.display();
            }
            break;
        }
        case '7':
        {
            cout << "Exiting..." << endl;
            exit(1);
        }
        default:
            cout << "Invalid choice... Try again.\n";
        }
    }
    return 0;
}