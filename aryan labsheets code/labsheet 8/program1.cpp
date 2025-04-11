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
        //complete the missing code A
        marks.push_back(mark);
    }

    // create an instance of list iterator
    list<int>::iterator itr;

    // Using Iterator, Display marks
    cout << "Input Marks: ";
    for (itr = marks.begin(); itr != marks.end(); itr++){
        cout << *itr << " ";
    cout << endl;
}
    // Using Iterator, Check whether the mark is even or odd using iterator
    // Pl complete the code here...
    for(itr=marks.begin(); itr!=marks.end(); itr++){
        if(*itr%2==0){
            cout<<*itr<<" = "<<" Even "<<endl;
        }
        else{
            cout<<*itr<<" = "<<" Odd "<<endl;
        }
    }

    // Using Iterator,  update the marks by 10
    for (itr = marks.begin(); itr!=marks.end(); itr++){ //missing code D ; itr++)
        *itr = *itr + 10;
    }

    cout << "Updated Marks: ";
    // Using Iterator, Display updated marks
    for (itr = marks.begin(); itr != marks.end(); itr++){
        cout <<*itr << " ";
    cout << endl;
    }

    return 0;
}