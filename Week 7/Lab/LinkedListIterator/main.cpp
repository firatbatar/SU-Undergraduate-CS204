/*
Modified by Gizem Gezici
Modified Date: 10.04.2012
Linked List Iterator
*/

#include <iostream>
#include "MyList.h"
using namespace std;

// Print the list
void PrintForward(MyList &lst) {
    MyListItr itr(lst);
    cout << "Printing the list..." << endl;
    itr.goToBeginning();
    while (itr.hasMore()) {
        cout << itr.getData() << " ";
        // Since we're printing forward
        itr.next();
    }
    cout << endl;
    cout << endl;
}

// Print the list in reverse order
void PrintBackward(MyList &lst) {
    MyListItr itr(lst);
    cout << "Printing the list in reverse order ..." << endl;
    itr.goToEnd();
    while (itr.hasMore()) {
        cout << itr.getData() << " ";
        // Since we're printing backward
        itr.previous();
    }
    cout << endl;
    cout << endl;
}

int main() {
    int numElements = 0;
    string *dataList;

    cout << "Enter number of elements :";
    cin >> numElements;

    dataList = new string[numElements];

    // Get the input from the keyboard (string elements) in order to create the list
    for (int i = 0; i < numElements; i++) {
        cout << "Enter element :";
        cin >> dataList[i];
    }

    cout << endl;

    // Create the list with the entered elements from the keyboard
    MyList myList(dataList, numElements);
    PrintForward(myList);
    PrintBackward(myList);

    string s = "LastElement";
    string s1 = "FirstElement";

    myList.addToBeginning(s1);
    myList.addToEnd(s);

    PrintForward(myList);
    PrintBackward(myList);

    cin.ignore();
    cin.get();
    return 1;
}