#include "ih_oneagentperplayer.h"
#include "gridworld_event.h"

IH_OneAgentPerPlayer::IH_OneAgentPerPlayer(Player* player, int team):
    player(player),
    team(team)
{
    //this->player = player;
}

void IH_OneAgentPerPlayer::setWorld(Gridworld* world){
    this->world = world;
}

int IH_OneAgentPerPlayer::getReward(){
    /*Get event log of the world
     * Go through events and increase / decrease the reward based on the events and the players team.
     * Remove the first part of the log, the part that happened before the previous action of the next player.
     * Actions of this player will be recorded later in the updateworld function.
     */
    /*int reward;
    vector<Gridworld_Event*> events = world->getEventLog();*/

    return 0;
}

void IH_OneAgentPerPlayer::update(){
    vector<int> input;
    int reward;
    vector<int> action;

    action = player->act(input, reward);

    updateWorld(action);
}

void IH_OneAgentPerPlayer::updateWorld(vector<int> action){
    if(action[0] == 1){
        agent->performAction(Gridworld_Agent::MOVELEFT);
    }
    if(action[1] == 1){

    }
}

void IH_OneAgentPerPlayer::addAgent(Gridworld_Agent *agent){
    this->agent = agent;
}

int IH_OneAgentPerPlayer::getNumberOfAgents(){
    return numberOfAgents;
}
