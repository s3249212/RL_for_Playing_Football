#ifndef QLEARNINGPLAYER_H
#define QLEARNINGPLAYER_H

#include <string>
#include <math.h>

#include "player.h"

class QLearningPlayer : public Player
{
public:
    QLearningPlayer();
    virtual ~QLearningPlayer();

    double learning_rate_f();

    vector<int> getGridSizes() const;

protected:
    enum ActionSelection_t {
        Random = 0, Egreedy, Softmax
    };

    enum Hyperparameter_Change_t {
      Constant = 0, Exponential_decay, Linear
    };

    ActionSelection_t actionSelection = Egreedy;
    Hyperparameter_Change_t learning_rate_change = Constant;
    Hyperparameter_Change_t epsilon_change = Linear;

    double k_learning_rate = 8.2 * pow(10,-9);
    double k_epsilon = 8.2 * pow(10,-9);

    double learning_rate = 0.5;
    double discount_factor = 0.99; //discount factor
    double epsilon = 0.5; //initial epsilon value for random action selection
    double minEpsilon = 0;
    int epsilonDecreasingPeriod = 280000000;
    int softMaxDecreasingPeriod = 280000000;
    double maxSoftMaxTemp = 2;
    double minSoftMaxTemp = 0.2;

    vector<int> gridSizes = {1, 30};

    int nActions;

    int nSteps = 0;

    int selectAction(vector<double> qValues);

    int softmaxActionSelection(vector<double> qValues);
    int eGreedyActionSelection(vector<double> qValues);
    int randomActionSelection();

    double epsilon_f();
    double getSoftMaxTemp();
};

#endif // QLEARNINGPLAYER_H
