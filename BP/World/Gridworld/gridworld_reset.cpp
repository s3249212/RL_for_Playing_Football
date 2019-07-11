#include <array>
#include <vector>

#include "gridworld.h"

void Gridworld::resetAfterMatch(){
    resetLocations();
    score->reset();
    resetEventLog();
}

void Gridworld::resetLocations(){
    /*int nred = 0, nblue = 0;
    for(Gridworld_Agent* agent: agents){
        int x;
        if(agent->getTeam() == 0){
            x = nblue + 1;
            nblue++;
        } else {
            x = width - 2 - nred;
            nred++;
        }
        agent->setCoord({x, 1});
    }

    ball->setCoord({width / 2, height / 2});*/

    ball->setCoord({width / 2, height / 2});
    for(int i = 0; i < agents.size(); i++){
        int x;
        int y;
        bool isFree;
        do{
            x = rand() % (width - 2) + 1;
            y = rand() % (height - 2) + 1;

            isFree = (x != ball->getX() && y != ball->getY());
            int j = 0;
            while(j < i && isFree){
                isFree = (x != agents[0]->getX() && y != agents[0]->getY());
                j++;
            }
        } while(!isFree);
        agents[i]->setCoord({x, y});
    }
}

void Gridworld::updateAfterGoal(array<int, 2> coord)
{
    int team;
    if(coord[0] == 0){
        team = 1;
    } else {
        team = 0;
    }

    score->increaseScore(team);

    addEvent(Gridworld_Event::GOAL, team);

    for(Gridworld_IH* ih: ihs){
        ih->updateEndEpisode();
        ih->resetAfterEpisode();
    }

    resetEventLog();

    resetLocations();
}
