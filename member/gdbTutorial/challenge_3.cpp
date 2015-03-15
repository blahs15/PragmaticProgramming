//Author: Raymond S. Chan
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

  int low, high, mid, num, count;
  high = 9; //size of array
  low = 0;
  num = atoi(str);
  mid = (low + high)/2;
  count = 0;

  while (low < high)
  {
    count++;
    mid = (low + high)/2;
    //cout << "low is " << low << " high is " << high 
    //     << " mid[" << mid << "] = " << data[mid] << endl;
    if (data[mid] < num) // go right
      low = (high + low)/2;
    else if (data[mid] > num) //go left
      high = (high - low)/2;
    else // can't look no more
    {
      if (data[mid] == num)
      {
        cout << "found it! with " << count << " iterations." << endl;
        break;
      }
      else
      {
        cout << ":( " << num <<" does not exist. Made "<< count << " iterations. " << endl;
        break;
      }
    }
  }   
  return 0;
}
