#include "Board.h"
#include <unordered_map>

#ifndef MiniMax_h
#define MiniMax_h

class MiniMax{
private:
    unordered_map<long long, int> hashTable; //stores points for states, so that you do not need to calculate every time 
    //Points: black = +1, white = -1 
    //String Board State: 0 - none, 1 - black , 2 - white
public:
friend class Game;

private:
    Player checkEnd(Unordered_map board); 
    //WHITEE - white winner BLACKK - black winner, TIE - no one won = non existant condition, NONE - continue playing no one won
    vector<Unordered_map> possibleMoves (Unordered_map board, Player player);
    string getBoardstate(Unordered_map board, Player player);
    long long hashFunction(string boardState);
    int assignPoints (string boardState);
    void populateHashTable(Unordered_map board, Player player);
    int findPoint(string boardState);
};
#endif 
