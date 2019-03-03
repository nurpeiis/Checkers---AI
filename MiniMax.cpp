#include "MiniMax.h"
#include "iostream"
#include <vector>
#include <cmath>
using namespace std;

Player MiniMax::checkEnd(Unordered_map board){
    int noBlack = 0;
    int noWhite = 0;
    bool blackTie = true;
    bool whiteTie = true;
    for (int i = 0; i < BOARDSIZE; i++){
        //cout<<"hello";
        if(i%2 == 0){
            //cout<<"hello";
            for (int j = 0; j < BOARDSIZE; j = j+2){
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
            for (int j = 1; j < BOARDSIZE; j = j+2){
                if (board.at({i,j}).getState() == State::BLACK){
                    noBlack++;
                    //cout<<"hello";
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

vector<Unordered_map> MiniMax::possibleMoves(Unordered_map board, Player player){
    vector<Unordered_map> possibleMoves;
    if (player == Player::BLACKK){
        for (int i = 0; i < BOARDSIZE; i++){
            if (i%2 == 0){
                for (int j = 0; j < BOARDSIZE; j = j + 2){
                    if (board.at({i,j}).getState() == State::BLACK){
                        
                        //Check four diagonals
                        //Black can move back diagonally iff white is there annd the next one is free
                        if(i+1 < BOARDSIZE && j+1 < BOARDSIZE){
                            Unordered_map newBoard = board;
                            if (board.at({i+1,j+1}).getState() == State::NONE){
                                newBoard.at({i,j}).setState(State::NONE);
                                newBoard.at({i+1,j+1}).setState(State::BLACK);
                            }

                            else if (board.at({i+1,j+1}).getState() == State::WHITE || board.at({i+1,j+1}).getState() == State::WHITEKING){
                                if(i+2 < BOARDSIZE && j+2 < BOARDSIZE){
                                    if (board.at({i+2,j+2}).getState() == State::NONE){
                                        newBoard.at({i,j}).setState(State::NONE);
                                        newBoard.at({i+1,j+1}).setState(State::NONE);
                                        newBoard.at({i+2,j+2}).setState(State::BLACK);
                                    }
                                }
                            }
                            possibleMoves.push_back(newBoard);
                        }

                        if(i+1 < BOARDSIZE && j-1 > -1){
                            Unordered_map newBoard = board;
                            if (board.at({i+1,j-1}).getState() == State::NONE){
                                newBoard.at({i,j}).setState(State::NONE);
                                newBoard.at({i+1,j-1}).setState(State::BLACK);
                            }
                            else if (board.at({i+1,j-1}).getState() == State::WHITE || board.at({i+1,j-1}).getState() == State::WHITEKING){
                                if(i+2 < BOARDSIZE && j-2 > -1){
                                    if (board.at({i+2,j-2}).getState() == State::NONE){
                                        newBoard.at({i,j}).setState(State::NONE);
                                        newBoard.at({i+1,j-1}).setState(State::NONE);
                                        newBoard.at({i+2,j-2}).setState(State::BLACK);
                                    }
                                }
                            }
                            possibleMoves.push_back(newBoard);
                        }
                        //backward eating
                        if(i-1 > -1 && j+1 < BOARDSIZE){
                            Unordered_map newBoard = board;
                            if (board.at({i-1,j+1}).getState() == State::WHITE || board.at({i-1,j-1}).getState() == State::WHITEKING){
                                if(i-2 > -1 && j+2 < BOARDSIZE){
                                    if (board.at({i-2,j+2}).getState() == State::NONE){
                                        newBoard.at({i,j}).setState(State::NONE);
                                        newBoard.at({i-1,j+1}).setState(State::NONE);
                                        newBoard.at({i-2,j+2}).setState(State::BLACK);
                                    }
                                }
                            }
                            possibleMoves.push_back(newBoard);
                        }
                        if(i-1 > -1 && j-1 > -1){
                            Unordered_map newBoard = board;
                            if (board.at({i-1,j-1}).getState() == State::WHITE || board.at({i-1,j-1}).getState() == State::WHITEKING){
                                if(i-2 > -1 && j-2 > -1){
                                    if (board.at({i-2,j-2}).getState() == State::NONE){
                                        newBoard.at({i,j}).setState(State::NONE);
                                        newBoard.at({i-1,j-1}).setState(State::NONE);
                                        newBoard.at({i-2,j-2}).setState(State::BLACK);
                                    }
                                }
                            }
                            possibleMoves.push_back(newBoard);
                        }

                    }
                    /* Future aim, if finish early, do this part

                    else if (board.at({i,j}).getState() == State::BLACKKING){

                    }
                    else if (board.at({i,j}).getState() == State::WHITEKING){

                    }
                    */
                    else if (board.at({i,j}).getState() == State::WHITE){
                        
                        //Check four diagonals
                        //Black can move back diagonally iff white is there annd the next one is free
                        if(i-1 > -1 && j+1 < BOARDSIZE){
                            Unordered_map newBoard = board;
                            if (board.at({i-1,j+1}).getState() == State::NONE){
                                newBoard.at({i,j}).setState(State::NONE);
                                newBoard.at({i-1,j+1}).setState(State::WHITE);
                            }

                            else if (board.at({i-1,j+1}).getState() == State::BLACK|| board.at({i-1,j+1}).getState() == State::BLACKKING){
                                if(i-2 < -1 && j+2 < BOARDSIZE){
                                    if (board.at({i+2,j+2}).getState() == State::NONE){
                                        newBoard.at({i,j}).setState(State::NONE);
                                        newBoard.at({i-1,j+1}).setState(State::NONE);
                                        newBoard.at({i-2,j+2}).setState(State::WHITE);
                                    }
                                }
                            }
                            possibleMoves.push_back(newBoard);
                        }

                        if(i-1 > -1 && j-1 > -1){
                            Unordered_map newBoard = board;
                            if (board.at({i+1,j-1}).getState() == State::NONE){
                                newBoard.at({i,j}).setState(State::NONE);
                                newBoard.at({i+1,j-1}).setState(State::WHITE);
                            }
                            else if (board.at({i+1,j-1}).getState() == State::BLACK || board.at({i+1,j-1}).getState() == State::BLACKKING){
                                if(i-2 > -1 && j-2 > -1){
                                    if (board.at({i-2,j-2}).getState() == State::NONE){
                                        newBoard.at({i,j}).setState(State::NONE);
                                        newBoard.at({i-1,j-1}).setState(State::NONE);
                                        newBoard.at({i-2,j-2}).setState(State::WHITE);
                                    }
                                }
                            }
                            possibleMoves.push_back(newBoard);
                        }
                        //forward eating
                        if(i+1 < BOARDSIZE && j+1 < BOARDSIZE){
                            Unordered_map newBoard = board;
                            if (board.at({i+1,j+1}).getState() == State::BLACK || board.at({i-1,j-1}).getState() == State::BLACKKING){
                                if(i+2 < BOARDSIZE && j+2 < BOARDSIZE){
                                    if (board.at({i+2,j+2}).getState() == State::NONE){
                                        newBoard.at({i,j}).setState(State::NONE);
                                        newBoard.at({i+1,j+1}).setState(State::NONE);
                                        newBoard.at({i+2,j+2}).setState(State::WHITE);
                                    }
                                }
                            }
                            possibleMoves.push_back(newBoard);
                        }
                        if(i+1 < BOARDSIZE && j-1 > -1){
                            Unordered_map newBoard = board;
                            if (board.at({i-1,j-1}).getState() == State::BLACK || board.at({i-1,j-1}).getState() == State::BLACKKING){
                                if(i+2 < BOARDSIZE && j-2 > -1){
                                    if (board.at({i-2,j-2}).getState() == State::NONE){
                                        newBoard.at({i,j}).setState(State::NONE);
                                        newBoard.at({i+1,j-1}).setState(State::NONE);
                                        newBoard.at({i+2,j-2}).setState(State::WHITE);
                                    }
                                }
                            }
                            possibleMoves.push_back(newBoard);
                        }
                    }     
                }
            }

            else{
                for (int j = 1; j < BOARDSIZE; j = j + 2){
                    if (board.at({i,j}).getState() == State::BLACK){
                        
                        //Check four diagonals
                        //Black can move back diagonally iff white is there annd the next one is free
                        if(i+1 < BOARDSIZE && j+1 < BOARDSIZE){
                            Unordered_map newBoard = board;
                            if (board.at({i+1,j+1}).getState() == State::NONE){
                                newBoard.at({i,j}).setState(State::NONE);
                                newBoard.at({i+1,j+1}).setState(State::BLACK);
                            }

                            else if (board.at({i+1,j+1}).getState() == State::WHITE || board.at({i+1,j+1}).getState() == State::WHITEKING){
                                if(i+2 < BOARDSIZE && j+2 < BOARDSIZE){
                                    if (board.at({i+2,j+2}).getState() == State::NONE){
                                        newBoard.at({i,j}).setState(State::NONE);
                                        newBoard.at({i+1,j+1}).setState(State::NONE);
                                        newBoard.at({i+2,j+2}).setState(State::BLACK);
                                    }
                                }
                            }
                            possibleMoves.push_back(newBoard);
                        }

                        if(i+1 < BOARDSIZE && j-1 > -1){
                            Unordered_map newBoard = board;
                            if (board.at({i+1,j-1}).getState() == State::NONE){
                                newBoard.at({i,j}).setState(State::NONE);
                                newBoard.at({i+1,j-1}).setState(State::BLACK);
                            }
                            else if (board.at({i+1,j-1}).getState() == State::WHITE || board.at({i+1,j-1}).getState() == State::WHITEKING){
                                if(i+2 < BOARDSIZE && j-2 > -1){
                                    if (board.at({i+2,j-2}).getState() == State::NONE){
                                        newBoard.at({i,j}).setState(State::NONE);
                                        newBoard.at({i+1,j-1}).setState(State::NONE);
                                        newBoard.at({i+2,j-2}).setState(State::BLACK);
                                    }
                                }
                            }
                            possibleMoves.push_back(newBoard);
                        }
                        //backward eating
                        if(i-1 > -1 && j+1 < BOARDSIZE){
                            Unordered_map newBoard = board;
                            if (board.at({i-1,j+1}).getState() == State::WHITE || board.at({i-1,j-1}).getState() == State::WHITEKING){
                                if(i-2 > -1 && j+2 < BOARDSIZE){
                                    if (board.at({i-2,j+2}).getState() == State::NONE){
                                        newBoard.at({i,j}).setState(State::NONE);
                                        newBoard.at({i-1,j+1}).setState(State::NONE);
                                        newBoard.at({i-2,j+2}).setState(State::BLACK);
                                    }
                                }
                            }
                            possibleMoves.push_back(newBoard);
                        }
                        if(i-1 > -1 && j-1 > -1){
                            Unordered_map newBoard = board;
                            if (board.at({i-1,j-1}).getState() == State::WHITE || board.at({i-1,j-1}).getState() == State::WHITEKING){
                                if(i-2 > -1 && j-2 > -1){
                                    if (board.at({i-2,j-2}).getState() == State::NONE){
                                        newBoard.at({i,j}).setState(State::NONE);
                                        newBoard.at({i-1,j-1}).setState(State::NONE);
                                        newBoard.at({i-2,j-2}).setState(State::BLACK);
                                    }
                                }
                            }
                            possibleMoves.push_back(newBoard);
                        }

                    }
                    /* Future aim, if finish early, do this part

                    else if (board.at({i,j}).getState() == State::BLACKKING){

                    }
                    else if (board.at({i,j}).getState() == State::WHITEKING){

                    }
                    */
                    else if (board.at({i,j}).getState() == State::WHITE){
                        
                        //Check four diagonals
                        //Black can move back diagonally iff white is there annd the next one is free
                        if(i-1 > -1 && j+1 < BOARDSIZE){
                            Unordered_map newBoard = board;
                            if (board.at({i-1,j+1}).getState() == State::NONE){
                                newBoard.at({i,j}).setState(State::NONE);
                                newBoard.at({i-1,j+1}).setState(State::WHITE);
                            }

                            else if (board.at({i-1,j+1}).getState() == State::BLACK|| board.at({i-1,j+1}).getState() == State::BLACKKING){
                                if(i-2 < -1 && j+2 < BOARDSIZE){
                                    if (board.at({i+2,j+2}).getState() == State::NONE){
                                        newBoard.at({i,j}).setState(State::NONE);
                                        newBoard.at({i-1,j+1}).setState(State::NONE);
                                        newBoard.at({i-2,j+2}).setState(State::WHITE);
                                    }
                                }
                            }
                            possibleMoves.push_back(newBoard);
                        }

                        if(i-1 > -1 && j-1 > -1){
                            Unordered_map newBoard = board;
                            if (board.at({i+1,j-1}).getState() == State::NONE){
                                newBoard.at({i,j}).setState(State::NONE);
                                newBoard.at({i+1,j-1}).setState(State::WHITE);
                            }
                            else if (board.at({i+1,j-1}).getState() == State::BLACK || board.at({i+1,j-1}).getState() == State::BLACKKING){
                                if(i-2 > -1 && j-2 > -1){
                                    if (board.at({i-2,j-2}).getState() == State::NONE){
                                        newBoard.at({i,j}).setState(State::NONE);
                                        newBoard.at({i-1,j-1}).setState(State::NONE);
                                        newBoard.at({i-2,j-2}).setState(State::WHITE);
                                    }
                                }
                            }
                            possibleMoves.push_back(newBoard);
                        }
                        //forward eating
                        if(i+1 < BOARDSIZE && j+1 < BOARDSIZE){
                            Unordered_map newBoard = board;
                            if (board.at({i+1,j+1}).getState() == State::BLACK || board.at({i-1,j-1}).getState() == State::BLACKKING){
                                if(i+2 < BOARDSIZE && j+2 < BOARDSIZE){
                                    if (board.at({i+2,j+2}).getState() == State::NONE){
                                        newBoard.at({i,j}).setState(State::NONE);
                                        newBoard.at({i+1,j+1}).setState(State::NONE);
                                        newBoard.at({i+2,j+2}).setState(State::WHITE);
                                    }
                                }
                            }
                            possibleMoves.push_back(newBoard);
                        }
                        if(i+1 < BOARDSIZE && j-1 > -1){
                            Unordered_map newBoard = board;
                            if (board.at({i-1,j-1}).getState() == State::BLACK || board.at({i-1,j-1}).getState() == State::BLACKKING){
                                if(i+2 < BOARDSIZE && j-2 > -1){
                                    if (board.at({i-2,j-2}).getState() == State::NONE){
                                        newBoard.at({i,j}).setState(State::NONE);
                                        newBoard.at({i+1,j-1}).setState(State::NONE);
                                        newBoard.at({i+2,j-2}).setState(State::WHITE);
                                    }
                                }
                            }
                            possibleMoves.push_back(newBoard);
                        }
                    }     
                }
            }
        }
    }
    return possibleMoves;
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

int MiniMax::assignPoints (string boardState){
    int points = 0;
    for (char & c: boardState.substr(0, boardState.length()-1) ){//do not go to last char as it is the player type
        if (c == '2')
            points--;
        else if (c == '1')
            points++;
    }
    return points;
}

void MiniMax::populateHashTable(Unordered_map board, Player player){
    string state = getBoardstate(board, player);
    long long key = hashFunction(state);
    if (this -> hashTable.find(key) == hashTable.end()){
        int point = assignPoints(state);
        hashTable.insert({key, point});
    }
}

int MiniMax::findPoint(string boardState){
    int point = INT_MIN;
    long long key = hashFunction(boardState);
    if (this -> hashTable.find(key) != hashTable.end()){
        point = hashTable.at(key);
    }
    return point;
}