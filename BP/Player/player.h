#ifndef PLAYER_H
#define PLAYER_H

#include <vector>

using namespace std;

class Player{
public:
    Player();

    int totalReward = 0;

    virtual int act(vector<int> input, int reward);
};

#endif
