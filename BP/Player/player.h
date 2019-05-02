#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "World/world.h"

using namespace std;

class Player{
protected:
    World::Mode mode;

public:
    Player();

    int totalReward = 0;

    virtual void updateEndOfMatch(vector<int> input, int reward);

    virtual int act(vector<int> input, int reward);

    void setMode(World::Mode mode);
};

#endif
