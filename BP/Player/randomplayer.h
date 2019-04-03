#ifndef RANDOMPLAYER_H
#define RANDOMPLAYER_H

#include <vector>
#include "player.h"

class RandomPlayer: public Player
{
public:
    RandomPlayer();

    vector<int> act(vector<int> input, int reward);
};

#endif // RANDOMPLAYER_H
