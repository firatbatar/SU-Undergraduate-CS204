/*
CS204 Fall 2023-2024 HW#1
Fırat Batar
*/

#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

bool fileToMatrix(ifstream& file, vector<vector<char>>& matrix, int size) {
    // Returns "false" if the matrix is invalid, "true" otherwise

    // Read each row
    string row;
    for (int i = 0; i < size; i++) {
        file >> row;
        if (row.length() != size) {  // Check if the size of the matrix (# of cols) is consistant or not
            return false;
        }

        // Read each column
        vector<char> column;  // Create a temp vector for the column
        for (int j = 0; j < size; j++) {
            char c = row[j];
            if (!isalpha(c)) {  // Check if the character is a letter
                return false;
            }

            column.push_back(c);  // Add the entry to column vector
        }

        matrix.push_back(column);  // Add the column to the matrix
    }

    return true;
}

vector<vector<int>> findNeighbourDirs(int r, int c, int size) {
    // Get the neighbours of a given cell as directions
    // Up: {0, -1}, Right: {1, 0}, Down: {0, 1}, Left: {-1, 0}

    vector<vector<int>> neighbours;
    vector<int> n(2, 0);

    // Left
    if (r >= 1) {
        n[0] = -1;
        n[1] = 0;
        neighbours.push_back(n);
    }
    // Right
    if (r < size - 1) {
        n[0] = 1;
        n[1] = 0;
        neighbours.push_back(n);
    }
    // Up
    if (c >= 1) {
        n[0] = 0;
        n[1] = -1;
        neighbours.push_back(n);
    }
    // Down
    if (c < size - 1) {
        n[0] = 0;
        n[1] = 1;
        neighbours.push_back(n);
    }

    return neighbours;
}

// Find the next step for the search given the prevStep and count of the search
void nextStep(vector<int>& prevStep, int& stepCounter, int& counter, bool clockwise) {
    // As the spiral grows we need to do the same movement more
    // For example: D R U U L L D D D R R R U U U U L L L L (1D, 1R, 2U, 2L, 3D, 3R, ...)
    // "stepCounter" counts to determine in which state we are
    //		0,1: first stage; 2,3: second stage; 4,5: third stage; etc.
    // "counter" counts the # of times we repeated the current move

    int stage = stepCounter / 2 + 1;  // Find the the current stage for counter to reach
    counter++;

    // Reverse the multiplier for reversing the order for clockwise and counter-clockwise search
    int clockwiseMult;
    if (clockwise) {
        clockwiseMult = 1;
    }
    else {
        clockwiseMult = -1;
    }

    if (counter == stage) {  // If the current stage is complete, change the move
        if (prevStep[0] == 0) {
            prevStep[0] = -clockwiseMult * prevStep[1];
            prevStep[1] = 0;
        }
        else {
            prevStep[1] = clockwiseMult * prevStep[0];
            prevStep[0] = 0;
        }

        stepCounter++;  // Increment the counter for the stage
        counter = 0;    // Reset the counter
    }
}

