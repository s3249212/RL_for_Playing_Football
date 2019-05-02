#ifndef WORLD_H
#define WORLD_H

#include "../View/view.h"

#include <iostream>
#include <fstream>

class World
{
public:
    enum Mode{
        TEST = 0, TRAINING
    };

    View* getView();

    virtual void runTraining(){};
    //void setPaused(int boolean);

    /*save load delete restart start (= run)*/

protected:
    View* view;

    std::ofstream savefile;

    int nBlocks = 20;

    int nTrainingPerBlock = 0;
    int nTestPerBlock = 100;

    virtual void runMatch(Mode mode){};

    virtual void saveStatistics(){};
};

#endif // WORLD_H
