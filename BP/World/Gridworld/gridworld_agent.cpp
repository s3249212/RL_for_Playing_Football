#include <string>

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
    performMovement(action);
    performKick(action);
}

void Gridworld_Agent::performMovement(Actionoptions action){
    int newX = x, newY = y;

    switch(action){
    case STANDSTILL:
        break;
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
        world->getBall()->setMovement(0, 0, 0);
    }

    if(world->isFree(newCoord)){
        x = newX;
        y = newY;
    }
}

void Gridworld_Agent::performKick(Actionoptions action){
    bool isLeft;
    int level = 0;
    array<int, 2> ballCoord = world->getBall()->getCoord();

    if(ballCoord[0] >= x - 1 && ballCoord[0] <= x + 1 &&
            ballCoord[1] >= y - 1 && ballCoord[1] <= y + 1){
        int relativeX = ballCoord[0] - x;
        int relativeY = ballCoord[1] - y;

        array<int, 2> kickdeltas;
        switch(action){
        case KICKLEFT1:
            isLeft = true;
            level = 1;
            kickdeltas = getKickDirection(relativeX, relativeY, isLeft);
            break;
        case KICKLEFT2:
            isLeft = true;
            level = 2;
            kickdeltas = getKickDirection(relativeX, relativeY, isLeft);
            break;
        case KICKLEFT3:
            isLeft = true;
            level = 3;
            kickdeltas = getKickDirection(relativeX, relativeY, isLeft);
            break;
        case KICKFORWARD1:
            level = 1;
            kickdeltas = {relativeX, relativeY};
            break;
        case KICKFORWARD2:
            level = 2;
            kickdeltas = {relativeX, relativeY};
            break;
        case KICKFORWARD3:
            level = 3;
            kickdeltas = {relativeX, relativeY};
            break;
        case KICKRIGHT1:
            isLeft = false;
            level = 1;
            kickdeltas = getKickDirection(relativeX, relativeY, isLeft);
            break;
        case KICKRIGHT2:
            isLeft = false;
            level = 2;
            kickdeltas = getKickDirection(relativeX, relativeY, isLeft);
            break;
        case KICKRIGHT3:
            isLeft = false;
            level = 3;
            kickdeltas = getKickDirection(relativeX, relativeY, isLeft);
            break;
        default:
            level = 0;
        }
        if(level > 0){
            world->getBall()->setMovement(kickdeltas[0], kickdeltas[1], level);
        }
    }
}

array<int,2> Gridworld_Agent::getKickDirection(int relativeX, int relativeY, bool isLeft){
    int x = relativeX;
    int y = relativeY;
    if(isLeft){
        if(relativeX == 0){
            x = relativeY;
            y = relativeY;
        } else if(relativeY == 0) {
            x = relativeX;
            y = -relativeX;
        } else if(relativeX == relativeY){
            x = 0;
            y = relativeY;
        } else {
            x = relativeX;
            y = 0;
        }
    } else {
        if(relativeX == 0){
            x = -relativeY;
            y = relativeY;
        } else if(relativeY == 0) {
            x = relativeX;
            y = relativeX;
        } else if(relativeX == relativeY){
            x = relativeX;
            y = 0;
        } else {
            x = 0;
            y = relativeY;
        }
    }

    return {x, y};
}