// Search for a given word starting from a given position with given direction (clockwise or counterclockwise)
bool checkWord(vector<vector<char>>& matrix, vector<int>& startPos, string word, int matrixSize, bool clockwise) {
    vector<vector<int>> neigbourDir =
        findNeighbourDirs(startPos[0], startPos[1], matrixSize);  // Get the available neighbours of the starting cell
    vector<vector<int>> validDirections;

    // Start position (row and column)
    int r = startPos[0];
    int c = startPos[1];

    for (int i = 0; i < neigbourDir.size(); i++) {
        vector<int> n = neigbourDir[i];
        char neighbourChar = matrix[r + n[0]][c + n[1]];  // Value of neighbour

        if (word[1] == neighbourChar) {    // If it matches the second letter of the word then the we can contiune to
                                           // search from that direction
            validDirections.push_back(n);  // Mark direction as valid
        }
    }

    if (validDirections.size() == 0) return false;  // If no valid neighbour is found, exit

    // Start forming words in all valid directions
    for (int i = 0; i < validDirections.size(); i++) {
        bool checker = true;  // Checker for correct word

        int len = 2;                            // current length of the search (first two has been already checked)
        int goalLen = word.length();            // Length of the word
        vector<int> step = validDirections[i];  // Which direction to move
        vector<int> currentPos = {r + step[0], c + step[1]};  // Current position
        int stepCounter = 0;
        int counter = 0;  // Counters for next steps
        char neighbourChar;
        while (len != goalLen) {
            nextStep(step, stepCounter, counter, clockwise);  // Get the next step (as a direction)
            currentPos = {currentPos[0] + step[0],
                          currentPos[1] + step[1]};  // Get the position for the neighbour (and move)

            // If we go outside of the matrix (no neighbour) then cannot complete the word
            if (currentPos[0] < 0 || currentPos[0] >= matrixSize || currentPos[1] < 0 || currentPos[1] >= matrixSize) {
                checker = false;  // Can't find the word in this direction
                break;            // Break the while loop and move to the next (if exists) valid direction
            }

            neighbourChar = matrix[currentPos[0]][currentPos[1]];  // Get the value of the neighbour

            if (neighbourChar != word[len]) {  // If characters don't match, exit
                checker = false;               // Can't find the word in this direction
                break;                         // Break the while loop and move to the next (if exists) valid direction
            }

            len++;
        }

        // If word was found
        if (checker) return true;
    }

    // If word is not found
    return false;
}

int main() {
    ifstream inputFile;
    string filename;

    // Ask for a file name until a valid name is entered
    do {
        cout << "Enter the name of the file" << endl;
        cin >> filename;
        inputFile.open(filename.c_str());

        if (inputFile.fail()) {
            cout << "Could not open the file " << filename << endl;
        }
    } while (inputFile.fail());  // File could not open

    // Read the first line for the matrixSize
    int matrixSize;
    inputFile >> matrixSize;

    // Read the file for matrix and create a vector<vector<char>>
    vector<vector<char>> matrix;
    bool isMatrixValid = fileToMatrix(inputFile, matrix, matrixSize);

    // If matrix is invalid, abort
    if (!isMatrixValid) {
        cout << "Error: Input file is not in correct format!" << endl;
        return 0;
    }

    // Words to search
    string word;
    vector<string> words;
    int numOfWords = -1;
    inputFile >> numOfWords;  // Read the number of words

    if (numOfWords == -1 ||
        numOfWords == 0) {  // Probably an extra row of matrix (or an actual problem with # of words)
        cout << "Error: Input file is not in correct format!" << endl;
        return 0;
    }

    // Read the words from the file
    for (int i = 0; i < numOfWords; i++) {
        inputFile >> word;
        words.push_back(word);
    }

    // Go over all cells
    vector<string> foundWords;
    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < matrixSize; j++) {
            char cell = matrix[i][j];  // Get the current cell

            // Check every unfound words for matching first letters
            for (int idx = words.size() - 1; idx >= 0; idx--) {
                if (cell == words[idx][0]) {
                    vector<int> pos = {i, j};
                    bool wordCheckCC =
                        checkWord(matrix, pos, words[idx], matrixSize, false);  // Check for the word counter-clockwise
                    bool wordCheckC =
                        checkWord(matrix, pos, words[idx], matrixSize, true);  // Check for the word clockwise

                    if (wordCheckC || wordCheckCC) {
                        foundWords.push_back(words[idx]);  // Mark word as found
                        words.erase(words.begin() + idx);  // Remove from unfound words
                    }
                }
            }
        }
    }

    // If any word is found, print them
    if (foundWords.size() != 0) {
        cout << foundWords.size() << " Words Are Found:  ";
        for (int i = 0; i < foundWords.size(); i++) {
            cout << foundWords[i] << " ";
        }
    }
    else {
        cout << "No word is found!" << endl;
    }
    return 0;
}