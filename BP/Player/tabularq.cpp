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
    this->nStates = nStates;
    //qDebug() << nStates;
    qTable = new float*[nStates]();
    for(int i = 0; i < nStates; i++){
        qTable[i] = new float[nActions](); //action size
    }
}

void TabularQ::updateEndOfMatch(vector<int> input, int reward)
{

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
        /*if(reward != 0){
            qDebug() << "Updating q value" << reward << learning_rate << gamma;
        }*/
        //qDebug() << qTable[prevState][prevAction];
        float maxQAction = qTable[currentState][0];

        for(int i = 1; i < nActions; i++){
            if(qTable[currentState][i] > maxQAction){
                maxQAction = qTable[currentState][i];
            }
        }

        qTable[prevState][prevAction] *= 1 - learning_rate;
        qTable[prevState][prevAction] += learning_rate * (reward + gamma * maxQAction);
        //qDebug() << qTable[prevState][prevAction];
        //qDebug() << maxQAction << "-";
    }

    //currentState = prevState;
    prevState = currentState;
}

int TabularQ::act(vector<int> input, int reward){
    qLearningUpdate(input, reward);

    int currentState = getStateNumber(input);
    float minQAction = qTable[currentState][0];
    float sum = 0;
    int selectedAction = -1;

    for(int i = 1; i < nActions; i++){
        if(qTable[currentState][i] < minQAction){
            minQAction = qTable[currentState][i];
        }
        sum += qTable[currentState][i];
    }

    sum += -minQAction * nActions;

    float currentSum = 0.0f;
    float random = rand() % 1000000 / 1000000.0f;
    for(int i = 0; i < nActions; i++){
        currentSum += qTable[currentState][i] + -minQAction;
        //qDebug() << random << currentSum << sum;
        if(random < currentSum / (sum + 0.000001f)){
            selectedAction = i;
            break;
        }
    }

    //qDebug() << "Selected action" << selectedAction;

    totalReward += reward;

    int currentAction;
    if(rand() % 100 < 80 && selectedAction != -1){
        //qDebug() << "Selected action";
        currentAction = selectedAction;
    } else {
        //qDebug() << "Random action";
        currentAction = rand() % 8;
    }



    prevAction = currentAction;

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

