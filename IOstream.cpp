#include "IOstream.h"
using namespace std;
IOstream::IOstream(){

}
movePosition IOstream::getMove(){
    movePosition positionn;
    int p1, p2;
    cin >> p1;
    cin >> p2;
    //start position
    positionn.first.first = p1/10;
    positionn.first.second = p1 - 10*positionn.first.first;
    //end position
    positionn.second.first = p2/10;
    positionn.second.second = p2 - 10*positionn.second.first;
    return positionn;
}

void IOstream::DrawBoard(Unordered_map &board){
    cout<<" |0|1|2|3|4|5|6|7|"<<endl;
    for (int i = 0; i<BOARDSIZE; i++){
        cout<<i<<"|";
        for (int j = 0; j<BOARDSIZE; j++){
            State state = board.at(position({i, j})).getState();
            cout<< getSymbol(state)<< "|";
        }
        cout<<endl;
    }
    cout<<endl;
}
string IOstream::getSymbol(State state){
    if (state == NONE)
        return " ";
    else if (state == BLACK)
        return "b";
    else if (state == WHITE)
        return "w";
    else if (state == BLACKKING)
        return "B";
    else if (state == WHITEKING)
        return "W";
}