#include "Game.h"

using namespace std;

Game::Game(){
    currentPlayer=Player::BLACKK;
}

movePosition Game::makeIO(){
    Unordered_map board = this->board.getBoard();
    IOstream::DrawBoard(board);//Display::DrawBoard(board)
    //io.DrawBoard(board);
   //get move
    auto move = IOstream::getMove();
    return move;
}

void Game::switchPlayer(){
    if(currentPlayer==Player::WHITEE)
        currentPlayer = Player::BLACKK;
    else
        currentPlayer = Player::WHITEE;
    
}

void Game::start(){
    this->board.setBoard();
    MiniMax minimaxx;
    //game loop
    while(minimaxx.checkEnd(this->board.getBoard(), currentPlayer) == Player::NONEE){ 

        MoveType moveOutcome(MoveType::PROHIBITED);
        if (currentPlayer == Player::BLACKK){
            string boardState = minimaxx.getBoardstate(board.getBoard(), currentPlayer);
            long long key = minimaxx.hashFunction(boardState);
            if(minimaxx.moveTable.find(key) == minimaxx.moveTable.end()){
                minimaxx.explore(0, board.getBoard(), currentPlayer);
            }
            movePosition move = minimaxx.moveTable[key];
            //cout << key << endl;
            cout<< move.first.first << move.first.second << " "<< move.second.first << move.second.second<<endl;
            //if(move.first.first == 0 && move.first.second == 0 && move.second.second ==0 && move.second.first ==0)
               // return;
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
            switchPlayer();
        }
    }
    if(minimaxx.checkEnd(this->board.getBoard(), currentPlayer) == Player::WHITEE){
        cout<<"You won the smartest player in the world\n";
    }
    else if (minimaxx.checkEnd(this->board.getBoard(), currentPlayer) == Player::BLACKK){
        cout << "You lost to artificial intelligence. Sad Reacts;(\n";
    }
    else
    {
        cout << "You as smart as the smartest virtual player\n";
    }  
}