#ifndef GRIDWORLD_BALL_H
#define GRIDWORLD_BALL_H

#include "gridworld.h"

using namespace std;

class Gridworld;

class Gridworld_Ball
{
private:
    int x = 1;
    int y = 2;
    Gridworld* world;

public:
    Gridworld_Ball(Gridworld* world);
    Gridworld_Ball(Gridworld* world, array<int, 2> coord);

    int getX();
    int getY();

    array<int, 2> getCoord();

    void move(int deltaX, int deltaY);

    void setCoord(array<int, 2> coord);
};

#endif // GRIDWORLD_BALL_H
