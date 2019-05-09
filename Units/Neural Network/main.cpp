#include <iostream>

#include "neural_network.h"

using namespace std;

int main(int argc, char** argv){
    vector<int> layerSizes;
    layerSizes.push_back(1);
    layerSizes.push_back(1);
    Neural_network nn(layerSizes);
    vector<float> input;
    input.push_back(3.0f);
    //input.push_back(4.0f);
    vector<float> target;
    target.push_back(100.0f);
    //target.push_back(2.0f);
    nn.print();
    for(int i = 0; i < 10; i++){
        vector<float> output = nn.forwardPass(input);
        for(float o: output){
            cout << o << endl;
        }
        cout<<endl;
        nn.print();
        nn.backwardPass(target);
        nn.print();
    }
    vector<float> output = nn.forwardPass(input);
    for(float o: output){
        cout << o << endl;
    }
    cout<<endl;
    nn.print();
    return 0;
}