//
// Created by 김유진 on 2019-02-28.
//
#include <iostream>
#include "world.h"
#include "observer.h"
#include "../model/gridWorld.h"

#ifndef BACHELORPROJECT_VIEW_H
#define BACHELORPROJECT_VIEW_H

class ViewGridWorld : public Observer {
public:
    ViewGridWorld(GridWorld* gridw);
    
    void setModel(GridWorld* gridw);
    void render();

private:
    GridWorld* gridWorld;
};

#endif //BACHELORPROJECT_VIEW_H
