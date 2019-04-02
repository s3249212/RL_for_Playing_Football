#ifndef GRIDWORLD_AGENT_H
#define GRIDWORLD_AGENT_H

#include <array>

#include "gridworld.h"

using namespace std;

class Gridworld;

class Gridworld_Agent
{
private:
    int x;
    int y;
    Gridworld* world;
    int team;

public:
    Gridworld_Agent(Gridworld* world);
    Gridworld_Agent(Gridworld* world, array<int, 2> coord);

    int getX();
    int getY();

    array<int, 2> getCoord();
    void setCoord(array<int, 2> coord);

    int getTeam();
};

#endif // GRIDWORLD_AGENT_H
