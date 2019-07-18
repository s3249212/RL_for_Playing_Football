#ifndef MLPQ_H
#define MLPQ_H

#include <string>

#include "qlearningplayer.h"
#include "Util/neural_network.h"

class MLPQ : public QLearningPlayer
{
public:
    MLPQ();
    MLPQ(string filename);
    ~MLPQ();

    void initialize(int nInput, int nActions);

    void train(vector<double> prevInput, int prevAction, double reward);
    void train(vector<double> prevInput, int prevAction, vector<double> input, double reward);

    int act(vector<double> input);

    void resetAfterEpisode();

    void save(string filename);
    void load(string filename);

private:
    Neural_network* nn;

    vector<Neural_network::Activation_t> activationFunctions = {Neural_network::RELU, Neural_network::LINEAR};

    int nHiddenLayers = 1;
    int nHiddenNeuronsPerLayer = 50;
};

#endif // MLPQ_H
