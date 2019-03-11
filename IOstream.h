#include <iostream>
#include <string>
#include "Board.h"
using namespace std;

#ifndef IOstream_h
#define IOstream_h

using movePosition = pair<pair<int,int>, pair<int, int>>;//move from position A to position B

class IOstream{
public:
    IOstream();
    static movePosition getMove(); // static because you dont need to create object to get input and output
    static void DrawBoard(Unordered_map &board);
private:
    static string getSymbol(State state);
};
#endif