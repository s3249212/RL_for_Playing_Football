#include "mlpq.h"

#include "Util/neural_network.h"
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

using namespace std;

MLPQ::MLPQ()
{

}

MLPQ::MLPQ(string filename)
{
    this->sourcefile = filename;
}

MLPQ::~MLPQ()
{
    nn->print();
    delete nn;
}

void MLPQ::initialize(int nInput, int nActions){
    if(sourcefile != ""){
        load(sourcefile);
        return;
    }
    this->nActions = nActions;

    vector<int> layerSizes;
    layerSizes.push_back(nInput);
    for(int i = 0; i < nHiddenLayers; i++){
        layerSizes.push_back(nHiddenNeuronsPerLayer);
    }
    layerSizes.push_back(nActions);

    vector<Neural_network::Activation_t> activationFunctions;

    activationFunctions.push_back(Neural_network::SIGMOID);
    activationFunctions.push_back(Neural_network::LINEAR);
    nn = new Neural_network(layerSizes, activationFunctions);

}

void MLPQ::train(double reward){
    if(prevInput.size() == 0 || prevAction < 0){
        return;
    }

    vector<double> output = nn->forwardPass(prevInput);

    double target = reward;

    output[prevAction] = target;

    nn->backwardPass(output);
}

void MLPQ::train(vector<double> input, double reward)
{
    if(prevInput.size() == 0 || prevAction < 0){
        return;
    }

    vector<double> output = nn->forwardPass(input);

    double maxQValue;

    maxQValue = output[0];
    for(int i = 1; i < nActions; i++){
        //cout << output[i] << "\t";
        if(output[i] > maxQValue){
            maxQValue = output[i];
        }
    }
    //cout << endl;
    //cout << "Max Q Value: " << maxQValue << endl;

    output = nn->forwardPass(prevInput);

    double target = reward + discount_factor * maxQValue;

    /*cout << "Reward: " << reward << " discountfactor: " << discount_factor << " maxQValue: " << maxQValue << " target: " << target << endl;
    //cout << endl;

    cout << "BackwardPass results:" << endl;
    cout << "Previous output" << endl;
    for(double d: output){
        cout << d << "\t";
    }
    cout << endl;*/

    output[prevAction] = target;

    /*cout << "Target:"<< endl;
    for(double d: output){
        cout << d << "\t";
    }
    cout << endl;*/

    nn->backwardPass(output);

    /*output = nn->forwardPass(prevInput);

    cout << "New output:" << endl;
    for(double d: output){
        cout << d << "\t";
    }
    cout << endl << endl;*/

    //nn->print();
}

int MLPQ::act(vector<double> input){
    vector<double> qValues = nn->forwardPass(input);

    int selectedAction = selectAction(qValues);

    prevAction = selectedAction;

    if(selectedAction < 0){
        cout << "Selected action: "<< selectedAction;
        exit(0);
    }

    prevInput = input;

    nSteps++;

    return selectedAction;
}

void MLPQ::resetAfterEpisode()
{
    prevAction = -1;
    prevInput.clear();
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
}
