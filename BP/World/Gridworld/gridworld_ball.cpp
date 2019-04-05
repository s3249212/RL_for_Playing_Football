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
    }

    if(world->isWithinBounds({newX, newY})){
        x = newX;
        y = newY;
    }
}
