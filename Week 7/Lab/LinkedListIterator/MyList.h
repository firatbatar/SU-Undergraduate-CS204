/*
Modified by Gizem Gezici
Modified Date: 10.04.2012
Linked List Iterator

*/

#ifndef MYLIST_H
#define MYLIST_H
#include <string>
using namespace std;

class MyList {
   public:
    MyList();
    MyList(string *, int);
    void addToEnd(string &n);
    void addToBeginning(string &n);
    int numberOfElements();

   private:
    struct Node {
        // These will be used in the public methods of the iterator class
        // in order to iterate the linked list in the main.
        Node *next;
        Node *previous;
        string &data;
        Node(string &d, Node *n, Node *p) : data(d), next(n), previous(p) {}
    };

    // Beginning of the list
    Node *head;

    // End of the list
    Node *tail;

    int numItems;

    friend class MyListItr;
};

class MyListItr {
   public:
    /*
    Update the specific string data in one of the linked list's nodes
    Implementation will be completed in the lab
    */
    MyListItr(const MyList &l);
    void next();
    string getData();
    void previous();
    void goToEnd();
    void goToBeginning();
    // Added by Gizem Gezici
    // In order to understand the list is at the beginning or the end (doubly linked list)
    bool hasMore();

   private:
    typedef MyList::Node Node;
    Node *current;
    const MyList &list;
};

#endif