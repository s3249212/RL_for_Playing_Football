#include "randomplayer.h"
#include <stdlib.h>

RandomPlayer::RandomPlayer()
{

}

void RandomPlayer::learn(vector<double> input, double reward){

}

int RandomPlayer::act(vector<int> input, int reward){
    return rand() % 8;
}

void RandomPlayer::resetAfterMatch()
{

}
