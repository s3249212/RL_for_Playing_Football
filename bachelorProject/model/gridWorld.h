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
    double reward;
    int team;
}PlayerInfo;

typedef struct Ball{
    int x;
    int y;
    int owner;
}Ball;

class GridWorld : public World {
    private:
        vector<Player> players;

    public:
        virtual void generateReward(Player p, PlayerInfo info, int playerIndex);
        virtual vector<double> generateInputVector(Player p, int playerIndex);
        PlayerInfo GetPos(PlayerInfo p);

        void SetPos(PlayerInfo p, int x, int y);

        void SetTeam(PlayerInfo p, int t);
};


#endif //BACHELORPROJECT_GRIDWORLD_H
