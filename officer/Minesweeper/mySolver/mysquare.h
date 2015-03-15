// Minesweeper Square
// written by Russell Miller

#ifndef MYSQUARE_H
#define MYSQUARE_H

#include "minesweeper.h"


class MySquare
{
  private:
    // bool mine;
    // bool flagged;
    // bool questionFlag;
    // int number;
    // bool revealed; // known

    Minesweeper* game;
    bool complete;
    int r; // row
    int c; // col
  public:
    void setUpGame( Minesweeper* game_ );
    // Square();
    // bool isMine() const;
    // void setMine();

    // bool isFlagged() const;
    // void setFlagged(); // toggle
    
    // bool isQuestion() const;
    // void setQuestion(); // toggle
    
    // int getNumber() const;
    // void setNumber( int num ); // changeable, does this matter?
    
    // bool isRevealed() const;
    // void reveal();

    bool isComplete();
    bool checkComplete();
    int getSurCount();
}; // class Square

// static Minesweeper* MySquare::game;


#endif