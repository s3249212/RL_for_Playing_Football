#ifndef RANDOMPLAYER_H
#define RANDOMPLAYER_H

#include <string>
#include <vector>
#include "player.h"

class RandomPlayer: public Player
{
public:
    RandomPlayer();

    void train(vector<double> prevInput, int prevAction, double reward);
    void train(vector<double> prevInput, int prevAction, vector<double> input, double reward);
    int act(vector<double> input);
    void resetAfterEpisode();
    void save(string filename);
    void load(string filename);

private:
    int nActions = 18;
};

#endif // RANDOMPLAYER_H
