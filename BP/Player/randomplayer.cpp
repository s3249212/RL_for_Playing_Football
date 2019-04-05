#include "randomplayer.h"
#include <stdlib.h>

RandomPlayer::RandomPlayer()
{

}

int RandomPlayer::act(vector<int> input, int reward){
    return rand() % 8;
}
