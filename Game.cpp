#include "Game.h"
#include <stdlib.h>
using namespace std;
Game::Game(){
    whiteScore=0;
    blackScore=0;
    surrender=false;
    currentPlayer=Player::NONE;
}

Player Game::getWinner(){
    Player winner=Player::NONE;
    if(surrender){
        if(currentPlayer==Player::WHITE)
            winner = Player::BLACK;
        else if(currentPlayer==Player::BLACK)
            winner = Player::WHITE;
    }
    else{
        if (whiteScore == 12)
            winner = Player::WHITE;
        else if (blackScore == 12)
            winner = Player::BLACK;
    }
    return winner;
}
void Game::start(){
    board.setBoard();
    //game loop
    while(getWinner() == Player::NONE){ 
       
        MoveType moveOutcome(MoveType::PROHIBITED);
        while(moveOutcome==MoveType::PROHIBITED){
            movePosition move = makeIO();
            this->board.move(move.first, move.second, this->currentPlayer);
        }
        if (moveOutcome==MoveType::USUAL){
            switchPlayer();
        }
        else if (moveOutcome==MoveType::COMBAT){
            updateScores();
            switchPlayer();
        }
    }
}
movePosition Game::makeIO(){
    system("cls"); //clean console
    unordered_map<position, Cell> board = this->board.getBoard();
    io.DrawBoard(board);
   //get move
    auto move = io.getMove();
    return move;
}
void Game::switchPlayer(){
    if(currentPlayer==Player::WHITE)
        currentPlayer = Player::BLACK;
    else
        currentPlayer = Player::WHITE;
    
}
void Game::updateScores(){
    if (currentPlayer == Player::WHITE)
        blackScore++;
    else
        whiteScore++;
    
}