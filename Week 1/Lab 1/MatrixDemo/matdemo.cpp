#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>  // for setw
#include <vector>

using namespace std;

// demonstrate class matrix

// Prints the matrix to the console
void Print(const vector<vector<int>>& mat) {
	for (int j = 0; j < mat.size(); j++) {
		for (int k = 0; k < mat[0].size(); k++) {
			cout << setw(4) << mat[j][k];
		}
		cout << endl;
	}
}

// Reports the sum of the elements on the diagonal
void SumDiagonal(const vector<vector<int>>& mat) {
	int sumdiag = 0;
	for (int k = 0; k < mat[0].size(); k++) {
		sumdiag += mat[k][k];
	}
	cout << "sum of diagonal is " << sumdiag << endl;
}

// Reports the sum of the elements on the columns
void SumColumn(const vector<vector<int>>& mat) {
	for (int j = 0; j < mat[0].size(); j++) {
		int sum = 0;
		for (int k = 0; k < mat.size(); k++) {
			sum += mat[j][k];
		}
		cout << "sum of column " << j << " is " << sum << endl;
	}
}

// Reports the sum of the elements on the reverse diagonal
void SumDiagonalReverse(const vector<vector<int>>& mat) {
	int startColumn = mat[0].size() - 1;

	int sum = 0;
	for (int i = 0; i <= startColumn; i++) {
		sum += mat[i][startColumn - i];
	}
	cout << "sum of diagonal in reverse is " << sum << endl;
}

int main() {
	string fileName;
	int j, k;
	vector<vector<int>> mat;
	vector<int> temp;
	cout << "Enter the input file name" << endl;
	cin >> fileName;

	ifstream input;
	input.open(fileName);

	if (input.fail()) {
		cout << "Could not open the file " << fileName << endl;
		return 0;
	}

	string line;
	while (!input.eof()) {
		getline(input, line);
		stringstream ss(line);

		int num;
		temp.clear();
		while (ss >> num) {
			temp.push_back(num);
		}
		mat.push_back(temp);
	}

	// NOTE THAT there was no row size check.
	// We are assuming the file is correct and use the number of
	// columns in the matrix as the number of columns in its first row.

	int rows = mat.size();
	int cols = mat[0].size();

	Print(mat);
	cout << "\n\n";

	SumColumn(mat);

	if (rows == cols)  // Diagonal only occurs in a square matrix
	{
		cout << "\n";
		SumDiagonal(mat);
		cout << "\n";
		SumDiagonalReverse(mat);
	}

	// 4 possible matrix declarations
	vector<vector<int>> mat1;
	Print(mat1);
	cout << "\n ********** \n";

	vector<vector<int>> mat2(rows);
	Print(mat2);
	cout << "\n ********** \n";

	vector<vector<int>> mat3(rows, vector<int>(cols));
	Print(mat3);
	cout << "\n ********** \n";

	vector<vector<int>> mat4(rows, vector<int>(cols, -1));
	Print(mat4);
	cout << "\n ********** \n";


	cout << "\n";
	cin.ignore();
	cin.get();
	return 0;
}
