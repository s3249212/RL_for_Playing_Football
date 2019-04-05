#ifndef GRIDWORLD_IH_H
#define GRIDWORLD_IH_H

#include "gridworld_agent.h"

class Gridworld_Agent;

class Gridworld_IH
{
private:
    int team;

public:
    Gridworld_IH();

    virtual int getNumberOfAgents(){return 0;}
    virtual void addAgent(Gridworld_Agent* agent){};
    virtual void update(){};

    virtual int getTeam();
};

#endif // GRIDWORLD_IH_H
