minesweeper.out: main.o minesweeper.o square.o mysquare.o
	g++ -Wall -g -o minesweeper.out main.o minesweeper.o square.o mysquare.o

main.o: main.cpp minesweeper.h
	g++ -Wall -g -c main.cpp

minesweeper.o: minesweeper.cpp minesweeper.h square.h
	g++ -Wall -g -c minesweeper.cpp

square.o: square.cpp square.h
	g++ -Wall -g -c square.cpp

mysquare.o: mysquare.cpp mysquare.h
	g++ -Wall -g -c mysquare.cpp

clean:
	rm -f minesweeper.out main.o minesweeper.o square.o core mysquare.o
