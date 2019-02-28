//
// Created by 김유진 on 2019-02-21.
//

#ifndef BACHELORPROJECT_PLAYER_H
#define BACHELORPROJECT_PLAYER_H

#include <vector>

using namespace std;

class Player{
    public:
        virtual vector<double> act(vector<double> input, vector<double> reward);
};


#endif //BACHELORPROJECT_PLAYER_H
