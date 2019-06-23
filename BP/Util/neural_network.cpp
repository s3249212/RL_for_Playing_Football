#include "neural_network.h"

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cmath>

#include "Util/util_functions.h"

double Neural_network::activationFunction(double input, int layerIdx){
    Activation_t activation_type = activationfunctions[layerIdx - 1];
    switch(activation_type){
        case LINEAR:
            return input;
        case SIGMOID:
            return 1.0 / (1.0 + exp(-input));
    }
}

double Neural_network::dActivationFunction(double input, int layerIdx){
    Activation_t activation_type = activationfunctions[layerIdx - 1];
    switch(activation_type){
        case LINEAR:
            return 1;
        case SIGMOID:
            double output = 1.0 / (1.0 + exp(-input));
            return output * (1 - output);
    }
}

Neural_network::Neural_network(vector<int> layerSizes, vector<Activation_t> activationfunctions):
layerSizes(layerSizes),
activationfunctions(activationfunctions)
{
    nodes = new Node_t*[layerSizes.size()];
    weights = new double**[layerSizes.size() - 1];
    for(int i = 0; i < layerSizes.size(); i++){
        nodes[i] = new Node_t[layerSizes.at(i) + 1];
        nodes[i][layerSizes.at(i)].out = bias;
        if(i < layerSizes.size() - 1){
            weights[i] = new double*[layerSizes.at(i) + 1];
            for(int j = 0; j < layerSizes.at(i) + 1; j++){
                weights[i][j] = new double[layerSizes.at(i + 1)];
                for(int k = 0; k < layerSizes.at(i + 1); k++){
                    weights[i][j][k] = minInit + static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / (maxInit - minInit)));
                }
            }
        }
    }
}

Neural_network::Neural_network(string filename)
{
    activationfunctions = {SIGMOID, LINEAR};
    load(filename);
}

Neural_network::~Neural_network(){
    for(int i = 0; i < layerSizes.size(); i++){
        if(i < layerSizes.size() - 1){
            for(int j = 0; j < layerSizes.at(i) + 1; j++){
                delete[] weights[i][j];
            }
            delete[] weights[i];
        }
        delete[] nodes[i];
    }
    delete[] nodes;
    delete[] weights;
}

vector<double> Neural_network::forwardPass(vector<double> input){
    if(input.size() != layerSizes.at(0)){
        cerr << "Given input size is not equal to the size of the input layer!";
        exit(-144);
    }

    // Reset all nodes in the network to 0.
    for(int i = 0; i < layerSizes.size(); i++){
        for(int j = 0; j < layerSizes.at(i); j++){
            nodes[i][j].in = 0;
            nodes[i][j].out = 0;
            nodes[i][j].errdiff = 0;
        }
    }

    //Set the output of the first layer equal to the given input.
    for(int i = 0; i < layerSizes.at(0); i++){
        nodes[0][i].out = input.at(i);
    }

    //timer("Actual forward prop");
    for(int i = 0; i < layerSizes.size() - 1; i++){
        for(int j = 0; j < layerSizes.at(i) + 1; j++){
            if(nodes[i][j].out != 0){
                for(int k = 0; k < layerSizes.at(i + 1); k++){
                    nodes[i + 1][k].in += nodes[i][j].out * weights[i][j][k];
                }
            }
        }
        for(int j = 0; j < layerSizes.at(i + 1); j++){
            //nodes[i + 1][j].in += bias * weights[i][layerSizes.at(i)][j];
            nodes[i + 1][j].out = activationFunction(nodes[i + 1][j].in, i + 1);
        }
    }
    //timer();

    vector<double> output;
    for(int i = 0; i < layerSizes.at(layerSizes.size() - 1); i++){
        output.push_back(nodes[layerSizes.size() - 1][i].out);
    }

    return output;
}

