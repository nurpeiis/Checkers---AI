#include "IOstream.h"
using namespace std;
const movePosition & IOstream::getMove(){
    movePosition position;
    int p1, p2;
    cin >> p1;
    cin >> p2;
    //start position
    position.first.first = p1/10;
    position.first.second = p1 - 10*position.first.first;
    //end position
    position.second.first = p2/10;
    position.second.second = p2 - 10*position.second.first;
    return position;
}

void IOstream::DrawBoard(unordered_map<position, Cell> &board){
    for (int i = 0; i<BOARDSIZE; i++){
        cout<<"|";
        for (int j = 0; j<BOARDSIZE; j++){
            State state = board.at(position({i, j})).getState();
            cout<< getSymbol(state)<< "|";
        }
        cout<<endl;
    }
}
string IOstream::getSymbol(State state){
    if (state == NONE)
        return " ";
    else if (state == BLACK)
        return "b";
    else if (state == WHITE)
        return "w";
}