/*
Modified by Gizem Gezici
Date: 13.03.2012
Postfix to Infix Conversion by Using Stacks
Push Back, Pop Up, Print, Clear 
*/

#include <iostream>
#include "DynamicStringStack.h"
#include "strutils.h"

using namespace std;

// ClearStack: Free function
// Motivation behind making this as a free function:
// This function could be implemented by the notion
// of linked lists by reaching the next pointer of
// top pointer. However, for stacks we should use 
// pop up member function in order to clear the stack.
void ClearStack(DynamicStringStack & myStack) {
	string value = "";
	if(myStack.isEmpty()) {
		cout << "Stack is empty!" << endl;
	}
	else {
		while (!myStack.isEmpty()) {
			myStack.pop(value);
		}
	}
}

// Same motivation holds for print function.
void Print(DynamicStringStack& myStack) {
	DynamicStringStack reverseStack;
	string value = "";

	if(myStack.isEmpty()) {
		cout << "Empty Stack!" << endl;
	}
	else {
		// Reverse of the stack
		cout << "Printing the stack..." << endl;
		while(!myStack.isEmpty()) {
			myStack.pop(value);
			cout << value << " ";
			reverseStack.push(value);
		}
		cout << endl;
	}

	// Again my real stack
	while(!reverseStack.isEmpty()) {
		reverseStack.pop(value);
		myStack.push(value);
	}
}

int main() {	
	DynamicStringStack iStack, prevStack;

	// Postfix to Infix Conversion By Using Stack
	// Postfix: 3 4 5 + * 10 / (# for the end of the expression)
	// Infix: (3*(4+5)/10)
	string postfix = "";
	string str = "";

	cout << "Enter a postfix statement having operators/operands " << endl << "separated with spaces: e.g., 3 4 5 + * 10 / # " << endl << 
		"(for the end of the expression)" << endl;
	cin >> str;
	// Please leave spaces between inputs (read as string)
	while(str != "#") {		
		postfix += str;
		if((str != "+") && (str != "-") && (str != "*") && (str != "/")) {
			iStack.push(str);
		}
		else {
			string arg1,arg2;

			iStack.pop(arg1);
			iStack.pop(arg2);

			// Reverse Order Print for the last number will be added to the left
			// Important not for '+' but some operators.
			string expression = "(" + arg2 + str + arg1 + ")";

			iStack.push(expression);

		}
		cin >> str;
	}

	string infix;
	iStack.pop(infix);

	cout << "Postfix: " << postfix << endl;
	cout << "Infix: " << infix << endl;

	// Store the elements in the stack
	for(int i=0; i<10; i++) {
		string str = itoa(i);
		iStack.push(str);
	}

	// In order to see the effects of member functions of DynamicStringStack class.
	Print(iStack);
	ClearStack(iStack);
	Print(iStack);

	return 0;
}

