#include "Game.h"
#include <stdlib.h>
using namespace std;
Game::Game(){
    whiteScore=0;
    blackScore=0;
    surrender=false;
    currentPlayer=Player::WHITEE;
}

Player Game::getWinner(){
    Player winner=Player::NONEE;
    if(surrender){
        if(currentPlayer==Player::WHITEE)
            winner = Player::BLACKK;
        else if(currentPlayer==Player::BLACKK)
            winner = Player::WHITEE;
    }
    else{
        if (whiteScore == 12)
            winner = Player::WHITEE;
        else if (blackScore == 12)
            winner = Player::BLACKK;
    }
    return winner;
}

void Game::start(){
    this->board.setBoard();
    //game loop
    while(getWinner() == Player::NONEE){ 

        MoveType moveOutcome(MoveType::PROHIBITED);
        while(moveOutcome==MoveType::PROHIBITED){
            movePosition move = makeIO();
            moveOutcome = this->board.move(move.first, move.second, this->currentPlayer);
        }
        if (moveOutcome==MoveType::USUAL){
            cout<<"Usual\n";
            switchPlayer();
        }
        else if (moveOutcome==MoveType::COMBAT){
            updateScores();
            switchPlayer();
        }
    }
}
movePosition Game::makeIO(){
    system("cls");
    Unordered_map board = this->board.getBoard();
    io.DrawBoard(board);
   //get move
    auto move = io.getMove();
    return move;
}
void Game::switchPlayer(){
    if(currentPlayer==Player::WHITEE)
        currentPlayer = Player::BLACKK;
    else
        currentPlayer = Player::WHITEE;
    
}
void Game::updateScores(){
    if (currentPlayer == Player::WHITEE)
        blackScore++;
    else
        whiteScore++;
    
}