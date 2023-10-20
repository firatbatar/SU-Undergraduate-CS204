/*************************************
 *Modified by Gizem Gezici
 *Date: 05.03.2012
 *Modified by Gizem Gezici on 13.03.2012 (Bug fix on addToEnd member function)
 *************************************/

#include "linkedList.h"

#include <iostream>

using namespace std;

linkedlist::linkedlist() { head = nullptr; }

void linkedlist::printList() {
    node* ptr = head;
    // List is empty
    if (head == nullptr) {
        cout << "List is empty" << endl;
    }
    else {
        cout << "Printing: ";
        while (ptr) {
            cout << ptr->data << " ";
            ptr = ptr->next;
        }
        cout << endl;
    }
}

void linkedlist::addToEnd(string n) {
    node* ptr = head;
    node* temp = new node(n, nullptr);
    // List is empty
    if (head == nullptr) {
        head = temp;
    }
    else {
        while (ptr->next) {
            ptr = ptr->next;
        }
        ptr->next = temp;
    }
}

void linkedlist::addToBeginning(string n) {
    // List is empty
    if (head == nullptr) {
        head = new node(n, nullptr);
    }
    else {
        head = new node(n, head);
    }
}

void linkedlist::deleteList() {
    while (head) {
        node* temp = head->next;
        delete head;
        head = temp;
    }
}

void linkedlist::printListInverse() {
    if (head == nullptr) {
        cout << "List is empty" << endl;
    }
    else {
        cout << "Reversed List: ";
        int count = 0;
        node* temp = head;
        while (temp) {
            count++;
            temp = temp->next;
        }

        for (int i = count - 1; i >= 0; i--) {
            temp = head;
            for (int j = 0; j < i; j++) {
                temp = temp->next;
            }
            cout << temp->data << " ";
        }
        cout << endl;
    }
}
