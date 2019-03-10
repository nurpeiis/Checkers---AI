#include "Board.h"
#include "IOstream.h"
#include "MiniMax.h"

#ifndef Game_h
#define Game_h

class Game{//it will get inputs and outputts
private:
    Player currentPlayer;
    Board board;
    movePosition makeIO();
    Player getPlayer();
    void switchPlayer();
    Player getWinner(Unordered_map board);
public:
    Game();
    void start();
};

#endif 
