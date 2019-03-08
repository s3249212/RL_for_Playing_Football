//
// Created by 김유진 on 2019-03-07.
//

#ifndef BACHELORPROJECT_GRIDWORLD_H
#define BACHELORPROJECT_GRIDWORLD_H

#include <vector>
#include "player.h"
#include "world.h"

typedef struct PlayerInfo{
    int x;
    int y;
    int team;
}PlayerInfo;

class GridWorld : public World {
    private:
        vector<Player> players;

    public:
        virtual void generateReward(Player p, int playerIndex);
        virtual vector<double> generateInputVector(Player p, int playerIndex);
};


#endif //BACHELORPROJECT_GRIDWORLD_H
