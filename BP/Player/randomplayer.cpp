#include <string>
#include <stdlib.h>
#include "player.h"
#include "randomplayer.h"

RandomPlayer::RandomPlayer()
{

}

void RandomPlayer::train(vector<double> prevInput, int prevAction, double reward)
{

}

void RandomPlayer::train(vector<double> prevInput, int prevAction, vector<double> input, double reward){

}

int RandomPlayer::act(vector<double> input){
    return rand() % nActions;
}

void RandomPlayer::resetAfterEpisode()
{
    
}

void RandomPlayer::save(string filename)
{
    
}

void RandomPlayer::load(string filename)
{
    
}
