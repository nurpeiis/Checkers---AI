#include "MiniMax.h"
#include "iostream"
using namespace std;
Player MiniMax::checkEnd(Unordered_map board){
    int noBlack = 0;
    int noWhite = 0;
    bool blackTie = true;
    bool whiteTie = true;
    for (int i = 0; i < BOARDSIZE; i++){
        cout<<"hello";
        if(i == 0 || i == 2 || i == 4 || i == 6){
            cout<<"hello";
            for (int j = 0; j < BOARDSIZE; j+2){
                if (board.at({i,j}).getState() == State::BLACK){
                    noBlack++;
                }
                else if (board.at({i,j}).getState() == State::WHITE){
                    noWhite++;
                    if(i != 0 && whiteTie){
                        whiteTie = false;
                    }
                } 
            }
        }
        else{
            for (int j = 1; j < BOARDSIZE; j+2){
                if (board.at({i,j}).getState() == State::BLACK){
                    noBlack++;
                    cout<<"hello";
                    if (i != 7 && blackTie){
                        blackTie = false;
                    }
                } 
                else if (board.at({i,j}).getState() == State::WHITE)
                    noWhite++;
            }
        }
    }
    if (noBlack == 0)
        return Player::WHITEE;
    else if (noWhite == 0)
        return Player::BLACKK;
    else if (noBlack>0 && noWhite>0)
        return Player::NONEE;
    else if (blackTie || whiteTie)
        return Player::TIE;
}