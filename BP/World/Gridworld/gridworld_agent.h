#ifndef GRIDWORLD_AGENT_H
#define GRIDWORLD_AGENT_H

#include <array>

#include "gridworld.h"

using namespace std;

class Gridworld;

class Gridworld_Agent
{
public:
    enum Actionoptions{
        STANDSTILL = 0, MOVELEFT, MOVERIGHT,MOVEUPRIGHT,MOVEUPLEFT,MOVEDOWNRIGHT,MOVEDOWNLEFT,MOVEUP, MOVEDOWN,
        KICKLEFT1, KICKLEFT2, KICKLEFT3, KICKFORWARD1, KICKFORWARD2, KICKFORWARD3, KICKRIGHT1, KICKRIGHT2, KICKRIGHT3
    };

    Gridworld_Agent(Gridworld* world, int team);
    Gridworld_Agent(Gridworld* world, int team, array<int, 2> coord);

    int getX();
    int getY();

    array<int, 2> getCoord();
    void setCoord(array<int, 2> coord);

    int getTeam();

    void performAction(Actionoptions action);

private:
    int x = 0;
    int y = 0;
    Gridworld* world;
    int team = 0;

    void performMovement(Actionoptions action);
    void performKick(Actionoptions action);

    array<int,2> getKickDirection(int relativeX, int relativeY, bool isLeft);
};

#endif // GRIDWORLD_AGENT_H
