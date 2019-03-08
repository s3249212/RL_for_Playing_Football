//
// Created by 김유진 on 2019-03-01.
//

#ifndef BACHELORPROJECT_TEAM_H
#define BACHELORPROJECT_TEAM_H

#include <string>
#include "player.h"

class Team{
    private:
        vector<Player> players;
        string name;

    public:
        Team(string name): name(name) {};

        void addPlayer(Player p);
        vector<Player> getPlayers();
        string getName();
};
#endif //BACHELORPROJECT_TEAM_H
