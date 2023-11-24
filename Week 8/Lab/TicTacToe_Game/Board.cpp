/*
Created by Gizem Gezici
Modified by Zeynep Dogmus
Modify Date: April 2013
Board Class
*/
#include "Board.h"
#include <iostream>

using namespace std;

Board::Board() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            myBoard[i][j] = "_";
        }
    }
}

bool Board::ToBePlayed(string playedStr, int row, int col) {
    if ((row >= 0 && row < 3) && (col >= 0 && col < 3)) {
        if (CellIsEmpty(row, col)) {
            myBoard[row][col] = playedStr;
            return true;
        }
        else {
            cout << "This cell is not empty, invalid move, try again!" << endl;
            return false;
        }
    }
    else {
        cout << "This cell is not valid, invalid move, try again!" << endl;
        return false;
    }
}

void Board::DisplayBoard() const {
    cout << "Board: " << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << myBoard[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

bool Board::checkSomeoneWins(string playerCh) const {
    if (myBoard[0][0] == playerCh) {
        if (myBoard[0][1] == playerCh) {
            if (myBoard[0][2] == playerCh) {
                return true;
            }
        }

        if (myBoard[1][1] == playerCh) {
            if (myBoard[2][2] == playerCh) {
                return true;
            }
        }

        if (myBoard[1][0] == playerCh) {
            if (myBoard[2][0] == playerCh) {
                return true;
            }
        }
    }

    if (myBoard[0][1] == playerCh) {
        if (myBoard[1][1] == playerCh) {
            if (myBoard[2][1] == playerCh) {
                return true;
            }
        }
    }

    if (myBoard[0][2] == playerCh) {
        if (myBoard[1][2] == playerCh) {
            if (myBoard[2][2] == playerCh) {
                return true;
            }
        }

        if (myBoard[1][1] == playerCh) {
            if (myBoard[2][0] == playerCh) {
                return true;
            }
        }
    }

    if (myBoard[1][0] == playerCh) {
        if (myBoard[1][1] == playerCh) {
            if (myBoard[1][2] == playerCh) {
                return true;
            }
        }
    }

    if (myBoard[2][0] == playerCh) {
        if (myBoard[2][1] == playerCh) {
            if (myBoard[2][2] == playerCh) {
                return true;
            }
        }
    }

    return false;
}

bool Board::IsWithDraw() const {
    int countFullCells = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (CellIsEmpty(i, j)) {
                return false;
            }
        }
    }
    return true;
}

bool Board::CellIsEmpty(int row, int col) const { return myBoard[row][col] == "_"; }
