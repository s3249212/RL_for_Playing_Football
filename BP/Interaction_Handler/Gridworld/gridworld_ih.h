#ifndef GRIDWORLD_IH_H
#define GRIDWORLD_IH_H

#include "Player/player.h"
#include "World/Gridworld/gridworld_agent.h"

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
    virtual void setWorld(Gridworld* world){};

    virtual Player* getPlayer(){return NULL;}
};

#endif // GRIDWORLD_IH_H
