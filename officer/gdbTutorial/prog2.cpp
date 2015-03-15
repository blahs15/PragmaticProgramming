// Written by Russell Miller
// Pragmatic Programming GDB Debugging Tutorial
// Last Updated October 2014

// core Files
// Printing
#include <iostream>

using namespace std;

int foo( int a )
{
  return a * 2;
} // foo

int main()
{
  int ar[20];
  for( int i = 0; ; i++ )
  {
    ar[i] = foo(i);
  } // for
  ar[0] = ar[0]; // to make the variable not unused
  cout << endl;
} // main
