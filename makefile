fonbook: main.o hashMap.o trieName.o
	g++ -o fonbook hashMap.o trieName.o main.o 
hashMap.o: hashMap.h hashMap.cpp
	g++ -c hashMap.cpp
trieName.o: trieName.h trieName.cpp
	g++ -c trieName.cpp
main.o: main.cpp
	g++ -c main.cpp
clean:
	rm *.o output
