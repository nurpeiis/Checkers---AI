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
}

bool JustCrowned = 0;
MoveType Board::checkMove(position start, position end, Player player)
{
    int xDiff = abs(start.second - end.second); //you can move either to left or right- doesnt really matter
    int yDiff = end.first - start.first;
    MoveType moveResult;

    if(board.at(end).getState() != NONE){
        cout<<"WHAT ARE YOU DOING?? The cell is occupied"<<endl;
        moveResult=PROHIBITED;
      }
    else if (board.at(start).getState()==BLACK)
    {
        if ((board.at(end).getState() == NONE) && (xDiff == 1) && (yDiff == 1))
        {
            if (end.first == 7)
            {   JustCrowned = true;
                moveResult = USUAL;
            }
            else
            {   JustCrowned = false;
                moveResult = USUAL;
            }
        }
       else if ((board.at(end).getState() == NONE) && (xDiff == 2) && (yDiff == 2))
        {
            if (end.first == 7)
            {   JustCrowned = true;
                moveResult = COMBAT;
            }
            else
            {
                JustCrowned = false;
                moveResult = COMBAT;
            }
        }


    }
    else if (board.at(start).getState()==BLACKKING)
    {
        if ((board.at(end).getState() == NONE) && (xDiff == 1) && ((yDiff == 1) || (yDiff == -1)))
        {   JustCrowned = false;

            moveResult = USUAL;
        }
        else if ((board.at(end).getState() == NONE) && ((xDiff == 2) && (yDiff == 2)) && CheckIfValidJump(start, end) == 1)
        {
            JustCrowned = false;
            moveResult = COMBAT;
        }
        else
        {
            moveResult = PROHIBITED;
        }
    }
    else if (board.at(start).getState()==WHITE)
    {
        if ((board.at(end).getState() == NONE) && (xDiff == 1) && ((yDiff == -1)))
        {
            if (end.first == 0)
            {
                JustCrowned = true;
                moveResult = USUAL;
            }
            else
            {
                JustCrowned = false;
                moveResult = USUAL;
            }
        }
        else if ((board.at(end).getState() == NONE) && (xDiff == 2) && (yDiff == -2))
        {
            if (end.first == 0)
            {
                JustCrowned = true;
                moveResult = COMBAT;

            }
          else
            {
                JustCrowned = false;
                moveResult = COMBAT;

            }
        }
        else
        {
            moveResult = PROHIBITED;
        }
    }

    else if (board.at(start).getState()==WHITEKING)
    {
    if ((board.at(end).getState() == NONE) && ((xDiff == 1)) && ((yDiff == 1) || (yDiff == -1))){

        JustCrowned = false;
        moveResult = COMBAT;
    }
    else if ((board.at(end).getState() == NONE) && (xDiff == 1) && ((yDiff == -2) || (yDiff == 2)) && (CheckIfValidJump(start, end) == 1))
    {
        JustCrowned = false;
        moveResult = COMBAT;

    }
  }

      else {
        moveResult = PROHIBITED;
      }
    return moveResult;
}


MoveType Board::move(position start, position end, Player player)
{
    MoveType moveResult = checkMove(start, end, player);

   if (moveResult == USUAL)
    {
        if (JustCrowned == false)
        board.at(end).setState(board.at(start).getState());
        board.at(start).setState(NONE);

        if (JustCrowned == true){
            if (board.at(start).getState() == WHITE)
            {
                board.at(end).setState(WHITEKING);
                board.at(start).setState(NONE);
            }
            else
            {
                board.at(end).setState(WHITE);
                board.at(start).setState(NONE);

            }
    }
  }

     if (moveResult == COMBAT)
    {
      position middlePos((start.first + end.first) / 2, (start.second + end.second) / 2);
        if (JustCrowned == false)
            {

        board.at(end).setState(board.at(start).getState());
        board.at(middlePos).setState(NONE);
        board.at(start).setState(NONE);
        }
        if (JustCrowned == true)
            if (board.at(start).getState() == WHITE)
            {
                board.at(end).setState(WHITEKING);
                board.at(middlePos).setState(NONE);
                board.at(start).setState(NONE);

            }
            else{
                board.at(end).setState(BLACKKING);
                board.at(middlePos).setState(NONE);
                board.at(start).setState(NONE);
            }
        cout << "Congrats! You ate the other player\n";
    }
    else if (moveResult == PROHIBITED)

    {
        cout << "This move is not allowed. Try again :(\n";
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
        return 1;
    }
    else if ((((board.at(end).getState() == WHITEKING) || (board.at(end).getState() == WHITE)) && ((board.at(check).getState() == BLACKKING) || (board.at(check).getState() == BLACK))))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

Unordered_map Board::getBoard(){
    return this -> board;
}