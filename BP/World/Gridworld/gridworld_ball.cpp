#include "gridworld_ball.h"

Gridworld_Ball::Gridworld_Ball(Gridworld* world):
    world(world)
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
