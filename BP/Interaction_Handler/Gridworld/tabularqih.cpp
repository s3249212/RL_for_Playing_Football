#include "tabularqih.h"

TabularQIH::TabularQIH(Gridworld* gridworld, TabularQ* player, int team):
gridworld(gridworld),
player(player),
tabularQPlayer(player),
team(team)
{
    tabularQPlayer->initialize();
}

TabularQIH::generateInput(){
    vector<int> input;
    input.push_back(world->getBallCoord()[0]);
    input.push_back(world->getBallCoord()[1]);
    input.push_back(agents[0]->getCoord()[0]);
    input.push_back(agents[0]->getCoord()[1]);
    int opponentTeam = (team == 1 ? 0: 1);
    input.push_back(world->getTeam(opponentTeam).at(0)[0]);
    input.push_back(world->getTeam(opponentTeam).at(0)[1]);

    return input;
}