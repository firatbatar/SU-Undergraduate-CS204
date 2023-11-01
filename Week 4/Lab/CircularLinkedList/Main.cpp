#include <iostream>
#include <string>

#include "linkedList.h"

int main() {
    linkedlist list;
    string word = "";
    cout << "Please enter a word!" << endl;
    // Ctrl-Z in order to exit from the loop
    while (cin >> word) {
        list.addToBeginning(word);
        cout << "Please enter a word!" << endl;
    }

    list.printList();
    list.printListInverse();

    // system("pause");
    return 0;
}
