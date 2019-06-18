#ifndef QLEARNINGPLAYER_H
#define QLEARNINGPLAYER_H

#include "player.h"

class QLearningPlayer : public Player
{
public:
    QLearningPlayer();
    virtual ~QLearningPlayer();

    double learning_rate_f();

protected:
    enum ActionSelection_t {
        Random = 0, HighestQ, Softmax
    };

    enum Hyperparameter_Change_t {
        Constant = 0, Exponential_decay
    };

    ActionSelection_t actionSelection = Softmax;
    Hyperparameter_Change_t learning_rate_change = Constant;
    Hyperparameter_Change_t epsilon_change = Constant;

    double k_learning_rate = 0.0000000001;
    double k_epsilon = 0.01;

    double learning_rate = 0.01;
    double discount_factor = 0.99; //discount factor
    double epsilon = 0.1; //initial epsilon value for random action selection
    double softMaxTemp = 10;

    int nActions;

    int nSteps = 0;

    int selectAction(vector<double> qValues);

    int softmaxActionSelection(vector<double> qValues);
    int highestQActionSelection(vector<double> qValues);
    int randomActionSelection();

    double epsilon_f();
};

#endif // QLEARNINGPLAYER_H
