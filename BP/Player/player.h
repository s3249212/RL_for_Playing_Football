#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>

using namespace std;

class Player{

public:
    Player();
    virtual ~Player();

    virtual void train(vector<double> input, double reward, bool terminal = 0) = 0;
    virtual int act(vector<double> input) = 0;
    virtual void resetAfterMatch() = 0;
    virtual void save(string filename) = 0;
    virtual void load(string filename) = 0;

protected:
    string sourcefile = "";
};

#endif
