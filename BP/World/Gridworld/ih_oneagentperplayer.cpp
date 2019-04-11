#include <QDebug>

#include "ih_oneagentperplayer.h"
#include "gridworld_event.h"

#define numberOfEvents 3

IH_OneAgentPerPlayer::IH_OneAgentPerPlayer(Player* player, int team):
    player(player),
    team(team)
{
    //this->player = player
    rewards = new int*[4];
    for (int i = 0; i < 4; ++i) {
      rewards[i] = new int [numberOfEvents];
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
    int reward=0;
    vector<Gridworld_Event*> events = world->getEventLog();

    for(Gridworld_Event* event: events){
        Team team;
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
        /*if(event->player == player){
            team = SAME_PLAYER;
            world->removeFromEventLog(event);
        } else if(event->team == this->team){
            team = SAME_TEAM;
        } else {
            team = OPPOSITE_TEAM;
        }*/
        qDebug() << "Event" << this->team << event->team << team << event->event_type << rewards[team][event->event_type];
        reward += rewards[team][event->event_type];
    }
    if(reward != 0){
        qDebug() << team << "Reward: " << reward;
    }
    return reward;
}

void IH_OneAgentPerPlayer::update(){
    vector<int> input;
    int reward = getReward();
    int action;

    action = player->act(input, reward);

    updateWorld(action);
}

void IH_OneAgentPerPlayer::updateWorld(int action){
    //qDebug() << action;
    agent->performAction(static_cast<Gridworld_Agent::Actionoptions>(action));
    /*if(action[0] == 1){
        agent->performAction(Gridworld_Agent::MOVELEFT);
    }
    if(action[1] == 1){
        agent->performAction(Gridworld_Agent::MOVERIGHT);
    }
    if(action[2] == 1){
        agent->performAction(Gridworld_Agent::MOVEUPRIGHT);
    }
    if(action[3] == 1){
        agent->performAction(Gridworld_Agent::MOVEUPLEFT);
    }
    if(action[4] == 1){
        agent->performAction(Gridworld_Agent::MOVEDOWNRIGHT);
    }
    if(action[5] == 1){
        agent->performAction(Gridworld_Agent::MOVEDOWNLEFT);
    }
    if(action[6] == 1){
        agent->performAction(Gridworld_Agent::MOVEUP);
    }
    if(action[7] == 1){
        agent->performAction(Gridworld_Agent::MOVEDOWN);
    }
    if(action[8] == 1){
        agent->performAction(Gridworld_Agent::SHOOT);
    }*/

}

void IH_OneAgentPerPlayer::addAgent(Gridworld_Agent *agent){
    this->agent = agent;
}

int IH_OneAgentPerPlayer::getNumberOfAgents(){
    return numberOfAgents;
}

int IH_OneAgentPerPlayer::getTeam(){
    return team;
}
