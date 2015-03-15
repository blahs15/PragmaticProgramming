Pragmatic Programming GDB Debugging Tutorial
Last Updated January 2015
Made by: Russell Miller, Shyam Pinnipati
In Collaboration with: Raymond Chan, Michael Lu

-What is GDB?
Short for GNU Debugger, it helps a programmer debug their code. Some supported lanuages include C, C++, Java, and Objective-C.
http://en.wikipedia.org/wiki/GNU_Debugger

-What problems can GDB help me debug?
Segmentation Faults (seg faults)
tracking variables
other runtime errors
GDB can also be compared to other debuggers, as many of them have similar capabilities like printing variables and breakpoints.

-How does it work? (short summary)
While a compiler helps find problems before your program is run, a debugger can help you find problems _while_ the program is being run. A runtime error can occur consistantly and/or can sometimes occur only with certain inputs. 


-Table of Contents:
0: compiling
--GDB controls
1: Starting GDB
2-1: core Files
2-2: printing
3-1: breakpoints
4-1: step, next
4-2: display
5: backtrace <-- one of the most useful commands
Help: Need more help? Enter "help" into gdb.
--GDB Tips and Tricks
3-2: Breakpoint Loop Trick
6: Null Pointers
GDB commands summary


-Prog0: compiling
0.1) First, compile the file using the following line:
g++ -Wall prog0.cpp
0.2) You should get a compile error.  Go ahead and edit the file to fix the error.
(hint: add a semicolon on the line suggested in the compile error)
0.3) Try compiling again. Hopefully it will have no output when it compiles correctly.


--GDB CONTROLS


-Prog1: Starting GDB
1.1) First, compile the program using the following line: (different than before!)
g++ -Wall prog1.cpp -g
Notice the "-g" flag. Basically, this flag is REQUIRED when compiling if you want to use gdb. Feel free to ask if you want to know why.
1.2) To start gdb, type "gdb [executable]":
gdb a.out
This will open up the program in the gdb interface.
1.3) To start the program, enter "r" (run)
1.4) CALM DOWN
1.5) Take a deeeeeep breath
1.6) Are you having fun?
1.7) No? :(
1.8) Would you like it to stop?
1.9) Try typing ctrl+c
1.10) This stops the program, but in gdb, it doesn't actually end the program. It's still running, but it's frozen in place where you stopped it.
Enter "k" to end the program (kill)
1.11) Now to exit gdb, enter "q" (quit)
(you don't need to fix the program, you can just move on)


-Prog2: core files
(On some computers, core files are not created. If that's the case, don't worry, but it may still be good to understand what they are. There are some benefits to not using them anyway.)
2.1) compile the program:
g++ -Wall -g prog2.cpp
2.2) The program should work perfectly. We are all very good programmers, there shouldn't be any errors.
Run the program:
a.out
2.3) ...What? seg fault?!? *flips table*
A seg fault occurs when the program is trying to access memory space that it isn't supposed to have access to.  Luckily, *puts table back*, seg faults are actually the easier kind of bug to fix.
2.4) If you look at the files in the directory, there should now be a new file called "core":
enter "ls"
Core files are created when your program doesn't end normally. They save the current state of your program, like all the variable values, what function you're in, etc.
2.5) In order to look at the state of the program when it stopped, enter gdb with the core file using "gdb [executable] core":
gdb a.out core
2.6) In the giant jumble of text that appears, hopefully you'll notice a line of code from the program. This line is where the seg fault occurred.
This is what the core is most useful for, finding out where the error is occurring, so you can examine that area with other gdb commands to isolate the bug.


-Prog2 part2: printing
2.7) To print the variable values, you use "p [variable]" (print)
This print is actually very powerful, you can print variable values, values at a specific index in an array, an entire array, a dereferenced pointer, and even a function call.
Some restrictions apply when using a core file. To get around these, rerun the program.
enter "r"
p ar -- print the array ar
p i -- print the value stored in i
p *ar -- print the value in the 0th index of ar (same as ar[0])
p ar[15] -- print the value in the 15th index of ar
p foo(i) -- print the return value from the function foo()
2.8) Now that you know the variable values, but without knowing what the surrounding code is, you still can't fix it.
Enter "l" (List)
List will show 10 lines surrounding the line you're on.
2.9) Try and spot the bug on your own if you want.
2.10) [Spoiler] Notice the size of the array is 20, meaning the max index value should be 19. The best way to fix the error is to make the condition in the for() loop "i < 20".
2.11) Now that you've located the bug, you can quit gdb using the "q" command and edit the code. For this tutorial, you can just move on to the next step instead of fixing the code.
2.12) Lastly, core files can take up a massive amount of memory. You should remember to remove the core files when they're no longer needed.
rm core


