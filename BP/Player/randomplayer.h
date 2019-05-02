#ifndef RANDOMPLAYER_H
#define RANDOMPLAYER_H

#include <vector>
#include "player.h"

class RandomPlayer: public Player
{
public:
    RandomPlayer();

    void updateEndOfMatch(vector<int> input, int reward);

    int act(vector<int> input, int reward);
};

#endif // RANDOMPLAYER_H
