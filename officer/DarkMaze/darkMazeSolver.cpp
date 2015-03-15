#ifndef MAZE_SOLVER
#define MAZE_SOLVER

#include <iostream>
#include <cstdlib>
#include "darkMaze.h"

using namespace std;

class MazeSolver
{
private:
  Maze* m;
public:
  MazeSolver( Maze* maze_ ) : m(maze_) {}

  void solve()
  {
    // WRITE SOLVER HERE
    // cout << m->lookUp() << endl;
    // cout << m->lookDown() << endl;
    // cout << m->lookLeft() << endl;
    // cout << m->lookRight() << endl;

    // int temp = 0;
    while( 1 )
    {
      // m->goDown();
      // m->goRight();
      // m->goUp();
      // m->goLeft();
      // m->goDown();
      // m->goRight();

      int r = rand() % 4;
      switch( r )
      {
        case 0:
          m->goDown();
          break;
        case 1:
          m->goUp();
          break;
        case 2:
          m->goLeft();
          break;
        case 3:
          m->goRight();
          break;
      } // switch random

      // temp++;
      // if( temp > 1000 )
      //   m->giveUp();

      // if( !(temp % 200) )
      //   m->printPath();
    }
  } // solve()
  
}; // class MazeSolver


// Can write more functions here if you want!


#endif