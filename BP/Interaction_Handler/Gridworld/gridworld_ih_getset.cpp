#include "gridworld_ih.h"

int Gridworld_IH::getTeam(){
    return team;
}

Player* Gridworld_IH::getPlayer(){
    return player;
}

string Gridworld_IH::getStatistics()
{
    stringstream stream;
    stream << world->getScore()[team] << "\t";
    return stream.str();
}

int Gridworld_IH::getNumberOfAgents(){
    return requiredNumberOfAgents;
}

void Gridworld_IH::setMode(Mode mode){
    this->mode = mode;
}
