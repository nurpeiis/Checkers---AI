#include "Board.h"
#include "IOstream.h"
#include "MiniMax.h"

#ifndef Game_h
#define Game_h

class Game{//it will get inputs and outputts
private:
    int whiteScore;
    int blackScore;
    Player currentPlayer;
    bool surrender;
    Board board;
    IOstream io;
    movePosition makeIO();
    Player getPlayer();
    void switchPlayer();
    void updateScores();
public:
    Game();
    const Player& getWinner(Unordered_map board);
    void start();
};

#endif 
