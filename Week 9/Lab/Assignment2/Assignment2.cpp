/*
Author: Ismail Fatih Yõldõrõm
Modified by Gizem Gezici
Modified Date: 02.05.2012
Bit operations
*/

#include<iostream>
using namespace std;

void DivideByTwo(unsigned int & num)
{
	num = num >> 1; //No danger of overflow! Just divide it by two by shifting one bit right.
}

//Gets the LSB and by shifting right and sets MSB to LSB
void CycleRight(unsigned int & num)
{
	unsigned int rightBit = num & 1 ;
	num = num >> 1;
	num = num | (rightBit << 31);
}

//TODO: Implement the following function.
//Gets the MSB and by shifting left sets LSB to MSB (i.e. cycle)
//The function gets a reference parameter
void CycleLeft(unsigned int & num)
{
    
}

//TODO: In order to calculate the distance, you need to count 
//the number of different bits in a and b. 
unsigned int HammingDistance(unsigned int a, unsigned int b)
{
	
}


void MultiplyByTwo(unsigned int & num)
{
  //TODO:Check if shifting one bit to the left will overflow or not;
  //The function should return if it will.
    
  num = num << 1; //If there is no danger of overflow, then multiply it by 2
  //(shift to the left) by one bit.
}


//Prints the num in binary to the screen.
void PrintToScreen(unsigned int  num)
{
	char * list  = new char[8 * sizeof(unsigned int) + 1];
	list[32] = '\0';
	for(int i = 0; i < 32; i++)
	{
		if((num & 1) == 1)
		{
			list[31-i] = '1';
		}
		else
		{
			list[31-i] = '0';
		}

		num = num >> 1;
	}

	cout << list << endl;
}

int main()
{
	unsigned int a = 26354234;
	unsigned int b = 68768764;
	PrintToScreen(a);

	CycleRight(a);CycleRight(a);
	PrintToScreen(a);
	cout << endl;
	CycleRight(a);CycleRight(a);
	PrintToScreen(a);
	cout << endl;

	PrintToScreen(b);
	CycleLeft(b);CycleLeft(b);
	PrintToScreen(b);
	cout << endl;
	
	CycleLeft(a);
	PrintToScreen(a);
	cout << endl;

	unsigned int c = HammingDistance(a,b);
	cout << c << endl;
	cout << endl;

	cin.get();
	cin.ignore();
	return 0;
}
