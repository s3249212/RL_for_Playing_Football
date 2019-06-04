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
    int nInput = 2 * (world->getBlueTeam().size() + world->getRedTeam().size() + 1);
    int nActions = 18;
    MLPQPlayer->initialize(nInput, nActions);


}


vector<double> MLPQIH::generateInput()
{
    vector<double> input;
    input.push_back(agents[0]->getX() / world->getWidth());
    input.push_back(agents[0]->getY() / world->getHeight());
    for(Gridworld_IH* ih: world->getihs()){
        if(ih->getPlayer()!=player && ih->getTeam() == team){
            Gridworld_Agent* agent = ih->getAgents()[0];
            input.push_back(agent->getX() / world->getWidth());
            input.push_back(agent->getY() / world->getHeight());
        }
    }
    for(Gridworld_IH* ih: world->getihs()){
        if(ih->getTeam() != team){
            Gridworld_Agent* agent = ih->getAgents()[0];
            input.push_back(agent->getX() / world->getWidth());
            input.push_back(agent->getY() / world->getHeight());
        }
    }
    Gridworld_Ball *ball = world->getBall();
    input.push_back(ball->getX() / world->getWidth());
    input.push_back(ball->getY() / world->getHeight());
    return input;
}
