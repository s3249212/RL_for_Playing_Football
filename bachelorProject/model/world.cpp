//
// Created by 김유진 on 2019-03-01.
//
#include "world.h"
#include <iostream>
#include "observable.h"

using namespace std;


World::World(int nplayers, int algorithm){

}

void World::addPlayer(Player p) {
    players.push_back(p);
}

void World::update(World w) {
    notifyObservers();
}

vector<Player> World::getPlayers() {
    return players;
}

ostream & operator << (ostream &out, const World & w){
}

void World::train(){
    for(int i = 0; i < nCycles; i++){
        for(int j = 0; j < nTrainingPerCycle; j++){
            runTrainingMatch();
        }
        for(int j = 0; j < nTestPerCycle; j++){
            runTestMatch();
        }
    }
}