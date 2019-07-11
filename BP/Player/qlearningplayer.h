#ifndef QLEARNINGPLAYER_H
#define QLEARNINGPLAYER_H

#include <string>

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

    double k_learning_rate = 0.0000000001;
    double k_epsilon = 0.0000001;

    double learning_rate = 0.5;
    double discount_factor = 0.99; //discount factor
    double epsilon = 0.05; //initial epsilon value for random action selection
    double minEpsilon = 0;
    int epsilonDecreasingPeriod = 20000000;
    int softMaxDecreasingPeriod = 20000000;
    double maxSoftMaxTemp = 0.2;
    double minSoftMaxTemp = 0.2;

    vector<int> gridSizes = {1, 1, 20};

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
