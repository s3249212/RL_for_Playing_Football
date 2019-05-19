#include "gridworld_ih.h"

Gridworld_IH::Gridworld_IH(){

}

void Gridworld_IH::update(bool terminal){
    vector<double> input = generateInput();
    double reward = generateReward();

    if(mode == TRAINING){
        player->learn(input, reward, terminal);
    }
    int output = player->act(input);

    handleOutput(output);
}

void Gridworld_IH::resetAfterMatch()
{
    player->resetAfterMatch();
}

void Gridworld_IH::handleOutput(int output){
    agents.at(0)->performAction(static_cast<Gridworld_Agent::Actionoptions>(output));
}

void Gridworld_IH::addAgent(Gridworld_Agent *agent){
    agents.push_back(agent);
}
