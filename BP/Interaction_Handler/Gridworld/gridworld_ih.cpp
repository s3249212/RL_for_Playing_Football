#include "gridworld_ih.h"

Gridworld_IH::Gridworld_IH(Gridworld_IH::InputType inputType, Gridworld_IH::RewardType rewardType, OuputType outputType):
    inputType(inputType),
    rewardType(rewardType),
    outputType(outputType)
{

}

void Gridworld_IH::update(){
    vector<int> input = generateInput();
    int reward = generateReward();

    vector<int> output = player->act(input, reward);

    handleOutput(output);
}

int Gridworld_IH::getTeam(){
    return team;
}

