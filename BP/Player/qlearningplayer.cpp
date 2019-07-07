#include "qlearningplayer.h"
#include "Util/util_functions.h"

#include <iostream>

using namespace std;

QLearningPlayer::QLearningPlayer()
{

}

QLearningPlayer::~QLearningPlayer()
{

}

double QLearningPlayer::learning_rate_f(){
    switch(learning_rate_change){
    case Exponential_decay:
        return exponential_decay(learning_rate, k_learning_rate, nSteps);
    case Constant:
    default:
        return learning_rate;
    }
}

vector<int> QLearningPlayer::getGridSizes() const
{
    return gridSizes;
}

double QLearningPlayer::epsilon_f(){
    switch(epsilon_change){
    case Exponential_decay:
        return exponential_decay(epsilon, k_epsilon, nSteps);
    case Constant:
    default:
        return epsilon;
    }
}

//update the value estimate matrix given a new experience
//state = the environment state the experience happened
//finished = whether the episode has ended
int QLearningPlayer::selectAction(vector<double> qValues)
{
    int selectedAction;
    switch(actionSelection){
    case Softmax:
        selectedAction = softmaxActionSelection(qValues);
        break;
    case Egreedy:
        selectedAction = eGreedyActionSelection(qValues);
        break;
    case Random:
    default:
        cout << "Selecting random action" << endl;
        selectedAction = randomActionSelection();
    }

    return selectedAction;
}

double QLearningPlayer::getSoftMaxTemp(){
    if(nSteps > softMaxDecreasingPeriod){
        return minSoftMaxTemp;
    }
    double time_factor = nSteps / static_cast<double>(softMaxDecreasingPeriod);
    return (1 - time_factor) * maxSoftMaxTemp + time_factor * minSoftMaxTemp;
}

int QLearningPlayer::softmaxActionSelection(vector<double> qValues)
{
    vector<double> probabilities = softmax(qValues, getSoftMaxTemp());
    return weightedRandomSelection(probabilities);
}

int QLearningPlayer::eGreedyActionSelection(vector<double> qValues)
{
    int selectedAction = -1;

    double maxQAction = qValues[0];

    for(int i = 1; i < nActions; i++){
        if(qValues[i] > maxQAction){
            maxQAction = qValues[i];
            selectedAction = i;
        }
    }

    if(selectedAction == -1 || rand() / static_cast <double> (RAND_MAX) <= epsilon_f()){
        selectedAction = randomActionSelection();
    }

    return selectedAction;
}

int QLearningPlayer::randomActionSelection()
{
    return rand() % nActions;
}
