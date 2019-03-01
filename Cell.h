#ifndef Cell_h
#define Cell_h
enum State {WHITE, BLACK, WHITEKING, BLACKKING, NONE}; //if black checker=0, white checker=1, no checkers =2

class Cell{
private:
    State state;
public:
    Cell();
    Cell(State state);
    State getState();
    void setState(State state);
};

#endif 
