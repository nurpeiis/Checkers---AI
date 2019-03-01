#include "Board.h"

#include <unordered_map>


#ifndef MiniMax_h
#define MiniMax_h


class MiniMax{
private:
    Player checkEnd(Unordered_map board); 
    //WHITEE - white winner BLACKK - black winner, TIE - no one won = non existant condition, NONE - continue playing no one won
    string getBoardstate(Unordered_map board);
    //vector<Unordered_map> possibleMoves(Unordered_map board); 
    long long hashFunction(string base3);
public:
friend class Game;
};
#endif 
