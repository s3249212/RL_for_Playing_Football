#include "tabularq.h"
#include <stdlib.h>
#include <math.h>
#include <QDebug>
using namespace std;

TabularQ::TabularQ(Gridworld* gridworld):
    world(gridworld)
{
    gridworld->getWidth();
    int nStates = pow(world->getWidth() * world->getHeight(), 3);
    //qDebug() << nStates;
    qTable = new float*[nStates]();
    for(int i = 0; i < nStates; i++){
        qTable[i] = new float[nActions](); //action size
    }
}

int TabularQ::getStateNumber(vector<int> input){
    int idx = input.at(0);
    for(int i = 1; i < 6; i++){
        int mFactor = i % 2? world->getHeight(): world->getWidth();
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
    //qDebug() << currentState;

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

    currentState = prevState;
}

int TabularQ::act(vector<int> input, int reward){
    qLearningUpdate(input, reward);

    int currentState = getStateNumber(input);
    float minQAction = qTable[currentState][0];
    float sum = 0;
    int selectedAction = 0;

    for(int i = 1; i < nActions; i++){
        if(qTable[currentState][i] < minQAction){
            minQAction = qTable[currentState][i];
        }
        sum += qTable[currentState][i];
    }

    sum += -minQAction * nActions;

    float sumPrev = 0.0f;
    float random = rand() % 1000000 / 1000000.0f;
    for(int i = 0; i < nActions; i++){
        if(random < (sumPrev + qTable[currentState][i] + -minQAction) / sum){
            selectedAction = i;
            break;
        }
        sumPrev += qTable[currentState][i] + -minQAction;
    }

    qDebug() << "Selected action" << selectedAction;

    totalReward += reward;

    int currentAction;
    if(rand() % 100 < 80){
        //qDebug() << "Selected action";
        currentAction = selectedAction;
    } else {
        //qDebug() << "Random action";
        currentAction = rand() % 8;
    }

    prevAction = currentAction;

    return currentAction;
}

