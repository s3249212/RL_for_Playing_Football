#ifndef TABULARQ_H
#define TABULARQ_H

#include <array>
#include <vector>

#include "qlearningplayer.h"

class TabularQ : public QLearningPlayer
{
private:
    int prevAction = -1;
    int prevState = -1;

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

    void train(vector<double> input, double reward, bool terminal = 0);

    void resetAfterMatch();

    int act(vector<double> input);

    void save(string filename);
    void load(string filename);

    void printQTable();
};

#endif // TABULARQ_H
