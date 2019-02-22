#include "Board.h"
#include <iostream>
using namespace std;
Board::Board(){

}
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
    noWhite=12;
    noBlack=2;
}
/*
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
            else if((xDiff==1 && yDiff==-1 && player==Player::BLACKK) || (xDiff==1 && yDiff==1 && player==Player::WHITEE)){
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
*/
bool JustCrowned = 0;
MoveType Board::checkMove(position start, position end, Player player)
{
    int xDiff = abs(start.second - end.second); //you can move either to left or right- doesnt really matter
    int yDiff = end.first - start.first;
    MoveType move;
    State state = NONE;
    if ((player == Player::WHITEE) && (state == State::WHITE))
    {
        if ((board.at(end).getState() == NONE) && (xDiff == 1) && (yDiff == 1))
        {
            if (end.second == 7)
            {
                JustCrowned = true;
                move = USUAL;
            }
            else
            {
                JustCrowned = false;
                move = USUAL;
            }
        }
        else if ((board.at(end).getState() == NONE) && (xDiff == 2) && (yDiff == 2) && CheckIfValidJump(start, end))
        {
            if (end.first == 7)
            {
                JustCrowned = true;
                move = COMBAT;
            }
            else
            {
                JustCrowned = false;
                move = COMBAT;
            }
        }
        else
        {
            return (move = PROHIBITED);
        }
    }
    else if ((player == Player::WHITEE) && (state == State::WHITEKING))
    {
        if ((board.at(end).getState() == NONE) && (xDiff == 1) && ((yDiff == 1) || (yDiff == -1)))
        {
            JustCrowned = false;
            move = USUAL;
        }
        else if ((board.at(end).getState() == NONE) && ((xDiff == 2) && (yDiff == 2)) && CheckIfValidJump(start, end) == 1)
        {
            JustCrowned = false;
            move = COMBAT;
        }
        else
        {
            move = PROHIBITED;
        }
    } //end of if WhiteKing
    else if ((player == Player::BLACKK) && (state == State::BLACK))
    {
        if ((board.at(end).getState() == NONE) && (xDiff == 1) && ((yDiff == -1)))
        {
            if (end.second == 0)
            {
                JustCrowned = true;
                move = USUAL;
            }
            else
            {
                JustCrowned = false;
                move = USUAL;
            }
        }
        else if ((board.at(end).getState() == NONE) && (xDiff == 1) && (yDiff == -2) && CheckIfValidJump(start, end) == 1)
        {
            if (end.second == 0)
            {
                JustCrowned = true;
                move = COMBAT;
            }
            else
            {
                JustCrowned = false;
                move = COMBAT;
            }
        }
        else
        {
            move = PROHIBITED;
        }
    }

    else if ((player == Player::BLACKK) && (state == State::BLACKKING))
    {
        if ((board.at(end).getState() == NONE) && ((xDiff == 1)) && ((yDiff == 1) || (yDiff == -1)))
            JustCrowned = false;
        move = COMBAT;
    }
    else if ((board.at(end).getState() == NONE) && (xDiff == 1) && ((yDiff == -2) || (yDiff == 2)) && (CheckIfValidJump(start, end) == 1))
    {
        JustCrowned = false;
        move = COMBAT;
    }
    else
    {
        move = PROHIBITED;
    }
    return move;
}

MoveType Board::move(position start, position end, Player player)
{
    MoveType moveResult = checkMove(start, end, player);
    if (moveResult == USUAL)
    {
        if (JustCrowned == false)
            board.at(end).setState(board.at(start).getState());
        board.at(start).setState(NONE);
        //S
        if (JustCrowned == true)
            if (board.at(start).getState() == WHITE)
            {
                board.at(end).setState(WHITEKING);
                board.at(start).setState(NONE);
                //S
            }
            else
            {
                board.at(end).setState(BLACKKING);
                board.at(start).setState(NONE);
                //S
            }
    }
    else if (moveResult == COMBAT)
    {
        if (JustCrowned == false)
            board.at(end).setState(board.at(start).getState());
        board.at(start).setState(NONE);
    
        if (JustCrowned == true)
            if (board.at(start).getState() == WHITE)
            {
                board.at(end).setState(WHITEKING);
                board.at(start).setState(NONE);
                //S
            }
            else
            {
                board.at(end).setState(BLACKKING);
                board.at(start).setState(NONE);
                //S
            }
        position middlePos((start.first + end.first) / 2, (start.second + end.second) / 2);
        board.at(middlePos).setState(NONE);
        //S
        cout << "Oh the other player jumped your piece";
    }
    else if (moveResult == PROHIBITED)
    {
        cout << "This move is not allowed. Try again :(";
    }
    return moveResult;
}

bool Board::CheckIfValidJump(position start, position end)
{
    int CombatRow = (end.first + start.first) / 2;
    int CombatCol = ((end.second + start.second) / 2);
    position check(CombatRow, CombatCol);
    if ((((board.at(end).getState() == BLACKKING) || (board.at(end).getState() == BLACK)) && ((board.at(check).getState() == WHITEKING) || (board.at(check).getState() == WHITE))))
    {
        return true;
    }
    else if ((((board.at(end).getState() == WHITEKING) || (board.at(end).getState() == WHITE)) && ((board.at(check).getState() == BLACKKING) || (board.at(check).getState() == BLACK))))
    {
        return true;
    }
    else
    {
        return false;
    }
}
Unordered_map Board::getBoard(){
    return this -> board;
}