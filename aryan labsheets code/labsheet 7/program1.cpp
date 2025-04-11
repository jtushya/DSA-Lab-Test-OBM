#include <iostream>
#include<string>
using namespace std;

struct Node {
    char data;
    Node* next;
    Node* prev;
    Node(char val) : data(val), next(nullptr), prev(nullptr) {}
};

class Deque {
private:
    Node* front;
    Node* rear;
public:
    Deque() : front(nullptr), rear(nullptr) {}
    ~Deque() {
        while (!isEmpty()) popFront();
    }
    void pushFront(char x) {
        Node* newNode= new Node(x);
        if(isEmpty()) front=rear=newNode;
        else{
            newNode->next=front;
            front->prev=newNode;
            front=newNode;
        }
    }
    void pushBack(char x) {
        Node* newNode = new Node(x);
        if (isEmpty()) front = rear = newNode;
        else {
            rear->next = newNode;
            newNode->prev = rear;
            rear = newNode;
        }
    }
    char popFront() {
        if (isEmpty()) return '\0';
        char val = front->data;
        Node* temp = front;
        front = front->next;
        if (front) front->prev = nullptr;
        else rear = nullptr;
        delete temp;
        return val;
    }
    char popBack() {
      if(isEmpty()) return '\0';
      char val=rear->data;
      Node*temp=rear;
      rear=rear->prev;
      if(rear) rear->next=nullptr;
      else rear=nullptr;
      delete temp;
      return val;
    }

    bool isEmpty() { return front == nullptr; }
};

bool isPalindrome(string s) {
    int l=0; 
    int r=s.length()-1;
    while(l<=s){
       if(s[l]!=s[r]){
        return false;
        break;
       }
       l++;
       s--;
    }

    return true;
}

bool canFormPalindrome(Deque& dq, string s = "") {
    //base case
    if(dq.isEmpty()) return isPalindrome(s);

    //first pop from the front
    char left= dq.popFront();
    if(canFormPalindrome(dq,s+left)) return true;

    //if cannot form, then backtrack;
    dq.pushFront(left);

    //similarly pop from the back
    char right=popBack();
    if(canFormPalindrome(dq,s+right)) return true;
    
    //if cannot form, then backtrack
    dq.popBack(right);

    //if none of the case worked, then return false as we couldnt form the palindrome

    return false;
}

int main() {
    Deque dq;
    string input = "rearcca";
    for (char c : input) dq.pushBack(c);
    cout << (canFormPalindrome(dq) ? "YES" : "NO") << endl;
    return 0;
}