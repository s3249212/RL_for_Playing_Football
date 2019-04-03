#include "gridworld.h"
#include "gridworld_agent.h"
#include <vector>
#include "../../View/Gridworld/gridworldview.h"

using namespace std;

Gridworld::Gridworld(){
    view = new GridworldView(this);
    ball = new Gridworld_Ball(this);
    view = new GridworldView(this);
}

/*Gridworld::run(){
    for(int i = 0; i < 100; i++){
        for(int j = 0; j < players.size(); j++){
            array<int, 3> actions = players.at(j)->act({1, 2, 3}, {1});
            updateState(j, actions);
        }
    }
}

Gridworld::updateState(int currentPlayer, array<int, 3> actions){
    Player* player = players.at(currentPlayer);
    Agent* agent = player->getAgent();

}*/

array<int, 2> Gridworld::getBall(){
    array<int, 2> ball = {1,2};
    return ball;
}

vector<array<int,2>> Gridworld::getBlueTeam(){
    vector <array <int, 2>> blue;
    for(auto b: agents){
        if(b->getTeam() == 0){
            blue.push_back(b->getCoord());
        }
    }
    return blue;
}

vector<array<int,2>> Gridworld::getRedTeam(){
    vector <array <int, 2>> red;
    for(auto r: agents){
        if(r->getTeam() == 1){
            red.push_back(r->getCoord());
        }
    }
    return red;
}

int Gridworld::getGoalLength(){
    return 1;
}

int Gridworld::getWidth(){
    return width;
}

int Gridworld::getHeight(){
    return height;
}

void Gridworld::addIH(Gridworld_IH *ih){
    ihs.push_back(ih);
    int nAgents = ih->getNumberOfAgents();
    for(int i=0; i<nAgents; i++){
        Gridworld_Agent * agent = new Gridworld_Agent(this);
        addAgent(agent);
        ih->addAgent(agent);
    }
}

void Gridworld::addAgent(Gridworld_Agent *agent){
    agents.push_back(agent);
}

vector<Gridworld_Event*> Gridworld::getEventLog(){
    return eventLog;
}
