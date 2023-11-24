/* Author: Zeynep Dogmus
 * Date: April 2013
 * Templated Vector Example
 */
#include "MyVector.h"
#include <iostream>
#include <string>
using namespace std;

// Default Constructor
template <class itemType>
MyVector<itemType>::MyVector() {
    myVector = nullptr;
}

// Constructor with Dynamic Allocation
template <class itemType>
MyVector<itemType>::MyVector(int newSize, itemType value) {
    size = newSize;
    myVector = new itemType[size];
    for (int i = 0; i < size; i++) {
        myVector[i] = value;
    }
}

// Displays the elements in the vector
template <class itemType>
void MyVector<itemType>::display() {
    for (int i = 0; i < size; i++) {
        cout << myVector[i] << " ";
    }
    cout << endl << endl;
}

// Adds val to every element of the vector
template <class itemType>
void MyVector<itemType>::increaseElements(itemType value) {
    for (int i = 0; i < size; i++) {
        myVector[i] = myVector[i] + value;
    }
}

// Destructor
template <class itemType>
MyVector<itemType>::~MyVector() {
    delete[] myVector;
}
