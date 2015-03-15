// Russell Miller
// Pragmatic Programming
// December 2014

#include <iostream>
#include <fstream>

using namespace std;

enum State { UNDECIDED, FILLED, EMPTY };

class Line
{
  public:
    static int dimension;
    int* hints; // hints for line
    int numHints; // num of hints for line
    State* solution; // state the solution is in -- use optional
                     // undecided, filled, empty

    bool complete; // line is solved

    Line() : numHints(0), complete(false)
    {
      hints = new int[(dimension+1)/2];
      solution = new State[dimension];
    }
}; // class Line

Line *rows, *cols;
int Line::dimension;

void readPuz( char* argv );
void initialCheck( Line& );
bool solveLine( Line& );
void printPuz();


int main( int argc, char** argv )
{
  if( argc != 2 )
    return 0;
  readPuz( argv[1] );

  for( int i = 0; i < Line::dimension; i++ )
  { // initialCheck loop
    initialCheck( rows[i] );
    initialCheck( cols[i] );
    for( int k = 0; k < Line::dimension; k++ )
    {
      if( rows[i].solution[k] != UNDECIDED )
        cols[k].solution[i] = rows[i].solution[k];
      if( cols[i].solution[k] != UNDECIDED )
        rows[k].solution[i] = cols[i].solution[k];
    } // for changes made
  }

  bool hasChanged = true;
  while( hasChanged )
  {
    hasChanged = false;
    for( int i = 0; i < Line::dimension; i++ )
    {
      if( solveLine( rows[i] ) )
      {
        hasChanged = true;
        for( int k = 0; k < Line::dimension; k++ )
          cols[k].solution[i] = rows[i].solution[k];
      } // if rows
      if( solveLine( cols[i] ) )
      {
        hasChanged = true;
        for( int k = 0; k < Line::dimension; k++ )
          rows[k].solution[i] = cols[i].solution[k];
      } // if cols
    } // for rows, cols
  } // while solving

  printPuz();
} // main()



void readPuz( char* argv )
{
  ifstream inf( argv );
  inf >> Line::dimension;

  rows = new Line[Line::dimension];
  cols = new Line[Line::dimension];

  char c;
  inf >> c >> noskipws;
  for( int lineNum = 0; c != '\n'; )
  {
    if( c == ' ' )
    {
      if( rows[lineNum].numHints == 0 )
        rows[lineNum].hints[rows[lineNum].numHints++] = 0;
      lineNum++;
    }
    else // segment in row
      rows[lineNum].hints[rows[lineNum].numHints++] = c - 'A' + 1;
    inf >> c;
  } // while rows
  inf >> c;
  for( int lineNum = 0; c != '\n'; )
  {
    if( c == ' ' )
    {
      if( cols[lineNum].numHints == 0 )
        cols[lineNum].hints[cols[lineNum].numHints++] = 0;
      lineNum++;
    }
    else // segment in col
      cols[lineNum].hints[cols[lineNum].numHints++] = c - 'A' + 1;
    inf >> c;
  } // while cols
  inf >> skipws;
  inf.close();
} // readPuz()

void printPuz()
{
  for( int i = 0; i < Line::dimension; i++ )
  {
    for( int k = 0; k < Line::dimension; k++ )
    {
      if( rows[i].solution[k] == EMPTY )
        cout << 'X';
      else if( rows[i].solution[k] == FILLED )
        cout << 'O';
      else // undecided
        cout << '.';
      cout << ' ';
    } // for
    for( int k = 0; k < rows[i].numHints; k++ )
      cout << " " << rows[i].hints[k];
    cout << endl;
  } // for
  for( int i = 0; i < (Line::dimension+1)/2; i++ )
  {
    for( int k = 0; k < Line::dimension; k++ )
      if( cols[k].numHints > i )
      {
        cout << cols[k].hints[i];
        if( cols[k].hints[i] < 10 )
          cout << ' ';
      } // if
      else // no hint for this column
        cout << "  ";
    cout << endl;
  } // for col hints
  cout << endl;
} // printPuz()



void initialCheck( Line& l )
{
  if( l.hints[0] == 0 )
  {
    for( int i = 0; i < l.dimension; i++ )
      l.solution[i] = EMPTY;
    l.complete = true;
    return;
  } // if nothing filled

  // find required space
  int reqSpace = -1;
  for( int i = 0; i < l.numHints; i++ )
    reqSpace += l.hints[i] + 1;
  int leeway = l.dimension - reqSpace;

  int pos = 0;
  if( !leeway ) // required space fills entire line
  {
    for( int i = 0; i < l.numHints; i++ )
    {
      for( int k = 0; k < l.hints[i]; k++ )
      {
        l.solution[pos++] = FILLED;
      } // for each hint
      l.solution[pos++] = EMPTY;
    } // for all hints
    l.complete = true;
    return;
  }

  for( int i = 0; i < l.numHints; i++ )
  {
    for( int k = 0; k < l.hints[i]; k++ )
    {
      if( k >= leeway )
        l.solution[pos] = FILLED;
      pos++;
    } // for each hint
    pos++;
  } // for all hints
} // initialCheck()


bool solveLine( Line& l )
{
  bool change = false;
  if( l.complete )
    return change;

  return change;
} // solveLine()

