#include "qlearningplayer.h"
#include "Util/util_functions.h"

#include <stdio.h>

using namespace std;

QLearningPlayer::QLearningPlayer()
{

}

double QLearningPlayer::learning_rate_f(){
    switch(learning_rate_change){
    case Constant:
        return learning_rate;
        break;
    case Exponential_decay:
        double lr = exponential_decay(learning_rate, k_learning_rate, nSteps);
        return lr;
        break;
    }
}

double QLearningPlayer::epsilon_f(){
    switch(epsilon_change){
    case Constant:
        return epsilon;
    case Exponential_decay:
        return exponential_decay(epsilon, k_epsilon, nSteps);
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
    case HighestQ:
        selectedAction = highestQActionSelection(qValues);
        break;
    case Random:
    default:
        cout << "Selecting random action" << endl;
        selectedAction = randomActionSelection();
    }

    return selectedAction;
}

int QLearningPlayer::softmaxActionSelection(vector<double> qValues)
{
    vector<double> probabilities = softmax(values, softMaxTemp);
    return weightedRandomSelection(probabilities);
}

int QLearningPlayer::highestQActionSelection(vector<double> qValue)
{
    int selectedAction = -1;

    double maxQAction = qTable[state][0];

    for(int i = 1; i < nActions; i++){
        if(qTable[state][i] > maxQAction){
            maxQAction = qTable[state][i];
            selectedAction = i;
        }
    }

    if(selectedAction == -1 || rand() / static_cast <double> (RAND_MAX) <= epsilon_f()){
        selectedAction = randomActionSelection();
    }

    return selectedAction;
}

int TabularQ::randomActionSelection()
{
    return rand() % nActions;
}
