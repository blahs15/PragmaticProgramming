// Written by Russell Miller
// Pragmatic Programming
// November 2014
// compile with: "g++ nonogramChecker.cpp -o nonogramChecker.out"

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

using namespace std;

enum State { UNDECIDED, FILLED, EMPTY };
enum Status { VALID, INCOMPLETE, INCORRECT };

class Line
{
  public:
    static int dimension;
    int* hints; // hints for line
    int numHints; // num of hints for line
    State* solution; // state the solution is in -- use optional
                     // filled, empty
    State* mySolution; // state my solution is in
                       // undecided, filled, empty
    Status status; // line is valid/incomplete/incorrect
    bool matches; // mySol does not differ from Sol

    Line()
    {
      hints = new int[(dimension+1)/2];
      numHints = 0;
      solution = new State[dimension];
      mySolution = new State[dimension];
      status = VALID;
      matches = true;
    }
}; // class Line

Line *rows, *cols;
int Line::dimension;
bool isSolution; // solution file provided

void checkArguments( int );
void readPuz( char* );
void readSol( char* );
void readMySol( char* );
void printPuzs();
void checkLines();
void checkLine( Line& );
void printStats();

int main( int argc, char** argv )
{
  checkArguments( argc );
  readPuz( argv[1] );
  isSolution = false;
  if( argc == 4 )
  {
    isSolution = true;
    readSol( argv[2] );
  }
  readMySol( argv[2 + isSolution] );

  printPuzs();
  checkLines();
  printStats();
} // main()

void checkArguments( int argc )
{
  // checks command line arguments
  if( argc != 3 && argc != 4 )
  {
    cout << endl << "Usage: nonogramChecker.out nonoPuz.txt [nonoSol.txt] yourSol.txt" << endl;

    cout << endl << "Ex: \"nonogramChecker.out nonoPuz-20-14527.txt mySol.txt\"" << endl
         << "The mySol.txt file should have the entire grid printed out with each row on a different line." << endl
         << "\'.\' represents an Undecided square" << endl
         << "\'O\' represents an Filled square" << endl
         << "\'X\' represents an Empty square" << endl;

    cout << endl << "The actual solution input is optional." << endl
         << "Providing the actual solution will allow a more detailed check,"
         << endl << "but some puzzles may have more than 1 correct solution,"
         << endl << "so differing from the provided solution may be okay." << endl;

    cout << endl;
    exit( 0 );
  } // if
} // checkArguments()


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


void readSol( char* argv )
{
  ifstream inf( argv );
  for( int i = 0; i < Line::dimension; i++ )
    for( int j = 0; j < Line::dimension; j++ )
    {
      char c;
      do
      {
        inf >> c;
      } while( c != '.' && c != 'O' && c != 'X' );
      if( c == '.' )
        rows[i].solution[j] = cols[j].solution[i] = UNDECIDED;
      else if( c == 'O' )
        rows[i].solution[j] = cols[j].solution[i] = FILLED;
      else //if( c == 'X' )
        rows[i].solution[j] = cols[j].solution[i] = EMPTY;
    } // for
  inf.close();
} // readSol()


void readMySol( char* argv )
{
  ifstream inf( argv );
  for( int i = 0; i < Line::dimension; i++ )
    for( int j = 0; j < Line::dimension; j++ )
    {
      char c;
      do
      {
        inf >> c;
      } while( c != '.' && c != 'O' && c != 'X' );
      if( c == '.' )
        rows[i].mySolution[j] = cols[j].mySolution[i] = UNDECIDED;
      else if( c == 'O' )
        rows[i].mySolution[j] = cols[j].mySolution[i] = FILLED;
      else //if( c == 'X' )
        rows[i].mySolution[j] = cols[j].mySolution[i] = EMPTY;
    } // for
  inf.close();
} // readSol()


void printPuzs()
{
  if( isSolution )
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
  } // if isSolution
  cout << endl;
  // MY SOLUTION
  for( int i = 0; i < Line::dimension; i++ )
  {
    for( int k = 0; k < Line::dimension; k++ )
    {
      if( rows[i].mySolution[k] == EMPTY )
        cout << 'X';
      else if( rows[i].mySolution[k] == FILLED )
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
} // printPuzs


void checkLines()
{
  for( int i = 0; i < Line::dimension; i++ )
  {
    checkLine( rows[i] );
    checkLine( cols[i] );
  } // for
} // checkLines()


void checkLine( Line& l )
{
  int curCount = 0;
  int hintNum = 0;
  bool complete = true;
  for( int i = 0; i < Line::dimension; i++ )
  {
    if( l.mySolution[i] != UNDECIDED )
    {
      if( isSolution && l.mySolution[i] != l.solution[i] )
        l.matches = false;
      if( l.mySolution[i] == FILLED )
      {
        curCount++;
      } // if filled
      else // empty
      {
        if( curCount != 0 )
        {
          if( hintNum >= l.numHints )
            l.status = INCORRECT;
          else if( curCount != l.hints[hintNum++] )
            l.status = INCORRECT;
          curCount = 0;
        }
      } // else empty
    } // if !undecided
    else
    {
      complete = false;
    } // else undecided
  } // for
  if( curCount != 0 )
  {
    if( hintNum >= l.numHints )
      l.status = INCORRECT;
    else if( curCount != l.hints[hintNum++] )
      l.status = INCORRECT;
    curCount = 0;
  }
  if( hintNum != l.numHints )
    l.status = INCORRECT;
  if( !complete )
    l.status = INCOMPLETE;
} // checkLine()


void printStats()
{
  for( int i = 0; i < Line::dimension; i++ )
  {
    cout << "row" << i << ":  ";
    if( isSolution )
    {
      if( rows[i].matches )
        cout << "matches;";
      else
        cout << "does not match;";
    } // if isSolution
    if( rows[i].status == VALID )
      cout << "  VALID";
    else if( rows[i].status == INCORRECT )
      cout << "  INCORRECT";
    else
      cout << "  INCOMPLETE";
    cout << endl;
  } // for
  cout << endl;

  for( int i = 0; i < Line::dimension; i++ )
  {
    cout << "col" << i << ":  ";
    if( isSolution )
    {
      if( cols[i].matches )
        cout << "matches;";
      else
        cout << "does not match;";
    } // if isSolution
    if( cols[i].status == VALID )
      cout << "  VALID";
    else if( cols[i].status == INCORRECT )
      cout << "  INCORRECT";
    else
      cout << "  INCOMPLETE";
    cout << endl;
  } // for
  cout << endl;
} // printStats()