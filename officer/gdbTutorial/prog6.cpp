// Written by Russell Miller
// Pragmatic Programming GDB Debugging Tutorial
// Last Updated October 2014

// NULL Pointers
#include <iostream>
using namespace std;

int main()
{
  int num;
  int num2 = 10;
  int arr[10];
  int *ptr;
  int *ptr2Arr = new int[10];
  int *ptr3 = NULL;

  for( int i = 0; i < 10; i++ )
  {
    arr[i] = i;
    ptr2Arr[i] = i;
  } // for

  cout << "num " << num << endl;
  cout << "num2 " << num2 << endl;
  cout << "arr " << arr << endl;
  cout << "*arr " << *arr << endl;
  cout << "ptr " << ptr << endl;
  cout << "*ptr " << *ptr << endl;
  cout << "ptr2Arr " << ptr2Arr << endl;
  cout << "*ptr2Arr " << *ptr2Arr << endl;
  cout << "ptr3 " << ptr3 << endl;
  cout << "*ptr3 " << *ptr3 << endl;
} // main()