#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H

#include <vector>

using namespace std;

class Neural_network{
    private:
    typedef struct{
        float in;
        float out;
        float errdiff;
    } Node_t;

    vector<int> layerSizes;

    Node_t** nodes;
    float*** weights;

    float learning_rate = 0.01f;

    float bias = 1.0f;

    float minInit = -1.0f;
    float maxInit = 1.0f;

    float activationFunction(float input);
    float dActivationFunction(float input);

    public:
    Neural_network(vector<int> layerSizes);
    ~Neural_network();
    vector<float> forwardPass(vector<float> input);
    void backwardPass(vector<float> targets);

    void print();
};

#endif
