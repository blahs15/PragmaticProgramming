#ifndef MAZE_SOLVER
#define MAZE_SOLVER

#include <iostream>
#include <cstdlib>
#include <queue>
#include "darkMaze.h"
#include "Escape_Sequence_Colors.h"

using namespace std;

enum Fill {WAL, EMP, UNK}; // wall, empty, unknown

class MazeSolver
{
private:
  typedef struct
  { int r, c; } Pos; // position

  Maze* m;
  Fill** maze;
  int maxrows; // max possible rows
  int maxcols; // max possible cols
  int rows; // min rows known
  int cols; // min cols known
  Pos p; // player position
  Pos e; // possible exit position

  int** shortestPath;

public:
  // MazeSolver( Maze* maze_ );

  // void solve();

    // go__() calls lookAround()
  // bool goUp();
  // bool goDown();
  // bool goRight();
  // bool goLeft();

  // void lookAround();
  // int lookUp();
  // int lookDown();
  // int lookRight();
  // int lookLeft();


// Can write more functions here if you want!

MazeSolver( Maze* maze_ ) : m(maze_), maxrows(150), maxcols(79), rows(75), cols(60)
{
  maze = new Fill*[maxrows];
  for( int i = 0; i < maxrows; i++ )
  {
    maze[i] = new Fill[maxcols];
    for( int k = 0; k < maxcols; k++ )
      maze[i][k] = UNK;
  } // for

  for( int i = 0; i < rows; i++ ) // set left wall borders
    maze[i][0] = WAL;
  for( int k = 0; k < cols; k++ ) // set right wall borders
    maze[0][k] = WAL;

  p.r = 1;
  p.c = 1;
  maze[p.r][p.c] = EMP;
  e.r = rows-2;
  e.c = cols-2;

  // shortestPath
  shortestPath = new int*[maxrows];
  for( int i = 0; i < maxrows; i++ )
    shortestPath[i] = new int[maxcols];

} // MazeSolver constructor

void solve()
{
  // WRITE SOLVER HERE
  lookAround();
  // print();

  int count = 0;
  while( 1 )
  {
    int dir = findShortestPath( 0, 0 );
    switch( dir )
    {
      case 0:
        goRight();
        break;
      case 1:
        goDown();
        break;
      case 2:
        goLeft();
        break;
      case 3:
        goUp();
        break;
      default:
        print();
        cout << "I give up." << endl;
        m->giveUp();
    } // switch(dir)
    
    if( count > 2000 )
    {
      print();
      cout << "I give up." << endl;
      m->giveUp();
    } // if giveUp()
    count++;
  } // while
  print();
} // solve()


void lookAround()
{
  lookUp();
  lookDown();
  lookRight();
  lookLeft();
} // lookAround()

int lookUp()
{
  int dist = m->lookUp();
  if( !dist ) // if exit
  {
    print();
    while(1)
      m->goUp();
  } // exit found
  for( int i = 1; i < dist; i++ )
  {
    maze[p.r-i][p.c] = EMP;
  } // for distance
  maze[p.r-dist][p.c] = WAL;
  return dist;
} // look()
int lookDown()
{
  int dist = m->lookDown();
  if( !dist ) // if exit
  {
    print();
    while(1)
      m->goDown();
  } // exit found
  for( int i = 1; i < dist; i++ )
  {
    maze[p.r+i][p.c] = EMP;
  } // for distance
  maze[p.r+dist][p.c] = WAL;
  if( p.r + dist + 1 > rows )
  {
    rows = p.r + dist + 1;
    e.r = rows-2;
  } // if new furthest wall
  return dist;
} // look()
int lookRight()
{
  int dist = m->lookRight();
  if( !dist ) // if exit
  {
    print();
    while(1)
      m->goRight();
  } // exit found
  for( int i = 1; i < dist; i++ )
  {
    maze[p.r][p.c+i] = EMP;
  } // for distance
  maze[p.r][p.c+dist] = WAL;
  if( p.c + dist + 1> cols )
  {
    cols = p.c + dist + 1;
    e.c = cols-2;
  } // if new furthest wall
  return dist;
} // look()
int lookLeft()
{
  int dist = m->lookLeft();
  if( !dist ) // if exit
  {
    print();
    while(1)
      m->goLeft();
  } // exit found
  for( int i = 1; i < dist; i++ )
  {
    maze[p.r][p.c-i] = EMP;
  } // for distance
  maze[p.r][p.c-dist] = WAL;
  return dist;
} // look()


bool goUp()
{
  bool success = m->goUp();
  if( success )
  {
    p.r--;
    lookAround();
  }
  return success;
} // goUp()
bool goDown()
{
  bool success = m->goDown();
  if( success )
  {
    p.r++;
    lookAround();
  }
  return success;
} // goDown()
bool goRight()
{
  bool success = m->goRight();
  if( success )
  {
    p.c++;
    lookAround();
  }
  return success;
} // goRight()
bool goLeft()
{
  bool success = m->goLeft();
  if( success )
  {
    p.c--;
    lookAround();
  }
  return success;
} // goLeft()


void print()
{
  for( int i = 0; i < rows; i++ )
  {
    for( int k = 0; k < cols; k++ )
    {
      if( i == p.r && k == p.c )
        cout << COLOR_GREEN_YELLOW << "P"; // player
      else if( i == e.r && k == e.c )
        cout << COLOR_BLACK_CYAN << "E"; // exit
      else if( WAL == maze[i][k] ) // wall
      {
        cout << COLOR_MAGENTA_BLACK;
        if( (i && WAL == maze[i-1][k]) || (i != rows-1 && WAL == maze[i+1][k]) )
        {
          if( (k && WAL == maze[i][k-1]) || (k != cols-1 && WAL == maze[i][k+1]) )
            cout << "+"; // walls up|down & left|right
          else
            cout << "|"; // walls up|down
        } // wall up|down
        else if( (k && WAL == maze[i][k-1]) || (k != cols-1 && WAL == maze[i][k+1]) )
          cout << "-"; // walls left|right
        else
          cout << "X";
      } // if wall
      else if( EMP == maze[i][k] )
        cout << COLOR_BLACK_BLACK << ".";
      else if( UNK == maze[i][k] )
        cout << COLOR_BLACK_BLACK << " "; // unvisited
      else // if( 2 <= maze[i][k] )
        cout << COLOR_CYAN_BLACK << maze[i][k]-1; // visit #
    } // for cols
    cout << endl;
  } // for rows
  cout << COLOR_NORMAL;
  cout << "exit: (" << e.r << "," << e.c << ")" << endl;
} // print()


int findShortestPath( int rows2, int cols2 )
{
  int max = maxrows * maxcols;
  for( int i = 0; i < maxrows; i++ )
  {
    for( int k = 0; k < maxcols; k++ )
    {
      if( WAL == maze[i][k] )
        shortestPath[i][k] = 0; // empty
      else
        shortestPath[i][k] = max; // wall
    } // cols
  } // for rows
  // initiate undetermined edges
  for( int i = 0; i < maxrows; i++ )
    shortestPath[i][0] = shortestPath[i][maxcols-1] = 0;
  for( int k = 0; k < maxcols; k++ )
    shortestPath[0][k] = shortestPath[maxrows-1][k] = 0;

  shortestPath[p.r][p.c] = 1; // start count
  queue<Pos> locs; // locations
  Pos p2; // p2 = start pos
  p2.r = p.r;
  p2.c = p.c;
  locs.push(p2); // push start pos

  while( !locs.empty() ) // empty => path not found
  {
    int r = locs.front().r;
    int c = locs.front().c;
    int count = shortestPath[r][c];
    if( r == e.r && c == e.c )
      break; // exit found

    // down, right, left, up
    // don't need to check for walls since they are < count
    if( shortestPath[r+1][c] > count + 1 /*|| (r+1 == e.r && c == e.c)*/ )
    {
      shortestPath[r+1][c] = count + 1;
      p2.r = r+1;
      p2.c = c;
      locs.push(p2);
    } // if down
    if( shortestPath[r][c+1] > count + 1 /*|| (r == e.r && c+1 == e.c)*/ )
    {
      shortestPath[r][c+1] = count + 1;
      p2.r = r;
      p2.c = c+1;
      locs.push(p2);
    } // if right
    if( shortestPath[r][c-1] > count + 1 /*|| (r == e.r && c-1 == e.c)*/ )
    {
      shortestPath[r][c-1] = count + 1;
      p2.r = r;
      p2.c = c-1;
      locs.push(p2);
    } // if left
    if( shortestPath[r-1][c] > count + 1 /*|| (r-1 == e.r && c == e.c)*/ )
    {
      shortestPath[r-1][c] = count + 1;
      p2.r = r-1;
      p2.c = c;
      locs.push(p2);
    } // if up
    locs.pop();
  } // while finding path

  if( !locs.empty() )
  {
    int dir;
    int r = locs.front().r;
    int c = locs.front().c;
    // shortestSteps = shortestPath[r][c] - 1;
    // int count = shortestPath[r][c] - 1;
    while( r != p.r || c != p.c )
    {
      int count = shortestPath[r][c] - 1;
      // left, up, right, down
      if( count == shortestPath[r][c-1] )
      {
        dir = 0; // goRight()
        c--; // if left
      }
      else if( count == shortestPath[r-1][c] )
      {
        dir = 1; // goDown()
        r--; // if up
      }
      else if( count == shortestPath[r+1][c] )
      {
        dir = 3; // goUp()
        r++; // if down
      }
      else if( count == shortestPath[r][c+1] )
      {
        dir = 2; // goLeft()
        c++; // if right
      }
      // shortestPath[r][c] = -2;
    } // while going back to start

    // for( int i = 0; i < rows; i++ )
    //   for( int k = 0; k < cols; k++ )
    //   {
    //     if( 0 < shortestPath[i][k] )
    //       shortestPath[i][k] = 1;
    //     else if( -2 == shortestPath[i][k] )
    //       shortestPath[i][k] = 2;
    //   } // for cols

    // printSol( shortestPath );
    return dir;
  } // if exit found

  // cout << "no path found" << endl;
  return -1;
} // findShortestPath()



}; // class MazeSolver
#endif