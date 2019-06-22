#ifndef RANDOMPLAYER_H
#define RANDOMPLAYER_H

#include <vector>
#include "player.h"

class RandomPlayer: public Player
{
public:
    RandomPlayer();

    void train(vector<double> input, double reward, bool terminal = 0);
    int act(vector<double> input);
    void resetAfterMatch();
    void save(string filename);
    void load(string filename);

private:
    int nActions = 18;
};

#endif // RANDOMPLAYER_H
