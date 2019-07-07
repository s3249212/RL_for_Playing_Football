#include <string>

#include "gridworld_ball.h"

Gridworld_Ball::Gridworld_Ball(Gridworld* world, array<int, 2> coord):
    world(world),
    x(coord[0]),
    y(coord[1])
{

}

int Gridworld_Ball::getX(){
    return x;
}

int Gridworld_Ball::getY(){
    return y;
}

array<int, 2> Gridworld_Ball::getCoord(){
    return {x, y};
}

void Gridworld_Ball::move(int deltaX, int deltaY){
    int newX = x + deltaX, newY = y + deltaY;

    if(world->isInGoal({newX, newY})){
        world->updateAfterGoal({newX, newY});
        return;
    }

    if(int n = world->hitsWall({newX, newY})){
        switch(n){
        case 1:
            newY = y;
            automaticDeltaY *= -1;
            break;
        case 2:
            newY = y;
            automaticDeltaY *= -1;
            break;
        case 3:
            newX = x;
            automaticDeltaX *= -1;
            break;
        case 4:
            newX = x;
            automaticDeltaX *= -1;
            newY = y;
            automaticDeltaY *= -1;
            break;
        case 5:
            newX = x;
            automaticDeltaX *= -1;
            newY = y;
            automaticDeltaY *= -1;
            break;
        case 6:
            newX = x;
            automaticDeltaX *= -1;
            break;
        case 7:
            newX = x;
            automaticDeltaX *= -1;
            newY = y;
            automaticDeltaY *= -1;
            break;
        case 8:
            newX = x;
            automaticDeltaX *= -1;
            newY = y;
            automaticDeltaY *= -1;
            break;
        }
    }

    if(world->hitsPlayer({newX, newY})){
        newX = x;
        newY = y;
        automaticDeltaX = 0;
        automaticDeltaY = 0;
        automaticLevel = 0;
    }

    x = newX;
    y = newY;
}

void Gridworld_Ball::setCoord(array<int, 2> coord)
{
    x = coord[0];
    y = coord[1];
}

void Gridworld_Ball::setMovement(int deltaX, int deltaY, int level)
{
    automaticDeltaX = deltaX;
    automaticDeltaY = deltaY;
    automaticLevel = level;
}

void Gridworld_Ball::automaticMove()
{
    for(int i = 0; i < automaticLevel; i++){
        move(automaticDeltaX, automaticDeltaY);
    }
    automaticLevel = 0;
    /*if(automaticLevel > 0){
        automaticLevel--;
    }*/
}


