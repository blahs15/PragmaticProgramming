// Written by Shyam Pinnipati, Russell Miller
// Pragmatic Programming GDB Debugging Tutorial
// Last Updated October 2014

// Breakpoints
// Breakpoint Loop Trick


// Line Numbers matter, starts at line 10
#include <iostream>
using namespace std;

void iterater(int num);
void recurser(int);
void recurser2(int); // in file pro3_1.cpp

#include "prog3_1.cpp"

int x;

int main()
{
	iterater(100);
	recurser(50);
	recurser2(50);
} // main()

void iterater(int num)
{
	for (int i = 0; i < num; ++i)
	{
		cout << i << endl;
		x = i + 1;
		i = x - 1;
	} // for
} // iterator()

void recurser(int num)
{
	if (num > 0)
	{
		cout << num << endl;
		x = num;
		num--;
		recurser(num);	
	} // if

	return;

} // recurser()
