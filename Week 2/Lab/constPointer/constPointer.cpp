/*
   Author: Kamer Kaya
   Date: Sept, 2014
*/

#include <iostream>

using namespace std;

//comment this line to get errors
#define VALID

int main() {
	int myInt = 1;
	int myInt2 = 2;

	//this is a pointer to a constant int
	const int* pInt = &myInt;
	cout << "before " << pInt << ": " << *pInt << endl;

#ifdef VALID
	//this is valid since we are changing 
	//the address of the pointer not the value
	pInt = &myInt2;
#else
	//this is not valid since the value of
	//the pointer points needs to be constant
	//try it!
	* pInt = myInt;
#endif

	cout << "after " << pInt << ": " << *pInt << endl;
	cout << "-----------------------------------" << endl;

	//this is a constant pointer to an int
	int* const pInt2 = &myInt;
	cout << "before " << pInt2 << ": " << *pInt2 << endl;

#ifdef VALID
	//this is valid since we are changing the value
	//not the address the constant pointer 
	* pInt2 = myInt2;
#else
	//this is not valid since we want to change 
	//the address of a constant pointer
	pInt2 = &myInt2;
#endif

	cout << "after " << pInt2 << ": " << *pInt2 << endl;
	cout << "-----------------------------------" << endl;

	return 1;
}
