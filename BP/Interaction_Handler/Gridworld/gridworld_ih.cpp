#include "gridworld_ih.h"

#include <QDebug>

Gridworld_IH::Gridworld_IH(Player* player, int team, int nAgents, Gridworld_IH::InputType inputType, Gridworld_IH::RewardType rewardType, OutputType outputType):
    player(player),
    team(team),
    requiredNumberOfAgents(nAgents),
    inputType(inputType),
    rewardType(rewardType),
    outputType(outputType)
{
    initRewardGeneration();

}

void Gridworld_IH::update(){
    //qDebug() << "Updating";
    //qDebug() << "Generating input...";
    vector<int> input = generateInput();
    //qDebug() << "Generating reward...";
    int reward = generateReward();

    //qDebug() << "Generating output...";
    int output = player->act(input, reward);

    handleOutput(output);
}

vector<int> Gridworld_IH::generateInput(){
    switch(inputType){
        case TabularQ:
            return inputTabularQ();
    }
    exit(-1);
}

int Gridworld_IH::generateReward(){
    switch(rewardType){
        case GOAL_TOUCH:
            return rewardGoalTouch();
    }
    return 0;
}

void Gridworld_IH::handleOutput(int output){
    agents.at(0)->performAction(static_cast<Gridworld_Agent::Actionoptions>(output));
}

vector<int> Gridworld_IH::inputTabularQ(){
    vector<int> input;
    //Input generation goes here
    return input;
}

int Gridworld_IH::rewardGoalTouch(){
    int reward = 0;

    vector<Gridworld_Event*> events = world->getEventLog();

    for(Gridworld_Event* event: events){
        Event_actor team;
        if(event->team == this->team){
            if(event->player == player){
                team = SAME_PLAYER;
                world->removeFromEventLog(event);
            } else {
                team = SAME_TEAM;
            }
        } else {
            if(event->player == player){
                team = PLAYER_TO_OPPONENT;
                world->removeFromEventLog(event);
            } else {
                team = OPPOSITE_TEAM;
            }
        }
        reward += rewards[team][event->event_type];
    }
    return reward;
}

void Gridworld_IH::initRewardGeneration(){
    switch(rewardType){
        case GOAL_TOUCH:
            rewards = new int*[4];
            for (int i = 0; i < 4; ++i) {
              rewards[i] = new int [3];
            }

            rewards[SAME_PLAYER][Gridworld_Event::GOAL] = 100;
            rewards[SAME_PLAYER][Gridworld_Event::TOUCH] = 1;
            rewards[SAME_PLAYER][Gridworld_Event::PASS] = 5;

            rewards[SAME_TEAM][Gridworld_Event::GOAL] = 100;
            rewards[SAME_TEAM][Gridworld_Event::TOUCH] = 1;
            rewards[SAME_TEAM][Gridworld_Event::PASS] = 5;

            rewards[PLAYER_TO_OPPONENT][Gridworld_Event::GOAL] = -100;
            rewards[PLAYER_TO_OPPONENT][Gridworld_Event::TOUCH] = 0;
            rewards[PLAYER_TO_OPPONENT][Gridworld_Event::PASS] = 0;

            rewards[OPPOSITE_TEAM][Gridworld_Event::GOAL] = -100;
            rewards[OPPOSITE_TEAM][Gridworld_Event::TOUCH] = -1;
            rewards[OPPOSITE_TEAM][Gridworld_Event::PASS] = -5;
        break;
    }
}

int Gridworld_IH::getTeam(){
    return team;
}

Player *Gridworld_IH::getPlayer(){
   return player;
}

void Gridworld_IH::addAgent(Gridworld_Agent *agent){
    //qDebug() << "Added an agent";
    agents.push_back(agent);
}

void Gridworld_IH::setWorld(Gridworld *world){
    this->world = world;
}

int Gridworld_IH::getNumberOfAgents(){
    return requiredNumberOfAgents;
}

