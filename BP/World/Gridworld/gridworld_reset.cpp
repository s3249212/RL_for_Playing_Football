#include <array>
#include <vector>

#include "gridworld.h"

void Gridworld::resetAfterMatch(){
    if(varyFieldSizes){
        changeFieldSize();
    }
    if(varyTeamSizes){
        changeTeamSizes();
    }
    resetLocations();
    score->reset();
    resetEventLog();
}

void Gridworld::changeFieldSize(){
    width = 2 * (rand() % ((maxWidth - minWidth) / 2)) + minWidth;
    height = 2 * (rand() % ((maxHeight - minHeight) / 2)) + minHeight;
    goallength = rand() % ((height - 2) / 2 ) + 1;
}

void Gridworld::changeTeamSizes(){
    for(Gridworld_IH* ih: ihs){
        for(Gridworld_Agent* a: ih->getAgents()){
            delete a;
        }
        ih->clearAgents();
    }
    ihs.clear();
    agents.clear();

    if(hasToPlayEqually){
        int maxTeamSize = leftType.size() < rightType.size()? leftType.size(): rightType.size();
        int newTeamSize = rand() % (maxTeamSize - minTeamSize) + minTeamSize;
        for(int i = 0; i < newTeamSize; i++){
            addIH(leftType[i]);
            addIH(rightType[i]);
        }
    } else {
        int newLeftTeamSize = rand() % (leftType.size() - minTeamSize) + minTeamSize;
        int newRightTeamSize = rand() % (rightType.size() - minTeamSize) + minTeamSize;

        for(int i = 0; i < newLeftTeamSize; i++){
            addIH(leftType[i]);
        }

        for(int i = 0; i < newRightTeamSize; i++){
            addIH(rightType[i]);
        }
    }
}

void Gridworld::resetLocations(){
    if(randomInitialization){
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
    } else {
        int nred = 0, nblue = 0;
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

        ball->setCoord({width / 2, height / 2});
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
