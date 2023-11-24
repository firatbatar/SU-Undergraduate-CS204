/*
Created by Gizem Gezici
Modified by Zeynep Dogmus
Modify Date: April 2013
Player Class
Please pay attention to the class design.
*/
#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <string>
#include "Board.h"
using namespace std;

// Uncomment the line below to see an example of object sharing with pointer
// #define WITHPOINTER

class Player {
   public:
    Player();
#ifdef WITHPOINTER
    Player(Board *myboard, string c) : board(myboard), playerChar(c) {}
#else
    Player(Board &myboard, string c) : board(myboard), playerChar(c) {}
#endif

    // Play function of the player class will call ToBePlayed function of Board Class.
    bool Play(string playedStr, int row, int col);
    bool wins();

   private:
#ifdef WITHPOINTER
    // Pointer to keep the shared object between two players
    Board *board;
#else
    // Referenced variable (shared object between two players)
    Board &board;
#endif
    string playerChar;
};

#endif