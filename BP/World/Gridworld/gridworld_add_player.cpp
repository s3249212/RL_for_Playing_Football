#include "gridworld.h"

#include "Interaction_Handler/Gridworld/tabularqih.h"
#include "Interaction_Handler/Gridworld/randomih.h"
#include "Interaction_Handler/Gridworld/mlpqih.h"
#include "Interaction_Handler/Gridworld/visiongrid_ih.h"

void Gridworld::addPlayer(RandomPlayer *player, int team){
    Gridworld_IH* ih = new RandomIH(this, player, team);
    addIH(ih);
}

void Gridworld::addIH(Gridworld_IH *ih){
    ihs.push_back(ih);

    int nAgents = ih->getNumberOfAgents();
    for(int i = 0; i < nAgents; i++){
        int x = ih->getTeam() == 0? getBlueTeam().size() + 1: width - 2 - getRedTeam().size();

        Gridworld_Agent * agent = new Gridworld_Agent(this, ih->getTeam(), {x, 1});

        addAgent(agent);
        ih->addAgent(agent);
    }
}

void Gridworld::addAgent(Gridworld_Agent *agent){
    agents.push_back(agent);
}

void Gridworld::addPlayer(TabularQ *player, int team)
{
    Gridworld_IH* ih = new TabularQIH(this, player, team);
    addIH(ih);
}

void Gridworld::addPlayer(MLPQ *player, int team)
{
    Gridworld_IH* ih = new VisionGrid_IH(this, player, team, player->getGridSizes());
    addIH(ih);
}
