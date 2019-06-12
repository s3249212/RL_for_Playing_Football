#include "util_functions.h"

#include <vector>
#include <stdlib.h>
#include <cmath>

using namespace std;

vector<double> softmax(vector<double> values, double temp)
{
    double sum = 0.0;
    for(int i = 0; i < values.size(); i++){
        values[i] = exp(values[i] / temp);
        sum += values[i];
    }
    for(int i = 0; i < values.size(); i++){
        values[i] = values[i] / sum;
    }
    return values;
}

int weightedRandomSelection(vector<double> probabilities){
    double random = rand() / static_cast <double> (RAND_MAX);
    double currentSum = 0.0;

    for(int i = 0; i < probabilities.size(); i++){
        currentSum += probabilities[i];
        if(random < currentSum){
            return i;
        }
    }

    return -1;
}

int softmaxActionSelection(vector<double> values, double temp){
    vector<double> probabilities = softmax(values, temp);
    return weightedRandomSelection(probabilities);
}
