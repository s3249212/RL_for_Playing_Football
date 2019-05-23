#include "gridworld_ih.h"

#include <sstream>
#include <iostream>

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
    stream << totalreward;
    resetMatchStatistics();
    return stream.str();
}

void Gridworld_IH::resetMatchStatistics(){
    totalreward = 0;
}

int Gridworld_IH::getNumberOfAgents(){
    return requiredNumberOfAgents;
}

void Gridworld_IH::setMode(Mode mode){
    this->mode = mode;
}
