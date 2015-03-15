// Written by Shyam Pinnipati, Russell Miller
// Pragmatic Programming GDB Debugging Tutorial
// Last Updated October 2014

// Backtrace
#include <iostream>
#include <stdlib.h>
using namespace std;

void foo1();
void foo2();
void foo3();
void foo4();

int main()
{
  foo1();
  return 0;
}

void foo1()
{
    foo2();
}

void foo2()
{
    foo3();
}

void foo3()
{
    foo4();
}

void foo4()
{
  int ar[20];
  for( int i = 0; ; i++ )
  {
    ar[i] = i * 2;
  } // for
  ar[0] = ar[0]; // to make the variable not unused
}
