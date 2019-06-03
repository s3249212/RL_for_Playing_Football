#include "neural_network.h"

#include <iostream>
#include <stdlib.h>

double Neural_network::activationFunction(double input){
return input;
}

double Neural_network::dActivationFunction(double input){
return 1;
}

Neural_network::Neural_network(vector<int> layerSizes):
layerSizes(layerSizes)
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

    for(int i = 0; i < layerSizes.size() - 1; i++){
        for(int j = 0; j < layerSizes.at(i); j++){
            for(int k = 0; k < layerSizes.at(i + 1); k++){
                nodes[i + 1][k].in += nodes[i][j].out * weights[i][j][k];
            }
        }
        for(int j = 0; j < layerSizes.at(i + 1); j++){
            nodes[i + 1][j].in += bias * weights[i][layerSizes.at(i)][j];
            nodes[i + 1][j].out = activationFunction(nodes[i + 1][j].in);
        }
    }

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

    for(int i = 0; i < layerSizes.at(layerSizes.size() - 1); i++){
        nodes[layerSizes.size() - 1][i].errdiff = nodes[layerSizes.size() - 1][i].out - targets.at(i);
        cout << "Errdiff: " << nodes[layerSizes.size() - 1][i].errdiff << endl;
    }
    cout << endl;

    for(int i = layerSizes.size() -1; i > 0; i--){
        for(int j = 0; j < layerSizes.at(i); j++){
            for(int k = 0; k < layerSizes.at(i - 1) + 1; k++){
                if(k < layerSizes.at(i -1)){
                    nodes[i - 1][k].errdiff += nodes[i][j].errdiff * dActivationFunction(nodes[i][j].in) * weights[i - 1][k][j];
                }
                float diff_w = nodes[i][j].errdiff * dActivationFunction(nodes[i][j].in) * nodes[i - 1][k].out;
                //cout << "Diff_w" << diff_w << endl;
                weights[i - 1][k][j] -= learning_rate * diff_w;
                cout << learning_rate << " " << diff_w << " " << learning_rate * diff_w << endl;
            }
        }
    }
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
            cout << nodes[i][j].out << "\t";
        }
        cout << "\n";
    }
}
