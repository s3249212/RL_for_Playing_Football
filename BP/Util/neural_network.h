#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H

#include <vector>
#include <string>

using namespace std;

class Neural_network{
    private:
    typedef struct{
        double in;
        double out;
        double errdiff;
    } Node_t;

    vector<int> layerSizes;

    Node_t** nodes;
    double*** weights;

    double learning_rate = 0.01;

    double bias = 1.0f;

    double minInit = -1.0;
    double maxInit = 1.0;

    double activationFunction(double input);
    double dActivationFunction(double input);

    public:
    Neural_network(vector<int> layerSizes);
    Neural_network(string filename);
    ~Neural_network();
    vector<double> forwardPass(vector<double> input);
    void backwardPass(vector<double> targets);
    void save(string filename);
    void load(string filename);

    void print();
};

#endif
