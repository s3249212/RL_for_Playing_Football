#include "gridworld.h"
#include "gridworld_agent.h"
#include <vector>
#include "../../View/Gridworld/gridworldview.h"

using namespace std;

Gridworld::Gridworld(){
    view = new GridworldView(this);
    for(int i = 0; i < 10; i++){
        redTeam.push_back(new Gridworld_Agent(this, {i + 1, 1}));
        blueTeam.push_back(new Gridworld_Agent(this, {width - i - 2, 1}));
    }
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
    for(auto b: blueTeam){
        blue.push_back(b->getCoord());
    }
    return blue;
}

vector<array<int,2>> Gridworld::getRedTeam(){
    vector <array <int, 2>> red;
    for(auto r: redTeam){
        red.push_back(r->getCoord());
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

