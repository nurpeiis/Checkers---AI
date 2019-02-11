#include <iostream>
#include "Board.h"
using namespace std;
#ifndef Game_h
#define Game_h
enum Player {WHITE, BLACK};
class Game{//it will get inputs and outputts
private:
    Board board;
public:
    Game();
    ~Game();
    State getState();
    void DrawBoard(); //call this function after every move is maade
    void updateState(State state);
};

#endif 
