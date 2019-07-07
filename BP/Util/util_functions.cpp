#include "util_functions.h"

#include <vector>
#include <stdlib.h>
#include <cmath>
#include <iostream>
#include <chrono>
#include <array>
#include <string>

using namespace std;
using namespace std::chrono;

vector<double> softmax(vector<double> values, double temp)
{
    double sum = 0.0;

    double maxValue = values[0];
    for(int i = 1; i < values.size(); i++){
        if(maxValue < values[i]){
            maxValue = values[i];
        }
    }

    for(int i = 0; i < values.size(); i++){
        values[i] = exp((values[i] - maxValue) / temp);
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

double exponential_decay(double init, double k, int t){
    return init * exp(-k * t);
}

high_resolution_clock::time_point t1;
string functionname = "";
array<int, 3> times = {1000000, 60, 60};
array<string, 4> names = {"microseconds", "seconds", "minutes", "hours"};

void timer(string newFunctionName){
    if(functionname != ""){
        auto elapsedTime = duration_cast<microseconds>( high_resolution_clock::now() - t1 ).count();
        cout << "Time of " << functionname << ":";
        for(int i = names.size() - 1; i >= 0; i--){
            auto helper = elapsedTime;
            for(int j = 0; j < i; j++){
                helper /= times[j];
            }
            if(helper > 0){
                cout << " " << helper << " " << names[i];
            }
        }
        cout << endl;
    }
    functionname = newFunctionName;
    t1 = high_resolution_clock::now();
}
