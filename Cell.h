using namespace std;
enum State {Black, White, None}; //if black checker=0, white checker=1, no checkers =2
#ifndef Cell_h
#define Cell_h
class Cell{
private:
    State state;
public:
    Cell();
    Cell(State state);
    ~Cell();
    State getState();
    void updateState(State state);
};

#endif 
