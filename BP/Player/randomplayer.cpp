#include <stdlib.h>
#include "player.h"
#include "randomplayer.h"

RandomPlayer::RandomPlayer()
{

}

void RandomPlayer::learn(vector<double> input, double reward, bool terminal){

}

int RandomPlayer::act(vector<double> input){
    return rand() % 8;
}

void RandomPlayer::resetAfterMatch()
{

}
