#include "MiniMax.h"
#include "iostream"
#include <vector>
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