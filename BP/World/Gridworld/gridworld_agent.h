#ifndef GRIDWORLD_AGENT_H
#define GRIDWORLD_AGENT_H

#include <array>

#include "gridworld.h"

using namespace std;

class Gridworld;

class Gridworld_Agent
{
private:
    int x = 0;
    int y = 0;
    Gridworld* world;
    int team = 0;

public:
    enum Actionoptions{
        MOVELEFT=0, MOVERIGHT,MOVEUPRIGHT,MOVEUPLEFT,MOVEDOWNRIGHT,MOVEDOWNLEFT,MOVEUP, MOVEDOWN, SHOOT
    };

    Gridworld_Agent(Gridworld* world, int team);
    Gridworld_Agent(Gridworld* world, int team, array<int, 2> coord);

    int getX();
    int getY();

    array<int, 2> getCoord();
    void setCoord(array<int, 2> coord);

    int getTeam();

    void performAction(Actionoptions action);


};

#endif // GRIDWORLD_AGENT_H
