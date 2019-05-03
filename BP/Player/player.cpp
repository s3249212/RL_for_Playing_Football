#include "player.h"

Player::Player(){

}

void Player::updateEndOfMatch(vector<int> input, int reward){}

void Player::resetAfterMatch(){}

int Player::act(vector<int> input, int reward){}

void Player::setMode(World::Mode mode){
    this->mode = mode;
}
