#include "Game.h"

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
    MiniMax minimaxx;
    //game loop
    while(getWinner() == Player::NONEE){ 

        MoveType moveOutcome(MoveType::PROHIBITED);
        string state = minimaxx.getBoardstate(this->board.getBoard(), currentPlayer);
        cout<<"Check if end: " <<minimaxx.checkEnd(this->board.getBoard())<<endl;
        cout<<"Return state: "<< state << endl;
        cout<<"Return hashed number from base 3 to base 10: "<< minimaxx.hashFunction(state)<< endl;
        cout<<"Return points: "<< minimaxx.assignPoints(state)<<endl;
        cout<<"Return points with wrong finding: "<< minimaxx.findPoint(state)<<endl;
        minimaxx.populateHashTable(this->board.getBoard(), currentPlayer);
        cout<<"Return points with corrected state: "<<minimaxx.findPoint(state)<<endl;
        while(moveOutcome==MoveType::PROHIBITED){
            movePosition move = makeIO();
            moveOutcome = this->board.move(move.first, move.second, this->currentPlayer);
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