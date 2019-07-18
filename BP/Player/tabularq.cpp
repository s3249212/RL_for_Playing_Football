#include <iostream>
#include <string>
#include "tabularq.h"
#include <stdlib.h>
#include <math.h>
#include <fstream>

using namespace std;

TabularQ::TabularQ()
{
    
}

TabularQ::TabularQ(string savefile)
{
    this->sourcefile = savefile;
}

TabularQ::~TabularQ(){
    this->nStates = nStates;
    this->nActions = nActions;

    for(int i = 0; i < nStates; i++){
        delete[] qTable[i]; //action size
    }
    delete[] qTable;
}

void TabularQ::initialize(int nStates, int nActions){
    if(sourcefile != ""){
        cout << "Loading the sourcefile" << endl;
        load(sourcefile);
        save("/home/julian/testsavefile");
        return;
    }
    this->nStates = nStates;
    this->nActions = nActions;

    qTable = new double*[nStates]();
    for(int i = 0; i < nStates; i++){
        qTable[i] = new double[nActions](); //action size
        for(int j = 0; j < nActions; j++){
            qTable[i][j] =  minInit + static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / (maxInit - minInit)));
        }
    }
}

void TabularQ::train(vector<double> prevInput, int prevAction, double reward){
    int prevState = static_cast<int>(prevInput[0]);

    if(prevAction != -1){
        qTable[prevState][prevAction] *= 1 - learning_rate_f();
        qTable[prevState][prevAction] += learning_rate_f() * reward;
    }
}

void TabularQ::train(vector<double> prevInput, int prevAction, vector<double> input, double reward){
    int prevState = static_cast<int>(prevInput[0]);
    int currentState = static_cast<int>(input.at(0));

    if(prevAction != -1){
        double maxQAction = qTable[currentState][0];

        for(int i = 1; i < nActions; i++){
            if(qTable[currentState][i] > maxQAction){
                maxQAction = qTable[currentState][i];
            }
        }

        qTable[prevState][prevAction] *= 1 - learning_rate_f();
        qTable[prevState][prevAction] += learning_rate_f() * (reward + discount_factor * maxQAction);
    }

    prevState = currentState;
}

vector<double> TabularQ::getQValues(int currentState){
    vector<double> qValues(nActions, 0);
    for(int i = 0; i < nActions; i++){
        qValues[i] = qTable[currentState][i];
    }
    return qValues;
}

int TabularQ::act(vector<double> input){
    int currentState = static_cast<int>(input.at(0));

    vector<double> qValues = getQValues(currentState);

    int selectedAction = selectAction(qValues);

    nSteps++;

    return selectedAction;
}

void TabularQ::save(string filename)
{
    ofstream filestream(filename);
    filestream << actionSelection << " ";
    filestream << maxInit << " " << minInit << " ";
    filestream << nActions << " " << nStates << " ";

    filestream << learning_rate << " ";
    filestream << discount_factor << " "; //discount factor
    filestream << epsilon << " "; //initial epsilon value for random action selection

    filestream << learning_rate_change << " ";
    filestream << epsilon_change << " ";

    filestream << k_learning_rate << " ";
    filestream << k_epsilon << " ";

    filestream << nSteps << " ";
    for(int i = 0; i < nStates; i++){
        for(int j = 0; j < nActions; j++){
            filestream << qTable[i][j] << " ";
        }
    }

    filestream.close();
}

void TabularQ::load(string filename)
{
    ifstream filestream(filename);
    int helper;

    filestream >> helper;

    actionSelection = static_cast<ActionSelection_t>(helper);

    filestream >> maxInit >> minInit;

    filestream >> nActions >> nStates;

    filestream >> learning_rate;
    filestream >> discount_factor; //discount factor
    filestream >> epsilon; //initial epsilon value for random action selection

    filestream >> helper;
    learning_rate_change = static_cast<Hyperparameter_Change_t>(helper);
    filestream >> helper;
    epsilon_change = static_cast<Hyperparameter_Change_t>(helper);

    filestream >> k_learning_rate;
    filestream >> k_epsilon;

    filestream >> nSteps;

    qTable = new double*[nStates]();
    for(int i = 0; i < nStates; i++){
        qTable[i] = new double[nActions](); //action size
        for(int j = 0; j < nActions; j++){
            filestream >> qTable[i][j];
        }
    }
    filestream.close();
}

void TabularQ::resetAfterEpisode()
{
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
