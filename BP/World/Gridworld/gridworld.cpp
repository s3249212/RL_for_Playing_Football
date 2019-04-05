
#include <vector>
#include "gridworld.h"
#include "gridworld_agent.h"
#include "../../View/Gridworld/gridworldview.h"

using namespace std;

Gridworld::Gridworld(){
    view = new GridworldView(this);
    ball = new Gridworld_Ball(this, {width / 2, height/2});
    view = new GridworldView(this);
    score = new Gridworld_Score();
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

void Gridworld::run(){
    for(int i = 0; i < 1000; i++){
        for(Gridworld_IH* ih: ihs){
            ih->update();
        }
        view->update();
    }
}

array<int, 2> Gridworld::getBallCoord(){
    return ball->getCoord();
}

Gridworld_Ball* Gridworld::getBall(){
    return ball;
}

vector<array<int,2>> Gridworld::getBlueTeam(){
    vector <array <int, 2>>* blue = new vector<array <int, 2>>;
    for(Gridworld_Agent* b: agents){
        if(b->getTeam() == 0){
            blue->push_back(b->getCoord());
        }
    }
    return *blue;
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
    return goallength;
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
        int x = ih->getTeam() == 0? getBlueTeam().size() + 1: width - 2 - getRedTeam().size();
        Gridworld_Agent * agent = new Gridworld_Agent(this, ih->getTeam(), {x, 1});
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

bool Gridworld::isWithinBounds(array<int, 2> coord){
    bool b = true;

    b = b && coord[0] > 0;
    b = b && coord[0] < width - 1;
    b = b && coord[1] > 0;
    b = b && coord[1] < height -1;

    b = b && coord != ball->getCoord();

    for(Gridworld_Agent* a: agents){
        b = b && coord != a->getCoord();
    }

    return b;
}

bool Gridworld::isInGoal(array<int, 2> coord)
{
    int min = height / 2 - goallength;
    int max = height / 2 + goallength;

    return (coord[0] == 0 || coord[0] == width - 1) &&
            coord[1] >= min && coord[1] <= max;
}

void Gridworld::updateAfterGoal(array<int, 2> coord)
{
    int team;
    if(coord[0] == 0){
        team = 1;
    } else {
        team = 0;
    }


}

array<int, 2> Gridworld::getScore()
{
    return score->getScore();
}
