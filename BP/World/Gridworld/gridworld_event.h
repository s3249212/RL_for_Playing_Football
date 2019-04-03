#ifndef GRIDWORLD_EVENT_H
#define GRIDWORLD_EVENT_H

#include "Player/player.h"


class Gridworld_Event
{    
public:
    enum Event_type{
        GOAL = 0, TOUCH, PASS
    };

    Player* player;
    Event_type event_type;
    int team;

    Gridworld_Event();
};

#endif // GRIDWORLD_EVENT_H
