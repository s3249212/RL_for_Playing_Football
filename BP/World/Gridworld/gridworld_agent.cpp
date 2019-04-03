#include "gridworld_agent.h"
#include "gridworld.h"

Gridworld_Agent::Gridworld_Agent(Gridworld* world):
    world(world)
{

}

Gridworld_Agent::Gridworld_Agent(Gridworld* world, array<int, 2> coord):
    world(world),
    x(coord[0]),
    y(coord[1])
{}

int Gridworld_Agent::getX(){
    return x;
}

int Gridworld_Agent::getY(){
    return y;
}

array<int, 2> Gridworld_Agent::getCoord(){
    return {x, y};
}

void Gridworld_Agent::setCoord(array<int, 2> coord){
    x = coord[0];
    y = coord[1];
}

int Gridworld_Agent::getTeam(){
    return team;
}
