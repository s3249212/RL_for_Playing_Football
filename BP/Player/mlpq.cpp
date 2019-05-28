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
    delete nn;
}

void MLPQ::initialize(int nInput, int nActions){
    this->nActions = nActions;

    vector<int> layerSizes;
    layerSizes.push_back(nInput + 1);
    for(int i = 0; i < nHiddenLayers; i++){
        layerSizes.push_back(nHiddenNeuronsPerLayer);
    }
    layerSizes.push_back(1);
    nn = new Neural_network(layerSizes);
}

void MLPQ::train(vector<double> input, double reward, bool terminal)
{
    vector<double> output;
    int qValue, maxQValue;

    input.push_back(0);
    output = nn->forwardPass(input);
    maxQValue = output[0];

    for(int i = 1; i < nActions; i++){
        input.at(input.size() - 1) = i;
        output = nn->forwardPass(input);
        qValue = output[0];
        if(qValue > maxQValue){
            maxQValue = qValue;
        }
    }

    prevInput.push_back(prevAction);
    nn->forwardPass(prevInput).at(0);

    double target = reward + discount_factor * maxQValue;

    nn->backwardPass({target});
}

int MLPQ::act(vector<double> input){
    int selectedAction = selectAction(input);

    prevAction = selectedAction;

    nSteps++;
    return selectedAction;
}

int MLPQ::selectAction(vector<double> input)
{
    vector<double> output, qValues;

    input.push_back(0);

    for(int i = 0; i < nActions; i++){
        input.at(input.size() - 1) = i;
        output = nn->forwardPass(input);
        qValues.push_back(output[0]);
    }

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

    if(selectedAction == -1 || rand() % 100 / 100.0f <= epsilon_f()){
        selectedAction = randomActionSelection();
    }

    return selectedAction;
}

int MLPQ::softmaxActionSelection(vector<double> qValues)
{
    int selectedAction = -1;

    float sum = 0;
    float minQAction = qValues[0];

    for(int i = 1; i < nActions; i++){
        qValues[i] = exp(qValues[i]);
        if(qValues[i] < minQAction){
            minQAction = qValues[i];
        }
        sum += qValues[i];
    }

    sum += -minQAction * nActions;

    float currentSum = 0.0f;
    float random = rand() % 1000000 / 1000000.0f;
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
