#include "Board.h"
#include <unordered_map>
#include "IOstream.h"

#ifndef MiniMax_h
#define MiniMax_h

class MiniMax{
private:
    unordered_map<long long, double> hashTable; //stores points for states, so that you do not need to calculate every time 
    unordered_map<long long, movePosition> moveTable;
    //Points: black = +1, white = -1 
    //String Board State: 0 - none, 1 - black , 2 - white
public:
    double explore(Unordered_map board, Player player);
    friend class Game;

private:
    Player checkEnd(Unordered_map board); 
    //WHITEE - white winner BLACKK - black winner, TIE - no one won = non existant condition, NONE - continue playing no one won
    string getBoardstate(Unordered_map board, Player player);
    long long hashFunction(string boardState);
    double assignPoints (string boardState);
    double theoreticalMax (string board);
    double theoreticalMin (string board);
    double evaluatePoints (string board);
    bool valid(int r, int c);
    void update(Unordered_map& nextBoard, long long key, Player player, double& current_point, movePosition & move);
    Unordered_map nextState (Unordered_map currentBoard, movePosition move, State change);
};
#endif 
