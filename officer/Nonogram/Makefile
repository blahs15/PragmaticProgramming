all: nonoChecker.out nonoGen.out nonoSolver.out

nonoChecker.out: nonogramChecker.cpp
	g++ -Wall -o nonoChecker.out nonogramChecker.cpp

nonoGen.out: nonogramGen.cpp
	g++ -Wall -o nonoGen.out nonogramGen.cpp

nonoSolver.out: nonoSolver.cpp
	g++ -Wall -o nonoSolver.out nonoSolver.cpp

clean:
	rm -f nonoChecker.out nonoGen.out nonoSolver.out core *.o