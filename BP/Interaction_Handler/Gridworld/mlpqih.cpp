#include <array>
#include <string>
#include <vector>

#include "mlpqih.h"

#include "World/Gridworld/gridworld_agent.h"
#include "World/Gridworld/gridworld_ball.h"

MLPQIH::MLPQIH(Gridworld *gridworld, MLPQ *player, int team)
{
    this->world = gridworld;
    this->player = player;
    this->team = team;
    this->MLPQPlayer = player;
}

void MLPQIH::initialize()
{
    nInput = 4 * world->getWidth() * world->getHeight();
    int nActions = 18;
    input = new vector<double>(nInput, 0);
    MLPQPlayer->initialize(nInput, nActions);
}

vector<double> MLPQIH::generateInput()
{
    for(int i = 0; i < nInput; i++){
        (*input)[i] = 0;
    }

    int idx = agents[0]->getX() * world->getHeight() + agents[0]->getY();
    (*input)[idx] = 1;

    for(Gridworld_Agent* agent: world->getAgents()){
        idx = agent->getX() * world->getHeight() + agent->getY();
        if(agent->getTeam() == team && agent != agents[0]){
            idx += world->getWidth() * world->getHeight();
            (*input)[idx] = 1;
        } else if(agent->getTeam() != team){
            idx += 2 * world->getWidth() * world->getHeight();
            (*input)[idx] = 1;
        }
    }

    idx = world->getBall()->getX() * world->getHeight() + world->getBall()->getY() + 3 * world->getWidth() * world->getHeight();
    (*input)[idx] = 1;

    return *input;
}
