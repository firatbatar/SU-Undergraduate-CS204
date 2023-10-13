/***************************
********Author: Gizem Gezici
********Date: 28.02.2012****
********Dynamic Array******/
/*This program will read a file and then create a dynamic array with the lines of the text file.
It just calculates the average number of characters in the text file.*/

#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int main() {
	ifstream file;
	string filename = "dynamicArrayContent.txt";
	//If the filename is taken as a parameter c_str usage is a must.
	file.open(filename.c_str());
	string line = "";
	int countOfLines = 0;
	//Read the file in order to obtain the number of lines
	while (getline(file, line)) {
		countOfLines++;
	}
	//The size of a built-in array cannot be variable

	//Creating a dynamic array
	string* myList = new string[countOfLines];

	//To read the file from the beginning
	file.clear();
	file.seekg(0, ios::beg);

	int index = 0;
	//Read the file again in order to store the lines of the text file by using array indices
	while (getline(file, line)) {
		myList[index] = line;
		index++;
	}

	//Calculate the average number of characters of the strings in the list
	double totalNumOfCharacters = 0;
	for (int i = 0; i < countOfLines; i++) {
		//TODO: use length() for each line to find the total number of characters
		totalNumOfCharacters += myList[i].length();
		// Or
		//totalNumOfCharacters += (*(myList + i)).length()
	}

	double averageOfNumCharacters = totalNumOfCharacters / countOfLines;
	cout << "The average number of characters in the file: " << averageOfNumCharacters << endl;

	return 0;
}
