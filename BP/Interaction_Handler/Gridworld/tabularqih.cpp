#include "tabularqih.h"
#include "gridworld_ih.h"

TabularQIH::TabularQIH(Gridworld* gridworld, TabularQ* player, int team):
tabularQPlayer(player)
{
    this->player = player;
    this->world = gridworld;
    this->team = team;

    int nstates = world->getWidth() * world->getHeight();
    int nactions = 8;
    tabularQPlayer->initialize(nstates, nactions);
}

vector<double> TabularQIH::generateInput(){
    vector<double> input;
    input.push_back(world->getBallCoord()[0]);
    input.push_back(world->getBallCoord()[1]);
    input.push_back(agents[0]->getCoord()[0]);
    input.push_back(agents[0]->getCoord()[1]);
    int opponentTeam = (team == 1 ? 0: 1);
    input.push_back(world->getTeam(opponentTeam).at(0)[0]);
    input.push_back(world->getTeam(opponentTeam).at(0)[1]);

    return input;
}

int TabularQIH::getStateNumber(vector<double> input){
    int idx = input.at(0);
    for(int i = 1; i < 6; i++){
        int mFactor = i % 2? world->getHeight(): world->getWidth();
        idx = mFactor * idx + input.at(i);
    }
    return idx;
}