-Prog3: breakpoints
3.1) compile the program:
g++ -Wall -g prog3.cpp
There are 2 files included in this program. "prog3.cpp" and "prog3_1.cpp"
3.2) This program won't have any bugs that will end the program. Without an official problem ending the program mid-run, how can you try to track the variables? (You may need to do this if the output isn't correct, but everything "works.")
The solution is to use breakpoints.
Breakpoints can be attached to lines of code so that whenever the program is about to execute that line of code, it will stop so the user can examine the program's state during runtime.
3.3) Start gdb:
gdb a.out
3.4) Insert your first breakpoint at line 32:
Enter "b 32"
Line 31 is a print statement inside a for loop:
31: cout << i << endl;
3.5) run the program
Enter "r"
3.6) The program should immediately stop when the program reaches line 32. While the program is stopped, you can perform commands like printing the current variables.
3.7) Now that you've stopped your program, and looked at whatever variables you wanted to, it might be good to continue running your program.
Enter "c" (continue)
Continue will make the program continue to run as it normally would until it hits the next breakpoint, ends, or a runtime error occurs.
3.8) The program should have stopped again at the same line, since you're in a loop. But now if you print the variables again, some of their values may have changed.
3.9) Go ahead and continue a few more times. A shortcut in gdb is that if you press enter with no input, it will repeat the last command you entered.  Press enter a few more times.
3.10) This for loop is realllyy long, isn't it? You can enter "L" to see it.  How about we delete this breakpoint so that we can continue on to the next part of the program?
Enter "d 1" (delete breakpoint 1)
3.11) Now, before continuing, let's insert a breakpoint into the 2nd part of the program. (If you didn't insert the breakpoint before continuing, you can insert the breakpoint and run the program again by entering "r")
Enter "b 42" (insert breakpoint at line 42)
3.12) Continue the program by entering "c"
3.13) This breakpoint is inside a recursive function: it's continuously calling itself.
3.14) Continue the program a few more times, feel free to look at the code with "L" (list) and "p [var]" (print).
3.15) One thing to notice is that at every breakpoint, it shows the parameter values of the current function. Since it's a recursive function, it's always changing.
3.16) Let's delete that breakpoint and enter a 3rd one.
Enter "d 2" (delete breakpoint 2)
3.17) If you look at the code (or just trust what I'm saying), the third function, recurser2(int) isn't in the file! If it's not in the current file, how would you insert a breakpoint without the line number?
There are 2 ways around this:
1. You can insert a breakpoint by naming the function. Then once you stop at the function, you can insert more breakpoints anywhere in that file.
2. You can insert a breakpoint by specifying the file name.
Let's do both:
Enter "b recurser2" (breakpoint at the top of the function "recurser2")
Enter "b prog3_1.cpp:14" (breakpoint in file prog3_1.cpp at line 14)
3.18) Go ahead and continue the program some more, and print out more values.
3.19) quit gdb with "q" whenever you want. The breakpoints will be deleted and the program will be killed for you.


[Prog3 part2: breakpoint loop trick -- moved to Tips and Tricks]


-Prog4: step, next
4.1) Compile the program:
g++ -Wall -g prog4.cpp
4.2) program summary:
This program simply calls foo1() which calls foo2() which calls foo3() which calls foo4().  Then it returns and repeats this 3 times.  The calculations made aren't important at the moment, they are more to take up space.
4.3) Enter gdb:
gdb a.out
4.4) Insert a breakpoint in foo1:
Enter "b foo1"
4.5) Run the program
Enter "r"
4.6) Other than the continue command (c), there are 2 other commands that allow you to go through your program slowly:
s (step) - continue to the next line of code being executed
n (next) - continue to the next line of code being executed in the current function
4.7) Step through the program a little bit: (Refer to step 3.9 for a small shortcut.)
Enter "s" 
Notice that you are starting inside the function foo1().
As you step through the program, you will eventually go inside foo2() and be able to print out any variables you'd like. Stepping through the program using "s" will let you go inside all of the function calls, and eventually returning to the previous function.
4.8) After a while, you may decide you don't care what's happening inside foo3() or something. If you are inside foo2(), you can use the command next:
Enter "n" (next)
When you get to the line:
  foo3( x );
Instead of going inside the function foo3(), you will instead just go to the line right after it:
  cout << "foo2" << endl;
4.9) Stepping through your program using these commands can help determine the details of an error, like by looking at how variables are changing.
It can help when you believe a specific area of the code is causing a problem instead of just a specific line.


-Prog4 part2: display, undisplay
4.10) What if you wanted to continuously look at a variable as you step through your code? You could print out the variable every time you make a step, but then you don't get to use the shortcut mentioned in step 3.9.
4.11) Restart the program in gdb:
gdb a.out
Enter "b 32"
Enter "r"
4.12) The command to display variables is similar to that of print:
Enter "disp x1" - (display variable x1)
Enter "disp a"
Enter "disp b"
Enter "disp c"
4.13) Step through the program a few times using "s"
4.14) Notice that on every step, the values stored in x1, a, and b are displayed automatically.
4.15) However, when you step into the next function foo2(), x1 disappears. This occurs because x1 is a local variable which is no longer available inside any other function besides foo1().
4.16) Step through the program some more.
4.17) Let's say you're getting tired of looking at all these variables at every step. Why don't we stop displaying some of them:
Enter "undisp 2" - (stop displaying variable a)
Enter "undisp 4"
4.18) Now if you step through the program again, those variables will stop showing up.
4.19) When finished, quit gdb with "q"


