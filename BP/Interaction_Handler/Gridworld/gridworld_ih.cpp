#include "gridworld_ih.h"

void Gridworld_IH::update(bool terminal = 0){
    vector<int> input = generateInput();
    int reward = generateReward();

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