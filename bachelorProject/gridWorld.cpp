
//
// Created by 김유진 on 2019-03-01.
//
#include "gridWorld.h"
#include <iostream>



GridWorld::GridWorld(){

}

PlayerInfo GetPos(PlayerInfo p){
    return p;
}


void SetPos(PlayerInfo p, int x, int y){
    p.x = x;
    p.y = y;
}

void SetTeam(PlayerInfo p, int t){
    p.team = t;
}

void GridWorld::generateReward(Player p, PlayerInfo info, int playerIndex){

}

vector<double> GridWorld::generateInputVector(Player p, int playerIndex){

}


ostream & operator << (ostream &out, const World & w){
    return out;
}

istream & operator >> (istream & in, World & w){
    return  in;
}

