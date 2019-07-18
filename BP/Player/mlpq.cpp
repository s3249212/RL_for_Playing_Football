#include <array>
#include <string>
#include <vector>

#include "mlpq.h"

#include "Util/neural_network.h"
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

MLPQ::MLPQ()
{

}

MLPQ::MLPQ(string filename)
{
    this->sourcefile = filename;
    load(sourcefile);
}

MLPQ::~MLPQ()
{
    nn->print();
    delete nn;
}

void MLPQ::initialize(int nInput, int nActions){
    if(sourcefile != ""){
        return;
    }
    this->nActions = nActions;

    vector<int> layerSizes;
    layerSizes.push_back(nInput);
    for(int i = 0; i < nHiddenLayers; i++){
        layerSizes.push_back(nHiddenNeuronsPerLayer);
    }
    layerSizes.push_back(nActions);

    nn = new Neural_network(layerSizes, activationFunctions);

}

void MLPQ::train(vector<double> prevInput, int prevAction, double reward){
    if(prevInput.size() == 0 || prevAction < 0){
        return;
    }

    vector<double> output = nn->forwardPass(prevInput);

    double target = reward;

    output[prevAction] = target;

    nn->backwardPass(output);
}

void MLPQ::train(vector<double> prevInput, int prevAction, vector<double> input, double reward)
{
    if(prevInput.size() == 0 || prevAction < 0){
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
}

int MLPQ::act(vector<double> input){
    vector<double> qValues = nn->forwardPass(input);

    int selectedAction = selectAction(qValues);

    nSteps++;

    return selectedAction;
}

void MLPQ::resetAfterEpisode()
{
}

void MLPQ::save(string filename)
{
    std::ofstream filestream(filename);
    filestream << discount_factor << " ";
    filestream << nHiddenLayers << " ";
    filestream << nHiddenNeuronsPerLayer << " ";
    filestream << nActions << " ";
    filestream << nSteps << " ";
    filestream << learning_rate_change << " ";
    filestream << epsilon_change << " ";
    filestream << actionSelection << " ";

    filestream << epsilon << " ";
    filestream << k_epsilon << " ";

    string nnfilename = filename.append("nn");
    filestream << nnfilename << " ";
    nn->save(nnfilename);

    filestream << softMaxDecreasingPeriod << " ";
    filestream << minSoftMaxTemp << " ";
    filestream << maxSoftMaxTemp << " ";

    filestream << gridSizes.size() << " ";
    for(int g: gridSizes){
        filestream << g << " ";
    }
}

void MLPQ::load(string filename)
{
    std::ifstream filestream(filename);
    filestream >> discount_factor;
    filestream >> nHiddenLayers;
    filestream >> nHiddenNeuronsPerLayer;
    filestream >> nActions;
    filestream >> nSteps;

    int helper;
    filestream >> helper;
    learning_rate_change = static_cast<Hyperparameter_Change_t>(helper);
    filestream >> helper;
    epsilon_change = static_cast<Hyperparameter_Change_t>(helper);
    filestream >> helper;
    actionSelection = static_cast<ActionSelection_t>(helper);

    filestream >> epsilon;
    filestream >> k_epsilon;

    string nnfilename;
    filestream >> nnfilename;
    nn = new Neural_network(nnfilename);

    filestream >> softMaxDecreasingPeriod;
    filestream >> minSoftMaxTemp;
    filestream >> maxSoftMaxTemp;

    int ngridsizes;
    filestream >> ngridsizes;
    gridSizes.clear();
    for(int i = 0; i < ngridsizes; i++){
        int g;
        filestream >> g;
        gridSizes.push_back(g);
    }
}
