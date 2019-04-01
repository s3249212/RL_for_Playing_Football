#include "gridworld.h"

using namespace std;

Gridworld::Gridworld(){
    viewWorld = v;
}

array<int, 2> Gridworld::getBall(){
    array<int, 2> ball = {1,2};
    return ball;
}

vector<array<int,2>> Gridworld::getBlueTeam(){
    vector <array <int, 2>> blue;
   return blue;
}

vector<array<int,2>> Gridworld::getRedTeam(){
   vector <array <int, 2>> red;
   return red;
}

int Gridworld::getGoalLength(){
   return 1;
}

int Gridworld::getWidth(){
    return 800;
}

int Gridworld::getHeight(){
    return 600;
}

