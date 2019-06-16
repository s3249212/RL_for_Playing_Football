#ifndef UTIL_FUNCTIONS_H
#define UTIL_FUNCTIONS_H

#include <vector>

using namespace std;

vector<double> softmax(vector<double> values, double temp);
int weightedRandomSelection(vector<double> probabilities);
double exponential_decay(double init, double k, int t);

#endif // UTIL_FUNCTIONS_H
