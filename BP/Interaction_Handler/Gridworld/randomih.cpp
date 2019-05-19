#include "randomih.h"

RandomIH::RandomIH(Gridworld* gridworld, RandomPlayer* player, int team)
{
    this->world = gridworld;
    this->player = player;
    this->team = team;
}

