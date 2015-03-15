// Written by Russell Miller
// Pragmatic Programming
// November 2014
// Compile with: "g++ nonogramGen.cpp -o nonogramGen.out"

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

using namespace std;

ofstream puz;
ofstream sol;
int dimension;
bool** puzzle;

void checkArguments( int, char** );
void openFiles( char** );
void generate();
void generatePuz();
void generateSol();

int main( int argc, char** argv )
{
  checkArguments( argc, argv );
  openFiles( argv );

  // dimension = atoi( argv[1] ); // moved to checkArguments()
  srand( atoi( argv[2] ) );
  generate();

  generatePuz();
  generateSol();
} // main()


void checkArguments( int argc, char** argv )
{
  // checks command line arguments
  if( argc != 3 )
  {
    cout << endl << "Usage: nonogramGen.out dimension seed" << endl;
    
    cout << endl << "Ex: \"nonogramGen.out 20 14527\" creates a 20x20 puzzle using the seed 14527" << endl;
    cout << "The puzzle will be in nonoPuz-20-14527.txt" << endl
         << "The solution will be in nonoSol-20-14527.txt" << endl;
    
    cout << endl << "The puzzle is represented by groups of chars." << endl
         << "A is 1, B is 2, C is 3, etc." << endl
         << "Line 1 in the file will have the dimension of the puzzle." << endl
         << "Line 2 will have the rows where each row is separated by a space." << endl
         << "Line 3 will have the columns where each column is separated by a space." << endl;
    
    cout << endl << "Ex: ADCA BBAA would represent the hint \"1 4 3 1\" for the 1st row/col, and \"2 2 1 1\" for the 2nd row/col" << endl;

    cout << endl;
    exit( 0 );
  } // if

  dimension = atoi( argv[1] );
  if( dimension < 5 || dimension > 40 )
  {
    cout << "Please choose a dimension between 5 and 40. (Suggested 5~25)" << endl;
    exit( 0 );
  } // if bad dimension
} // checkArguments()

void openFiles( char** argv )
{
  // creates and opens the files that will contain the puzzle and solution
  string temp = argv[1];
  string filename = "nonoPuz-" + temp + '-';
  string filename2 = "nonoSol-" + temp + '-';
  temp = argv[2];
  filename += temp + ".txt";
  filename2 += temp + ".txt";
  puz.open( filename.c_str() );
  sol.open( filename2.c_str() );
} // openFiles()

void generate()
{
  // generates the puzzle
  puzzle = new bool*[dimension];
  for( int i = 0; i < dimension; i++ )
  {
    puzzle[i] = new bool[dimension];
    for( int j = 0; j < dimension; j++ )
      puzzle[i][j] = false;
  } // for

  // 40-70% filled
  int numToFill = ((rand() % 31 + 40) / 100.0) * dimension * dimension;
  // cout << "numToFill " << numToFill << endl;

  while( numToFill )
  {
    int r = rand() % dimension;
    int c = rand() % dimension;
    if( !puzzle[r][c] )
    {
      puzzle[r][c] = true;
      numToFill--;
    } // if
  } // while
} // generate()

void generatePuz()
{
  puz << dimension << endl;

  for( int i = 0; i < dimension; i++ )
  {
    bool mark = false;
    int counter;
    for( int j = 0; j < dimension; j++ )
    {
      if( !mark )
      {
        if( puzzle[i][j] )
        {
          mark = true;
          counter = 0;
        } // if
      } // if first mark
      else
      {
        // still marked
        if( puzzle[i][j] )
          counter++;
        else
        {
          char c = 'A' + counter;
          puz << c;
          mark = false;
        } // else mark ends
      } // else already marked
    } // for

    if( mark )
    {
      char c = 'A' + counter;
      puz << c;
    } // if last is marked
    puz << ' ';
  } // for
  puz << endl;

  for( int i = 0; i < dimension; i++ )
  {
    bool mark = false;
    int counter;
    for( int j = 0; j < dimension; j++ )
    {
      if( !mark )
      {
        if( puzzle[j][i] )
        {
          mark = true;
          counter = 0;
        } // if
      } // if first mark
      else
      {
        // still marked
        if( puzzle[j][i] )
          counter++;
        else
        {
          char c = 'A' + counter;
          puz << c;
          mark = false;
        } // else mark ends
      } // else already marked
    } // for

    if( mark )
    {
      char c = 'A' + counter;
      puz << c;
    } // if last is marked
    puz << ' ';
  } // for
  puz << endl;
} // generatePuz()

void generateSol()
{
  sol << dimension << endl;
  for( int i = 0; i < dimension; i++ )
  {
    for( int j = 0; j < dimension; j++ )
    {
      if( puzzle[i][j] )
        sol << 'O';
      else
        sol << 'X';
    } // for
    sol << endl;
  } // for
} // generateSol()