-prog5: backtrace
5.1) Compile the program:
g++ -Wall -g prog5.cpp
5.2) Run the program:
a.out
5.3) Oh. A seg fault. How about we look at the core file:
gdb a.out core
5.4) Now we may have the line that causes the program to stop, we might not know what functions have been called when maybe they shouldn't have. Or perhaps one of the values being passed into a function is causing a problem.
5.5) To find what functions have been called, we use backtrace:
Enter "bt"
5.6) You can use "up" to go back out to a previous function and look at the local variables of the previous function:
Enter "up"
5.7) You can go up all the way to the main() function:
Enter "up"
Enter "up"
Enter "up"
5.8) Now you're in the main function. But you've gone too far!
Go back down to inner function:
Enter "down"
Enter "down"
5.9) These tools -- backtrace, up, and down -- are some of the most non-obviously useful tools for debugging. Backtrace helps find the root of the problem. Up and Down help navigate to previous functions, checking variables and parameters. Sometimes the seg fault occurs in functions that you didn't write, but the problem originated in the arguments you passed into them.


Help:
Need more help? Enter "help" into gdb.


--TIPS AND TRICKS


-Prog3 part2: breakpoint loop trick
3.19) Let's say you want to check an error with your loop, but you don't want to iterate through hundreds of breakpoint stops to get to a specific condition where your program runs into problems.
3.20) For this example, let's say you believe there's a problem whenever the value of i is 67. You can insert a breakpoint in the loop and interate through it, orrrr......
3.21) Edit the prog3.cpp file, and add the following at the beginning of, and inside the for loop:
if( i == 67 )
  cout << "here" << endl;
3.22) Now remember to compile the code again, and enter gdb:
g++ -Wall -g prog3.cpp
gdb a.out
3.23) insert a breakpoint at the new cout line:
Enter "b [line#]"
3.24) run the program:
Enter "r"
3.25) Now you've stopped at the 67th iteration of the loop without having to continue 67 times. Remember that a condition for your breakpoint can be anything you want.
3.26) You can now quit ("q") gdb again and move on.


-Prog6: Null Pointers
6.1) A common issue in programs is calling pointers that are pointing to the wrong spot. As you (should) know, pointers contain the address which contains the value that you are using. 
6.2) Most debuggers aren't very good at determining whether the pointer is pointing to the intended location.  But they can tell you if a pointer points to nothing, or NULL.
6.3) Compile the program:
g++ -g prog6.cpp
(There are warnings when compiling, I'm ignoring them for this)
6.4) Enter gdb:
gdb a.out
Run the program:
Enter "r"
6.5) It seg faulted, but print all the variables to see how things turn out:
6.6) Enter "p [var]" for the next few steps
6.7) p num - This is uninitialized, it may be 0 or a random number
6.8) p num2 - This prints out 10
6.9) p arr - This prints out all the values in the array
6.10) p *arr - This prints the first value in the array. Same as arr[0]
6.11) p ptr - This pointer is uninitialized, it may have a random address
6.12) p *ptr - This dereferences the random address, which will have a random value.
6.13) p ptr2Arr - This prints out the address of the begginning of the array. It's different from arr because it's allocated with "new"
6.14) p *ptr2Arr - This prints out the first value in the array. Same as ptr2Arr[0]
6.15) p ptr3 - This prints out "0x0". ptr3 was set to NULL, meaning it points at nothing. "0x0" is the number 0 is hexadecimal.
6.16) p *ptr3 - This returns an error because you aren't allowed to access a NULL address.
6.17) Accessing a NULL address is a commonly encountered problem that causes a Seg fault. Using GDB can help pinpoint faultily assigned pointers very quickly.



--CONTROLS SUMMARY
GNU DEBUGGER (gdb) CONTROLS

gcc –g = compile with –g to use gdb
gdb a.out = start with gdb
gdb a.out core = start with gdb at last (seg) fault/runtime error

Commands: (not case sensitive)
h = help = see gdb related commands
r = run = start program
bt = backtrace = where the error in the program occurred
up = up = go up one function
down = down = go down one function
l NN = list = show code around line NN (NN not needed)
l func = list = show code around function func
p var = print = print what is stored in variable var
b NN/func = breakpoint = add a pause at line NN or function func
d N = delete = delete breakpoint # N
n = next = execute up to next line in the current function
s = step = execute up to next line (can be within another function)
-- will tell you values of parameters
c = continue = run until next breakpoint
disp var = display = show variable var at each step
undisp N = undisplay = stop showing displayed var #N at each step
k = kill = stop/terminate/kill the running program
q = quit = quit gdb
