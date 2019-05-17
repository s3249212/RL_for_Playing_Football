#ifndef TABULARQ_H
#define TABULARQ_H

#include "Player/player.h"
#include "World/Gridworld/gridworld.h"
#include "Interaction_Handler/Gridworld/gridworld_ih.h"


#include <array>
#include <vector>

class TabularQ : public Player
{
private:
    enum ActionSelection_t {
        Random, HighestQ, Softmax
    };

    enum Hyperparameter_Change_t {
        Constant, Exponential_decay
    };

    ActionSelection_t actionSelection = Softmax;

    int prevAction = -1;
    int prevState = -1;

    float** qTable;
    int nActions;
    int nStates;

    float learning_rate = 0.01f;
    float gamma = 0.99f; //discount factor
    float epsilon = 0.1f; //initial epsilon value for random action selection

    Hyperparameter_Change_t learning_rate_change = Constant;
    Hyperparameter_Change_t epsilon_change = Constant;

    float k_learning_rate = 0.01f;
    float k_epsilon = 0.01f;

    int nSteps = 0;

    int selectAction(int state);

    int softmaxActionSelection(int state);
    int highestQActionSelection(int state);
    int randomActionSelection();

    float learning_rate_f();
    float exponential_decay(float init, float k, int t);
    float epsilon_f();

public:
    TabularQ();

    void initialize(int nStates, int nActions);

    void learn(vector<double> input, double reward);

    void resetAfterMatch();

    int act(vector<double> input, double reward);
    void printQTable();
};

#endif // TABULARQ_H
