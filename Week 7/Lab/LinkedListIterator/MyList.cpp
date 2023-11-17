/*
Modified by Gizem Gezici
Modified Date: 10.04.2012
Linked List Iterator

*/

#include "MyList.h"

// Default Constructor
MyList::MyList() {
    head = nullptr;
    tail = nullptr;
    numItems = 0;
}

// Constructor
MyList::MyList(string *list, int num) {
    head = nullptr;
    tail = nullptr;
    numItems = num;

    for (int i = 0; i < num; i++) {
        Node *new_node = new Node(list[i], nullptr, tail);
        if (!head) {
            head = new_node;
            tail = new_node;
        }
        else {
            tail->next = new_node;
            tail = new_node;
        }
    }
}

// Implemented by Gizem Gezici
void MyList::addToEnd(string &newData) {
    Node *ptr = head;

    // List is empty
    if (tail == nullptr) {
        Node *temp = new Node(newData, nullptr, nullptr);
        head = temp;
        tail = temp;
    }
    else {
        Node *temp = new Node(newData, nullptr, tail);
        tail->next = temp;
        tail = temp;
    }
    numItems++;
}

// Implemented by Gizem Gezici
void MyList::addToBeginning(string &newData) {
    // List is empty
    if (head == nullptr) {
        Node *temp = new Node(newData, nullptr, nullptr);
        head = temp;
        tail = temp;
    }
    else {
        Node *ptr = new Node(newData, head, nullptr);
        head->previous = ptr;
        head = ptr;
    }
}

int MyList::numberOfElements() { return numItems; }

MyListItr::MyListItr(const MyList &l) : list(l), current(l.head) {}

// Modified by Gizem Gezici
void MyListItr::next() {
    if (current) {
        current = current->next;
    }
}

// Modified by Gizem Gezici
void MyListItr::previous() {
    if (current) {
        current = current->previous;
    }
}

// Implemented by Gizem Gezici
bool MyListItr::hasMore() { return current; }

// Get the string data in the linked list node.
string MyListItr::getData() { return current->data; }

// Go to the beginning of the linked list.
void MyListItr::goToBeginning() { current = list.head; }

// Go to the end of the linked list.
void MyListItr::goToEnd() { current = list.tail; }
