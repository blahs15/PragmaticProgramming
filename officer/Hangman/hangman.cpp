// Russell Miller
// Pragmatic Programming: Hour of Code Week
// December 2014

#include <iostream>
#include <cstring>

#define CHANCES 7

using namespace std;

char word[300];
bool revealed[300];
bool guessed[26];
int length;

void print();

int main()
{

  cout << "Enter a word or phrase > ";
  // cin >> word;
  cin.getline( word, 299 );

  length = strlen(word);
  char guess;
  bool done = false;
  int chancesLeft = CHANCES;

  for( int i = 0; i < length; i++ )
  {
    revealed[i] = false;
    if( word[i] == ' ' )
      revealed[i] = true;
    else if( isalpha(word[i]) )
      word[i] = tolower(word[i]);
    else
    {
      cout << "only letters and spaces are allowed, exiting program..."
           << endl;
      return 0;
    } // else num/symbol
  } // for all chars in word
  for( int i = 0; i < 26; i++ )
    guessed[i] = false;

  cout << word << endl;
  cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
  print();
  cout << "Guesses left: " << chancesLeft << endl;
  cout << "Enter guess > ";
  while( !done && cin >> guess )
  {
    if( !isalpha(guess) )
    {
      cout << guess << " is not a letter, guess again > " << endl;
      continue;
    } // if not alpha
    else
      guess = tolower(guess);

    bool foundGuess = false;
    guessed[guess - 'a'] = true;
    for( int i = 0; i < length; i++ )
    {
      if( guess == word[i] )
      {
        foundGuess = true;
        revealed[i] = true;
      } // if found
    } // for

    print();

    if( !foundGuess )
    {
      chancesLeft--;
      if( chancesLeft == 0 )
        done = true; // break
    } // if wrong
    else
    {
      bool notDone = false;
      for( int i = 0; i < length; i++ )
        if( !revealed[i] )
          notDone = true;
      if( !notDone )
        done = true;
    }
    if( !done )
    {
      cout << "Guesses left: " << chancesLeft << endl;
      cout << "Enter guess > ";
    }
  } // while guessing

  if( chancesLeft == 0 )
    cout << "You lose :(" << endl;
  else
    cout << "You win!! :D" << endl; 
  cout << "The correct answer was: " << word << endl;
} // main()

void print()
{
  for( int i = 0; i < length; i++ )
  {
    if( revealed[i] )
      cout << word[i] << " ";
    else
      cout << "_ ";
  } // for


  cout << "\n" << "Guessed: ";
  for( int i = 0; i < 26; i++ )
    if( guessed[i] )
      cout << (char) (i + 'a') << " ";
  cout << "\n\n\n";
} // print()
