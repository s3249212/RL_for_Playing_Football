#include <string>

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

void Gridworld::addPlayer(MLPQ *player, int team, int inputType)
{
  Gridworld_IH* ih;
  switch(inputType){
  case 1:
    ih = new VisionGrid_IH(this, player, team, player->getGridSizes());
    break;
  case 0:
  default:
    ih = new MLPQIH(this, player, team);
  }
    addIH(ih);
}

void Gridworld::setType(MLPQ* player, int team, int inputType, int nPlayers){
  for(int i = 0; i < nPlayers; i++){
    Gridworld_IH* ih;

    switch(inputType){
    case 1:
      ih = new VisionGrid_IH(this, player, team, player->getGridSizes());
      ih->initialize();
      break;
    case 0:
    default:
      ih = new MLPQIH(this, player, team);
      ih->initialize();
    }

    if(team == 0){
      leftType.push_back(ih);
    } else {
      rightType.push_back(ih);
    }
  }
}

void Gridworld::setType(RandomPlayer* player, int team, int nPlayers){
  for(int i = 0; i < nPlayers; i++){
    Gridworld_IH* ih;

    ih = new RandomIH(this, player, team);
    ih->initialize();

    if(team == 0){
      leftType.push_back(ih);
    } else {
      rightType.push_back(ih);
    }
  }
}
