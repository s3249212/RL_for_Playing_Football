#include <stdlib.h>
#include "player.h"
#include "randomplayer.h"

RandomPlayer::RandomPlayer()
{

}

void RandomPlayer::train(vector<double> input, double reward, bool terminal){

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
