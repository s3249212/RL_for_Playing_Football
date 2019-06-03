#ifndef WORLD_H
#define WORLD_H

#include <iostream>
#include <fstream>

class World
{
public:
    enum Mode{
        TEST = 0, TRAINING
    };
    virtual void runTraining(){};
    //void setPaused(int boolean);

    /*save load delete restart start (= run)*/

protected:
    std::ofstream savefile;

    int nBlocks = 50;

    int nTrainingPerBlock = 0;
    int nTestPerBlock = 100;

    virtual void runMatch(Mode mode){};

    virtual void saveStatistics(){};
};

#endif // WORLD_H
