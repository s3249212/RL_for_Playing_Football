#include "gridworld.h"

int Gridworld::hitsWall(array<int, 2> coord){
    int n = 0; //number of wall

    int x = coord[0];
    int y = coord[1];

    if(y == 0){
        n += 1;
    }
    if(y == height - 1){
        n += 2;
    }
    if(x == 0){
        n += 6;
    }
    if(x == width - 1){
        n += 3;
    }

    return n;
}

bool Gridworld::hitsPlayer(array<int,2> coord){
    bool p = false;

    for(Gridworld_Agent* a: agents){
        if(coord == a->getCoord()){
            p = true;
        }
    }

    return p;
}

bool Gridworld::hitsBall(array<int, 2> coord){
    return coord == ball->getCoord();
}

bool Gridworld::isFree(array<int, 2> coord){
    return !hitsWall(coord) && !hitsPlayer(coord) && !hitsBall(coord);
}

bool Gridworld::isInGoal(array<int, 2> coord)
{
    int min = height / 2 - goallength;
    int max = height / 2 + goallength;

    return (coord[0] == 0 || coord[0] == width - 1) &&
            coord[1] >= min && coord[1] <= max;
}

