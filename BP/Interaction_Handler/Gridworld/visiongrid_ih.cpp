#include "visiongrid_ih.h"

VisionGrid_IH::VisionGrid_IH(Gridworld* gridworld, MLPQ* player, int team, vector<int> gridSizes)
{
    this->world = gridworld;
    this->MLPQPlayer = player;
    this->player = player;
    this->team = team;
    this->gridSizes = gridSizes;
}


void VisionGrid_IH::initialize()
{
    int nInput = ((2 * n + 1) * (2 * n + 1) - 1) * l;
    int nActions = 18;
    MLPQPlayer->initialize(nInput, nActions);
}

void VisionGrid_IH::resetAfterMatch()
{

}

vector<double> VisionGrid_IH::generateInput()
{

}
