#include "Cell.h"

Cell::Cell(){
    this->state= NONE;
}
Cell::Cell(State state){
    this->state=state;
}
const State& Cell::getState(){
    return this->state;
}
void Cell::setState(State state){
    this->state=state;
}
