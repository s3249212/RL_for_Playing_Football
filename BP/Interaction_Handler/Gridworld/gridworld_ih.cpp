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

void Gridworld_IH::update(bool terminal){
    vector<double> input = generateInput();
    double reward = generateReward();

    totalreward += reward;

    //if(mode == TRAINING){
        player->train(input, reward, terminal);
    //}
    int output = player->act(input);

    if(totalreward > 1000){
        cout << "High reward?! " << totalreward << endl;
        cout << output << endl << endl;
    }

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

vector<Gridworld_Agent*> Gridworld_IH::getAgents(){
    return agents;
}

void Gridworld_IH::save(string filename)
{
    player->save(filename);
}

void Gridworld_IH::load(string filename)
{
    player->load(filename);
}


