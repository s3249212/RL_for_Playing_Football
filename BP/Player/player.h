#ifndef PLAYER_H
#define PLAYER_H

#include <vector>

using namespace std;

class Player{
public:
    Player();

    virtual vector<int> act(vector<int> input, int reward);
};

#endif
