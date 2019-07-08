#include <array>
#include <string>
#include <vector>

#include <sstream>
#include <iostream>

#include "tabularqih.h"
#include "gridworld_ih.h"

TabularQIH::TabularQIH(Gridworld* gridworld, TabularQ* player, int team):
tabularQPlayer(player)
{
    this->player = player;
    this->world = gridworld;
    this->team = team;
}

void TabularQIH::initialize()
{
    int nstates = world->getWidth() * world->getHeight();
    nstates = nstates * nstates * nstates;
    int nactions = 18;
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

    int state = getStateNumber(input);
    input.clear();
    input.push_back(state);

    return input;
}

string TabularQIH::getStatistics()
{
    stringstream stream;
    stream << world->getScore()[team] << "\t";
    stream << totalreward << "\t";
    stream << tabularQPlayer->learning_rate_f();
    resetMatchStatistics();
    return stream.str();
}

int TabularQIH::getStateNumber(vector<double> input){
    int idx = input.at(0);
    for(int i = 1; i < 6; i++){
        int mFactor = i % 2? world->getHeight(): world->getWidth();
        idx = mFactor * idx + input.at(i);
    }
    return idx;
}
