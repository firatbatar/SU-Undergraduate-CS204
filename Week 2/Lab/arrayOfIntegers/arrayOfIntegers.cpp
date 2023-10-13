/************************
**Author: Gizem Gezici**
*****Date: 28.02.2012**
************************/
/*This program will traverse the elements of an array by using array indices.
And then it will traverse the elements of an array by using the array of pointers.*/

#include <iostream>
#include <string>

using namespace std;
//Built-in arrays don't have a size member function like tvector class.
void Print_List(int* arrayOfPointers[], int size) {
	cout << "Printing the array by using the pointer array: " << endl;
	for (int i = 0; i < size; i++) {
		cout << *arrayOfPointers[i] << endl;
	}
}

int main() {
	//The size of a built-in array should be constant
	const int size = 6;
	int* listOfIntegerPointers[size];
	int listOfIntegers[size];
	int num = 0;
	cout << "Please enter 6 numbers: " << endl;
	for (int i = 0; i < size; i++) {
		cin >> num;
		listOfIntegers[i] = num;
	}

	//Each pointer is assigned to the corresponding element of the array
	for (int i = 0; i < size; i++) {
		listOfIntegerPointers[i] = &listOfIntegers[i];
	}
	Print_List(listOfIntegerPointers, size);

	//These two ways of summing the elements of the built-in array will give the same result.
	int sumArray = 0;
	for (int j = 0; j < size; j++) {
		sumArray += listOfIntegers[j];
	}
	cout << "The sum of the elements in the array (through the array of integer pointers): " << sumArray << endl;

	int sumPointer = 0;
	for (int j = 0; j < size; j++) {
		sumPointer += *listOfIntegerPointers[j];
	}

	cout << "The sum of the elements in the array (through the array of integers): " << sumPointer << endl;

	//In order to see it on the console
	return 0;
}
