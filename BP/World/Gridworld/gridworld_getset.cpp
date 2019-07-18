#include <array>
#include <string>
#include <vector>

#include "gridworld.h"

array<int, 2> Gridworld::getBallCoord(){
    return ball->getCoord();
}

Gridworld_Ball* Gridworld::getBall(){
    return ball;
}

vector<array<int,2>> Gridworld::getTeam(int x){
    vector <array <int, 2>> team;
    for(Gridworld_Agent* a: agents){
        if(a->getTeam() == x){
            team.push_back(a->getCoord());
        }
    }
    return team;
}

vector<array<int,2>> Gridworld::getBlueTeam(){
    return getTeam(0);
}

vector<array<int,2>> Gridworld::getRedTeam(){
    return getTeam(1);
}

int Gridworld::getGoalLength(){
    return goallength;
}

int Gridworld::getWidth(){
    return width;
}

int Gridworld::getHeight(){
    return height;
}

void Gridworld::setWidth(int width){
  this->width = width;
}

void Gridworld::setHeight(int height){
  this->height = height;
}

void Gridworld::setNPlayers(int nPlayers){
	for(Gridworld_IH* ih: ihs){
        for(Gridworld_Agent* a: ih->getAgents()){
            delete a;
        }
        ih->clearAgents();
    }
    ihs.clear();
    agents.clear();

	for(int i = 0; i < newTeamSize; i++){
		addIH(leftType[i]);
		addIH(rightType[i]);
	}
}

void setVariation(bool varyFieldSizes, bool varyTeamSizes, bool hasToPlayEqually = true){
  this->varyFieldSizes = varyFieldSizes;
  this->varyTeamSizes = varyTeamSizes;
  this->hasToPlayEqually = hasToPlayEqually;
}

void setSaveFile(string name){
	
}

array<int, 2> Gridworld::getScore()
{
    return score->getScore();
}

vector<Gridworld_Event*> Gridworld::getEventLog(){
    return eventLog;
}

vector<Gridworld_IH *> Gridworld::getihs()
{
    return ihs;
}

array<bool, 6> Gridworld::getPixelData(array<int, 2> coord, int team){
    array<bool, 6> result;

    //Ball
    result[0] = (ball->getCoord() == coord);

    //your team
    result[1] = false;
    for(Gridworld_Agent* agent: agents){
        if(agent->getTeam() == team){
            result[1] = true;
            break;
        }
    }

    //opponent team
    result[2] = false;
    for(Gridworld_Agent* agent: agents){
        if(agent->getTeam() != team){
            result[2] = true;
            break;
        }
    }

    //wall
    result[3] = (coord[0] <= 0 || coord[0] >= width - 1 || coord[1] <= 0 || coord[1] >= height - 1);

    int minGoalY = height / 2 - goallength + height % 2;
    int maxGoalY = minGoalY + 2 * goallength - height % 2;
    //own goal
    int goalX = team * (width - 1);
    result[4] = (goalX == coord[0] && minGoalY <= coord[1] && maxGoalY >= coord[1]);

    //other goal
    goalX = (1 - team) * (width - 1);
    result[5] = (goalX == coord[0] && minGoalY <= coord[1] && maxGoalY >= coord[1]);

    return result;
}

vector<Gridworld_Agent *> Gridworld::getAgents()
{
    return agents;
}
