#include <vector>
#include <algorithm>

#include "gridworld.h"
#include "gridworld_event.h"

void Gridworld::addEvent(Gridworld_Event::Event_type event_type, int team)
{
    Gridworld_Event* event = new Gridworld_Event();
    event->event_type = event_type;
    event->team = team;
    event->player = ih->getPlayer();
    eventLog.push_back(event);
}



void Gridworld::resetEventLog(){
    for(Gridworld_Event* e: eventLog){
        delete e;
    }
    eventLog.clear();
}

void Gridworld::removeFromEventLog(Gridworld_Event *event)
{
     std::vector<Gridworld_Event *>::iterator i = std::find(eventLog.begin(), eventLog.end(), event);
     eventLog.erase(i);
     delete event;
}
