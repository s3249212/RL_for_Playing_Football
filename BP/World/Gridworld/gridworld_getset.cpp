#include "gridworld.h"

array<int, 2> Gridworld::getBallCoord(){
    return ball->getCoord();
}

Gridworld_Ball* Gridworld::getBall(){
    return ball;
}

vector<array<int,2>> Gridworld::getTeam(int x){
    vector <array <int, 2>> team;
    for(Gridworld_Agent* a: agents){
        if(a->getTeam() == x){
            team.push_back(a->getCoord());
        }
    }
    return team;
}

vector<array<int,2>> Gridworld::getBlueTeam(){
    return getTeam(0);
}

vector<array<int,2>> Gridworld::getRedTeam(){
    return getTeam(1);
}

int Gridworld::getGoalLength(){
    return goallength;
}

int Gridworld::getWidth(){
    return width;
}

int Gridworld::getHeight(){
    return height;
}

array<int, 2> Gridworld::getScore()
{
    return score->getScore();
}

vector<Gridworld_Event*> Gridworld::getEventLog(){
    return eventLog;
}
