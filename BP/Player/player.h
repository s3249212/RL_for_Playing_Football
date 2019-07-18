#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>

using namespace std;

class Player{

public:
    Player();
    virtual ~Player();

    virtual void train(vector<double> prevInput, int prevAction, double reward) = 0;
    virtual void train(vector<double> prevInput, int prevAction, vector<double> input, double reward) = 0;
    virtual int act(vector<double> input) = 0;
    virtual void resetAfterEpisode() = 0;
    virtual void save(string filename) = 0;
    virtual void load(string filename) = 0;

protected:
    string sourcefile = "";
};

#endif
