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

    ActionSelection_t actionSelection = Softmax;

    Gridworld* world;
    int prevAction = -1;
    int prevState = -1;

    float** qTable;
    int nActions = 8;
    int nStates;

    float learning_rate = 0.1f;
    float decrease_factor = 1.000f;
    float gamma = 0.99f; //discount factor
    float epsilon = 0.1f; //initial epsilon value for random action selection

    int getStateNumber(vector<int> input);
    float getQTableValue(vector<int> input, int a);

    void qLearningUpdate(vector<int> input, int reward);

    int selectAction(int state);

    int softmaxActionSelection(int state);
    int highestQActionSelection(int state);
    int randomActionSelection();

public:
    TabularQ(Gridworld* gridworld);

    void updateEndOfMatch(vector<int> input, int reward);

    void resetAfterMatch();

    int act(vector<int> input, int reward);
    void printQTable();
};

#endif // TABULARQ_H
