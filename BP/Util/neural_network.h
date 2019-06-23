#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H

#include <vector>
#include <string>

using namespace std;

class Neural_network{
    public:
    enum Activation_t{
        LINEAR, SIGMOID
    };

    Neural_network(vector<int> layerSizes, vector<Activation_t> activationfunctions);
    Neural_network(string filename);
    ~Neural_network();
    vector<double> forwardPass(vector<double> input);
    void backwardPass(vector<double> targets);
    void save(string filename);
    void load(string filename);

    void print();

    private:
    typedef struct{
        double in;
        double out;
        double errdiff;
    } Node_t;

    vector<int> layerSizes;
    vector<Activation_t> activationfunctions;

    Node_t** nodes;
    double*** weights;

    double learning_rate = 0.02;

    double bias = 1.0f;

    double minInit = -0.01;
    double maxInit = 0.01;

    double activationFunction(double input, int layerIdx);
    double dActivationFunction(double input, int layerIdx);

    
};

#endif