void Neural_network::backwardPass(vector<double> targets){
    if(targets.size() != layerSizes.at(layerSizes.size() - 1)){
        cerr << "Given target size is not equal to the size of the output layer!";
        exit(-145);
    }

    //timer("Setting errdiff to 0");
    for(int i = 0; i < layerSizes.size() - 1; i++){
        for(int j = 0; j < layerSizes[i]; j++){
            nodes[i][j].errdiff = 0;
        }
    }

    //timer("Determining initial errdiffs");
    for(int i = 0; i < layerSizes.at(layerSizes.size() - 1); i++){
        nodes[layerSizes.size() - 1][i].errdiff = (nodes[layerSizes.size() - 1][i].out - targets.at(i));
    }

    //timer("Doing actual back prop");
    for(int i = layerSizes.size() - 1; i > 1; i--){
        for(int k = 0; k < layerSizes.at(i); k++){
            if(nodes[i][k].errdiff != 0){
                nodes[i][k].errdiff *= dActivationFunction(nodes[i][k].in, i);
                for(int j = 0; j < layerSizes.at(i - 1); j++){
                    nodes[i - 1][j].errdiff += nodes[i][k].errdiff * weights[i - 1][j][k];
                }
            }
        }
    }

    for(int i = 0; i < layerSizes.size() - 1; i++){
        for(int j = 0; j < layerSizes[i] + 1; j++){
            if(nodes[i][j].out != 0){
                double lrtimesout = learning_rate * nodes[i][j].out;
                for(int k = 0; k < layerSizes[i + 1]; k++){
                    if(nodes[i + 1][k].errdiff != 0){
                        //double diff_w = nodes[i + 1][k].errdiff ;
                        weights[i][j][k] -= nodes[i + 1][k].errdiff * lrtimesout;//learning_rate * diff_w;
                    }
                }
            }
        }
    }
    /*
    for(int i = layerSizes.size() - 1; i > 0; i--){
        for(int k = 0; k < layerSizes.at(i); k++){
            if(nodes[i][k].errdiff != 0){
                nodes[i][k].errdiff *= dActivationFunction(nodes[i][k].in, i);
                for(int j = 0; j < layerSizes.at(i - 1) + 1; j++){
                    if(i != 1 && j < layerSizes.at(i -1)){
                        nodes[i - 1][j].errdiff += nodes[i][k].errdiff * weights[i - 1][j][k];
                    }

                    if(nodes[i - 1][j].out != 0){
                        double diff_w = nodes[i][k].errdiff * nodes[i - 1][j].out;
                        weights[i - 1][j][k] -= learning_rate * diff_w;
                    }
                }
            }
        }
    }
    */
    //timer();
}

void Neural_network::save(string filename)
{
    std::ofstream filestream(filename);

    filestream << learning_rate << " ";
    filestream << bias << " ";
    filestream << minInit << " ";
    filestream << maxInit << " ";
    filestream << layerSizes.size() << " ";
    for(int l: layerSizes){
        filestream << l << " ";
    }

    for(int i = 0; i < layerSizes.size() - 1; i++){
        for(int j = 0; j < layerSizes.at(i) + 1; j++){
            for(int k = 0; k < layerSizes.at(i + 1); k++){
                filestream << weights[i][j][k] << " ";
            }
        }
    }
    filestream.close();
}

void Neural_network::load(string filename){
    ifstream filestream(filename);
    /*char* str = new char[200];
    filestream.getline(str, 199);
    cout << str;
    string helper;
    filestream >> helper;
    cout << helper;*/
    //learning_rate = static_cast<double>(helper);
    filestream >> learning_rate;
    filestream >> bias;
    filestream >> minInit;
    filestream >> maxInit;

    int nLayers;
    filestream >> nLayers;
    layerSizes.clear();

    for(int i = 0; i < nLayers; i++){
        int l;
        filestream >> l;
        layerSizes.push_back(l);
    }

    nodes = new Node_t*[layerSizes.size()];
    weights = new double**[layerSizes.size() - 1];
    for(int i = 0; i < layerSizes.size(); i++){
        nodes[i] = new Node_t[layerSizes.at(i) + 1];
        nodes[i][layerSizes.at(i)].out = bias;
        if(i < layerSizes.size() - 1){
            weights[i] = new double*[layerSizes.at(i) + 1];
            for(int j = 0; j < layerSizes.at(i) + 1; j++){
                weights[i][j] = new double[layerSizes.at(i + 1)];
                for(int k = 0; k < layerSizes.at(i + 1); k++){
                    filestream >> weights[i][j][k];
                }
            }
        }
    }

    filestream.close();
}

void Neural_network::print(){
    for(int i = 0; i < layerSizes.size() - 1; i++){
        cout << "Layer " << i << endl;
        for(int j = 0; j < layerSizes.at(i) + 1; j++){
            for(int k = 0; k < layerSizes.at(i + 1); k++){
                cout << weights[i][j][k] << " ";
            }
            cout << "\n";
        }
        cout << "\n";
    }

    for(int i = 0; i < layerSizes.size(); i++){
        cout << "Layer " << i << endl;
        cout << "Output of the neurons" << endl;
        cout << "______________" << endl;

        for(int j = 0; j < layerSizes.at(i) + 1; j++){
            cout << "Node " << j << " In:" << nodes[i][j].in << "\tOut:" << nodes[i][j].out << "\tErrdiff:" << nodes[i][j].errdiff << endl;
        }
        cout << "\n";
    }
}
