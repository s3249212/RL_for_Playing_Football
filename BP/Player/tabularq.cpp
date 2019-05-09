#include "tabularq.h"
#include <stdlib.h>
#include <math.h>
#include <QDebug>

using namespace std;

TabularQ::TabularQ(Gridworld* gridworld):
    world(gridworld)
{
    nStates = pow(world->getWidth() * world->getHeight(), 3);
    qTable = new float*[nStates]();
    for(int i = 0; i < nStates; i++){
        qTable[i] = new float[nActions](); //action size
        for(int j = 0; j < nActions; j++){
            float minInit = -10.0f;
            float maxInit = 10.0f;
            qTable[i][j] =  minInit + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (maxInit - minInit)));
        }
    }
}

void TabularQ::updateEndOfMatch(vector<int> input, int reward)
{

}

void TabularQ::resetAfterMatch()
{
    prevAction = -1;
    prevState = -1;
}

int TabularQ::getStateNumber(vector<int> input){
    int idx = input.at(0);
    for(int i = 1; i < 6; i++){
        int mFactor = i % 2? world->getHeight(): world->getWidth();
        idx = mFactor * idx + input.at(i);
    }
    return idx;
}

float TabularQ::learning_rate_f(){
    switch(learning_rate_change){
    default:
    case Constant:
        return learning_rate;
    case Exponential_decay:
        return exponential_decay(learning_rate, k_learning_rate, nSteps);
    }
}

float TabularQ::epsilon_f(){
    switch(epsilon_change){
    default:
    case Constant:
        return epsilon;
    case Exponential_decay:
        return exponential_decay(epsilon, k_epsilon, nSteps);
    }
}

float TabularQ::exponential_decay(float init, float k, int t){
    return init * exp(-k * t);
}

//update the value estimate matrix given a new experience
//state = the environment state the experience happened
//finished = whether the episode has ended
void TabularQ::qLearningUpdate(vector<int> input, int reward){
    int currentState = getStateNumber(input);

    if(prevAction != -1){
        float maxQAction = qTable[currentState][0];

        for(int i = 1; i < nActions; i++){
            if(qTable[currentState][i] > maxQAction){
                maxQAction = qTable[currentState][i];
            }
        }

        qTable[prevState][prevAction] *= 1 - learning_rate;
        qTable[prevState][prevAction] += learning_rate * (reward + gamma * maxQAction);
    }

    prevState = currentState;
}

int TabularQ::selectAction(int state)
{
    switch(actionSelection){
    case Softmax:
        return softmaxActionSelection(state);
    case HighestQ:
        return highestQActionSelection(state);
    case Random:
    default:
        return randomActionSelection();
    }
}

int TabularQ::softmaxActionSelection(int state)
{
    int selectedAction = -1;

    float sum = 0;
    float minQAction = qTable[state][0];

    for(int i = 1; i < nActions; i++){
        if(qTable[state][i] < minQAction){
            minQAction = qTable[state][i];
        }
        sum += qTable[state][i];
    }

    sum += -minQAction * nActions;

    float currentSum = 0.0f;
    float random = rand() % 1000000 / 1000000.0f;
    for(int i = 0; i < nActions; i++){
        currentSum += qTable[state][i] + -minQAction;
        if(random < currentSum / (sum + 0.000001f)){
            selectedAction = i;
            break;
        }
    }
    return selectedAction;
}

int TabularQ::highestQActionSelection(int state)
{
    int selectedAction = -1;

    float maxQAction = qTable[state][0];

    for(int i = 1; i < nActions; i++){
        if(qTable[state][i] > maxQAction){
            maxQAction = qTable[state][i];
            selectedAction = i;
        }
    }

    return selectedAction;
}

int TabularQ::randomActionSelection()
{
    return rand() % nActions;
}

int TabularQ::act(vector<int> input, int reward){
    qLearningUpdate(input, reward);

    int currentState = getStateNumber(input);

    int selectedAction = selectAction(currentState);

    int currentAction;
    if(rand() % 100 / 100.0f > epsilon_f() && selectedAction != -1){
        currentAction = selectedAction;
    } else {
        currentAction = randomActionSelection();
    }

    prevAction = currentAction; 

    totalReward += reward;

    nSteps++;

    return currentAction;
}

void TabularQ::printQTable(){
    for(int i = 0; i < nStates; i++){
        for(int j = 0; j < nActions; j++){
            if(qTable[i][j] != 0){
                qDebug() << "State: " << i << ", action: " << j << ", Q value:"<< qTable[i][j] << "\n";
            }
        }
    }
}

