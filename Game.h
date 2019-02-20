#include "Board.h"
#include "IOstream.h"
using namespace std;
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
    Player getWinner();
    void start();
};

#endif 
