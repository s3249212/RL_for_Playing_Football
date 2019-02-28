//
// Created by 김유진 on 2019-02-21.
//

#ifndef BACHELORPROJECT_WORLD_H
#define BACHELORPROJECT_WORLD_H

#include "player.h"

class World{
    private:
        Player *players;

    public:
        virtual void simulate();
};


#endif //BACHELORPROJECT_WORLD_H
