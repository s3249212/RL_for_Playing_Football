#include "gridworld_ih.h"
#include <iostream>

double Gridworld_IH::generateReward(bool terminal){
    switch(rewardType){
        case GOAL_TOUCH:
            return rewardGoalTouch(terminal);
    }
    return 0;
}

int Gridworld_IH::rewardGoalTouch(bool terminal){
    int reward = 0;

    vector<Gridworld_Event*> events = world->getEventLog();

    for(Gridworld_Event* event: events){
        Event_actor team;

        if(event->team == this->team){
            if(event->player == player){
                team = SAME_PLAYER;
            } else {
                team = SAME_TEAM;
            }
        } else {
            if(event->player == player){
                team = PLAYER_TO_OPPONENT;
            } else {
                team = OPPOSITE_TEAM;
            }
        }

        reward += rewards[team][event->event_type];

        if(!terminal && event->player == player){
            world->removeFromEventLog(event);
        }
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

            rewards[SAME_PLAYER][Gridworld_Event::GOAL] = 1;
            rewards[SAME_PLAYER][Gridworld_Event::TOUCH] = 0;
            rewards[SAME_PLAYER][Gridworld_Event::PASS] = 0;

            rewards[SAME_TEAM][Gridworld_Event::GOAL] = 1;
            rewards[SAME_TEAM][Gridworld_Event::TOUCH] = 0;
            rewards[SAME_TEAM][Gridworld_Event::PASS] = 0;

            rewards[PLAYER_TO_OPPONENT][Gridworld_Event::GOAL] = -1;
            rewards[PLAYER_TO_OPPONENT][Gridworld_Event::TOUCH] = 0;
            rewards[PLAYER_TO_OPPONENT][Gridworld_Event::PASS] = 0;

            rewards[OPPOSITE_TEAM][Gridworld_Event::GOAL] = -1;
            rewards[OPPOSITE_TEAM][Gridworld_Event::TOUCH] = 0;
            rewards[OPPOSITE_TEAM][Gridworld_Event::PASS] = 0;
        break;
    }
}
