#include <QDebug>

#include "gridworld_agent.h"
#include "gridworld.h"

Gridworld_Agent::Gridworld_Agent(Gridworld* world, int team):
    world(world),
    team(team)
{

}

Gridworld_Agent::Gridworld_Agent(Gridworld* world, int team, array<int, 2> coord):
    world(world),
    team(team),
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

void Gridworld_Agent::performAction(Actionoptions action){
    int newX = x, newY = y;

    switch(action){
    case MOVELEFT:
        newX--;
        break;
    case MOVERIGHT:
        newX++;
        break;
    case MOVEUP:
        newY--;
        break;
    case MOVEDOWN:
        newY++;
        break;
    case MOVEUPLEFT:
        newX--;
        newY--;
        break;
    case MOVEUPRIGHT:
        newX++;
        newY--;
        break;
    case MOVEDOWNLEFT:
        newX--;
        newY++;
        break;
    case MOVEDOWNRIGHT:
        newX++;
        newY++;
        break;
    }

    array<int, 2> newCoord = {newX, newY};

    if(newCoord == world->getBall()->getCoord()){
        world->addEvent(Gridworld_Event::TOUCH, team);
        world->getBall()->move(newX - x, newY - y);
    }

    //qDebug() << "Coordinates: " << x << y << newX << newY;
    if(world->isWithinBounds(newCoord)){
        //qDebug() << "Changing coordinates";
        x = newX;
        y = newY;
    }
}
