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

    float** qTable;
    int nActions;
    int nStates;

    float learning_rate = 0.01f;
    float discount_factor = 0.99f; //discount factor
    float epsilon = 0.1f; //initial epsilon value for random action selection

    Hyperparameter_Change_t learning_rate_change = Constant;
    Hyperparameter_Change_t epsilon_change = Constant;

    float k_learning_rate = 0.0000000001f;
    float k_epsilon = 0.01f;

    int nSteps = 0;

    float minInit = -10.0f;
    float maxInit = 10.0f;

    int selectAction(int state);

    int softmaxActionSelection(int state);
    int highestQActionSelection(int state);
    int randomActionSelection();

    float exponential_decay(float init, float k, int t);
    float epsilon_f();

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

    float learning_rate_f();


    void printQTable();
};

#endif // TABULARQ_H
