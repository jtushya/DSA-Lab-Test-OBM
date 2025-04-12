#include <iostream>
using namespace std;

class DynamicArray {
private:
    int* arr;
    int capacity;
    int size;

    void resize() {
        capacity *= 2;
        int* newArr = new int[capacity];
        for (int i = 0; i < size; i++) {
            newArr[i] = arr[i];
        }
        delete[] arr;
        arr = newArr;
    }

public:
    DynamicArray() {
        capacity = 10;
        size = 0;
        arr = new int[capacity];
    }

    ~DynamicArray() {
        delete[] arr;
    }

    void push_back(int value) {
        if (size == capacity) {
            resize();
        }
        arr[size++] = value;
    }

    void pop_back() {
        if (size > 0) {
            size--;
        } else {
            cout << "Array is empty!" << endl;
        }
    }

    int get(int index) const {
        if (index >= 0 && index < size) {
            return arr[index];
        }
        cout << "Index out of bounds!" << endl;
        return -1;
    }

    void set(int index, int value) {
        if (index >= 0 && index < size) {
            arr[index] = value;
        } else {
            cout << "Index out of bounds!" << endl;
        }
    }

    int getSize() const {
        return size;
    }

    int getCapacity() const {
        return capacity;
    }

    bool isEmpty() const {
        return size == 0;
    }
};

int main() {
    DynamicArray da;

    da.push_back(1);
    da.push_back(2);
    da.push_back(3);

    cout << "Array elements: ";
    for (int i = 0; i < da.getSize(); i++) {
        cout << da.get(i) << " ";
    }
    cout << endl;

    da.pop_back();
    cout << "After pop_back, size: " << da.getSize() << endl;

    return 0;
}