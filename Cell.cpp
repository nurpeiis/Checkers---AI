#include "Cell.h"
using namespace std;
Cell::Cell(){
    this->state= NONE;
}
Cell::Cell(State state){
    this->state=state;
}
State Cell::getState(){
    return this->state;
}
void Cell::setState(State state){
    this->state=state;
}
