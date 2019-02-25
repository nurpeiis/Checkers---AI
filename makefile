checkers: main.o Cell.o Board.o Game.o IOstream.o
	g++ -o checkers main.o Cell.o Board.o Game.o IOstream.o
Cell.o: Cell.h Cell.cpp
	g++ -c Cell.cpp -std=c++11
Game.o: Game.h Game.cpp
	g++ -c Game.cpp -std=c++11
Board.o: Board.h Board.cpp
	g++ -c Board.cpp  -std=c++11
IOstream.o: IOstream.h IOstream.cpp
	g++ -c IOstream.cpp  -std=c++11
main.o: main.cpp
	g++ -c main.cpp  -std=c++11
clean:
	rm *.o output
