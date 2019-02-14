#include "Game.h"
using namespace std;
Game::Game(){

}
Player Game::getWinnner(){
    Player winner;
    if (whiteScore == 12)
        winner = Player::WHITE;
    else if (blackScore == 12)
        winner = Player::BLACK;

    return winner;
}