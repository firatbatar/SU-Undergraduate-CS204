// Demonstrates templated linked list class

#include <iostream>
#include "linkedlisttemplate.h"
// #include "linkedlisttemplate.cpp"
using namespace std;

int main() {
    string tmnt[] = {"Donatello", "Leonardo", "Raphael", "Michelangelo"};
    LinkedList<string> strlist;  // Linked list object with string element type
    LinkedList<int> intlist;     // Linked list object with integer element type

    for (int k = 0; k < 4; k++) {
        strlist.addToBeginning(tmnt[k]);
        intlist.addToBeginning(k + 1);
    }

    cout << "string list contains:\n";
    strlist.printList();

    cout << "integer list contains:\n";
    intlist.printList();
}
