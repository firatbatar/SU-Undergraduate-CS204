#include <iostream>
#include <fstream>       // for ifstream
#include <cctype>        // for tolower(), isalpha()
#include <string>
#include <vector>

using namespace std;

// count # occurrences of all characters in a file
// written: 8/5/94, Owen Astrachan, modified 5/1/99
// modified by Albert Levi 8/14/2002 and 12/17/2007
// modified by Gulsen Demiroz 11/5/2009
// switched to using vector: modified by Emir Artar 25/09/2012

void Print(const vector<int>& counts, int total);
void Count(ifstream& input, vector<int>& counts, int& total);

int main() {
	int	totalLetters = 0;  // counter for all letters      
	string filename;
	cout << "enter name of input file: ";
	cin >> filename;
	ifstream input(filename);

	if (input.fail()) {
		cout << "could not open file " << filename << endl;
		cin.get();
		cin.ignore();
		return 0;
	}

	// 0 for 'a', 1 for 'b', 2 for 'c', so on, 25 for 'z'
	// all initialized to 0
	vector<int> charCounts(26);

	Count(input, charCounts, totalLetters);
	Print(charCounts, totalLetters);

	cin.get();
	cin.ignore();
	return 0;
}

void Count(ifstream& input, vector<int>& counts, int& total)
// precondition: input open for reading and file pos. 
//               pointer is at the beginning
//               counts[k] == 0, where 0 <= k and k < 26
// postcondition: counts[k] = # occurrences of letter: 
//                0th entry for 'a', 1st for 'b', so on
//                total = # alphabetic characters     
{
	char ch;

	while (input.get(ch))        // read a character
	{
		if (isalpha(ch))         // is alphabetic (a-z) or (A-Z)?
		{
			total++;
			ch = tolower(ch);      // convert to lower case
			//TODO: Count here the characters in one statement
			counts[ch - 'a']++;
		}
	}
}

void Print(const vector<int>& counts, int total)
// precondition: total = total number of  letters
// postcondition: all values of counts from 'a' (0) to 'z' (25) printed     
{

	cout.setf(ios::fixed);     // print real numbers in decimal point notation
	cout.precision(1);         // print 1 decimal place 
	cout << "Letter   Count   Percentage" << endl;
	//TODO: Fix the for loop below
	for (int k = 0; k <= 25; k++) {
		cout << char(k + 'a') << "\t" << counts[k] << "\t";
		cout << 100 * double(counts[k]) / total << "% \n";
	}
}
