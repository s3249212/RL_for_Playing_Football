#include <string>
#include "gridworld_ih.h"

Gridworld_IH::Gridworld_IH(){
    initRewardGeneration();
}

Gridworld_IH::~Gridworld_IH(){
    for (int i = 0; i < 4; ++i) {
        delete[] rewards[i];
    }
    delete[] rewards;
}

void Gridworld_IH::updateEndEpisode()
{
    double reward = generateRewardEndEpisode();

    totalreward += reward;

    if(mode == TRAINING){
        player->train(prevInput, prevAction, reward);
    }
}

void Gridworld_IH::update(){
    vector<double> input = generateInput();
    double reward = generateReward();

    totalreward += reward;

    if(mode == TRAINING){
        player->train(prevInput, prevAction, input, reward);
    }

    int output = player->act(input);


    prevAction = output;

    if(output < 0){
        cout << "Selected action: "<< output;
        exit(0);
    }

    prevInput = input;

    handleOutput(output);
}

void Gridworld_IH::resetAfterEpisode()
{
    prevInput.clear();
    prevAction = 0;

    player->resetAfterEpisode();
}

void Gridworld_IH::handleOutput(int output){
    agents.at(0)->performAction(static_cast<Gridworld_Agent::Actionoptions>(output));
}

void Gridworld_IH::addAgent(Gridworld_Agent *agent){
    agents.push_back(agent);
}

vector<Gridworld_Agent*> Gridworld_IH::getAgents(){
    return agents;
}

void Gridworld_IH::clearAgents(){
    agents.clear();
}

void Gridworld_IH::save(string filename)
{
    player->save(filename);
}

void Gridworld_IH::load(string filename)
{
    player->load(filename);
}


