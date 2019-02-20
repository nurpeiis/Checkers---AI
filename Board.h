#include "Cell.h"
#include <unordered_map>
using namespace std;
#ifndef Board_h
#define Board_h
using position = pair<int, int>; //this is not to always write, x,y coordinates
enum MoveType {USUAL, COMBAT, PROHIBITED}; //if black checker=0, white checker=1, no checkers =2
enum Player {BLACKK, WHITEE, NONEE}; 
const int BOARDSIZE=8;
struct pairhash {
public:
  template <typename T, typename U>
  std::size_t operator()(const std::pair<T, U> &x) const
  {
    return std::hash<T>()(x.first) ^ std::hash<U>()(x.second);
  }
};

using Unordered_map = std::unordered_map<position, Cell, pairhash>;

class Board{
private:
    Unordered_map board; 
    int noWhite;
    int noBlack;//number of black cells
    MoveType checkMove(position start, position end, Player player); // it checks if the move is correct, it does not need to be pubblic, as is used by the program whenver user makes move
    //in the direction of black means it is moving downwards=  
public:
    Board();//initialize the board where first three and last three are whit and black respectively
    void setBoard(); //call this function after every move is maade
    MoveType move(position start, position end, Player player);
    void checkWin();  //Checks if one of the player won
    Unordered_map getBoard();
};

#endif 
