#ifndef MLPQ_H
#define MLPQ_H

#include "player.h"
#include "Util/neural_network.h"

class MLPQ : public Player
{
public:
    MLPQ();
    ~MLPQ();

    void initialize(int nInput, int nActions);

    void train(vector<double> input, double reward, bool terminal = 0);
    int act(vector<double> input);

    void resetAfterMatch();

    void save(string filename);
    void load(string filename);

    MLPQ(string filename);
private:
    Neural_network* nn;

    double discount_factor = 0.9;

    int nHiddenLayers = 1;
    int nHiddenNeuronsPerLayer = 20;

    int nActions;

    int nSteps = 0;

    enum Actionoptions{
        Random = 0, HighestQ, Softmax
    };

    enum Hyperparameter_Change_t {
        Constant = 0, Exponential_decay
    };

    Hyperparameter_Change_t learning_rate_change = Constant;
    Hyperparameter_Change_t epsilon_change = Constant;

    Actionoptions actionSelection = Softmax;

    double exponential_decay(double init, double k, int t);
    double epsilon_f();

    double epsilon = 0.1;
    double k_epsilon = 0.000000001;

    vector<double> prevInput;
    int prevAction = -1;
    int softmaxActionSelection(vector<double> qValues);
    int highestQActionSelection(vector<double> qValues);
    int randomActionSelection();
    int selectAction(vector<double> input);

    string sourcefile;
};

#endif // MLPQ_H
