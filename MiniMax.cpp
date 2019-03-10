#include "MiniMax.h"
#include "IOstream.h"
#include "Cell.h"
#include <vector>
#include <cmath>
using namespace std;

Player MiniMax::checkEnd(Unordered_map board){
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



string MiniMax::getBoardstate(Unordered_map board, Player player){
    //0 - none, 1 - black , 2 - white
    //need to look half of the cells
    string state = "";
    for (int i = 0; i < BOARDSIZE; i++){

        if(i%2 == 0){
            for (int j = 0; j < BOARDSIZE; j = j+2){
                if (board.at({i,j}).getState() == State::NONE){
                    state.push_back('0');
                }
                if (board.at({i,j}).getState() == State::BLACK){
                    state.push_back('1');
                }
                else if (board.at({i,j}).getState() == State::WHITE){
                    state.push_back('2');
                } 
            }
        }

        else{
            for (int j = 1; j < BOARDSIZE; j = j+2){
                if (board.at({i,j}).getState() == State::NONE){
                    state.push_back('0');
                }
                if (board.at({i,j}).getState() == State::BLACK){
                    state.push_back('1');
                }
                else if (board.at({i,j}).getState() == State::WHITE){
                    state.push_back('2');
                } 
            }
        }

    }
    //last bit is as follow: if the player is white = 2, black =1
    if(player == Player::BLACKK){
        state.push_back('1');
    }
    else if(player == Player::WHITEE){
        state.push_back('2');
    }
    return state;
}

long long MiniMax::hashFunction(string base3){
    long long key = 0;
    int base = 3;
    int counter = 0;
    for (char & c: base3){
        key = key + pow(base, counter)*(double)c;
        counter++;
    }

    return key;
}

double MiniMax::assignPoints (string boardState){
    double points = 0;
    for (char & c: boardState.substr(0, boardState.length()-1) ){//do not go to last char as it is the player type
        if (c == '2')
            points--;
        else if (c == '1')
            points++;
    }
    return points;
    
}


double MiniMax::theoreticalMax(string boardState){
    double points = 0;
    for (char & c: boardState.substr(0, boardState.length()-1) ){//do not go to last char as it is the player type
        if (c == '1')
            points++;
    }
    return points;
}
double MiniMax::theoreticalMin(string boardState){
    double points = 0;
    for (char & c: boardState.substr(0, boardState.length()-1) ){//do not go to last char as it is the player type
        if (c == '2')
            points--;
    }
    return points;
}
Unordered_map MiniMax::nextState (Unordered_map currentBoard, movePosition move, State change){
    currentBoard[{move.first.first, move.first.second}] = State::NONE;
    currentBoard[{move.second.first, move.second.second}] = change;
    return currentBoard;
}
bool MiniMax::valid(int r, int c){
    if(r > -1 && r < BOARDSIZE && c > -1 && c < BOARDSIZE)
        return true;
    else
        return false;
}
void MiniMax::update(int depth, Unordered_map& nextBoard, long long key,  Player player, double& current_point, movePosition & move){
    string nextBoardState = getBoardstate(nextBoard, player);
    long long nextKey = hashFunction(nextBoardState);
    if (player == Player::WHITEE){
        //double theoMin = theoreticalMin(nextBoardState);
        double theoMin = evaluatePoints (nextBoardState);
        if (current_point <= theoMin)
            return;
        double points = explore(depth+1, nextBoard, Player::BLACKK);
        current_point = min(current_point, points);
    }
    else if (player == Player::BLACKK){
        //double theoMax = theoreticalMax(nextBoardState);
        double theoMax = evaluatePoints (nextBoardState);
        if (current_point >= theoMax)
            return;
        double points = explore(depth+1, nextBoard, Player::WHITEE);
        if(current_point < points){
            current_point =  points;
            moveTable[key] = move;
        }
    }
}
double MiniMax::evaluatePoints (string boardState){
    int noBlack = 0;
    int noWhite = 0;
    for (char & c: boardState.substr(0, boardState.length()-1) ){
        if (c == '1')
            noBlack++;
        else if (c == '2')
            noWhite++;
    }
    double points = 0;
    if (noBlack == noWhite){
        return points;
    }
    else if (noBlack > noWhite){
        points = noBlack - noWhite + (noBlack/12.0);
    }
    else {
        points = -(noWhite - noBlack) - (noWhite/12.0);
    }
    return points;
}
double MiniMax::explore(int depth, Unordered_map board, Player player){ 
    string boardState = getBoardstate(board, player);
    long long key = hashFunction(boardState);
    //if (key == 137123399843755760L) cout << "STARTING\n";
    if (moveTable.find(key) != moveTable.end())
        return hashTable[key];
    //if (key == 137123399843755760L) cout << "RUNNING\n";
    //cout << "RUNNING " << key << endl; 
    if (depth <= DEPTH && checkEnd(board) == Player::NONEE){
        double current_point = player == Player::WHITEE ? 13.0 : -13.0;
        //cout << "Inside\n";
        //do stuff;
        State sign [3] = {State::BLACK, State::WHITE, State::NONE};
        int index = player == Player::BLACKK ? 0:1;
        //define directionalities
        int dr[2][4] = {{1,1,-1,-1}, {-1,-1,1,1}};
        int dc[2][4] = {{-1,1,-1,1}, {-1,1,-1,1}};
        for (int i = 0; i < BOARDSIZE; i++){
            for (int j = 0; j < BOARDSIZE; j++){
                if(board.at({i,j}).getState() == sign[index]){                   
                    //usual move = no combat
                    for (int k = 0; k < 2; k++){
                        int r = i + dr[index][k];
                        int c = j + dc[index][k];
                        //if (key == 137123399843755760L) cout << i << j << ' ' << r << c << endl;
                        if(valid(r,c)){
                            if(board.at({r,c}).getState() == sign[2]){
                                movePosition move;
                                move.first.first = i;
                                move.first.second = j;
                                move.second.first = r;
                                move.second.second = c;
                                Unordered_map newBoard = board;
                                Unordered_map nextBoard = nextState(newBoard, move, sign[index]);
                                //cout<< "A " <<move.first.first << move.first.second << " "<< move.second.first << move.second.second<<endl;
                                update(depth, nextBoard, key, player, current_point, move);
                            }
                        }
                    }
                    for (int k = 0; k < 4; k++){
                        int midR = i + dr[index][k];
                        int midC = j + dc[index][k];
                        int lastR = i + 2*dr[index][k];
                        int lastC = j + 2*dc[index][k];
                        //if (key == 137123399843755760L) cout << i << j << ' ' << lastR << lastC << endl;
                        if(valid(midR, midC) && valid(lastR, lastC)){
                            if(board.at({midR,midC}).getState() == sign[1-index] && board.at({lastR, lastC}).getState() == sign[2]){
                                movePosition move;
                                move.first.first = i;
                                move.first.second = j;
                                move.second.first = lastR;
                                move.second.second = lastC;
                                Unordered_map newBoard = board;
                                newBoard[{midR, midC}] = State::NONE;         
                                Unordered_map nextBoard = nextState(newBoard, move, sign[index]);
                                //cout<< "B " <<move.first.first << move.first.second << " "<< move.second.first << move.second.second<<endl;
                                update(depth, nextBoard, key, player, current_point, move);
                            }
                        }
                    }
                }
            }
        }
        hashTable[key] = current_point;
        return current_point;
    }
    else{
        double points = evaluatePoints(boardState);
        hashTable[key] = points;
        return points;
    } 
}