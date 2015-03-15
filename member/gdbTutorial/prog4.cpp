// Written by Russell Miller
// Pragmatic Programming GDB Debugging Tutorial
// Last Updated October 2014

// Step, Next
// Display


// Line Numbers matter, starts at line 10
#include <iostream>
using namespace std;


void foo1( int x );
void foo2( int x );
void foo3( int x );
void foo4( int x );

int a, b, c, d;

int main()
{
  a = b = c = d = 0;

  foo1( 0 );
  foo1( 1 );
  foo1( 2 );
} // main()

void foo1( int x1 )
{
  x1++;
  a += x1;
  cout << "a = " << a << endl;
  foo2( x1 );
  cout << "foo1" << endl;
} // foo1

void foo2( int x2 )
{
  x2++;
  b += x2;
  cout << "b = " << b << endl;
  foo3( x2 );
  cout << "foo2" << endl;
} // foo2

void foo3( int x3 )
{
  x3++;
  c += x3;
  cout << "c = " << c << endl;
  foo4( x3 );
  cout << "foo3" << endl;
} // foo3

void foo4( int x4 )
{
  x4++;
  d += x4;
  cout << "d = " << d << endl;
  cout << "foo4" << endl;
} // foo4
