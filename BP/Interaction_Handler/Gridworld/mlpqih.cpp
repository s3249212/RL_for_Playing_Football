#include "mlpqih.h"

#include "World/Gridworld/gridworld_agent.h"
#include "World/Gridworld/gridworld_ball.h"

MLPQIH::MLPQIH(Gridworld *gridworld, MLPQ *player, int team)
{
    this->world = gridworld;
    this->player = player;
    this->team = team;
    this->MLPQPlayer = player;

    int nInput = 2 * (gridworld->getBlueTeam().size() + gridworld->getRedTeam().size() + 1);
    int nActions = 18;
    player->initialize(nInput, nActions);
}

vector<double> MLPQIH::generateInput()
{
    vector<double> input;
    input.push_back(agents[0]->getX());
    input.push_back(agents[0]->getY());
    Gridworld_Ball *ball = world->getBall();
    input.push_back(ball->getX());
    input.push_back(ball->getY());
    for(Gridworld_IH* ih: world->getihs()){
        if(ih->getPlayer()!=player && ih->getTeam() == team){
            Gridworld_Agent* agent = ih->getAgents()[0];
            input.push_back(agent->getX());
            input.push_back(agent->getY());
        }
    }
    for(Gridworld_IH* ih: world->getihs()){
        if(ih->getTeam() != team){
            Gridworld_Agent* agent = ih->getAgents()[0];
            input.push_back(agent->getX());
            input.push_back(agent->getY());
        }
    }
    return input;
}
