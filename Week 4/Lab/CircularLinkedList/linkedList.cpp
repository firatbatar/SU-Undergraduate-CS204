#include "linkedList.h"

#include <iostream>

using namespace std;

// creating an empty linkedlist
linkedlist::linkedlist() {
    // TODO: Implement this
    head = nullptr;
}

// printing the elements of the list
void linkedlist::printList() {
    // TODO: Implement the function
    node *temp = head;
    do {
        cout << temp->data << " ";
        temp = temp->next;
    } while (temp != head);
    cout << endl;
}

// adds an element to the beginning of the list
void linkedlist::addToBeginning(string n) {
    if (head == nullptr) {
        // TODO: Implement this case
        head = new node(n, nullptr);
        head->next = head;
    }
    else {
        // TODO: Implement this case
        node *tail = head;
        do {
            tail = tail->next;
        } while (tail != head);

        node *new_node = new node(n, head);
        head = new_node;
        tail->next = head;
    }
}

// printing the list elements in the reverse order
void linkedlist::printListInverse() {
    printListInverse(head->next);
    cout << head->data << endl;
}

void linkedlist::printListInverse(node *n) {
    // TODO: Implement this RECURSIVE helper function (used by the function above)
    if (n->next != head) {
        printListInverse(n->next);
    }

    cout << n->data << " ";
}