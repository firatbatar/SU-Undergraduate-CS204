/*
Created by Gizem Gezici
Modified by Zeynep Dogmus
Modify Date: April 2013
Board Class
Please pay attention to the class design.
*/
#ifndef BOARD_H
#define BOARD_H

#include <string>
using namespace std;

class Board {
   public:
    Board();
    // These functions are not called by main function; but are called by
    // Player class and since we did not declare friend class we should make
    // these functions public.
    bool ToBePlayed(string playedStr, int row, int col);
    bool checkSomeoneWins(string plCh) const;

    // These functions should be public in order to be called in the main function
    void DisplayBoard() const;
    bool IsWithDraw() const;

   private:
    string myBoard[3][3];
    // Since this is a helper function, it is private
    bool CellIsEmpty(int row, int col) const;
};
#endif
