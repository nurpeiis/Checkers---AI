#include "Cell.h"
#include <vector>
using namespace std;
using position = pair<int, int>; //this is not to always write, x,y coordinates
enum State {Black, White, None}; //if black checker=0, white checker=1, no checkers =2
#ifndef Board_h
#define Board_h
class Board{
private:
    vector<vector<Cell>> board[8][8];  
public:
    Board();//initialize the board where first ttthree and last three are whit and black respectively
    ~Board();
    Cell getState(position pos); // returns the state of certain cell
    void move();
    void checkMove(); // it checks if the move is correct
    void DrawBoard(); //call this function after every move is maade
    void checkWin();  //Checks if one of the player won
};

#endif 
