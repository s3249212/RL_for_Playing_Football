#ifndef TABULARQ_H
#define TABULARQ_H

#include <array>
#include <vector>

#include "player.h"

class TabularQ : public Player
{
private:
    enum ActionSelection_t {
        Random = 0, HighestQ, Softmax
    };

    enum Hyperparameter_Change_t {
        Constant = 0, Exponential_decay
    };

    ActionSelection_t actionSelection = Softmax;

    int prevAction = -1;
    int prevState = -1;

    double** qTable;
    int nActions;
    int nStates;

    double learning_rate = 0.01;
    double discount_factor = 0.99; //discount factor
    double epsilon = 0.1; //initial epsilon value for random action selection
    double softMaxTemp = 0.1;

    Hyperparameter_Change_t learning_rate_change = Constant;
    Hyperparameter_Change_t epsilon_change = Constant;

    double k_learning_rate = 0.0000000001;
    double k_epsilon = 0.01;

    int nSteps = 0;

    double minInit = -10.0;
    double maxInit = 10.0;

    int selectAction(int state);

    int softmaxActionSelection(int state);
    int highestQActionSelection(int state);
    int randomActionSelection();

    double exponential_decay(double init, double k, int t);
    double epsilon_f();

    string sourcefile = "";

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

    double learning_rate_f();


    void printQTable();
};

#endif // TABULARQ_H
