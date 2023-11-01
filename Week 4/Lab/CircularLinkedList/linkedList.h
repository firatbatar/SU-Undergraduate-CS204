#ifndef _LINKEDLIST_H
#define _LINKEDLIST_H
#include <string>
using namespace std;

struct node
 {
	string data;
	node *next;

	node()
	{}

	node(const string &s, node * link)
		: data(s), next(link)
	{}
};

class linkedlist
{
private:
	node *head;		//Head node, start of LinkedList
	void printListInverse(node *n);


public:
	linkedlist();			//Constructor
	void printList();		//Prints the given LinkedList from head to end
	void printListInverse();//Prints the given LinkedList from end to head

	void addToBeginning(string n);	//Inserts new node at the beginning of the LinkedList with given data
};


#endif
