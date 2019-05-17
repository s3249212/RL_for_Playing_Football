#ifndef RANDOMPLAYER_H
#define RANDOMPLAYER_H

#include <vector>
#include "player.h"

class RandomPlayer: public Player
{
public:
    RandomPlayer();

    void learn(vector<double> input, vector<double> reward);
    int act(vector<double> input);
    void resetAfterMatch();    
};

#endif // RANDOMPLAYER_H
