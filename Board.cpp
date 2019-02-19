#include "Board.h"
#include <iostream>
using namespace std;
Board::Board(){
    for (int i =0; i<8; i++){
        for (int j=0; j<8; j++){
            position pos=position(i,j);
            Cell cell;
            if((i==0 || i==2) && j%2==0)
                cell.setState(State::BLACK);
            else if(i==1  && (j+1%2)==0)
                cell.setState(State::BLACK);
            else if((i==5||i==7)  && (j+1%2)==0)
                cell.setState(State::WHITE);
            else if(i==6&& j%2==0)
                cell.setState(State::WHITE);
            else
                cell.setState(State::NONE);
            board.insert({pos, cell});
        }
    }
}
void Board::setBoard(){
    for (int i =0; i<BOARDSIZE; i++){
        for (int j=0; j<BOARDSIZE; j++){
            position pos=position(i,j);
            Cell cell;
            if((i==0 || i==2) && j%2==0)
                cell.setState(State::BLACK);
            else if(i==1  && j%2==1)
                cell.setState(State::BLACK);
            else if((i==5||i==7)  && j%2==1)
                cell.setState(State::WHITE);
            else if(i==6&& j%2==0)
                cell.setState(State::WHITE);
            else
                cell.setState(State::NONE);
            board.insert({pos, cell});
        }
    }
    noWhite=12;
    noBlack=2;
}
MoveType Board::checkMove(position start, position end, Player player){
    if (end.first>7 || end.second>7)// cannot go outside
        return PROHIBITED;
    else{
        int xDiff = abs(start.second - end.second); //you can move either to left or right- doesnt really matter
        int yDiff = end.first - start.first;
        MoveType move=PROHIBITED;
        if(board.at(end).getState() == NONE){
            position middlePos((start.first+end.first)/2, (start.second+end.second)/2);
            State middleState = board.at(middlePos).getState();
            State startState = board.at(start).getState();
            if(xDiff==2 && abs(yDiff)==2){
                if(startState!=middleState && middleState!=NONE)
                    move = COMBAT;
            }    
            else if((xDiff==1 && yDiff==1 && player==Player::BLACKK) || (xDiff==1 && yDiff==-1 && player==Player::WHITEE)){
                move = USUAL;
            }
        }
        return move;
    }
}

MoveType Board::move(position start, position end, Player player){
    MoveType moveResult=checkMove(start, end,player);
    if (moveResult==USUAL){
        board.at(end).setState(board.at(start).getState());
        board.at(start).setState(NONE);
    }
    else if (moveResult==COMBAT){
        board.at(end).setState(board.at(start).getState());
        board.at(start).setState(NONE);
        position middlePos((start.first+end.first)/2, (start.second+end.second)/2);
        board.at(middlePos).setState(NONE);
    }
    return moveResult;
}

Unordered_map Board::getBoard(){
    return this -> board;
}