/*
Created by Gizem Gezici
Modified by Zeynep Dogmus
Modify Date: April 2013
TicTacToe Game-Object Sharing Example
*/

#include <iostream>
#include <string>
#include "Board.h"
#include "Player.h"

using namespace std;

int main() {
    Board myBoard = Board();

#ifdef WITHPOINTER
    Player playerX = Player(&myBoard, "X");
    Player playerO = Player(&myBoard, "O");
#else
    Player playerX = Player(myBoard, "X");
    Player playerO = Player(myBoard, "O");
#endif

    int row = 0;
    int col = 0;
    char turn = 'X';
    bool continueGame = true;
    bool validMove = false;

    while (continueGame) {
        if (turn == 'X') {
            cout << "PlayerX turn: " << endl;
            cin >> row >> col;
            validMove = playerX.Play("X", row, col);
        }
        else if (turn == 'O') {
            cout << "PlayerO turn: " << endl;
            cin >> row >> col;
            validMove = playerO.Play("O", row, col);
        }
        // If a valid move has been done, change the turn
        if (validMove) {
            if (turn == 'X')
                turn = 'O';
            else if (turn == 'O')
                turn = 'X';
        }

        myBoard.DisplayBoard();

        // Check whether one of the players won or the game ended with draw
        if (playerX.wins()) {
            continueGame = false;
            cout << "PlayerX won the game!" << endl;
        }
        else if (playerO.wins()) {
            continueGame = false;
            cout << "PlayerO won the game!" << endl;
        }
        else if (myBoard.IsWithDraw()) {
            continueGame = false;
            cout << "Noone won the game!" << endl;
        }
    }

    cout << "Game is over!" << endl;
    cout << "Final state of the board: " << endl;
    myBoard.DisplayBoard();

    return 0;
}