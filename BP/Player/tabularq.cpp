#include <iostream>
#include "tabularq.h"
#include "player.h"
#include <stdlib.h>
#include <math.h>

using namespace std;

TabularQ::TabularQ()
{
    
}

TabularQ::~TabularQ(){

}

void TabularQ::initialize(int nStates, int nActions){
    this->nStates = nStates;
    this->nActions = nActions;

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

void TabularQ::learn(vector<double> input, double reward, bool terminal){
    int currentState = static_cast<int>(input.at(0));

    //cout << "Actually learning :)\n";
    //cout << "Reward: " << reward << endl;

    if(prevAction != -1){
        //cout << "prevAction is not -1" << endl;
        float maxQAction = qTable[currentState][0];

        for(int i = 1; i < nActions; i++){
            if(qTable[currentState][i] > maxQAction){
                maxQAction = qTable[currentState][i];
            }
        }

        qTable[prevState][prevAction] *= 1 - learning_rate_f();
        qTable[prevState][prevAction] += learning_rate_f() * (reward + gamma * maxQAction);
    }

    prevState = currentState;
}

int TabularQ::act(vector<double> input){
    int currentState = static_cast<int>(input.at(0));

    int selectedAction = selectAction(currentState);

    prevAction = selectedAction;

    nSteps++;

    //cout << "Selected action: " << selectedAction << endl;

    return selectedAction;
}

float TabularQ::learning_rate_f(){
    switch(learning_rate_change){
    case Constant:
        return learning_rate;
        break;
    case Exponential_decay:
        float lr = exponential_decay(learning_rate, k_learning_rate, nSteps);
        //std::cout << "Learning rate: " << lr << "\n";
        return lr;
        break;
    }
}

void TabularQ::resetAfterMatch()
{
    prevAction = -1;
    prevState = -1;
}


float TabularQ::epsilon_f(){
    switch(epsilon_change){
    case Constant:
        return epsilon;
    case Exponential_decay:
        return exponential_decay(epsilon, k_epsilon, nSteps);
    }
}

float TabularQ::exponential_decay(float init, float k, int t){
    //std::cout << init << " k:" << k << " t:" << t << "\n";
    return init * exp(-k * t);
}

//update the value estimate matrix given a new experience
//state = the environment state the experience happened
//finished = whether the episode has ended
int TabularQ::selectAction(int state)
{
    int selectedAction;
    switch(actionSelection){
    case Softmax:
        selectedAction = softmaxActionSelection(state);
        break;
    case HighestQ:
        selectedAction = highestQActionSelection(state);
        break;
    case Random:
    default:
        cout << "Selecting random action" << endl;
        selectedAction = randomActionSelection();
    }

    if(selectedAction == -1 || rand() % 100 / 100.0f <= epsilon_f()){
        selectedAction = randomActionSelection();
    }

    return selectedAction;
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

void TabularQ::printQTable(){
    for(int i = 0; i < nStates; i++){
        for(int j = 0; j < nActions; j++){
            if(qTable[i][j] != 0){
                //qDebug() << "State: " << i << ", action: " << j << ", Q value:"<< qTable[i][j] << "\n";
            }
        }
    }
}
