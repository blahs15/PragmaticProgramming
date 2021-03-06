// Author: Raymond S. Chan
#include <iostream>
#include <string.h>
#include <stdlib.h>

using namespace std;

int main(void)
{
  //Micheal's read input segment
  int data[10];
  char * str = new char[255];
  cin >> str;
  data[0] = atoi(strtok(str,";"));
  cout << "Read in numbers: ";
  for (int i = 1; i < 10; i++ )
  {
    data[i] = atoi(strtok(NULL,";"));
    cout << data[i-1] << " ";
  }
  cout << data[9] << " end" << endl;
  
  cout << "Search for ... ";
  cin >> str;
  cout << "Looking for ... " << str << endl;

  int low, high, mid, num;
  high = 9;
  low = 0;
  num = atoi(str);
  mid = (low + high)/2;

  while (low < high)
  {
    //cout << "low is " << low << "high is " << high << " mid[" << mid << "] = " << data[mid] << endl;
    mid = (low + high)/2;
    if (mid < num) // go right
      low = (high + low)/2;
    else if (mid > num) //go left
      high = (high - low)/2;
    else // low == high == mid
      if (data[mid] == num)
        cout << "found it!" << endl;
      else
        cout << ":(" << endl;
  }   
  return 0;
}
