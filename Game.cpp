#include "Game.h"

using namespace std;

Game::Game(){
    whiteScore=0;
    blackScore=0;
    surrender=false;
    currentPlayer=Player::BLACKK;
}

const Player& Game::getWinner(Unordered_map board){
    int noBlack = 0;
    int noWhite = 0;
    int lowestBlackRow = -1;
    int highestWhiteRow = 8;
    for (int i = 0; i < BOARDSIZE; i++){
        //cout<<"hello";
        if(i%2 == 0){
            //cout<<"hello";
            for (int j = 0; j < BOARDSIZE; j = j+2){
                if (board.at({i,j}).getState() == State::BLACK){
                    noBlack++;
                    lowestBlackRow = max(lowestBlackRow, i);
                }
                else if (board.at({i,j}).getState() == State::WHITE){
                    noWhite++;
                    highestWhiteRow = min(highestWhiteRow, i);
                } 
            }
        }
        else{
            for (int j = 1; j < BOARDSIZE; j = j+2){
                if (board.at({i,j}).getState() == State::BLACK){
                    noBlack++;
                    lowestBlackRow = max(lowestBlackRow, i);
                } 
                else if (board.at({i,j}).getState() == State::WHITE)
                    noWhite++;
                    highestWhiteRow = min(highestWhiteRow, i);
            }
        }
    }
    if (noBlack == 0)
        return Player::WHITEE;
    else if (noWhite == 0)
        return Player::BLACKK;
    else if (highestWhiteRow - lowestBlackRow > 1)
        return Player::TIE;
    else 
        return Player::NONEE;
}

void Game::start(){
    this->board.setBoard();
    MiniMax minimaxx;
    //game loop
    while(getWinner(this->board.getBoard()) == Player::NONEE){ 

        MoveType moveOutcome(MoveType::PROHIBITED);
        if (currentPlayer == Player::BLACKK){
            string boardState = minimaxx.getBoardstate(board.getBoard(), currentPlayer);
            long long key = minimaxx.hashFunction(boardState);
            if(minimaxx.moveTable.find(key) == minimaxx.moveTable.end()){
                minimaxx.explore(0, board.getBoard(), currentPlayer);
            }
            movePosition move = minimaxx.moveTable[key];
            cout<< move.first.first << move.first.second << " "<< move.second.first << move.second.second<<endl;
            moveOutcome = this->board.move(move.first, move.second, this->currentPlayer);
        } 
        else{ 
            while(moveOutcome==MoveType::PROHIBITED){
                movePosition move = makeIO();
                moveOutcome = this->board.move(move.first, move.second, this->currentPlayer);
            }
        }
        if (moveOutcome==MoveType::USUAL){
            switchPlayer();
        }
        else if (moveOutcome==MoveType::COMBAT){
            updateScores();
            switchPlayer();
        }
    }
    if(getWinner(this->board.getBoard()) == Player::WHITEE){
        cout<<"You won the smartest player in the world\n";
    }
    else if (getWinner(this->board.getBoard()) == Player::BLACKK){
        cout << "You lost to artificial intelligence. Sad Reacts;(\n";
    }
    else
    {
        cout << "You as smart as the smartest virtual player\n";
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