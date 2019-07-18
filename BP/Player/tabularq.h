#ifndef TABULARQ_H
#define TABULARQ_H

#include <array>
#include <string>
#include <vector>

#include "qlearningplayer.h"

class TabularQ : public QLearningPlayer
{
private:
    double** qTable;
    int nStates; 

    double minInit = -10.0;
    double maxInit = 10.0;

    vector<double> getQValues(int currentState);
public:
    TabularQ();
    TabularQ(string savefile);
    ~TabularQ();

    void initialize(int nStates, int nActions);

    void train(vector<double> prevInput, int prevAction, double reward);
    void train(vector<double> prevInput, int prevAction, vector<double> input, double reward);

    void resetAfterEpisode();

    int act(vector<double> input);

    void save(string filename);
    void load(string filename);

    void printQTable();
};

#endif // TABULARQ_H
