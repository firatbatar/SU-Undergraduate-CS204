#include <iostream>

using namespace std;

/*
  Author: Dilara Akdogan
  Date: Feb. 2014
  Modified: Kamer Kaya, Sept., 2014
*/

int main() {
	cout << "-------------------------------------------------" << endl;
	int* p_int;	// pointer with no memory allocation
	p_int = new int;	// memory allocation
	*p_int = 1;		// change content of pointer
	cout << "Address p_int shows (heap) " << p_int << endl;	    // address
	cout << "The content at the address " << *p_int << endl;		// content
	cout << "-------------------------------------------------" << endl;

	int* p_int2 = new int; // new pointer memory allocation
	*p_int2 = 2;
	cout << "Address p_int2 shows (heap) " << p_int2 << endl;	    // address
	cout << "The content at the address " << *p_int2 << endl;		// content
	cout << "-------------------------------------------------" << endl;

	p_int2 = p_int; // assign one pointer to another
	cout << "p_int2 = p_int " << endl;
	cout << "Address p_int2 shows (heap) " << p_int2 << endl;	    // address
	cout << "The content at the address " << *p_int2 << endl;		// content
	cout << "-------------------------------------------------" << endl;

	int myInt = 3;
	p_int2 = &myInt;  // assign address of a variable to a pointer
	cout << "after p_int2 = &myInt (myInt = 3)" << endl;
	cout << "Address p_int2 shows (stack) " << p_int2 << endl;	    // address
	cout << "The content at the address " << *p_int2 << endl;		// content
	cout << "-------------------------------------------------" << endl;

	int myInt2 = 4;
	*p_int2 = myInt2; // change content of pointer
	cout << "*p_int2 = myInt2 (myInt2 = 4) " << endl;
	cout << "Address p_int2 shows (stack) " << p_int2 << endl;	    // address
	cout << "The content at the address " << *p_int2 << endl;		// content	
	cout << "-------------------------------------------------" << endl;

	int myInt3 = 5;
	cout << "Address myInt3 is (stack) " << &myInt3 << endl;	    // address

	//TODO: Mark every address line in this code as HEAP or STACK
	//(If you do not know what are these please ask to TA.)
	//Then compare the addresses at the console and check if the HEAP addresses
	//and STACK addresses are close to each other. 

	return 0;
}
