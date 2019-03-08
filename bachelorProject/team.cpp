//
// Created by 김유진 on 2019-03-01.
//

#include "team.h"


void Team::addPlayer(Player p) {
    players.push_back(p);
}

vector<Player> Team::getPlayers() {
    return players;
}

string Team::getName() {
    return name;
}