#ifndef MLPQ_H
#define MLPQ_H

#include "qlearningplayer.h"
#include "Util/neural_network.h"

class MLPQ : public QLearningPlayer
{
public:
    MLPQ();
    MLPQ(string filename);
    ~MLPQ();

    void initialize(int nInput, int nActions);

    void train(double reward);
    void train(vector<double> input, double reward);

    int act(vector<double> input);

    void resetAfterEpisode();

    void save(string filename);
    void load(string filename);

private:
    Neural_network* nn;

    int nHiddenLayers = 1;
    int nHiddenNeuronsPerLayer = 30;

    vector<double> prevInput;
    int prevAction = -1;
};

#endif // MLPQ_H
