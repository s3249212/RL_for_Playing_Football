#include "mlpq.h"

#include "Util/neural_network.h"
#include <math.h>
#include <stdlib.h>
#include <iostream>

MLPQ::MLPQ()
{

}

MLPQ::~MLPQ()
{
    nn->print();
    delete nn;
}

void MLPQ::initialize(int nInput, int nActions){
    this->nActions = nActions;

    vector<int> layerSizes;
    layerSizes.push_back(nInput);
    for(int i = 0; i < nHiddenLayers; i++){
        layerSizes.push_back(nHiddenNeuronsPerLayer);
    }
    layerSizes.push_back(nActions);
    nn = new Neural_network(layerSizes);
}

void MLPQ::train(vector<double> input, double reward, bool terminal)
{
    if(prevInput.size() == 0){
        return;
    }

    vector<double> output = nn->forwardPass(input);

    double maxQValue;

    maxQValue = output[0];
    for(int i = 1; i < nActions; i++){
        if(output[i] > maxQValue){
            maxQValue = output[i];
        }
    }

    output = nn->forwardPass(prevInput);

    double target = reward + discount_factor * maxQValue;

    output[prevAction] = target;

    nn->backwardPass(output);

    //nn->print();
}

int MLPQ::act(vector<double> input){
    int selectedAction = selectAction(input);

    prevAction = selectedAction;
    prevInput = input;

    nSteps++;

    return selectedAction;
}

void MLPQ::resetAfterMatch()
{
    prevAction = -1;
    prevInput.clear();
}

int MLPQ::selectAction(vector<double> input)
{
    vector<double> qValues = nn->forwardPass(input);

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

    if(selectedAction == -1 || rand() / static_cast <float> (RAND_MAX)<= epsilon_f()){
        selectedAction = randomActionSelection();
    }

    return selectedAction;
}

int MLPQ::softmaxActionSelection(vector<double> qValues)
{
    int selectedAction = -1;

    float sum = 0;
    float minQAction = exp(qValues[0]);

    for(int i = 1; i < nActions; i++){
        qValues[i] = exp(qValues[i]);
        if(qValues[i] < minQAction){
            minQAction = qValues[i];
        }
        sum += qValues[i];
    }

    sum += -minQAction * nActions;

    float currentSum = 0.0f;
    float random = rand() / static_cast <float> (RAND_MAX);
    for(int i = 0; i < nActions; i++){
        currentSum += qValues[i] + -minQAction;
        if(random < currentSum / (sum + 0.000001f)){
            selectedAction = i;
            break;
        }
    }
    return selectedAction;
}

int MLPQ::highestQActionSelection(vector<double> qValues)
{
    int selectedAction = -1;
    double maxQValue;
    int i = 0;

    for(auto qValue : qValues){
        if(qValue > maxQValue || selectedAction == -1){
            maxQValue = qValue;
            selectedAction = i;
        }
        i++;
    }

    return selectedAction;
}

int MLPQ::randomActionSelection()
{
    return rand() % nActions;
}

float MLPQ::epsilon_f(){
    switch(epsilon_change){
    case Constant:
        return epsilon;
    case Exponential_decay:
        return exponential_decay(epsilon, k_epsilon, nSteps);
    }
}

float MLPQ::exponential_decay(float init, float k, int t){
    return init * exp(-k * t);
}
