Pragmatic Programming
Minesweeper Solver Competition
Jan 15 ~ Jan 29, 2015
Organized by Russell Miller


void ContestInformation()
{
  A minesweeper generator is provided that will contain a minefield in memory.

  Inside the file "minesweeper.h" is a list of functions that you are allowed to use to create a function that solves the puzzle. All of the provided functions are described within that header file and perform the same actions that you would be able to do if you were solving the puzzle manually.
  You should not need to look at what is inside any of the other files to create the solver, however you are welcome to do so.

  The contest winners will be chosen based on the percentage of some chosen Advanced level minefields that are solved by their programs. To discourage random guessing, a small penalty will be given to programs that reveal a mine and lose.

  To compile the program, type "make" on the command line to run the compile lines in the Makefile.

  A few cases where the minefield would require guessing has been checked for, and is not allowed during the generation of the puzzle.

  The goal is to think about what logic is involved when solving the puzzle manually, and converting that logic into code.
  Remember to also have fun coding!
} // ContestInformation()


void SolverRules()
{
  Because there needs to be a program running in the background to check your inputs, your solver is required to be written in C++. For those that know C, but not C++, writing in C should be fine.
  This competition is mainly meant for students, but others may try to create a solver too!

  Your solver should be written in the function "solveMinesweeper()" inside "main.cpp". You may add functions, files, or classes, as you see fit.

  You should not use a random number generator to choose which squares to reveal.
  You should not modify any of the other .h or .cpp files.
} // SolverRules()


Solver Submission()
{
  I mainly require submission in order to check that the few rules above aren't violated.

  To submit your solver, I have set up a handin directory in CSIF.  Otherwise they may be emailed to me at rusmiller@ucdavis.edu.

  The files to be submitted should just be main.cpp and any other files you've created, along with a Makefile if you've modified it.

  To use handin, type the following while in CSIF:
  handin blahs15 minesweeper {files}+
} // Submission()

