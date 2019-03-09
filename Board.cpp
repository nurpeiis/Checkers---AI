#include "Board.h"
#include <iostream>
using namespace std;
void Board::setBoard(){
    for (int i =0; i<BOARDSIZE; i++){
        for (int j=0; j<BOARDSIZE; j++){
            position pos=position(i,j);
            Cell cell;
            if((i==0 || i==2) && j%2==0)
                cell.setState(State::BLACK);
            else if(i==1  && j%2!=0)
               cell.setState(State::BLACK);
            else if((i==5||i==7)  && j%2!=0)
                cell.setState(State::WHITE);
            else if(i==6 && j%2==0)
                cell.setState(State::WHITE);
            else
                cell.setState(State::NONE);
            board.insert({pos, cell});
        }
    }
}

MoveType Board::checkMove(position start, position end, Player player)
{
    State sign [3] = {State::BLACK, State::WHITE, State::NONE};
    int index = player == Player::BLACKK ? 0:1;
    //define directionalities
    if(board.at({start.first,start.second}).getState() == sign[index]){
        if(abs(start.first - end.first) == 1 && abs(start.second - end.second) == 1){
            if(board.at({end.first, end.second}).getState() == sign[2]){
                return MoveType::USUAL;
            }
            else 
                return MoveType::PROHIBITED;
        }
        else if (abs(start.first - end.first) == 2 && abs(start.second - end.second) == 2){
            if (board.at({end.first, end.second}).getState() == sign[2]){
                int midR = abs(start.first + end.first)/2;
                int midC = abs(start.second + end.second)/2;
                if(board.at({midR, midC}).getState() == sign[1-index]){
                    return MoveType::COMBAT;
                }
                else 
                    return MoveType::PROHIBITED;
            }
            else 
                return MoveType::PROHIBITED;
        }
        else
            return MoveType::PROHIBITED;
    }
    else 
        return MoveType::PROHIBITED;
}


MoveType Board::move(position start, position end, Player player)
{
    MoveType moveResult = checkMove(start, end, player);

    if (moveResult == USUAL)
    {
        board.at(end).setState(board.at(start).getState());
        board.at(start).setState(NONE);
    }

    if (moveResult == COMBAT)
    {
        position middlePos((start.first + end.first) / 2, (start.second + end.second) / 2);
        board.at(end).setState(board.at(start).getState());
        board.at(middlePos).setState(NONE);
        board.at(start).setState(NONE);
        cout << "Congrats! You ate the other player\n";
    }
    else if (moveResult == PROHIBITED)

    {
        cout << "This move is not allowed. Try again :(\n";
    }
    return moveResult;

}

const Unordered_map& Board::getBoard(){
    return this -> board;
}