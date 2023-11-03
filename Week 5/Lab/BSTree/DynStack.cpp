#include <iostream>
#include "DynStack.h"
using namespace std;

DynStack::DynStack()
{
	top = nullptr; 
}

void DynStack::push(tnode* node)
{
	StackNode *newNode;

	newNode = new StackNode;
	newNode->node = node;

	// If there are no nodes in the list
	// make newNode the first node
	if (isEmpty())
	{
		top = newNode;
		newNode->next = nullptr;
	}
	else	// Otherwise, insert NewNode before top
	{
		newNode->next = top;
		top = newNode;
	}
}

//****************************************************
// Member function pop pops the value at the top     *
// of the stack off, and copies it into the variable *
// passed as an argument.                            *
//****************************************************
void DynStack::pop(tnode* &node)
{
	StackNode *temp;

	if (isEmpty())
	{
		cout << "The stack is empty.\n";
	}
	else	// pop value off top of stack
	{
		node = top->node;
		temp = top->next;
		delete top;
		top = temp;
	}
}

//****************************************************
// Member funciton isEmpty returns true if the stack *
// is empty, or false otherwise.                     *
//****************************************************
bool DynStack::isEmpty(void)
{
	bool status;

	if (top == NULL)
		status = true;
	else
		status = false;

	return status;
}

