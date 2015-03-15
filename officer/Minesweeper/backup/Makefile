minesweeper.out: main.o minesweeper.o square.o
	g++ -Wall -g -o minesweeper.out main.o minesweeper.o square.o

main.o: main.cpp minesweeper.h
	g++ -Wall -g -c main.cpp

minesweeper.o: minesweeper.cpp minesweeper.h square.h
	g++ -Wall -g -c minesweeper.cpp

square.o: square.cpp square.h
	g++ -Wall -g -c square.cpp

clean:
	rm -f minesweeper.out main.o minesweeper.o square.o core
