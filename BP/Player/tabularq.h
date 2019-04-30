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
    Gridworld *world;
    int prevAction;
    int prevState;

    float** qTable;
    int nActions = 8;

    float learning_rate = 0.5f;
    float gamma = 0.99f; //discount factor
    float e = 1; //initial epsilon value for random action selection

    int getStateNumber(vector<int> input);
    float getQTableValue(vector<int> input, int a);
public:
    TabularQ();

    float getQTableValue();
    void qLearningUpdate(vector<int> input, int reward);

    int act(vector<int> input, int reward);
};

#endif // TABULARQ_H
