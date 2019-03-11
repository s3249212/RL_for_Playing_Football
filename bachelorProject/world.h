//
// Created by 김유진 on 2019-02-21.
//

#ifndef BACHELORPROJECT_WORLD_H
#define BACHELORPROJECT_WORLD_H

#include "player.h"
#include "observable.h"
#include <vector>
#include <iostream>

typedef struct Ball{
    int x;
    int y;
    int owner;
}Ball;

class World: public Observable {
    private:
        vector<Player> players;
        //Ball ball;
        int nTrainingPerCycle;
        int nTestPerCycle;
        int nCycles;

    public:
        void train();
        World(int nplayers, int algorithm);
        virtual void runTrainingMatch();
        virtual void runTestMatch();
        void addPlayer(Player p);
        vector<Player> getPlayers();
        void update(World w);

    friend ostream & operator << (ostream &out, const World &w);
    friend istream & operator >> (istream &in, World &w);

};


#endif //BACHELORPROJECT_WORLD_H
