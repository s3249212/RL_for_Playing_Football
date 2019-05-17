#ifndef PLAYER_H
#define PLAYER_H

#include <vector>

using namespace std;

class Player{

public:
    Player();

    virtual void learn(vector<double> input, double reward, bool terminal = 0);
    virtual int act(vector<double> input);
    virtual void resetAfterMatch();
};

#endif
