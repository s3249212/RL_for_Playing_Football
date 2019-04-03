#include "ih_oneagentperplayer.h"
#include "gridworld_event.h"

IH_OneAgentPerPlayer::IH_OneAgentPerPlayer(Gridworld* world, Player* player, Gridworld_Agent* agent):
    world(world),
    agent(agent)
{
    this->player = player;
}

int IH_OneAgentPerPlayer::getReward(){
    /*Get event log of the world
     * Go through events and increase / decrease the reward based on the events and the players team.
     * Remove the first part of the log, the part that happened before the previous action of the next player.
     * Actions of this player will be recorded later in the updateworld function.
     */
    int reward;
    vector<Gridworld_Event::Event_type> events = world->getEventLog();


}

void IH_OneAgentPerPlayer::movement(){
    vector<int> input;
    vector<int> reward;
    vector<int> action;

    action = player->act(input, reward);

    updateWorld(action);
}

void IH_OneAgentPerPlayer::updateWorld(vector<int> action){

}
