// Minesweeper driver
// written by Russell Miller

#include <iostream>
#include "minesweeper.h"
#include "mysquare.h"

using namespace std;


Minesweeper* makeGame();
void solveMinesweeper( Minesweeper* game );


int main()
{
  Minesweeper* game = makeGame();
  solveMinesweeper( game );
} // main()

Minesweeper* makeGame()
{
  int choice = 0, seed;
  cout << "Seed for Random Number Generator: ";
  cin >> seed;
  cout << "Minesweeper Menu:" << endl;
  cout << "1. Advanced (30x16, 99 mines) (default)" << endl
       << "2. Intermediate (16x16, 40 mines)" << endl
       << "3. Beginner (9x9, 10 mines)" << endl
       << "4. Custom" << endl
       << "Choice: ";
  cin >> choice;
  // if( choice == 1 )
  //   return new Minesweeper(30,16,99,seed);
  if( choice == 2 )
    return new Minesweeper(16,16,40,seed);
  if( choice == 3 )
    return new Minesweeper(9,9,10,seed);
  if( choice == 4 )
  {
    int rows, cols, mines;
    cout << "Specifications?" << endl
         << "(format: rows cols mines)" << endl;
    cin >> rows >> cols >> mines;
    // cout << rows << "," << cols << "," << mines << endl;
    return new Minesweeper(rows,cols,mines,seed);
  } // if custom
  return new Minesweeper(30,16,99,seed);
} // makeGame()


void solveMinesweeper( Minesweeper* game )
{
  // MUST USE THIS FIRST LINE
  game->revealSquare(game->numRows()/2,game->numCols()/2);
  // MUST USE THIS FIRST LINE
  int rows = game->numRows();
  int cols = game->numCols();
  game->print();

  bool hasChanged = true;
  while( hasChanged )
  {
    hasChanged = false;

    { // method 1
      for( int r = 0; r < rows; r++ )
      {
        for( int c = 0; c < cols; c++ )
        {
          // if( game->isRevealed(r,c) >= 0 && game->surFlags(r,c) + game->surEmpty(r,c)
        } // for col
      } // for row
    } // method 1
    game->print();

  } // while hasChanged
  game->endGame();
} // solveMinesweeper()




