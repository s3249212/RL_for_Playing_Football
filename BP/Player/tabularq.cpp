#include "tabularq.h"
#include <stdlib.h>
#include <math.h>

using namespace std;

TabularQ::TabularQ()
{
    int nStates = pow(world->getWidth() * world->getHeight(), 3);
    qTable = new float*[nStates]();
    for(int i=0;i<nStates;i++){
        qTable[i] = new float[nActions](); //action size
    }


}

int TabularQ::getStateNumber(vector<int> input){
    int idx = input.at(0);
    for(int i = 1; i < 6; i++){
        int mFactor = i % 2? world->getWidth(): world->getHeight();
        idx = mFactor * idx + input.at(i);
    }
    return idx;
}


float TabularQ::getQTableValue(vector<int> input, int a){
    int idx = getStateNumber(input);
    return qTable[idx][a];
}


//update the value estimate matrix given a new experience
//state = the environment state the experience happened
//finished = whether the episode has ended
void TabularQ::qLearningUpdate(vector<int> input, int reward){
    int currentState = getStateNumber(input);

    if ( prevAction!= -1){ //action = gridWorld_agent action
        int maxQAction = qTable[currentState][0];
        for(int i = 1; i < nActions; i++){
            if(qTable[currentState][i] > maxQAction){
                maxQAction = qTable[currentState][i];
            }
        }

        qTable[prevState][prevAction] *= 1 - learning_rate;
        qTable[prevState][prevAction] += learning_rate * (reward + gamma * maxQAction);
    }
    currentState = prevState;
}

int TabularQ::act(vector<int> input, int reward){
    qLearningUpdate(input, reward);
    return rand() % 8;
}

