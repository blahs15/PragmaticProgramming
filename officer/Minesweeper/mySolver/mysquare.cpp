// Minesweeper Square
// written by Russell Miller

#include <iostream>
#include "mysquare.h"

using namespace std;

void MySquare::setUpGame( Minesweeper* game_ )
{
  game = game_;
} // setUpGame()

// Square::Square()
//   : mine(false), flagged(false), number(0), revealed(false)
// {} // Square constructor


// bool Square::isMine() const
// { return mine; }

// void Square::setMine()
// { mine = true; }

// bool Square::isFlagged() const
// { return flagged; }

// void Square::setFlagged() // toggles
// { flagged = !flagged; }

// bool Square::isQuestion() const
// { return flagged; }

// void Square::setQuestion() // toggles
// { questionFlag = !questionFlag; }

// int Square::getNumber() const
// { return number; }

// void Square::setNumber( int num )
// { number = num; }

// bool Square::isRevealed() const
// { return revealed; }

// void Square::reveal()
// { revealed = true; }

bool MySquare::isComplete()
{ return complete; }

bool MySquare::checkComplete()
{ 
  if( complete )
    return true;

  if( game->surEmpty(r,c) == getSurCount() )
    return complete = true;
  return false;
} // checkComplete()

int MySquare::getSurCount()
{

  int surCount = 8;
  if( 0 == r || game->numRows() - 1 == r )
  { // square is on vetical edge
    if( 0 == c || game->numCols() - 1 == c )
    {
      surCount = 3;
    } // if corner
    else
      surCount = 5;
  } // if vertical edge
  else if( 0 == c || game->numCols() - 1 == c )
  {
    surCount = 5;
  } // if horizontal edge

  return surCount;
} // getSurCount()

