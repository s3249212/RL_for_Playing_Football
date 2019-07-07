#ifndef QV_H
#define QV_H

#include <string>

#include "qlearningplayer.h"
#include "Util/neural_network.h"

class QV : public QLearningPlayer
{
public:
    QV();
    QV(string filename);
    ~QV();

    void initialize(int nInput, int nActions);

    void train(double reward);
    void train(vector<double> input, double reward);

    int act(vector<double> input);

    void resetAfterEpisode();

    void save(string filename);
    void load(string filename);

private:
    Neural_network* qn;
    Neural_network* vn;

    int nHiddenLayers = 1;
    int nHiddenNeuronsPerLayer = 50;

    vector<double> prevInput;
    int prevAction = -1;
};

#endif // QV_H
