#include <iostream>
#include <string>
#include "Board.h"
using namespace std;
#ifndef IOstream_h
#define IOstream_h
using movePosition = pair<pair<int,int>, pair<int, int>>;//move from position A to position B
const int BOARDSIZE=8;
class IOstream{
public:
    IOstream();
    static const movePosition& getMove(); // static because you dont need to create object to get input and output
    static void DrawBoard(unordered_map<position, Cell> &board);
private:
    static string getSymbol(State state);
};
#endif