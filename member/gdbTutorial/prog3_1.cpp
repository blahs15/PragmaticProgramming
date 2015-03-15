// Written by Shyam Pinnipati
// Pragmatic Programming GDB Debugging Tutorial
// Last Updated October 2014

// Breakpoints
// Breakpoint Loop Trick


// Line Numbers matter, starts at line 10
void recurser2(int num)
{
	if (num > 0)
	{
		cout << num << endl;
		num--;
		recurser2(num);	
	} // if

	return;

} // recurser2()
