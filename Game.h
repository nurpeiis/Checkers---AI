#include "Board.h"
#include "IOstream.h"
using namespace std;
#ifndef Game_h
#define Game_h
class Game{//it will get inputs and outputts
private:
    int whiteScore;
    int blackScore;
public:
    Game();
    Player getWinnner();
};

#endif 
