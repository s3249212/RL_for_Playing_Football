#include <iostream>
#include "tabularq.h"
#include "player.h"
#include <stdlib.h>
#include <math.h>
#include <fstream>

using namespace std;

TabularQ::TabularQ()
{
    
}

TabularQ::TabularQ(string savefile):
    sourcefile(savefile)
{

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

void TabularQ::train(vector<double> input, double reward, bool terminal){
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

int TabularQ::act(vector<double> input){
    int currentState = static_cast<int>(input.at(0));

    int selectedAction = selectAction(currentState);

    prevAction = selectedAction;

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

double TabularQ::learning_rate_f(){
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

void TabularQ::resetAfterMatch()
{
    prevAction = -1;
    prevState = -1;
}


double TabularQ::epsilon_f(){
    switch(epsilon_change){
    case Constant:
        return epsilon;
    case Exponential_decay:
        return exponential_decay(epsilon, k_epsilon, nSteps);
    }
}

double TabularQ::exponential_decay(double init, double k, int t){
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

    return selectedAction;
}

int TabularQ::softmaxActionSelection(int state)
{
    int selectedAction = -1;

    double sum = 0;

    for(int i = 0; i < nActions; i++){
        sum += exp(softMaxTemp * qTable[state][i]);
    }

    double currentSum = 0.0;
    double random = rand() / static_cast <double> (RAND_MAX);

    for(int i = 0; i < nActions; i++){
        currentSum += exp(softMaxTemp * qTable[state][i]);
        if(random < currentSum / sum){
            selectedAction = i;
            break;
        }
    }

    return selectedAction;
}

int TabularQ::highestQActionSelection(int state)
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

void TabularQ::printQTable(){
    for(int i = 0; i < nStates; i++){
        for(int j = 0; j < nActions; j++){
            if(qTable[i][j] != 0){
                //qDebug() << "State: " << i << ", action: " << j << ", Q value:"<< qTable[i][j] << "\n";
            }
        }
    }
}
